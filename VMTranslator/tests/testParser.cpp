#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/parser.hpp"
#include <fstream>

// Helper to write a temporary test file
void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST_CASE("Testing Parser::advance()") {
    SUBCASE("Advances through vm instructions") {
        std::string testPath = "test_hasMoreLines.vm";

        createTestFile(testPath, "// VM test file\n push constant 10\n add // comment");

        Parser parser(testPath);

        parser.advance();
        CHECK(parser.getCommand() == "push constant 10");

        parser.advance();
        CHECK(parser.getCommand() == "add");
        
    }
};

TEST_CASE("Testing Parser::commandType()") {
    SUBCASE("Test extraction of first token") {
        std::string testPath = "test_hasMoreLines.vm";

        createTestFile(testPath, "add\n push constant 10\n pop argument 2");

        Parser parser(testPath);

        parser.advance();
        CHECK(parser.commandType() == CommandType::C_ARITHMETIC);

        parser.advance();
        CHECK(parser.commandType() == CommandType::C_PUSH);

        parser.advance();
        CHECK(parser.commandType() == CommandType::C_POP);
    }
}