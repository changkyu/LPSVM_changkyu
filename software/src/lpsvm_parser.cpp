/*
 * lpsvm_parser.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: changkyu
 */

#include <iostream>
#include <fstream>
#include <string>

#include "lpsvm_parser.h"
#include "lpsvm_log.h"

LPSVM_Parser::LPSVM_Parser() {
    // TODO Auto-generated constructor stub

}

LPSVM_Parser::~LPSVM_Parser() {
    // TODO Auto-generated destructor stub
}

Eigen::MatrixXd* LPSVM_Parser::Parse(std::string filepath)
{
    Eigen::MatrixXd* ret_pFeatureNLabel = NULL;
    std::ifstream f;
    f.open( filepath.c_str());
    if( f.is_open() )
    {
        int n_lines = std::count(std::istreambuf_iterator<char>(f),
                                 std::istreambuf_iterator<char>(), '\n');
        // ignore '\n's at the end of the file
        f.seekg(-1,std::ios_base::end);
        for( int j=-2; f.get() == '\n'; j--)
        {
            f.seekg(j,std::ios_base::end);
            if( f.get() == '\n' )
            {
                n_lines--;
            }
        }

        f.clear();
        f.seekg(0);

        // Allocate Memory for elems
        LPSVM_Data *elems = new LPSVM_Data[n_lines];
        std::string buf_line;
        int idx_min =  INFINITY;
        int idx_max = -INFINITY;
        for( int i=0; std::getline(f,buf_line); i++ )
        {
            std::istringstream s_line(buf_line);
            std::string token;
            char* endptr;

            // Get # of valid feature
            int n_features = std::count(std::istreambuf_iterator<char>(s_line),
                                         std::istreambuf_iterator<char>(), ':');
            s_line.clear();
            s_line.seekg(0);

            // Get Label first
            std::getline(s_line, token, ' ');
            elems[i].label = std::strtol(token.c_str(), &endptr, 0);
            elems[i].features = new LPSVM_Feature[n_features];
            elems[i].n_features = n_features;
            for( int j=0; std::getline(s_line, token, ' '); j++ )
            {
                std::size_t pos_colon = token.find(':');
                if( pos_colon != std::string::npos )
                {
                    // index
                    elems[i].features[j].idx
                     = std::strtol(token.substr(0,pos_colon).c_str(), &endptr, 0);
                    if(idx_max < elems[i].features[j].idx ) idx_max = elems[i].features[j].idx;
                    if(idx_min > elems[i].features[j].idx ) idx_min = elems[i].features[j].idx;

                    // feature
                    elems[i].features[j].value
                     = std::strtof(token.substr(pos_colon+1,token.length()).c_str(), &endptr);
                }
            }
        }
        f.close();

        // Convert to Matrix
        int size_idx = idx_max-idx_min+1;
        ret_pFeatureNLabel = new Eigen::MatrixXd(n_lines, size_idx + 1); // n_lines x (size_idx + label)
        *ret_pFeatureNLabel = Eigen::MatrixXd::Zero(n_lines,size_idx);
        for( int i=0; i<n_lines; i++ )
        {
            int n_features = elems[i].n_features;
            for( int j=0; j<n_features; j++ )
            {
            	(*ret_pFeatureNLabel)(i,elems[i].features[j].idx - idx_min) = elems[i].features[j].value;
            }
            (*ret_pFeatureNLabel)(i,size_idx - idx_min) = elems[i].label;
        }

        // Free Memory for elems
        for( int i=0; i<n_lines; i++ )
        {
            delete elems[i].features;
        }
        delete elems;
    }
    else
    {
        LOG("Unable to read file" << filepath << std::endl);
    }
    return ret_pFeatureNLabel;
}
