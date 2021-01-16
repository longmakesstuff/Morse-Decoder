#include <String.hpp>
#include <iostream>
#include <cassert>
#include <Common.hpp>

void testSplit() {
    auto tokens = strSplit("1\n2\n\n3\n");
    assert(tokens.size() == 4);
}

void testConvert() {
    auto numbers = strToNum<fpt>(std::vector<std::string>{"1", "2", "n", "3"});
    assert(numbers.size() == 3);
}

void encodeAndFilter() {
    auto tokens = encodeAndFilter(std::vector<std::string>{"f474e", "f474", "474e", "f474e\t", "f474e\t\r"});
    for(const auto& token : tokens)    {
        std::cout << token << std::endl;
    }
}

int main() {
    testSplit();
    testConvert();
    encodeAndFilter();
}