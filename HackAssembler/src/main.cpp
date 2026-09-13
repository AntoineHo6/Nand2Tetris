#include <iostream>
#include <fstream>
#include <string>
#include "parser.cpp"

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    return 0;
}