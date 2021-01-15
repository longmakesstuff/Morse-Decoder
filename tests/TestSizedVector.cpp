#include <cassert>
#include <SizedVector.hpp>
#include <Common.hpp>

void assertEqual(const std::vector<fpt> &a, const std::vector<fpt> &b) {
    assert(a.size() == b.size());
    for (int32_t i = 0; i < a.size(); i++) {
        assert(a[i] == b[i]);
    }
}

int main() {
    SizedVector<fpt> vect{3};
    assertEqual(vect.data(), std::vector<fpt>{});
    vect << 0;
    assertEqual(vect.data(), std::vector<fpt>{0});
    vect << 1;
    assertEqual(vect.data(), std::vector<fpt>{0, 1});
    vect << 2;
    assertEqual(vect.data(), std::vector<fpt>{0, 1, 2});
    vect << 3;
    assertEqual(vect.data(), std::vector<fpt>{1, 2, 3});

    vect.push_back(std::vector<fpt>{4, 5});
    assertEqual(vect.data(), std::vector<fpt>{3, 4, 5});

    vect.push_back(std::vector<fpt>{6, 7, 8});
    assertEqual(vect.data(), std::vector<fpt>{6, 7, 8});
}