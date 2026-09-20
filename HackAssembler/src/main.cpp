#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <bitset>
#include <ctype.h>

#include "parser.cpp"
#include "code.cpp"
#include "symbolTable.cpp"


/*
    The first pass will add all LABEL symbols to the Symbol Table.
    The address of LABEL symbols is the line number at which the label is located at.
    e.g: if (LOOP) is located on line 10 of the file, then it's address will be 10.
*/
void firstPass(SymbolTable& symbolTable, const std::string& filePath) {
    Parser parser(filePath);

    int lineCounter = 0;

    while (parser.hasMoreLines()) {
        parser.advance();
        if (parser.instructionType() == InstrType::L_INSTRUCTION) {
            symbolTable.addEntry(parser.symbol(), lineCounter);
        }
        else {
            lineCounter++;
        }
    }
}


/*
    The second pass will convert every assembly line into it's corresponding 16 bit binary form.
    Addresses for the first variable starts at RAM[16]. The second RAM[17] and so on. 
*/
int secondPass(SymbolTable& symbolTable, const std::string& filePath) {
    Parser parser(filePath);

    // create output file
    std::filesystem::path p(filePath);
    std::string fileStem = p.stem().string();
    std::ofstream hackFile(fileStem + ".hack");

    if (!hackFile.is_open()) {
        std::cerr << "Error: Could not create hack file!\n";
        return 1;
    }
    
    int varAddressCounter = 16;

    while (parser.hasMoreLines()) {
        parser.advance();

        switch(parser.instructionType()) {
            case InstrType::A_INSTRUCTION: {
                std::string symbol = parser.symbol();
                int value;

                if (symbolTable.contains(symbol)) { // @<label> or existing @<variable>
                    value = symbolTable.getAddress(symbol);
                }
                else if (isdigit(symbol.at(0))) {   // @<number>
                    value = std::stoi(symbol);
                }
                else {  // new @<variable>
                    value = varAddressCounter;
                    symbolTable.addEntry(symbol, value);
                    varAddressCounter++;
                }
                
                hackFile << "0" + std::bitset<15>(value).to_string() << '\n';

                break;
            }
            case InstrType::C_INSTRUCTION: {
                hackFile << "111" + Code::comp(parser.comp())
                                   + Code::dest(parser.dest()) 
                                   + Code::jump(parser.jump()) << '\n';
                break;                
            }
            case InstrType::L_INSTRUCTION: {
                continue;
            }
        }
    }

    return 0;
}


int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!\n" << std::endl;
        return 1;
    }

    const std::string filePath = argv[1];

    SymbolTable symbolTable;

    firstPass(symbolTable, filePath);

    secondPass(symbolTable, filePath);

    return 0;

}
