/*************************************************************************
    > File Name: jsonser.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _JSONSER_H
#define _JSONSER_H

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <sstream>
#include <string>

using ptree = boost::property_tree::ptree;

std::string ptreeToJsonString(const ptree& tree);

#endif
