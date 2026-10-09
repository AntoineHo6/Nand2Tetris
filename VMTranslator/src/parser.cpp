#include "../include/parser.hpp"
// #include <fstream>
#include <iostream>
#include <string_view>
#include <sstream>
#include <unordered_set>


Parser::Parser(const std::string& filePath): file(filePath) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
}

bool Parser::hasMoreLines() {
    return file.peek() != EOF;
}


/*
    Should only be called if hasMoreLines() is true.
*/
void Parser::advance() {
    std::string line;

    while (std::getline(file, line)) {
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line.erase(commentPos);
        }

        std::string_view sv = line;

        size_t start = sv.find_first_not_of(" \t\r\n");
        if (start == std::string_view::npos) {
            continue; // empty or comment line
        }

        size_t end = sv.find_last_not_of(" \t\r\n");

        command = sv.substr(start, end - start + 1);
        return;
    }
}


CommandType Parser::commandType() {
    std::stringstream ss(command);
    std::string firstToken;

    ss >> firstToken;

    static const std::unordered_set<std::string> arithmeticCmds = {
        "add", "sub", "neg",
        "eq",  "gt",  "lt",
        "and", "or",  "not"
    };

    if (arithmeticCmds.contains(firstToken)) {
        return CommandType::C_ARITHMETIC;
    }
    else if (firstToken == "push") {
        return CommandType::C_PUSH;
    }
    else if (firstToken == "pop") {
        return CommandType::C_POP;
    }

    // chapter 2 will implement the rest of the commands. For now, return random command type.
    return CommandType::C_RETURN;
}

std::string_view Parser::getCommand() {
    return command;
}