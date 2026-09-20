#pragma once
#include <string>
#include <unordered_map>

class SymbolTable {
    public:
        SymbolTable();
        void addEntry(const std::string& symbol, int address);
        bool contains(const std::string& symbol) const;
        int getAddress(const std::string& symbol) const;
    
    private:
        std::unordered_map<std::string, int> table;
};