#pragma once
#include <string_view>
#include <fstream>

enum class CommandType {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
};

class Parser {
    public:
        explicit Parser(const std::string& filepath);
        bool hasMoreLines();
        void advance();
        CommandType commandType();
        std::string_view arg1();
        int arg2();
        std::string_view getCommand();
        
    private:
        std::ifstream file;
        std::string command;
};