#include "AST.h"
#include "SymTable.h"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <string>

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
    if (!l || !r) { 
        err = "Linia " + std::to_string(line) + ": Lipsesc operanzii pentru operatorul '" + op + "'"; 
        return nullptr; 
    }
    if (l->exprType != r->exprType) {
        err = "Linia " + std::to_string(line) + ": Tipuri incompatibile pentru operatorul '" + op + "'. " +
              "Stanga este '" + typeToString(l->exprType) + "', iar Dreapta este '" + typeToString(r->exprType) + "'.";
        return nullptr;
    }
    if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (l->exprType == ValueType::STRING) {
            if (op != "+") {
                err = "Linia " + std::to_string(line) + ": Operatorul '" + op + "' nu este permis pe string-uri (doar '+').";
                return nullptr;
            }
        }
        else if (l->exprType == ValueType::BOOL) {
            err = "Linia " + std::to_string(line) + ": Nu se pot efectua operatii aritmetice ('" + op + "') pe tipul bool.";
            return nullptr;
        }
        return new ASTNode(op, l->exprType, l, r);
    }
    if (op == "&&" || op == "||") {
        if (l->exprType != ValueType::BOOL) {
            err = "Linia " + std::to_string(line) + ": Operatorul '" + op + "' necesita operanzi de tip BOOL. " +
                  "S-a primit: " + typeToString(l->exprType);
            return nullptr;
        }
        return new ASTNode(op, ValueType::BOOL, l, r);
    }

    return nullptr;
}

ASTNode* ASTNode::makeUnary(const std::string& op, ASTNode* x, int line, std::string& err) {
    if (!x) return nullptr;
    if (op == "!" && x->exprType != ValueType::BOOL) {
        err = "Linia " + std::to_string(line) + ": Operatorul '!' se aplica doar pe BOOL. S-a primit: " + typeToString(x->exprType);
        return nullptr;
    }
    if (op == "-" && (x->exprType != ValueType::INT && x->exprType != ValueType::FLOAT)) {
        err = "Linia " + std::to_string(line) + ": Operatorul '-' unar necesita INT sau FLOAT.";
        return nullptr;
    }
    return new ASTNode(op, x->exprType, x, nullptr);
}

ASTNode* ASTNode::makeCompare(const std::string& op, ASTNode* l, ASTNode* r, int line, std::string& err) {
    if (!l || !r) return nullptr;
    if (l->exprType != r->exprType) {
        err = "Linia " + std::to_string(line) + ": Comparatie ('" + op + "') intre tipuri diferite: " +
              typeToString(l->exprType) + " vs " + typeToString(r->exprType);
        return nullptr;
    }
    return new ASTNode(op, ValueType::BOOL, l, r);
}

ASTNode* ASTNode::makeAssign(ASTNode* idNode, ASTNode* expr, int line, std::string& err) {
    if (!idNode || !expr) return nullptr;
    if (idNode->exprType != expr->exprType && idNode->exprType != ValueType::UNKNOWN) {
        err = "Linia " + std::to_string(line) + ": Nu se poate atribui o valoare de tip '" + 
              typeToString(expr->exprType) + "' unei variabile de tip '" + typeToString(idNode->exprType) + "'.";;
        return nullptr;
    }
    return new ASTNode(":=", idNode->exprType, idNode, expr);
}

ASTNode* ASTNode::makePrint(ASTNode* expr) {
    return new ASTNode("Print", expr ? expr->exprType : ValueType::UNKNOWN, expr, nullptr);
}

static Value applyBinary(const std::string& op, const Value& a, const Value& b, std::string& err) {
    // tipuri incompatibile
    if (a.type != b.type) {
        err = ": Tipuri incompatibile pentru operatorul '" + op + "': " +
              typeToString(a.type) + " vs " + typeToString(b.type);
        return Value();
    }

    if (op == "+") {
        if (a.type == ValueType::INT)   return Value::fromInt(std::get<int>(a.data) + std::get<int>(b.data));
        if (a.type == ValueType::FLOAT) return Value::fromFloat(std::get<double>(a.data) + std::get<double>(b.data));
        if (a.type == ValueType::STRING) return Value::fromString(std::get<std::string>(a.data) + std::get<std::string>(b.data));
    }

    if (op == "-") {
        if (a.type == ValueType::INT)   return Value::fromInt(std::get<int>(a.data) - std::get<int>(b.data));
        if (a.type == ValueType::FLOAT) return Value::fromFloat(std::get<double>(a.data) - std::get<double>(b.data));
    }

    if (op == "*") {
        if (a.type == ValueType::INT)   return Value::fromInt(std::get<int>(a.data) * std::get<int>(b.data));
        if (a.type == ValueType::FLOAT) return Value::fromFloat(std::get<double>(a.data) * std::get<double>(b.data));
    }

    if (op == "/") {
        if (a.type == ValueType::INT) {
            int denom = std::get<int>(b.data);
            if (denom == 0) { err = ": Impartire la 0"; return Value(); }
            return Value::fromInt(std::get<int>(a.data) / denom);
        }
        if (a.type == ValueType::FLOAT) {
            double denom = std::get<double>(b.data);
            if (denom == 0.0) { err = ": Impartire la 0.0"; return Value(); }
            return Value::fromFloat(std::get<double>(a.data) / denom);
        }
    }

    if (op == "&&") {
        if (a.type != ValueType::BOOL) { err = ": '&&' doar pe BOOL"; return Value(); }
        return Value::fromBool(std::get<bool>(a.data) && std::get<bool>(b.data));
    }

    if (op == "||") {
        if (a.type != ValueType::BOOL) { err = ": '||' doar pe BOOL"; return Value(); }
        return Value::fromBool(std::get<bool>(a.data) || std::get<bool>(b.data));
    }

    err = ": Operator binar neimplementat '" + op + "'";
    return Value();
}


static Value applyCompare(const std::string& op, const Value& a, const Value& b) {
    if (a.type == ValueType::INT) {
        int x = std::get<int>(a.data), y = std::get<int>(b.data);
        if (op == "==") return Value::fromBool(x == y);
        if (op == "<") return Value::fromBool(x < y);
        if (op == ">") return Value::fromBool(x > y);
        if (op == "<=") return Value::fromBool(x <= y);
        if (op == ">=") return Value::fromBool(x >= y);
        if (op == "!=") return Value::fromBool(x != y);
    }
    return Value::fromBool(false);
}

Value ASTNode::eval(SymTable* scope, std::ostream& out, std::string& err, int line) const {
    if (!left && !right) {
        if (label == "OTHER") return Value::defaultFor(exprType);
        if (!label.empty() && std::isalpha((unsigned char)label[0]) && label != "true" && label != "false" && label != "Print" && label != "SEQ") {
            bool ok = false;
            Value v = scope->getValue(label, &ok);
            if (!ok) { err = ": Variabila '" + label + "' este nedefinita"; return Value(); }
            return v;
        }
        if (exprType == ValueType::INT) return Value::fromInt(std::stoi(label));
        if (exprType == ValueType::STRING) return Value::fromString(label);
        if (exprType == ValueType::BOOL) return Value::fromBool(label == "true");
        if (exprType == ValueType::FLOAT) return Value::fromFloat(std::stof(label));
        return Value::defaultFor(exprType);
    }
    if (label == "SEQ") {
        if (left) left->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        if (right) right->eval(scope, out, err, line);
        return Value();
    }
    if (label == ":=") {
        Value rv = right->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        if (left->label == ".") {
            std::string objName = left->left->label;
            std::string fieldName = left->right->label;
            std::string compositeKey = objName + "." + fieldName;
            bool ok = scope->setValue(compositeKey, rv);
            if (!ok) {
               err = ": Nu s-a putut seta campul '" + fieldName + "' al obiectului '" + objName + "'.";
            }
            return rv;
        }
        scope->setValue(left->label, rv);
        return rv;
    }
    if (label == ".") {
        std::string objName = left->label;
        std::string fieldName = right->label;
        std::string compositeKey = objName + "." + fieldName;
        bool ok = false;
        Value v = scope->getValue(compositeKey, &ok);
        if (!ok) { 
            return Value::defaultFor(exprType);
        }
        return v;
    }
    if (label == "Print") {
        Value v = left->eval(scope, out, err, line);
        out << v.toString() << "\n";
        return v;
    }
    if (label == "If") {
        Value cond = left->eval(scope, out, err, line);
        if (!err.empty()) return Value();
        if (cond.type == ValueType::BOOL && std::get<bool>(cond.data)) {
            if (right) right->eval(scope, out, err, line);
        }
        return Value();
    }
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
    Value a = left ? left->eval(scope, out, err, line) : Value();
if(!err.empty()) return Value();
if (!right) {
    if (label == "-") {
        if (a.type == ValueType::INT)   return Value::fromInt(-std::get<int>(a.data));
        if (a.type == ValueType::FLOAT) return Value::fromFloat(-std::get<double>(a.data));
        err = ": Minus unar pe tip invalid (" + typeToString(a.type) + ")";
        return Value();
    }
    if (label == "!") {
        if (a.type == ValueType::BOOL) return Value::fromBool(!std::get<bool>(a.data));
        err = ": Operatorul '!' pe tip invalid (" + typeToString(a.type) + ")";
        return Value();
    }
    return Value();
}
Value b = right->eval(scope, out, err, line);
if(!err.empty()) return Value();

if (label == "+" || label == "-" || label == "*" || label == "/" || label == "&&" || label == "||")
    return applyBinary(label, a, b, err);

return applyCompare(label, a, b);

}