#include "../include/symbolTable.hpp"
#include <string>
#include <unordered_map>

SymbolTable::SymbolTable() {
    // predefined symbols
    table.reserve(23);

    table["SP"] = 0;
    table["LCL"] = 1;
    table["ARG"] = 2;
    table["THIS"] = 3;
    table["THAT"] = 4;

    for (int i = 0; i < 16; i++) {
        table.emplace("R" + std::to_string(i), i);
    }
    
    table["SCREEN"] = 16384;
    table["KDB"] = 24576;
}


void SymbolTable::addEntry(const std::string& symbol, int address) {
    table.insert({symbol, address});
}


bool SymbolTable::contains(const std::string& symbol) const {
    auto got = table.find(symbol);

    if (got == table.end()) {
        return false;
    }

    return true;
}

/*
    Assumes the symbol exists
*/
int SymbolTable::getAddress(const std::string& symbol) const {
    auto got = table.find(symbol);

    return got->second;
}

