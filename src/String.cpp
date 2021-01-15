#include <regex>
#include "String.hpp"
#include "Common.hpp"


// https://stackoverflow.com/a/64886763/9448540
std::vector<std::string> strSplit(const std::string &data, const std::string &separator) {
    std::regex rex(separator);
    std::vector<std::string> ret(std::sregex_token_iterator(data.begin(), data.end(), rex, -1),
                                 std::sregex_token_iterator());
    for (auto it = ret.begin(); it != ret.end();) {
        if (it->empty()) {
            it = ret.erase(it);
        } else {
            it++;
        }
    }
    return ret;
}
