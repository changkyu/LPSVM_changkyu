/*
 * LPsvm_param.cpp
 *
 *      Author: changkyu
 */

#include <boost/program_options.hpp>

#include "lpsvm_log.h"
#include "lpsvm_options.h"

namespace po = boost::program_options;

LPSVM_Options::LPSVM_Options(int argc, char **argv)
{
    po::options_description desc("\nAvailable Options for 'Support Vector Machine with Linear Programming'\n");
    desc.add_options()
    (LPSVM_OPTION__HELP,                                             "produce help message")
    (LPSVM_OPTION__LOG_FILEPATH,   po::value<std::string>(),         "filepath for log")
    (LPSVM_OPTION__TRAIN_FILEPATH, po::value<std::string>(),         "filepath for train")
    (LPSVM_OPTION__MODEL_FILEPATH, po::value<std::string>(),         "filepath for model")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count(LPSVM_OPTION__HELP))
    {
        LOG( desc << std::endl );
        exit(1);
    }
    //////////////////////////////////////////////////////////////////
    // input data
    //////////////////////////////////////////////////////////////////
    if (vm.count(LPSVM_OPTION__LOG_FILEPATH))
        m_param.filepath_log = vm[LPSVM_OPTION__LOG_FILEPATH].as<std::string>();
    else
        m_param.filepath_log = "./log.txt";

    if (vm.count(LPSVM_OPTION__TRAIN_FILEPATH))
        m_param.filepath_train = vm[LPSVM_OPTION__TRAIN_FILEPATH].as<std::string>();
    else
        m_param.filepath_train = "./train.txt";

    if (vm.count(LPSVM_OPTION__MODEL_FILEPATH))
        m_param.filepath_model = vm[LPSVM_OPTION__MODEL_FILEPATH].as<std::string>();
    else
        m_param.filepath_model = "./model.txt";
}

void LPSVM_Options::PrintArguments()
{
    LOG( "---< Parameter Settings >-------------------------------"    << std::endl );
    LOG( LPSVM_OPTION__LOG_FILEPATH << ": " << m_param.filepath_log     << std::endl );
    LOG( LPSVM_OPTION__TRAIN_FILEPATH << ": " << m_param.filepath_train << std::endl );
    LOG( LPSVM_OPTION__MODEL_FILEPATH << ": " << m_param.filepath_model << std::endl );
    LOG( "--------------------------------------------------------"    << std::endl );
    LOG( std::endl );
}
