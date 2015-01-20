/*
 * lpsvm_parser.h
 *
 *  Created on: Jan 16, 2015
 *      Author: changkyu
 */

#ifndef LPSVM_PARSER_H_
#define LPSVM_PARSER_H_

#include <Eigen/Dense>

typedef struct LPSVM_Feature
{
	short idx;
	float value;
} LPSVM_Feature;

typedef struct LPSVM_Data
{
    int    label;
    LPSVM_Feature* features;
    short  n_features;
} LPSVM_Data;

typedef class LPSVM_Parser {
public:
    LPSVM_Parser();
    virtual ~LPSVM_Parser();

    Eigen::MatrixXd* Parse(std::string filepath);

} LPSVM_Parser;

#endif /* LPSVM_PARSER_H_ */
