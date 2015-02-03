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

	typedef enum ERROR
	{
		SUCCESS = 0 ,
		ERROR_CONVERT2PRIMAL2DUAL_UNSUPPORTTED_PROBLEM_TYPE,
		ERROR_CONVERT2STANDARDFORM_INVALID_PROBLEM_TYPE
	} ERROR;

	ERROR ConvertPrimal2Dual(	Eigen::MatrixXd& A_in, Eigen::VectorXd& b_in, Eigen::VectorXd& c_in,
								Problem_Description& problem_desc,
								Eigen::MatrixXd* &p_A_out, Eigen::VectorXd* &p_b_out, Eigen::VectorXd* &p_c_out  );

	ERROR Convert2StandardForm(	Eigen::MatrixXd& A_in, Eigen::VectorXd& b_in, Eigen::VectorXd& c_in,
								Problem_Description& problem_desc,
								Eigen::MatrixXd* &p_A_out, Eigen::VectorXd* &p_b_out, Eigen::VectorXd* &p_c_out  );

	Solution* Solve_Primal(Eigen::MatrixXd &A, Eigen::VectorXd &b, Eigen::VectorXd &c);


} LPSVM_SimplexSolver;

#define LPSVM_SIMPLEX_EXCEPTION_INPUT_A_SIZE 1

#endif /* LPSVM_SIMPLEXSOLVER_H_ */
