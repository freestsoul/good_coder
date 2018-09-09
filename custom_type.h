#ifndef GOOD_CODER_CUSTOM_TYPE_H
#define GOOD_CODER_CUSTOM_TYPE_H

#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "parse_comm_type.h"

struct CustomTypeExample {
    int int_value;
    double double_value;
};

int parse_custom_type_example(const std::string& str, CustomTypeExample* value) {
    std::vector<std::string> svec;
    boost::split(svec, str, boost::is_any_of("|"));

    ParseCommType<int>::Instance().parse_comm_type(svec[0], &(value->int_value));
    ParseCommType<double>::Instance().parse_comm_type(svec[1], &(value->double_value));

    return 0;
}

#endif
