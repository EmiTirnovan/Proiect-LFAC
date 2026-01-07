#include "SymTable.h"
#include <fstream>
#include <iostream>

using namespace std;

SymTable::SymTable(string name, SymTable* parent) : scopeName(name), parent(parent) {}

SymTable::~SymTable() {
    symbols.clear();
    runtimeValues.clear();
}

bool SymTable::addSymbol(IdInfo info) {
    if (symbols.find(info.name) != symbols.end())
        return false;

    symbols[info.name] = info;
    initDefaultValueIfVariable(info);
    return true;
}

void SymTable::updateSymbol(const IdInfo& info) {
    symbols[info.name] = info;
}

IdInfo* SymTable::lookup(string name) {
    auto it = symbols.find(name);
    if (it != symbols.end())
        return &it->second;
    if (parent)
        return parent->lookup(name);
    return nullptr;
}

SymTable* SymTable::getParent() { return parent; }
string SymTable::getScopeName() { return scopeName; }

void SymTable::printTable() {
    ofstream fout("tables.txt", ios::app);
    if(!fout.is_open()) return;
    
    fout << "Scope: " << scopeName << "\n";
    for (const auto& pair : symbols) {
        fout << "Name: " << pair.second.name << ", Kind: " << pair.second.kind;
        if (pair.second.kind == VARIABLE) {
             if (runtimeValues.count(pair.second.name))
                 fout << " Val: " << runtimeValues[pair.second.name].toString();
        }
        fout << "\n";
    }
    fout << "Runtime Values Dump:\n";
    for(auto& rv : runtimeValues) {
        if (rv.first.find('.') != string::npos) {
            fout << "  " << rv.first << " = " << rv.second.toString() << "\n";
        }
    }
    fout << "--------------------------\n";
    fout.close();
}

void SymTable::initDefaultValueIfVariable(const IdInfo& info) {
    if (info.kind != VARIABLE) return;
    ValueType t = stringToType(info.type);
    if (runtimeValues.find(info.name) == runtimeValues.end()) {
        runtimeValues[info.name] = Value::defaultFor(t);
    }
}

ValueType SymTable::getValueType(const string& name, bool* ok) {
    IdInfo* info = lookup(name);
    if (!info) {
        if (ok) *ok = false;
        return ValueType::UNKNOWN;
    }
    if (ok) *ok = true;
    return stringToType(info->type);
}

Value SymTable::getValue(const string& name, bool* ok) {
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->runtimeValues.count(name)) {
            if (ok) *ok = true;
            return s->runtimeValues[name];
        }
    }
    size_t dotPos = name.find('.');
    if (dotPos != string::npos) {
        string baseName = name.substr(0, dotPos);
        for (SymTable* s = this; s != nullptr; s = s->parent) {
            if (s->symbols.count(baseName)) {
                if (ok) *ok = true;
                return Value();
            }
        }
    }
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->symbols.count(name)) {
            IdInfo& info = s->symbols[name];
            Value def = Value::defaultFor(stringToType(info.type));
            s->runtimeValues[name] = def;
            if (ok) *ok = true;
            return def;
        }
    }

    if (ok) *ok = false;
    return Value();
}

bool SymTable::setValue(const string& name, const Value& v) {
    size_t dotPos = name.find('.');
    if (dotPos != string::npos) {
        string baseName = name.substr(0, dotPos);
        for (SymTable* s = this; s != nullptr; s = s->parent) {
            if (s->symbols.count(baseName)) {
                s->runtimeValues[name] = v;
                return true;
            }
        }
        return false;
    }
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->symbols.count(name)) {
            s->runtimeValues[name] = v;
            return true;
        }
    }
    return false;
}