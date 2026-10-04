#pragma once
#include <string>
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
        std::string arg1();
        int arg2();
        
    private:
        std::ifstream file;
        std::string instr;
};