#include <String.hpp>
#include <iostream>
#include <cassert>
#include <Common.hpp>

void testSplit() {
    auto tokens = strSplit("1\n2\n\n3\n");
    assert(tokens.size() == 3);
}

void testConvert() {
    auto numbers = strToNum<fpt>(std::vector<std::string>{"1", "2", "n", "3"});
    assert(numbers.size() == 3);
}

int main() {
    testSplit();
    testConvert();
}