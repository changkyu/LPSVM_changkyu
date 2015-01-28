/*
 * lpsvm_simplexsolver.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: changkyu
 */

#include <exception>

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
VectorXd LPSVM_SimplexSolver::Solve(MatrixXd& A_in, VectorXd& b,  TYPE_CONSTRAINT type_constraint, VectorXd& c_in )
{
	VectorXd sol;
	int m = A_in.rows();
	int n = A_in.cols();

	int rows_A=0, cols_A=0;
	switch( type_constraint )
	{
		case CONSTRAINT_GE:
			break;
		case CONSTRAINT_EQ:
				rows_A = m;
				cols_A = n;
			break;
		case CONSTRAINT_LE:
				rows_A = m;
				cols_A = n+m;
			break;
	}

	MatrixXd A(rows_A, cols_A);
	VectorXd c(cols_A);
	switch( type_constraint )
	{
		case CONSTRAINT_GE:
			break;
		case CONSTRAINT_EQ:
			A = A_in;
			c = c_in;
			break;
		case CONSTRAINT_LE:
			A.block(0,0,m,n) = A_in;
			A.block(0,n,rows_A,rows_A) = MatrixXd::Identity(rows_A,rows_A);
			c.head(n) = c_in;
			c.tail(cols_A-n) = VectorXd::Zero(cols_A-n);
			break;
	}


	LOG("A: " << std::endl << A << std::endl);
	LOG("b: " << std::endl << b << std::endl);
	LOG("c': " << std::endl << c.transpose());
	LOG(std::endl);

	int len_J = cols_A-rows_A;
	VectorXi J(len_J); // J: index of non basic variables

	MatrixXd B(rows_A,rows_A);
	RowVectorXd cBT(rows_A);
	// Step 0. Initialize B, c_B and J
	// 1-1 J: index of non basic variables
	int idx_J=0;
	for( int col=0; col<cols_A; col++ )
	{
		if( col >= len_J ) // Initially, set B as the last block of A
		{
			B.block(0,0,rows_A,rows_A) = A.block(0,col,rows_A,rows_A);
			cBT = c.tail(rows_A);
			break;
		}
		else
		{
			J(idx_J) = col;
			idx_J++;
		}
	}
	LOG("B: " << std::endl << B << std::endl);
	LOG("cBT: " << std::endl << cBT << std::endl);
	LOG("J': " << J.transpose());
	LOG(std::endl);

	while(true)
	{
		// Step 1
		// 1.1 wT = c_B^T B^-1 (wT B = c_B^T)
		MatrixXd BBT( B*B.transpose() ); // wT BB^T = c_B^T B^T
		LOG("BBT: " << std::endl << BBT << std::endl);
		MatrixXd L( BBT.llt().matrixL() ); // wT LL^T = c_B^T B^T
		LOG("L: " << std::endl << L << std::endl);
		MatrixXd L_inv = L.inverse();
		LOG("L_inv: " << std::endl << L_inv << std::endl);
		MatrixXd wT( cBT * B.transpose() * L_inv.transpose() * L_inv ); // wT = c_B^T B^T L^-T L^-1
		LOG("wT:" << std::endl << wT << std::endl);

		VectorXd z_c(len_J);
		for( int j=0; j<len_J; j++ )
		{
			z_c.segment(j,1) = wT * A.block(0,J(j),rows_A,1) - c(J(j));
		}

	}

	return sol;
}
