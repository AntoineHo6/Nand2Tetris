#include "../include/parser.hpp"
#include <iostream>
#include <string_view>

// #include <algorithm>
#include <array>

namespace {
    std::string_view getToken(std::string_view sv, int index) {
        size_t pos = 0;
    
        for (int i = 0; i <= index; ++i) {
            // 1. Skip leading whitespace to find the start of the token
            pos = sv.find_first_not_of(" \t", pos);
            if (pos == std::string_view::npos) return {}; // Index out of bounds

            // 2. Find where this token ends (next whitespace or end of string)
            size_t end = sv.find_first_of(" \t", pos);

            // 3. If this is the target index, return the slice
            if (i == index) {
                return (end == std::string_view::npos) 
                        ? sv.substr(pos) 
                        : sv.substr(pos, end - pos);
            }

            // Otherwise, move past this token for the next iteration
            pos = end;
        }
        
        return {};
    }
}


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
    std::string_view sv = command;

    std::string_view token1 = getToken(sv, 0);

    static constexpr std::array<std::string_view, 9> arithmeticCmds = {
        "add", "sub", "neg",
        "eq",  "gt",  "lt",
        "and", "or",  "not"
    };

    std::string token1str{token1};
    if (std::ranges::find(arithmeticCmds, token1) != arithmeticCmds.end()) {
        return CommandType::C_ARITHMETIC;
    }
    else if (token1 == "push") {
        return CommandType::C_PUSH;
    }
    else if (token1 == "pop") {
        return CommandType::C_POP;
    }

    // chapter 2 will implement the rest of the commands. For now, return random command type.
    return CommandType::C_RETURN;
}


std::string_view Parser::arg1() {
    std::string_view sv = command;
    
    switch(commandType()) {
        case CommandType::C_ARITHMETIC:
            return command;
        case CommandType::C_POP:
        case CommandType::C_PUSH:
            return getToken(sv, 1);
        default:    // implement the rest in chap 2
            return "boop";
    }
}


int Parser::arg2() {
    // TODO
    return 0;
}


std::string_view Parser::getCommand() {
    return command;
}