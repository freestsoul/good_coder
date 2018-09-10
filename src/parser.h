#ifndef GOOD_CODER_MYPARSER_H
#define GOOD_CODER_MYPARSER_H

#include <string>
#include <vector>
#include <sstream>

#include "custom_type.h"
#include "parse_custom_type.h"
#include "parse_comm_type.h"

namespace myparser {

    class Parser {

    public:

        std::size_t split_line_columns(const std::string& line, const std::string& separator);

        std::vector<std::string> get_columns();

        template <typename T>
        int parse_comm_type(const size_t col, T* value);

        template <typename T>
        int parse_comm_type(const size_t col, T** value, size_t* count);

        template <typename T>
        int parse_custom_type(const size_t col, T* value);

    private:
        std::vector<std::string> columns;
    };

    std::size_t Parser::split_line_columns(const std::string& line, const std::string& separator) {
        /*
        std::cout << line << std::endl;
        columns.clear();
        std::string stemp;
        std::stringstream ss(line);
        while (std::getline(ss, stemp, '\t')) {
            columns.push_back(stemp);
        }

        for (auto ele : columns) {
            std::cout << "ele" << ele << std::endl;
        }
        */
        boost::split(columns, line, boost::is_any_of(separator));
        return columns.size();
    }

    std::vector<std::string> Parser::get_columns() {
        return columns;
    }

    template <typename T>
    int Parser::parse_comm_type(const size_t col, T* value) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCommType<T>::Instance().parse_comm_type(columns[col], value);
        return 0;
    }

    template <typename T>
    int Parser::parse_comm_type(const size_t col, T** value, size_t* count) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCommType<T>::Instance().parse_comm_type(columns[col], value, count);
        return 0;
    }

    template <typename T>
    int Parser::parse_custom_type(const size_t col, T* value) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCustomType<T>::Instance().parse_custom_type(columns[col], value);
        return 0;
    }

    template <>
    int Parser::parse_comm_type<char*>(const size_t col, char** value) {
        if (col >= columns.size()) {
            return -1;
        }

        std::string str = columns[col];
        char* str_tmp = new char[sizeof(char) * (str.length() + 1)];
        str.copy(str_tmp, str.length(), 0);
        *(str_tmp + str.length()) = '\0';
        *value = str_tmp;

        return 0;
    }
}

#endif
