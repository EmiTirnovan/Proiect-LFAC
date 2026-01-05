#include "SymTable.h"
#include <fstream>

using namespace std;

SymTable::SymTable(string name, SymTable* parent) : scopeName(name), parent(parent) {}

SymTable::~SymTable(){
    symbols.clear();
}

bool SymTable::addSymbol(IdInfo info){
    if(symbols.count(info.name))
        return false;
    symbols[info.name] = info;
    return true;
}

IdInfo* SymTable::lookup(string name){
    if(symbols.count(name))
        return &symbols[name];
    if(parent)
        return parent->lookup(name);
    return nullptr;
}

SymTable* SymTable::getParent(){
    return parent;
}

string SymTable::getScopeName(){
    return scopeName;
}

void SymTable::printTable(){
    ofstream fout("tables.txt", ios::app);
    fout << "Scope: " << scopeName << "\n";
    for(const auto& pair : symbols){
        fout << "Name: " << pair.second.name << ", Type: " << pair.second.type << ", Kind: ";
        switch(pair.second.kind){
            case VARIABLE: fout << "VARIABLE"; break;
            case FUNCTION: fout << "FUNCTION"; break;
            case CLASS_NAME: fout << "CLASS_NAME"; break;
        }
        if(pair.second.kind == FUNCTION){
            fout << ", Param Types: ";
            for(const auto& paramType : pair.second.param_types){
                fout << paramType << " ";
            }
        }
        fout << ", Value: " << pair.second.value << "\n";
    }
    fout << "--------------------------\n";
    fout.close();
}