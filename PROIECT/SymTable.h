#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "Value.h"

using namespace std;

enum IdKind { VARIABLE, FUNCTION, CLASS_NAME };

class SymTable;

class IdInfo{
public:
    string name;
    string type;
    string value;
    IdKind kind;
    vector<string> param_types;
    SymTable* defScope = nullptr;

    IdInfo(){}
    IdInfo(string name, string type, IdKind kind = VARIABLE, string value="")
        : name(name), type(type), kind(kind), value(value), defScope(nullptr) {}
};

class SymTable{
    SymTable* parent;
    map<string,IdInfo> symbols;
    string scopeName;
    map<string, Value> runtimeValues;

public:
    SymTable (string name, SymTable* parent = nullptr);
    ~SymTable();

    bool addSymbol(IdInfo info);
    void updateSymbol(const IdInfo& info);
    IdInfo* lookup(string name);
    SymTable* getParent();
    string getScopeName();
    void printTable();

    bool setValue(const string& name, const Value& v);
    Value getValue(const string& name, bool* ok = nullptr);
    ValueType getValueType(const string& name, bool* ok = nullptr);
    void initDefaultValueIfVariable(const IdInfo& info);
};