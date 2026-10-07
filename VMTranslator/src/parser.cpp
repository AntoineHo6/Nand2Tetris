#include "../include/parser.hpp"
#include <fstream>
#include <iostream>
#include <string_view>

/*
    eg: "add //comment" -> "add"
*/
void trimInlineComment(std::string& line) {
    size_t commentPos = line.find("//");
    if (commentPos != std::string::npos) {
        line = line.substr(0, commentPos);
    }
}

/*
    eg: "add   " -> "add"
*/
void trimTrailWhiteSpace(std::string& line) {
    size_t endPos = line.find_last_not_of(" \t\r\n");
    if (endPos != std::string::npos) {
        line = line.substr(0, endPos + 1);
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
        size_t posFirstChar = line.find_first_not_of(" \t\r\n"); 

        // skip empty lines and comment lines
        if (posFirstChar == std::string::npos || line.compare(posFirstChar, 2, "//") == 0) {
            continue;
        }

        // if vm line, do the following:
        line.erase(0, posFirstChar);    // Trim whitespace left

        trimInlineComment(line);

        trimTrailWhiteSpace(line);

        command = line;

        break;
    }
}

CommandType Parser::commandType() {
    // std::string_view temp = command;

    size_t start = command.find_first_not_of(" \t\n\r");
    
    size_t end = command.find_first_of(" \t\n\r", start);
    
    if (end == std::string_view::npos) {
        
    }

    // command.substr(start, end - start);
}

std::string_view Parser::getCommand() {
    return command;
}