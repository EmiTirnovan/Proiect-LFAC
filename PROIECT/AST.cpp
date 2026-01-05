#include "AST.h"
#include "SymTable.h"
#include <cctype>
#include <stdexcept>
#include <iostream>

ASTNode* ASTNode::literal(Value v) {
    return new ASTNode(v.toString(), v.type);
}

ASTNode* ASTNode::id(const std::string& name, ValueType t) {
    return new ASTNode(name, t);
}

ASTNode* ASTNode::other(ValueType t) {
    return new ASTNode("OTHER", t);
}

ASTNode* ASTNode::makeBinary(const std::string& op, ASTNode* l, ASTNode* r, int line, std::string& err) {
    if (!l || !r) { err = "Linia " + std::to_string(line) + ": operanzi lipsa"; return nullptr; }
    if (l->exprType != r->exprType) {
        err = "Linia " + std::to_string(line) + ": operanzi cu tipuri diferite";
        return nullptr;
    }
    if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (l->exprType == ValueType::STRING && op != "+") {
            err = "Linia " + std::to_string(line) + ": doar + permis pe string";
            return nullptr;
        }
        return new ASTNode(op, l->exprType, l, r);
    }
    if (op == "&&" || op == "||") {
        if (l->exprType != ValueType::BOOL) {
            err = "Linia " + std::to_string(line) + ": &&/|| necesita bool";
            return nullptr;
        }
        return new ASTNode(op, ValueType::BOOL, l, r);
    }
    return nullptr;
}

ASTNode* ASTNode::makeUnary(const std::string& op, ASTNode* x, int line, std::string& err) {
    if (!x) return nullptr;
    if (op == "!" && x->exprType == ValueType::BOOL) {
        return new ASTNode(op, ValueType::BOOL, x, nullptr);
    }
    return nullptr;
}

ASTNode* ASTNode::makeCompare(const std::string& op, ASTNode* l, ASTNode* r, int line, std::string& err) {
    if (!l || !r) return nullptr;
    if (l->exprType != r->exprType) {
        err = "Linia " + std::to_string(line) + ": comparatie intre tipuri diferite";
        return nullptr;
    }
    return new ASTNode(op, ValueType::BOOL, l, r);
}

ASTNode* ASTNode::makeAssign(ASTNode* idNode, ASTNode* expr, int line, std::string& err) {
    if (!idNode || !expr) return nullptr;
    // La asignare pe obiecte, tipurile pot sa difere usor daca e inheritance, dar aici simplificam
    if (idNode->exprType != expr->exprType && idNode->exprType != ValueType::UNKNOWN) {
        err = "Linia " + std::to_string(line) + ": tip diferit la assignment";
        return nullptr;
    }
    return new ASTNode(":=", idNode->exprType, idNode, expr);
}

ASTNode* ASTNode::makePrint(ASTNode* expr) {
    return new ASTNode("Print", expr ? expr->exprType : ValueType::UNKNOWN, expr, nullptr);
}

static Value applyBinary(const std::string& op, const Value& a, const Value& b) {
    if (op == "+") {
        if (a.type == ValueType::INT) return Value::fromInt(std::get<int>(a.data) + std::get<int>(b.data));
        if (a.type == ValueType::FLOAT) return Value::fromFloat(std::get<double>(a.data) + std::get<double>(b.data));
        if (a.type == ValueType::STRING) return Value::fromString(std::get<std::string>(a.data) + std::get<std::string>(b.data));
    }
    if (op == "-") {
        if (a.type == ValueType::INT) return Value::fromInt(std::get<int>(a.data) - std::get<int>(b.data));
    }
    if (op == "*") {
        if (a.type == ValueType::INT) return Value::fromInt(std::get<int>(a.data) * std::get<int>(b.data));
    }
    if (op == "/") {
        if (a.type == ValueType::INT && std::get<int>(b.data) != 0) return Value::fromInt(std::get<int>(a.data) / std::get<int>(b.data));
    }
    if (op == "&&") return Value::fromBool(std::get<bool>(a.data) && std::get<bool>(b.data));
    if (op == "||") return Value::fromBool(std::get<bool>(a.data) || std::get<bool>(b.data));
    return Value();
}

static Value applyCompare(const std::string& op, const Value& a, const Value& b) {
    if (a.type == ValueType::INT) {
        int x = std::get<int>(a.data), y = std::get<int>(b.data);
        if (op == "==") return Value::fromBool(x == y);
        if (op == "<") return Value::fromBool(x < y);
        if (op == ">") return Value::fromBool(x > y);
        // ... alte operatori
    }
    return Value::fromBool(false);
}

// ==========================================
//              EVALUATOR
// ==========================================

Value ASTNode::eval(SymTable* scope, std::ostream& out, std::string& err, int line) const {
    
    // 1. Literal sau ID simplu (fara copii)
    if (!left && !right) {
        if (label == "OTHER") return Value::defaultFor(exprType);
        
        // Daca este ID (litera si nu e true/false)
        if (!label.empty() && std::isalpha((unsigned char)label[0]) && label != "true" && label != "false" && label != "Print" && label != "SEQ") {
            bool ok = false;
            Value v = scope->getValue(label, &ok);
            if (!ok) { err = "Var nedefinita " + label; return Value(); }
            return v;
        }
        // Literals
        if (exprType == ValueType::INT) return Value::fromInt(std::stoi(label));
        if (exprType == ValueType::STRING) return Value::fromString(label);
        if (exprType == ValueType::BOOL) return Value::fromBool(label == "true");
        if (exprType == ValueType::FLOAT) return Value::fromFloat(std::stof(label));
        return Value::defaultFor(exprType);
    }

    // 2. Secventa de instructiuni (blocuri IF/WHILE)
    if (label == "SEQ") {
        if (left) left->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        if (right) right->eval(scope, out, err, line);
        return Value(); // SEQ returneaza void
    }

    // 3. Atribuire (:=)
    if (label == ":=") {
        Value rv = right->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        
        // MODIFICARE: Verificam daca stanga este un acces la membru (p.age)
        if (left->label == ".") {
            std::string objName = left->left->label;
            std::string fieldName = left->right->label;
            // Construim cheia compusa "p.age"
            std::string compositeKey = objName + "." + fieldName;
            
            // Setam valoarea (folosind o logica extinsa in SymTable sau pur si simplu fortand)
            bool ok = scope->setValue(compositeKey, rv);
            if (!ok) {
               // Daca setValue esueaza standard, incercam fallback pentru campuri
               // (vezi modificarea din SymTable.cpp)
               err = "Eroare la setarea campului " + compositeKey;
            }
            return rv;
        }

        // Atribuire standard (variabila simpla)
        scope->setValue(left->label, rv);
        return rv;
    }

    // 4. Acces membru (.)
    if (label == ".") {
        // Nu evaluam copiii standard! Evaluam conceptul de "p.age"
        std::string objName = left->label;
        std::string fieldName = right->label;
        std::string compositeKey = objName + "." + fieldName;
        
        bool ok = false;
        Value v = scope->getValue(compositeKey, &ok);
        if (!ok) { 
            // Daca nu exista inca (ex: neinitializat), returnam default pt tip
            return Value::defaultFor(exprType);
        }
        return v;
    }

    // 5. Instructiunea PRINT
    if (label == "Print") {
        Value v = left->eval(scope, out, err, line);
        out << v.toString() << "\n";
        return v;
    }

    // 6. IF Statement
    if (label == "If") {
        Value cond = left->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        
        // Executam blocul (right) doar daca conditia e true
        if (cond.type == ValueType::BOOL && std::get<bool>(cond.data)) {
            if (right) right->eval(scope, out, err, line);
        }
        return Value();
    }

    // 7. WHILE Statement
    if (label == "While") {
        while(true) {
            Value cond = left->eval(scope, out, err, line);
            if (!err.empty()) return Value();
            
            if (cond.type == ValueType::BOOL && std::get<bool>(cond.data)) {
                if (right) right->eval(scope, out, err, line);
                if (!err.empty()) return Value();
            } else {
                break;
            }
        }
        return Value();
    }

    // 8. Operatori binari
    Value a = left ? left->eval(scope, out, err, line) : Value();
    if(!err.empty()) return Value();
    Value b = right ? right->eval(scope, out, err, line) : Value();
    if(!err.empty()) return Value();
    
    if (label == "+" || label == "-" || label == "*" || label == "/" || label == "&&" || label == "||")
        return applyBinary(label, a, b);
    
    return applyCompare(label, a, b);
}