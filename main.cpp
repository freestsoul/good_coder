#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <boost/bind.hpp>

#include "parser.h"

int main(int argc, char** argv) {

    std::string in_file;
    std::string opt_string("f:h");
    int opt = 0;
    while ( (opt = getopt(argc, argv, opt_string.c_str())) != -1) {
        switch (opt) {
        case 'f':
            in_file = optarg;
            if (in_file.empty()) {
                std::cout << "usage: ./parser -f input_file" << std::endl;
                exit(-1);
            }
            break;
        case 'h':
            std::cout << "usage: ./parser -f input_file" << std::endl;
            exit(0);
        default:
            std::cout << "usage: ./parser -f input_file" << std::endl;
            exit(0);
        }
    }

    std::string line;
    std::ifstream input(in_file);

    ParseCustomType<CustomTypeExample>::Func func =
        boost::bind(&parse_custom_type_example, _1, _2);

    ParseCustomType<CustomTypeExample>::Instance().register_custom_func(func);

    Parser parser;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        size_t column_size = parser.split_line_columns(line, "\t");

        std::cout << "COLUMN:" << column_size << std::endl;

        int int_value;
        parser.parse_comm_type(0, &int_value);
        std::cout << int_value << std::endl;

        float float_value;
        parser.parse_comm_type(1, &float_value);
        std::cout << float_value << std::endl;

        int* array;
        size_t arr_len;
        parser.parse_comm_type(2, &array, &arr_len);
        for (size_t i = 0; i < arr_len; ++i) {
            std::cout << *(array + i) << ",";
        }
        std::cout << std::endl;

        CustomTypeExample custom_value;
        int ret = parser.parse_custom_type(3, &custom_value);

        if (0 != ret) {
            std::cout << "error! parse_custom_type" << std::endl;
            exit(-1);
        }

        std::cout << "custom type: int_value:" << custom_value.int_value << " double_value:" << custom_value.double_value << std::endl;

    }
    return 0;
}
