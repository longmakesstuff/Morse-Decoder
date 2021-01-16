#include <String.hpp>
#include <iostream>
#include <cassert>
#include <Common.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

class TestSizedVector : public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestSizedVector);
        CPPUNIT_TEST(testSplit);
        CPPUNIT_TEST(testConvert);
        CPPUNIT_TEST(testEncodeAndFilter);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override {
        TestFixture::setUp();
    }

    void tearDown() override {
        TestFixture::tearDown();
    }
    static void testSplit() {
        auto tokens = strSplit("1\n2\n\n3\n");
        CPPUNIT_ASSERT_EQUAL(3UL, tokens.size());
    }

    static void testConvert() {
        auto numbers = strToNum<fpt>(std::vector<std::string>{"1", "2", "n", "3"});
        CPPUNIT_ASSERT_EQUAL(3UL, numbers.size());
    }

    static void testEncodeAndFilter() {
        auto tokens = encodeAndFilter(std::vector<std::string>{"f474e", "f474", "474e", "f474e\t", "f474e\t\r"});
        CPPUNIT_ASSERT_EQUAL(3UL, tokens.size());
    }
};

int main() {
    CPPUNIT_TEST_SUITE_REGISTRATION(TestSizedVector);
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool success = runner.run();
    return !success;
}