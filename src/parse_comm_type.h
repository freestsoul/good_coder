#ifndef GOOD_CODER_PARSE_COMM_TYPE_H
#define GOOD_CODER_PARSE_COMM_TYPE_H

#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace myparser {

    template <typename T>
    class ParseCommType {

    public:

        static ParseCommType& Instance() {
            static ParseCommType singleton;
            return singleton;
        }

        void parse_comm_type(const std::string& str, T* value);
        void parse_comm_type(const std::string& str, T** value, size_t* count);

    private:
        ParseCommType() {}
        ParseCommType(ParseCommType const&) = delete;
        void operator=(ParseCommType const&) = delete;
    };

    template <typename T>
    void ParseCommType<T>::parse_comm_type(const std::string& str, T* value) {
        std::stringstream ss(str);
        ss >> *value;
    }

    template <typename T>
    void ParseCommType<T>::parse_comm_type(const std::string& str, T** value, size_t* count) {

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


}

#endif
