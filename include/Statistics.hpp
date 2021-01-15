#pragma once
#include <cinttypes>
#include <omp.h>
#include <vector>
#include <cmath>

inline double_t cdf(double x) {
    return std::erfc(-x / std::sqrt(2)) / 2;
}