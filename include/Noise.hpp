#pragma once

#include <cinttypes>
#include <omp.h>
#include <vector>
#include <cmath>
#include "Common.hpp"
#include "Statistics.hpp"

constexpr fpt kernel[9] = {1.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 4.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 1.0 / 16};
typedef void SignalFilter(SizedVector<fpt> &data);

void naive(SizedVector<fpt>& data) {
    fpt expected = data.mean();
#pragma omp parallel for
    for (int32_t i = 0; i < data.size(); i++) {
        if(data[i] < 15) {
            data[i] = expected;
        }
    }
}

void gaussian(SizedVector<fpt> &data) {
    if (data.size() > 50) {
        std::vector<fpt> output(data.size() - 9);
        int32_t lim = data.size() - 9;
#pragma omp parallel for
        for (int32_t i = 0; i < lim; i++) {
            fpt sum = 0;
            for (int32_t j = 0; j < 9; j++) {
                sum += data[i + j] * kernel[j];
            }
            output[i] = sum;
        }
        data.reset();
        data.push_back(output);
    }
}