#include <iostream>
#include "parser.cpp"

int main(int argc, char* argv[]) {
    std::string filePath = "../vm/basicTest.vm";
    Parser parser(filePath);

    return 0;
}