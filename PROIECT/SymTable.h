#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum IdKind { VARIABLE, FUNCTION, CLASS_NAME };

class IdInfo{
public:
    string name;
    string type;
    string value;
    IdKind kind;
    vector<string> param_types;
    IdInfo(){}
    IdInfo(string name,string type,IdKind kind = VARIABLE , string value=""):name(name),type(type),kind(kind),value(value){}
};

class SymTable{
    SymTable* parent;
    map<string,IdInfo> symbols;
    string scopeName;
public:
    SymTable (string name,SymTable* parent = nullptr);
    ~SymTable();
    bool addSymbol(IdInfo info);
    IdInfo* lookup(string name);
    SymTable* getParent();
    string getScopeName();
    void printTable();
};