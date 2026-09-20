#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <bitset>

#include "parser.cpp"
#include "code.cpp"

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!\n" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];

    std::filesystem::path p(filePath);
    std::string fileStem = p.stem().string();

    std::ofstream hackFile(fileStem + ".hack");

    if (!hackFile.is_open()) {
        std::cerr << "Error: Could not create hack file!\n";
        return 1;
    }

    Parser parser(filePath);
    
    while (parser.hasMoreLines()) {
        parser.advance();

        std::string binaryLine;
        switch(parser.instructionType()) {
            case InstrType::A_INSTRUCTION: {
                int value = std::stoi(parser.symbol());
                binaryLine = "0" + std::bitset<15>(value).to_string();
                break;
            }
            case InstrType::C_INSTRUCTION: {
                binaryLine = "111" + Code::comp(parser.comp())
                                   + Code::dest(parser.dest()) 
                                   + Code::jump(parser.jump());
                break;                
            }
            case InstrType::L_INSTRUCTION: {
                // TODO
                continue;
                break;
            }
        }

        // write to hackFile
        hackFile << binaryLine << '\n';
    }

    return 0;
}

std::string stringTo15BitBinary(const std::string& myString) {

}

