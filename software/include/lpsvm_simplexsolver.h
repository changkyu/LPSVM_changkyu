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

	typedef enum TYPE_CONSTRAINT
	{
		CONSTRAINT_GE=0,
		CONSTRAINT_EQ,
		CONSTRAINT_LE
	} TYPE_CONSTRAINT;

	/**
	 * Solve: solve Ax = b
	 */
	Eigen::VectorXd Solve(	Eigen::MatrixXd& mxContraints_LHS, Eigen::VectorXd& mxContraints_RHS, TYPE_CONSTRAINT type_constraint, Eigen::VectorXd& vcObjective );

} LPSVM_SimplexSolver;

#define LPSVM_SIMPLEX_EXCEPTION_INPUT_A_SIZE 1

#endif /* LPSVM_SIMPLEXSOLVER_H_ */
