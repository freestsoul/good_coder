#ifndef GOOD_CODER_PARSE_CUSTOM_TYPE_H
#define GOOD_CODER_PARSE_CUSTOM_TYPE_H

#include <string>
#include <map>
#include "custom_type.h"
#include <boost/any.hpp>
#include <boost/function.hpp>

template <typename T>
class ParseCustomType {

public:
    using Func = boost::function<int(const std::string&, T*)>;

    void register_custom_func(Func func) {
        const std::string key = typeid(T).name();
        custom_func_map[key] = func;
    }

    int get_custom_func(Func *func) {
        const std::string key = typeid(T).name();
        auto it = custom_func_map.find(key);

        if (it == custom_func_map.end()) {
            //TODO
            return -1;
        }

        *func = boost::any_cast<Func>(it->second);

        return 0;
    }

    int parse_custom_type(const std::string& str, T* value) {

        Func func;
        const std::string key = typeid(T).name();

        int ret = get_custom_func(&func);
        if (0 != ret) {
            //TODO;
        }

        func(str, value);

        return 0;
    }

    static ParseCustomType& Instance() {
        static ParseCustomType singleton;
        return singleton;
    }

private:
    ParseCustomType() {}
    ParseCustomType(ParseCustomType const&) = delete;
    void operator=(ParseCustomType const&) = delete;

private:
    std::map<std::string, boost::any> custom_func_map;
};

#endif
