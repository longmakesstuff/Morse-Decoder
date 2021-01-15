#pragma once

#include <string>
#include <vector>
#include "Common.hpp"

std::vector<std::string> strSplit(const std::string &data,
                                  const std::string &separator = "\n");

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
            LOG_ERROR("Error while converting string to number: " << it);
        }
    }
    return ret;
}