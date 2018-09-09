#ifndef GOOD_CODER_PARSE_COMM_TYPE_H
#define GOOD_CODER_PARSE_COMM_TYPE_H

#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

template <typename T>
class ParseCommType {

public:

    void parse_comm_type(std::string& str, T* value) {
        std::stringstream ss(str);
        ss >> *value;
    }

    void parse_comm_type(std::string& str, T** value, size_t* count) {

        std::vector<std::string> svec;
        boost::split(svec, str, boost::is_any_of(","));

        std::vector<T> res;
        for (auto ele : svec) {
            std::stringstream ss(ele);
            T temp;
            ss >> temp;
            res.push_back(temp);
        }

        *count = res.size();

        T* res_temp = new T[*count];
        std::copy(res.begin(), res.end(), res_temp);

        *value = res_temp;
    }

    static ParseCommType& Instance() {
        static ParseCommType singleton;
        return singleton;
    }

private:
    ParseCommType() {}
    ParseCommType(ParseCommType const&) = delete;
    void operator=(ParseCommType const&) = delete;

};

#endif
