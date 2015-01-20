/*
 * lpsvm_simplexsolver.h
 *
 *  Created on: Jan 19, 2015
 *      Author: changkyu
 */

#ifndef LPSVM_SIMPLEXSOLVER_H_
#define LPSVM_SIMPLEXSOLVER_H_

#include <Eigen/Dense>

typedef class LPSVM_SimplexSolver {
public:
	LPSVM_SimplexSolver(){}
	virtual ~LPSVM_SimplexSolver(){};

	/**
	 * Solve: solve Ax = b
	 */
	Eigen::VectorXd Solve(	Eigen::MatrixXd& mxContraints_LHS, Eigen::VectorXd& mxContraints_RHS, Eigen::VectorXd& vcObjective );

} LPSVM_SimplexSolver;

#endif /* LPSVM_SIMPLEXSOLVER_H_ */
