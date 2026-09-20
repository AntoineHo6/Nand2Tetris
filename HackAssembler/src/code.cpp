#include "../include/code.hpp"
#include <unordered_map>

std::string Code::dest(const std::string& mnemonic) {
    static const std::unordered_map<std::string, std::string> destMap = {
        {"M", "001"},
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"ADM", "111"}
    };

    auto res = destMap.find(mnemonic);

    return res != destMap.end() ? res->second : "000";
};

std::string Code::comp(const std::string& mnemonic) {
    static const std::unordered_map<std::string, std::string> compMap = {
        // a=0 computation instructions
        {"0",   "0101010"},
        {"1",   "0111111"},
        {"-1",  "0111010"},
        {"D",   "0001100"},
        {"A",   "0110000"},
        {"!D",  "0001101"},
        {"!A",  "0110001"},
        {"-D",  "0001111"},
        {"-A",  "0110011"},
        {"D+1", "0011111"},
        {"A+1", "0110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"D+A", "0000010"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},
        // a=1 computation instructions (uses M instead of A)
        {"M",   "1110000"},
        {"!M",  "1110001"},
        {"-M",  "1110011"},
        {"M+1", "1110111"},
        {"M-1", "1110010"},
        {"D+M", "1000010"},
        {"D-M", "1010011"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
    };

    // this assumes that mnemonic will always be valid
    auto res = compMap.find(mnemonic);

    return res->second; 
}

std::string Code::jump(const std::string& mnemonic) {
    static const std::unordered_map<std::string, std::string> jumpMap = {
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };

    auto res = jumpMap.find(mnemonic);

    return res != jumpMap.end() ? res->second : "000";
};