/*
 * lpsvm_simplexsolver.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: changkyu
 */

#include <exception>
#include <map>

#include "lpsvm_simplexsolver.h"
#include "lpsvm_log.h"

using namespace Eigen;

/**
 *
 * assume that
 *  A(m x n) matrix (m < n)
 *  x(n x 1) vector
 *  b(m x 1) vector
 *
 *  c(n x 1) vector
 */
LPSVM_SimplexSolver::Solution* LPSVM_SimplexSolver::Solve(MatrixXd& A_in, VectorXd& b, VectorXd& c_in, LPSVM_SimplexSolver::Problem_Description problem_desc )
{
	int m = A_in.rows();
	int n = A_in.cols();

	// TESt

	FullPivLU<MatrixXd> A_lu(A_in);

	LOG("A_LU: " << std::endl << A_lu.matrixLU() << std::endl );

	int rows_A=0, cols_A=0;
	switch( problem_desc.constraint )
	{
		case CONSTRAINT_EQ:
		{
			rows_A = m;
			cols_A = n;
		}
		break;

		case CONSTRAINT_LE:
		case CONSTRAINT_GE:
		{
			rows_A = m;
			cols_A = n+m;
		}
		break;
	}

	MatrixXd A(rows_A, cols_A);
	VectorXd c(cols_A);
	switch( problem_desc.constraint )
	{
		case CONSTRAINT_EQ:
		{
			A = A_in;
			c = c_in;
		}
		break;

		case CONSTRAINT_LE:
		case CONSTRAINT_GE:
		{
			A.block(0,0,m,n) = A_in;
			if( problem_desc.constraint == CONSTRAINT_GE )
			{
				LOG("Ax >= b -> [A -I]x = b" << std::endl);
				A.block(0,n,rows_A,rows_A) = -MatrixXd::Identity(rows_A,rows_A);
			}
			else
			{
				LOG("Ax <= b -> [A I]x = b" << std::endl);
				A.block(0,n,rows_A,rows_A) = MatrixXd::Identity(rows_A,rows_A);
			}
			c.head(n) = c_in;
			c.tail(cols_A-n) = VectorXd::Zero(cols_A-n);
		}
		break;
	}

	if( problem_desc.problem == MAX_PROBLEM )
	{
		LOG("Converted to MIN problem" << std::endl);
		c = -c;
	}

	for( int row=0; row<rows_A; row++ )
	{
		if( b(row) < 0 )
		{
			A.block(row,0,1,cols_A) = -A.block(row,0,1,cols_A);
		}
	}

	LOG("A: " << std::endl << A << std::endl);
	LOG("b: " << std::endl << b << std::endl);
	LOG("c': " << c.transpose());
	LOG(std::endl);

	VectorXi idxes_B(rows_A);
	std::map<int, int> map_idxes_B;

	int len_J = cols_A-rows_A;
	VectorXi idxes_J(len_J); // J: index of non basic variables
	std::map<int, int> map_idxes_J;

	MatrixXd B(rows_A,rows_A);
	RowVectorXd cBT(rows_A);
	// Step 0. Initialize B, c_B and J
	// 1-1 J: index of non basic variables
	int i=0;
	int j=0;
	for( int col=0; col<cols_A; col++ )
	{
		if( col >= len_J ) // Initially, set B as the last block of A
		{
			B.block(0,i,rows_A,1) = A.block(0,col,rows_A,1);
			cBT(i) = c(col);

			idxes_B(i) = col;
			map_idxes_B.insert( std::pair<int, int>(col, i) );
			i++;
		}
		else
		{
			idxes_J(j) = col;
			map_idxes_J.insert( std::pair<int, int>(col, j) );
			j++;
		}
	}

	VectorXd x_B(rows_A);
	while(true)
	{
		// Step 1
		LOG("Step 1 .........." << std::endl);
		LOG("idxes_B': " << idxes_B.transpose() << std::endl);
		LOG("idxes_J': " << idxes_J.transpose() << std::endl);
		LOG("B: " << std::endl << B << std::endl);
		LOG("cBT: " << cBT << std::endl);

		// 1.1 wT = c_B^T B^-1 (wT B = c_B^T)
		MatrixXd BBT( B*B.transpose() ); // wT BB^T = c_B^T B^T
		MatrixXd L( BBT.llt().matrixL() ); // wT LL^T = c_B^T B^T
		MatrixXd L_inv = L.inverse();
		MatrixXd B_inv( B.transpose() * L_inv.transpose() * L_inv );
		MatrixXd wT( cBT * B_inv ); // wT = c_B^T B^T L^-T L^-1
		LOG("check BB_inv" << std::endl << B*B_inv << std::endl );
		LOG("wT:" << wT << std::endl);

		x_B = B_inv * b;

		VectorXd z_c(len_J);
		for( j=0; j<len_J; j++ )
		{
			double c_j = c(idxes_J(j));
			MatrixXd z_j( wT * A.block(0,idxes_J(j),rows_A,1) );
			z_c(j) = z_j(0,0) - c_j;
		}
		LOG("z - c: " << z_c.transpose() << std::endl);

		VectorXd::Index k = -1;
		z_c.maxCoeff(&k);
		LOG("k: " << k << std::endl);
		if( z_c(k) < 0 )
		{
			LOG("Stop: z_c < 0" << std::endl;)
			break;
		}

		// Step 2
		LOG("Step 2 .........." << std::endl);
		int idx_k = idxes_J(k);
		LOG("idx_k: " << idx_k << std::endl);
		LOG("b_bar:" << std::endl << x_B << std::endl);

		VectorXd y_k = B_inv * A.block(0,idx_k,rows_A,1);
		LOG("y_k:" << y_k.transpose() << std::endl);

		bool b_stop = true;
		for( int r=0; r<rows_A; r++ )
		{
			if( y_k(r) > 0 )
			{
				b_stop = false;
				break;
			}
		}
		if( b_stop )
		{
			LOG("Stop: y_k <= 0" << std::endl;)
			break;
		}

		VectorXd x_k = x_B.cwiseQuotient( y_k );
		LOG("x_k: " << x_k.transpose() << std::endl);
		VectorXd::Index r = -1;
		x_k.minCoeff(&r);
		LOG("r: " << r << std::endl);

		// Step 3
		LOG("Step 3 .........." << std::endl);
		int idx_r = idxes_B(r);
		j = map_idxes_J[idx_k];
		idxes_J(j) = idx_r;
		map_idxes_J.erase(idx_k);
		map_idxes_J.insert( std::pair<int,int>(idx_r,j) );

		i = map_idxes_B[idx_r];
		idxes_B(i) = idx_k;
		map_idxes_B.erase(idx_r);
		map_idxes_B.insert( std::pair<int,int>(idx_k,i) );

		B.block(0,i,rows_A,1) = A.block(0,idxes_B(i),rows_A,1);
		cBT(i) = c(idxes_B(i));

		LOG("Leaving: " << idxes_J(j) << ", Entering: " << idxes_B(i) << std::endl);

		LOG("--------------------------------" << std::endl);
	}

	Solution* sol = new Solution;
	sol->x = VectorXd::Zero(n);
	for( i=0; i<rows_A; i++ )
	{
		if( idxes_B(i) < n )
		{
			sol->x(idxes_B(i)) = x_B(i);
		}
	}

	sol->objective_value = c_in.dot(sol->x);

	return sol;
}

LPSVM_SimplexSolver::Solution* LPSVM_SimplexSolver::Solve_Primal(Eigen::MatrixXd &A_in, Eigen::VectorXd &b, Eigen::VectorXd &c_in)
{

}
