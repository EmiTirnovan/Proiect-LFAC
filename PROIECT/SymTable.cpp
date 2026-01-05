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
             // Afisam si valorile simple
             if (runtimeValues.count(pair.second.name))
                 fout << " Val: " << runtimeValues[pair.second.name].toString();
        }
        fout << "\n";
    }
    // Debug: afisam si valorile runtime "orfane" (campuri de obiecte)
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

// MODIFICAT: Suport pentru campuri (dot notation)
Value SymTable::getValue(const string& name, bool* ok) {
    // 1. Cautam valoarea exacta in ierarhia de scope-uri
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->runtimeValues.count(name)) {
            if (ok) *ok = true;
            return s->runtimeValues[name];
        }
    }
    
    // 2. Daca e camp (contine .), verificam daca obiectul de baza exista
    size_t dotPos = name.find('.');
    if (dotPos != string::npos) {
        string baseName = name.substr(0, dotPos);
        for (SymTable* s = this; s != nullptr; s = s->parent) {
            // Daca gasim obiectul "p" declarat in acest scope
            if (s->symbols.count(baseName)) {
                // Returnam default (lazy init pentru campuri)
                if (ok) *ok = true;
                return Value(); // Sau Value::defaultFor(...) daca am sti tipul
            }
        }
    }

    // 3. Fallback standard
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->symbols.count(name)) {
            // Exista simbolul, dar nu are runtime value (poate neinitializat explicit)
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

// MODIFICAT: Suport pentru campuri
bool SymTable::setValue(const string& name, const Value& v) {
    // 1. Daca e camp (contine .)
    size_t dotPos = name.find('.');
    if (dotPos != string::npos) {
        string baseName = name.substr(0, dotPos);
        // Cautam unde este declarat obiectul "p" si salvam valoarea "p.age" in acel scope
        for (SymTable* s = this; s != nullptr; s = s->parent) {
            if (s->symbols.count(baseName)) {
                s->runtimeValues[name] = v;
                return true;
            }
        }
        return false; // Obiectul de baza nu exista
    }

    // 2. Logic standard
    for (SymTable* s = this; s != nullptr; s = s->parent) {
        if (s->symbols.count(name)) {
            s->runtimeValues[name] = v;
            return true;
        }
    }
    return false;
}