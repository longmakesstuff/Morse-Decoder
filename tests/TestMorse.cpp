#include <Morse.hpp>
#include <string>
#include <vector>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

class TestMorse : public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestMorse);
        CPPUNIT_TEST(testAlphabetCompleteness);
        CPPUNIT_TEST(testEncode);
        CPPUNIT_TEST(testDecode);
        CPPUNIT_TEST(testParse);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override {
        TestFixture::setUp();
    }

    void tearDown() override {
        TestFixture::tearDown();
    }

    static void testAlphabetCompleteness() {
        Morse m;
        for (auto &alpha : m.getAlphaToMorse()) {
            auto morse = m.getMorseToAlpha().find(alpha.second);
            CPPUNIT_ASSERT_EQUAL(morse->first, alpha.second);
        }
        for (auto &morse: m.getMorseToAlpha()) {
            auto alpha = m.getAlphaToMorse().find(morse.second);
            CPPUNIT_ASSERT_EQUAL(alpha->first, morse.second);
        }
        CPPUNIT_ASSERT_EQUAL(m.getMorseToAlpha().size(), m.getAlphaToMorse().size());
    }

    static void testEncode() {
        Morse m;
        std::vector<std::string> texts{
                "hello",
                "morse code",
                "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z",
                "The quick brown fox jumps over 13 lazy dogs"
        };
        std::vector<std::string> codes{
                ".... . .-.. .-.. ---",
                "-- --- .-. ... . / -.-. --- -.. .",
                ".- / -... / -.-. / -.. / . / ..-. / --. / .... / .. / .--- / -.- / .-.. / -- / -. / --- / .--. / --.- / .-. / ... / - / ..- / ...- / .-- / -..- / -.-- / --..",
                "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / ..-. --- -..- / .--- ..- -- .--. ... / --- ...- . .-. / .---- ...-- / .-.. .- --.. -.-- / -.. --- --. ..."
        };
        for (size_t i = 0; i < texts.size(); i++) {
            auto code = m.encode(texts[i]);
            CPPUNIT_ASSERT(code.has_value());
            CPPUNIT_ASSERT_EQUAL_MESSAGE(texts[i], codes[i], code.value());
        }
    }

    static void testDecode() {
        Morse m;
        std::vector<std::string> codes{
                "- .... .",
                "-",
                "-- --- .-. ... . /",
                "-- --- .-. ... . / -.-. --- -.. .",
                "- .... ..- -. -.. . .-. / -... --- .-.. - / .- -. -.. / .-.. .. --. .... - .. -. --. / ...- . .-. -.-- / ...- . .-. -.-- / ..-. .-. .. --. .... - . -. .. -. --. / -- ."
        };
        std::vector<std::string> texts{
                "THE",
                "T",
                "MORSE ",
                "MORSE CODE",
                "THUNDER BOLT AND LIGHTING VERY VERY FRIGHTENING ME"
        };

        for (size_t i = 0; i < codes.size(); i++) {
            auto code = m.decode(codes[i]);
            CPPUNIT_ASSERT(code.has_value());
            CPPUNIT_ASSERT_EQUAL_MESSAGE(texts[i], texts[i], code.value());
        }
    }

    static void testParse() {
        std::vector<std::string> codes{
                "- .... .",
                "-",
                "-- --- .-. ... . /",
                "-- --- .-. ... . / -.-. --- -.. .",
                "- .... ..- -. -.. . .-. / -... --- .-.. - / .- -. -.. / .-.. .. --. .... - .. -. --. / ...- . .-. -.-- / ...- . .-. -.-- / ..-. .-. .. --. .... - . -. .. -. --. / -- ."
        };
        std::vector<std::string> texts{
                "THE",
                "T",
                "MORSE ",
                "MORSE CODE",
                "THUNDER BOLT AND LIGHTING VERY VERY FRIGHTENING ME"
        };
        for (size_t i = 0; i < texts.size(); i++) {
            auto code = codes[i];
            Morse m;
            for (char & j : code) {
                m.add(j);
            }
            auto text = m.parse();
            CPPUNIT_ASSERT(text.has_value());
        }
    }
};

int main() {
    CPPUNIT_TEST_SUITE_REGISTRATION(TestMorse);
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool success = runner.run();
    return !success;
}
