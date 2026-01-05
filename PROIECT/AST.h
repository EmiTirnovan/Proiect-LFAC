#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "Value.h"

class SymTable;

class ASTNode {
public:
    std::string label;
    ValueType exprType {ValueType::UNKNOWN};
    ASTNode* left {nullptr};
    ASTNode* right {nullptr};

    ASTNode(std::string lbl, ValueType t, ASTNode* l = nullptr, ASTNode* r = nullptr)
        : label(std::move(lbl)), exprType(t), left(l), right(r) {}

    ~ASTNode() {
        delete left;
        delete right;
    }

    static ASTNode* literal(Value v);
    static ASTNode* id(const std::string& name, ValueType t);
    static ASTNode* other(ValueType t);

    static ASTNode* makeBinary(const std::string& op, ASTNode* l, ASTNode* r, int line, std::string& err);
    static ASTNode* makeUnary(const std::string& op, ASTNode* x, int line, std::string& err);
    static ASTNode* makeCompare(const std::string& op, ASTNode* l, ASTNode* r, int line, std::string& err);
    static ASTNode* makeAssign(ASTNode* idNode, ASTNode* expr, int line, std::string& err);
    static ASTNode* makePrint(ASTNode* expr);

    Value eval(SymTable* scope, std::ostream& out, std::string& err, int line) const;
};