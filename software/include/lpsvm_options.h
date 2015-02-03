/*
 * LPSVM_parser.h
 *
 *      Author: changkyu
 */

#ifndef LPSVM_OPTIONS_H_
#define LPSVM_OPTIONS_H_

#include <string>

typedef struct LPSVM_Param
{
    std::string filepath_log;
    std::string filepath_train;
    std::string filepath_model;
} LPSVM_Param;

typedef class LPSVM_Options
{
public:
    LPSVM_Options(int argc, char **argv);
    virtual ~LPSVM_Options(){};

    void PrintArguments();

    const LPSVM_Param GetParam(){return m_param;};

private:

    LPSVM_Param m_param;
} LPSVM_Options;

#define LPSVM_OPTION__HELP           ("help")
#define LPSVM_OPTION__LOG_FILEPATH   ("log_file")
#define LPSVM_OPTION__TRAIN_FILEPATH ("train_file")
#define LPSVM_OPTION__MODEL_FILEPATH ("model_file")

#endif /* LPSVM_OPTIONS_H_ */
