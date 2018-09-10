#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

size_t Ssplit(const std::string& str, const std::string& separator) {
    std::vector<std::string> svec;
    boost::split(svec, str, boost::is_any_of("\t"));

    for (auto ele : svec) {
        std::cout << ele << ",";
    }

    return svec.size();
}
int main() {
    std::string str("33\t44\t45");

    std::cout << Ssplit(str, "\t") << std::endl;
    return 0;
}
