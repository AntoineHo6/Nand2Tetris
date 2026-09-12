#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/code.hpp"
#include "../include/parser.hpp"

// Helper to write a temporary test file
void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST_CASE("Testing Code::dest()") {
    SUBCASE("Extracts dest mnemonic into it's binary equivalent") {
        std::string testPath = "codeDestTests.asm";
        createTestFile(testPath, "DM=A+1\nD-1");

        Parser parser(testPath);

        parser.advance();
        CHECK(Code::dest(parser.dest()) == "011");

        parser.advance();
        CHECK(Code::dest(parser.dest()) == "000");
    };
};


TEST_CASE("Testing Code::comp()") {
    // comp is mandatory, so we don't test if it's empty.
    SUBCASE("Extracts comp mnemonic into it's binary equivalent") {
        std::string testPath = "codeCompTests.asm";
        createTestFile(testPath, "DM=A+1\n");

        Parser parser(testPath);

        parser.advance();
        CHECK(Code::comp(parser.comp()) == "0011011");
    };
};


TEST_CASE("Testing Code::jump()") {
    SUBCASE("Extracts jump mnemonic into it's binary equivalent") {
        std::string testPath = "codeJumpTests.asm";
        createTestFile(testPath, "DM=A+1;JGT\nD-1");

        Parser parser(testPath);

        parser.advance();
        CHECK(Code::jump(parser.jump()) == "001");

        parser.advance();
        CHECK(Code::jump(parser.jump()) == "000");
    };
};