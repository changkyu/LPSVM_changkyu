//////////////////////////////////////////////////////////////////////////////////////////////////
// Support Vector Machine using Linear Programming
// Author: Changkyu Song (changkyu.song@rutgers.edu)
// Reference
// [1] libsvm: This project employs the input/output format of LIBSVM (Version 3.20, November 2014)
//             and refers its source code released at (http://www.csie.ntu.edu.tw/~cjlin/libsvm)
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "lpsvm_log.h"
#include "lpsvm_options.h"
#include "lpsvm_parser.h"
#include "lpsvm_simplexsolver.h"
#include "../3rdparty/simplex_tamas/SimplexSolver.h"
#include "../3rdparty/simplex_tamas/exception.h"

/**
 *
 * A main driver for LPsvm
 */
int main(int argc, char **argv)
{
    LPSVM_Options options(argc, (const char **) argv);
    g_log.open(options.GetParam().filepath_log);
    options.PrintArguments();

    LPSVM_SimplexSolver simplexSolver;
#if 0
    Eigen::MatrixXd A(2,5);
    A << 1,1,2,3,5,
         2,4,3,2,1;
    Eigen::VectorXd b(2);
    b << 19,57;
    Eigen::VectorXd c(5);
    c << 10, 24, 20, 20, 25;
#endif

    Eigen::MatrixXd A(3,2);
	A << 2,1,
		 2,3,
		 3,1;
	Eigen::VectorXd b(3);
	b << 18,42,24;
	Eigen::VectorXd c(2);
	c << 3,2;

    LPSVM_SimplexSolver::Problem_Description desc;
    desc.problem = LPSVM_SimplexSolver::MAX_PROBLEM;
    desc.constraint = LPSVM_SimplexSolver::CONSTRAINT_LE;

    LPSVM_SimplexSolver::Solution* sol = simplexSolver.Solve(A,b,c, desc);
    LOG("Sol: " << sol->x.transpose() << std::endl);
    LOG("Obj: " << sol->objective_value << std::endl);

#if 0
    LPSVM_Parser parser;
    Eigen::MatrixXd* mx_pConstraints = parser.Parse(options.GetParam().filepath_train);
    if(mx_pConstraints)
    {
    	Eigen::VectorXd objectiveFunction = Eigen::VectorXd::Ones(mx_pConstraints->cols()-1);

    	SimplexSolver *solver = new SimplexSolver(SIMPLEX_MINIMIZE, objectiveFunction, *mx_pConstraints);
    	if( solver )
    	{
			try
			{
				if (solver->hasSolution())
				{
					LOG( "The minimum is : " << solver->getOptimum() << std::endl );
					LOG( "The solution is: " << solver->getSolution().transpose() );
					LOG( std::endl );
				}
				else
				{
					LOG( "The linear problem has no solution." << std::endl );
				}
			}
			catch (FException *ex)
			{
				LOG( ex->getMessage() );
			}
			delete solver;
    	}

    	delete mx_pConstraints;
    }
#endif

    g_log.close();
    return 0;
}
