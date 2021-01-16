#include <cassert>
#include <SizedVector.hpp>
#include <Common.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


class TestSizedVector : public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestSizedVector);
        CPPUNIT_TEST(testVector);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override {
        TestFixture::setUp();
    }

    void tearDown() override {
        TestFixture::tearDown();
    }

    static void assertEqual(const std::vector<fpt> &a, const std::vector<fpt> &b) {
        CPPUNIT_ASSERT_EQUAL(a.size(), b.size());
        for (size_t i = 0; i < a.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(a[i], b[i]);
        }
    }

    static void testVector() {
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
};

int main() {
    CPPUNIT_TEST_SUITE_REGISTRATION(TestSizedVector);
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool success = runner.run();
    return !success;
}