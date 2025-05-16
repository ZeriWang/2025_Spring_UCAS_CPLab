#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "antlr4-runtime.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>

// Forward declarations
class Scope;

/**
 * @brief Type representation class
 *
 * This class represents types in the CACT language, including basic types,
 * array types, and function types with appropriate type-checking methods.
 */
struct Type {
    enum Base { UNKNOWN, INT, FLOAT, CHAR, VOID, ARRAY, FUNCTION, ERROR_TYPE } baseType;
    std::shared_ptr<Type> elementType; // For arrays or function return type
    std::vector<int> dimensions;       // For arrays, stores sizes. -1 for implicit first dim in param.
    std::vector<std::shared_ptr<Type>> paramTypes; // For functions

    bool isConst = false; // Indicates if the type itself is const (e.g. const int)
    bool isLValue = false; // Indicates if an expression yields an LValue

    Type(Base b = UNKNOWN) : baseType(b) {}

    static std::shared_ptr<Type> getInt(bool is_const = false) { 
        auto t = std::make_shared<Type>(INT); 
        t->isConst = is_const; 
        return t; 
    }
    static std::shared_ptr<Type> getFloat(bool is_const = false) { 
        auto t = std::make_shared<Type>(FLOAT); 
        t->isConst = is_const; 
        return t; 
    }
    static std::shared_ptr<Type> getChar(bool is_const = false) { 
        auto t = std::make_shared<Type>(CHAR); 
        t->isConst = is_const; 
        return t; 
    }
    static std::shared_ptr<Type> getVoid() { return std::make_shared<Type>(VOID); }
    static std::shared_ptr<Type> getError() { return std::make_shared<Type>(ERROR_TYPE); }
    static std::shared_ptr<Type> getArray(std::shared_ptr<Type> elemType, const std::vector<int>& dims, bool is_const = false) {
        auto t = std::make_shared<Type>(ARRAY);
        t->elementType = elemType;
        t->dimensions = dims;
        t->isConst = is_const; // Const applies to elements for arrays in C-like languages
        return t;
    }
    static std::shared_ptr<Type> getFunction(std::shared_ptr<Type> retType, const std::vector<std::shared_ptr<Type>>& pTypes) {
        auto t = std::make_shared<Type>(FUNCTION);
        t->elementType = retType; // Using elementType for return type
        t->paramTypes = pTypes;
        return t;
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
    bool compareArrayDimensions(const std::vector<int>& expected, const std::vector<int>& actual) const;

    /**
     * @brief Converts a type to its string representation
     *
     * This method produces a readable string representation of a type,
     * including basic types, array types with dimensions, and function types
     * with return type and parameter types.
     *
     * @return A string representing the type (with 'const' prefix if applicable)
     */
    std::string toString() const;

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
    bool equals(const Type& other) const;
};

/**
 * @brief Symbol information class
 *
 * This class represents information about symbols in the symbol table,
 * including variables, constants, function definitions, and parameters.
 */
struct SymbolInfo {
    std::string name;
    std::shared_ptr<Type> type;
    enum Kind { VARIABLE, CONSTANT, FUNCTION_DEF, PARAMETER } kind;
    antlr4::ParserRuleContext* definitionNode; // For location, redefinition checks
    bool isInitialized = false; 
    // For compile-time constant values (optional)
    std::variant<int, float, char> constValue; 
    bool hasConstValue = false;

    SymbolInfo(std::string n, std::shared_ptr<Type> t, Kind k, antlr4::ParserRuleContext* node)
        : name(std::move(n)), type(std::move(t)), kind(k), definitionNode(node) {
        if (k == CONSTANT) type->isConst = true;
    }
};

/**
 * @brief Scope management class
 *
 * This class represents a lexical scope in the program, managing symbols
 * defined within the scope and providing methods to look up symbols in the
 * current scope or parent scopes.
 */
class Scope {
public:
    /**
     * @brief Constructor for a new scope
     *
     * @param parent The parent scope, or nullptr for global scope
     * @param isFunctionScope Whether this scope is a function body
     * @param isLoopScope Whether this scope is a loop body
     */
    Scope(Scope* parent = nullptr, bool isFunctionScope = false, bool isLoopScope = false) 
        : parent_scope(parent), is_function_scope(isFunctionScope), is_loop_scope(isLoopScope) {}

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
    bool define(const std::string& name, std::shared_ptr<SymbolInfo> symbol);

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
    std::shared_ptr<SymbolInfo> resolve(const std::string& name) const;

    /**
     * @brief Resolves a symbol name in the current scope only
     *
     * This method looks up a symbol name in the current scope only,
     * without checking parent scopes.
     *
     * @param name The name of the symbol to resolve
     * @return The symbol information if found in current scope, nullptr otherwise
     */
    std::shared_ptr<SymbolInfo> resolveCurrent(const std::string& name) const;

    /**
     * @brief Gets the parent scope
     *
     * @return Pointer to the parent scope, or nullptr if this is the global scope
     */
    Scope* getParent() const { return parent_scope; }

    /**
     * @brief Checks if this scope is a function body
     *
     * @return true if this scope is a function body, false otherwise
     */
    bool isFunction() const { return is_function_scope; }

    /**
     * @brief Checks if this scope or any parent scope is a loop body
     *
     * This method determines if the current scope or any of its parent
     * scopes is marked as a loop body, which is important for validating
     * break and continue statements.
     *
     * @return true if this scope or any parent is a loop body, false otherwise
     */
    bool isLoop() const { 
        if (is_loop_scope) return true;
        if (parent_scope) return parent_scope->isLoop();
        return false;
    }

private:
    std::map<std::string, std::shared_ptr<SymbolInfo>> symbols;
    Scope* parent_scope;
    bool is_function_scope;
    bool is_loop_scope;
};

#endif // SYMBOL_TABLE_H
