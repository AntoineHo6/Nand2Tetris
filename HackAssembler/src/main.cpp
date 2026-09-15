#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "parser.cpp"

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
        return;
    }

    Parser parser(filePath);
    
    while (parser.hasMoreLines()) {
        parser.advance();

        // write to hackFile
        // hackFile << binaryLine << '\n';
    }

    return 0;
}

