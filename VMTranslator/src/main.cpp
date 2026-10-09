#include <iostream>
#include "parser.cpp"

int main(int argc, char* argv[]) {
    std::string filePath = "../vm/basicTest.vm";

    Parser parser(filePath);

    parser.advance();
    parser.commandType();

    return 0;
}