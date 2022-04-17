/*************************************************************************
    > File Name: jsonser.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include "jsonser.h"

std::string ptreeToJsonString(const ptree& tree) {
    std::stringstream ss;
    boost::property_tree::write_json(ss, tree, false);
    return ss.str();
}
