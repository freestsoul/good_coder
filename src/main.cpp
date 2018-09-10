#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <boost/bind.hpp>

#include "parser.h"

using namespace myparser;

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
    std::ifstream input(in_file, std::ios::binary);

    ParseCustomType<CustomTypeExample>::Func func =
        boost::bind(&parse_custom_type_example, _1, _2);

    ParseCustomType<CustomTypeExample>::Instance().register_custom_func(func);

    Parser parser;
    int row_ind = 0;
    while (std::getline(input, line)) {
        /*
        std::string line1 = "34\t89.9\tabcd\t33,45,98\t56|a|89.9";
        std::string line2 = "87\t103.9\t8efef\t88,22,1099\t77|d|90.99";
        std::cout << line_tmp << std::endl;
        std::cout << line2 << std::endl;
        std::cout << line.size() << ", " << line_tmp.size() << std::endl;
        */

        parser.split_line_columns(line, "\t");
        std::cout << "COLUMN " << ++row_ind << ":" << std::endl;

        int int_value;
        parser.parse_comm_type(0, &int_value);
        std::cout << "int value: " << int_value << std::endl;

        float float_value;
        parser.parse_comm_type(1, &float_value);
        std::cout << "float value: " << float_value << std::endl;

        char* ch_str;
        parser.parse_comm_type(2, &ch_str);
        std::string str_tmp(ch_str);
        std::cout << "char* value: " << str_tmp << std::endl;

        int* array;
        size_t arr_len;
        parser.parse_comm_type(3, &array, &arr_len);
        std::cout << "int array value: ";
        for (size_t i = 0; i < arr_len; ++i) {
            std::cout << *(array + i) << "\t";
        }
        std::cout << std::endl;

        CustomTypeExample custom_value;
        int ret = parser.parse_custom_type(4, &custom_value);

        if (0 != ret) {
            std::cout << "error! parse_custom_type" << std::endl;
            exit(-1);
        }

        std::cout << "custom type: " << std::endl;
        std::cout << "\tint_value: " << custom_value.int_value << std::endl;
        std::cout << "\tchar_value: " << custom_value.char_value << std::endl;
        std::cout << "\tdouble_value: " << custom_value.double_value << std::endl;

        std::cout << std::endl;
    }
    return 0;
}
