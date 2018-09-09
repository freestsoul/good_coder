#include <string>
#include <vector>

#include "custom_type.h"
#include "parse_custom_type.h"
#include "parse_comm_type.h"

class Parser {

public:
    std::size_t split_line_columns(const std::string& line, const std::string& separator) {
        std::cout << line << std::endl;
        columns.clear();
        boost::split(columns, line, boost::is_any_of(":"));
        for (auto ele : columns) {
            std::cout << "ele" << ele << std::endl;
        }
        return columns.size();
    }

    template <typename T>
    int parse_comm_type(const size_t col, T* value) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCommType<T>::Instance().parse_comm_type(columns[col], value);
        return 0;
    }

    template <typename T>
    int parse_comm_type(const size_t col, T** value, size_t* count) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCommType<T>::Instance().parse_comm_type(columns[col], value, count);
        return 0;
    }

    template <typename T>
    int parse_custom_type(const size_t col, T* value) {
        if (col >= columns.size()) {
            return -1; //TODO
        }

        ParseCustomType<T>::Instance().parse_custom_type(columns[col], value);
        return 0;
    }

private:
    std::vector<std::string> columns;
};
