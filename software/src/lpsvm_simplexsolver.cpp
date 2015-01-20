/*
 * lpsvm_simplexsolver.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: changkyu
 */

#include "lpsvm_simplexsolver.h"
#include <exception>

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
VectorXd LPSVM_SimplexSolver::Solve(MatrixXd& A, VectorXd& b, VectorXd& c )
{
	VectorXd sol;
	int m = A.rows();
	int n = A.cols();

	if( !(m<n) ) throw new std::exception("It must be \"m < n\" where A(m x n)");

	int len_J = n-m;
	VectorXd J = VectorXi(len_J); // J: index of non basic variables
	for( int j=0; j<len_J; j++ )
	{
		J(j) = j;
	}
	std::cout << A(J);

	return sol;
}
