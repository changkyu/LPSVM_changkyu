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

	typedef enum TYPE_PROBLEM
	{
		MIN_PROBLEM=0,
		MAX_PROBLEM
	} TYPE_PROBLEM;

	typedef enum TYPE_CONSTRAINT
	{
		CONSTRAINT_GE=0,
		CONSTRAINT_EQ,
		CONSTRAINT_LE
	} TYPE_CONSTRAINT;

	typedef struct Problem_Description
	{
		TYPE_PROBLEM problem;
		TYPE_CONSTRAINT constraint;
	}Problem_Description;

	typedef struct Solution
	{
		double objective_value;
		Eigen::VectorXd x;
	} Solution;

	/**
	 * Solve: solve Ax = b
	 */
	Solution* Solve(	Eigen::MatrixXd& mxContraints_LHS, Eigen::VectorXd& mxContraints_RHS, Eigen::VectorXd& vcObjective, Problem_Description problem_description );

private:
	Solution* Solve_Primal(Eigen::MatrixXd &A, Eigen::VectorXd &b, Eigen::VectorXd &c);

} LPSVM_SimplexSolver;

#define LPSVM_SIMPLEX_EXCEPTION_INPUT_A_SIZE 1

#endif /* LPSVM_SIMPLEXSOLVER_H_ */
