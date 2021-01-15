#include <Statistics.hpp>
#include <cassert>

int main() {
    assert(cdf(0.0) == 0.5);
    assert(cdf(1.96) == 0.9750021048517795);
    assert(cdf(-1.96) == 0.024997895148220435);
}