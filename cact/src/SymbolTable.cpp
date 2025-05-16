#include "include/SymbolTable.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// --- Type Implementation ---
/**
 * @brief Converts a type to its string representation
 * 
 * This method produces a readable string representation of a type,
 * including basic types, array types with dimensions, and function types
 * with return type and parameter types.
 * 
 * @return A string representing the type (with 'const' prefix if applicable)
 */
std::string Type::toString() const {
    std::string baseStr;
    switch (baseType) {
        case INT: baseStr = "int"; break;
        case FLOAT: baseStr = "float"; break;
        case CHAR: baseStr = "char"; break;
        case VOID: baseStr = "void"; break;
        case ARRAY: {
            baseStr = (elementType ? elementType->toString() : "unknown_element_type");
            for (size_t i = 0; i < dimensions.size(); ++i) {
                int dim = dimensions[i];
                baseStr += "[";
                if (dim == -1) {
                    baseStr += "";
                } else {
                    baseStr += std::to_string(dim);
                }
                baseStr += "]";
            }
            break;
        }
        case FUNCTION:
            baseStr = (elementType ? elementType->toString() : "unknown_ret_type");
            baseStr += "(";
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                baseStr += paramTypes[i]->toString();
                if (i < paramTypes.size() - 1) baseStr += ", ";
            }
            baseStr += ")";
            break;
        case ERROR_TYPE: baseStr = "error_type"; break;
        case UNKNOWN: baseStr = "unknown_type"; break;
        default: baseStr = "undefined_base_type"; break;
    }
    return (isConst ? "const " : "") + baseStr;
}

/**
 * @brief Compares array dimensions for type equality checking
 * 
 * This method compares two arrays of dimension sizes to determine if they
 * represent compatible array types. The first dimension is allowed to be
 * unspecified (-1) for array parameters.
 * 
 * @param expected The expected array dimensions
 * @param actual The actual array dimensions to check against
 * @return true if dimensions are compatible, false otherwise
 */
bool Type::compareArrayDimensions(const std::vector<int>& expected, const std::vector<int>& actual) const {
    if (expected.size() != actual.size()) {
        return false;
    }
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i == 0 && (expected[i] == -1 || actual[i] == -1)) {
            continue;
        }
        if (expected[i] != actual[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Compares two types for semantic equality
 * 
 * This method determines if two types are semantically equivalent.
 * For array types, it recursively compares element types and dimensions.
 * For function types, it compares return types and parameter types.
 * 
 * @param other The type to compare against
 * @return true if types are semantically equal, false otherwise
 */
bool Type::equals(const Type& other) const {
    if (baseType != other.baseType) return false;
    
    // For initialization and assignments, a const value can be assigned to a non-const variable
    // but a non-const value cannot be assigned to a const variable
    if (isConst && !other.isConst && baseType != FUNCTION) {
        return false;
    }
    
    switch (baseType) {
        case ARRAY: {
            if (!elementType || !other.elementType) return false;
            if (!elementType->equals(*other.elementType)) return false;
            return compareArrayDimensions(dimensions, other.dimensions);
        }
        case FUNCTION:
            if (!elementType || !other.elementType || !elementType->equals(*other.elementType)) return false;
            if (paramTypes.size() != other.paramTypes.size()) return false;
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                if (!paramTypes[i] || !other.paramTypes[i] || !paramTypes[i]->equals(*other.paramTypes[i])) return false;
            }
            return true;
        default:
            return true;
    }
}

// --- Scope Implementation ---
/**
 * @brief Defines a symbol in the current scope
 * 
 * This method attempts to add a symbol to the current scope's symbol table.
 * It handles redefinition of symbols, with special treatment for function definitions.
 * 
 * @param name The name of the symbol to define
 * @param symbol Information about the symbol being defined
 * @return true if the symbol was successfully defined, false if a conflicting definition exists
 */
bool Scope::define(const std::string& name, std::shared_ptr<SymbolInfo> symbol) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        if ((it->second->kind == SymbolInfo::FUNCTION_DEF && symbol->kind == SymbolInfo::FUNCTION_DEF) ||
            (it->second->kind != SymbolInfo::FUNCTION_DEF && symbol->kind != SymbolInfo::FUNCTION_DEF)) {
            return false;
        }
    }
    symbols[name] = symbol;
    return true;
}

/**
 * @brief Resolves a symbol name in the current scope or parent scopes
 * 
 * This method looks up a symbol name in the current scope and, if not found,
 * recursively searches parent scopes until either the symbol is found or
 * there are no more parent scopes.
 * 
 * @param name The name of the symbol to resolve
 * @return The symbol information if found, nullptr otherwise
 */
std::shared_ptr<SymbolInfo> Scope::resolve(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    if (parent_scope) {
        return parent_scope->resolve(name);
    }
    return nullptr;
}

/**
 * @brief Resolves a symbol name in the current scope only
 * 
 * This method looks up a symbol name in the current scope only,
 * without checking parent scopes.
 * 
 * @param name The name of the symbol to resolve
 * @return The symbol information if found in current scope, nullptr otherwise
 */
std::shared_ptr<SymbolInfo> Scope::resolveCurrent(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    return nullptr;
}
