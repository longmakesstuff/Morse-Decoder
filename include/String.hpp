#pragma once

#include <string>
#include <vector>
#include <regex>
#include "Common.hpp"

// Split incoming data into tokens
inline std::vector<std::string> strSplit(const std::string &data,
                                         const std::string &separator = "\n") {
    std::regex rex(separator);
    std::vector<std::string> ret(std::sregex_token_iterator(data.begin(), data.end(), rex, -1),
                                 std::sregex_token_iterator());
    return ret;
}

// Filter token, only allow correct formed strings
inline std::vector<std::string> encodeAndFilter(const std::vector<std::string> &data) {
    std::vector<std::string> ret;

    // Can be faster
    for(const auto& it : data) {
        if(it.size() >= 5 && it[0] == 'f' && it[4] == 'e' && std::isdigit(it[1]) && std::isdigit(it[2]) && std::isdigit(it[3])){
            std::stringstream  ss;
            ss << it[1] << it[2] << it[3];
            ret.push_back(ss.str());
        }
    }

    return ret;
}

template<typename T>
inline std::vector<T> strToNum(const std::vector<std::string> &data) {
    std::vector<T> ret;
    for (const auto &it : data) {
        try {
            if constexpr (std::is_same_v<T, float>) {
                ret.push_back(std::stof(it));
            } else if constexpr (std::is_same_v<T, double>) {
                ret.push_back(std::stod(it));
            } else if constexpr (std::is_same_v<T, int32_t>) {
                ret.push_back(std::stoi(it));
            } else if constexpr (std::is_same_v<T, int64_t>) {
                ret.push_back(std::stol(it));
            }
        } catch (std::invalid_argument &e) {
            //LOG_ERROR("Error while converting string to number: " << it);
        }
    }
    return ret;
}