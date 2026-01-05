#pragma once

#include <string>
#include <variant>
#include <sstream>

enum class ValueType { INT, FLOAT, STRING, BOOL, VOID, UNKNOWN };

inline std::string typeToString(ValueType t) {
    switch (t) {
        case ValueType::INT: return "int";
        case ValueType::FLOAT: return "float";
        case ValueType::STRING: return "string";
        case ValueType::BOOL: return "bool";
        case ValueType::VOID: return "void";
        default: return "unknown";
    }
}

inline ValueType stringToType(const std::string& s) {
    if (s == "int") return ValueType::INT;
    if (s == "float") return ValueType::FLOAT;
    if (s == "string") return ValueType::STRING;
    if (s == "bool") return ValueType::BOOL;
    if (s == "void") return ValueType::VOID;
    return ValueType::UNKNOWN;
}

class Value {
public:
    ValueType type {ValueType::UNKNOWN};
    std::variant<int, double, std::string, bool> data;

    Value() : type(ValueType::UNKNOWN), data(0) {}

    static Value fromInt(int v) {
        Value x; x.type = ValueType::INT; x.data = v; return x;
    }
    static Value fromFloat(double v) {
        Value x; x.type = ValueType::FLOAT; x.data = v; return x;
    }
    static Value fromBool(bool v) {
        Value x; x.type = ValueType::BOOL; x.data = v; return x;
    }
    static Value fromString(const std::string& v) {
        Value x; x.type = ValueType::STRING; x.data = v; return x;
    }

    static Value defaultFor(ValueType t) {
        switch (t) {
            case ValueType::INT: return fromInt(0);
            case ValueType::FLOAT: return fromFloat(0.0);
            case ValueType::STRING: return fromString("");
            case ValueType::BOOL: return fromBool(false);
            case ValueType::VOID: {
                Value x; x.type = ValueType::VOID; x.data = 0; return x;
            }
            default: return Value(); // Returneaza un unknown safe
        }
    }

    std::string toString() const {
        std::ostringstream oss;
        switch (type) {
            case ValueType::INT: oss << std::get<int>(data); break;
            case ValueType::FLOAT: oss << std::get<double>(data); break;
            case ValueType::BOOL: oss << (std::get<bool>(data) ? "true" : "false"); break;
            case ValueType::STRING: oss << std::get<std::string>(data); break;
            case ValueType::VOID: oss << "<void>"; break;
            default: oss << "<unknown>"; break;
        }
        return oss.str();
    }
};