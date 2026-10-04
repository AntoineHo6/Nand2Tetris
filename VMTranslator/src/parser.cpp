#include "../include/parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser(const std::string& filePath): file(filePath) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
}

bool Parser::hasMoreLines() {

}