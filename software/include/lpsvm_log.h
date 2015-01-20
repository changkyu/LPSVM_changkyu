/*
 * LPSVM_log.h
 *
 *  Created on: Jan 15, 2015
 *      Author: changkyu
 */

#ifndef LPSVM_LOG_H_
#define LPSVM_LOG_H_

#include <string>
#include <iostream>
#include <fstream>

class LPSVM_log
{
public:

    LPSVM_log()
    {
        m_pfLog = NULL;
    };

    ~LPSVM_log()
    {
        close();
    };

    void close()
    {
        if(m_pfLog)
        {
            m_pfLog->close();
            m_pfLog = NULL;
        }
    };

    void open(std::string filepath_log)
    {
        close();
        m_pfLog = new std::ofstream();
        m_pfLog->open(filepath_log.c_str());
    };

    std::ofstream *m_pfLog;
};

extern LPSVM_log g_log;

#define LOG(x) if(g_log.m_pfLog) *(g_log.m_pfLog) << x; std::cout << x;

#endif /* LPSVM_LOG_H_ */
