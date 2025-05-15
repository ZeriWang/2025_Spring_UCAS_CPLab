#include "include/SemanticAnalyzer.h"
#include "CactParser.h"
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
    if (isConst != other.isConst && baseType != FUNCTION) {
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

// --- SemanticAnalyzer Implementation ---
/**
 * @brief Constructor for the SemanticAnalyzer
 * 
 * Initializes the semantic analyzer with a reference to the parser
 * and sets up initial state for analysis.
 * 
 * @param parser_ptr Pointer to the CACT parser
 */
SemanticAnalyzer::SemanticAnalyzer(CactParser* parser_ptr) : parser(parser_ptr), currentScope(nullptr), mainFunctionFound(false) {
}

/**
 * @brief Prints all semantic errors detected during analysis
 * 
 * This method prints all semantic errors with source location information.
 * 
 * @param filename The source filename to include in error messages
 */
void SemanticAnalyzer::printErrors(const std::string& filename) const {
    for (const auto& err : errors) {
        std::cerr << filename << ":" << err.second->getLine() << ":" << err.second->getCharPositionInLine()
                  << ": error: " << err.first << std::endl;
    }
}

/**
 * @brief Creates a new scope and makes it the current scope
 * 
 * This method establishes a new lexical scope, optionally marking it as
 * a function scope or loop scope for special semantic checks.
 * 
 * @param isFunctionScope Whether the new scope is a function body
 * @param isLoopScope Whether the new scope is a loop body
 */
void SemanticAnalyzer::enterScope(bool isFunctionScope, bool isLoopScope) {
    currentScope = new Scope(currentScope, isFunctionScope, isLoopScope);
}

/**
 * @brief Exits the current scope and returns to the parent scope
 * 
 * This method cleans up the current scope and makes its parent
 * the new current scope.
 */
void SemanticAnalyzer::exitScope() {
    if (currentScope) {
        Scope* oldScope = currentScope;
        currentScope = currentScope->getParent();
        delete oldScope;
    }
}

/**
 * @brief Records a semantic error with context information
 * 
 * @param message The error message
 * @param ctx The parser rule context where the error occurred
 */
void SemanticAnalyzer::addError(const std::string& message, antlr4::ParserRuleContext* ctx) {
    if (ctx) {
        addError(message, ctx->getStart());
    } else {
        errors.push_back({message, nullptr});
    }
}
/**
 * @brief Records a semantic error with token information
 * 
 * @param message The error message
 * @param token The token where the error occurred
 */
void SemanticAnalyzer::addError(const std::string& message, antlr4::Token* token) {
    errors.push_back({message, token});
}

/**
 * @brief Extracts type information from a basic type context
 * 
 * @param ctx The basic type context to extract type from
 * @return The corresponding Type object
 */
std::shared_ptr<Type> SemanticAnalyzer::getTypeFromBasicTypeCtx(CactParser::BasicTypeContext *ctx) {
    if (ctx->Int()) return Type::getInt();
    if (ctx->Float()) return Type::getFloat();
    if (ctx->Char()) return Type::getChar();
    return Type::getError();
}

/**
 * @brief Extracts type information from a function type context
 * 
 * @param ctx The function type context to extract type from
 * @return The corresponding Type object
 */
std::shared_ptr<Type> SemanticAnalyzer::getTypeFromFunctionTypeCtx(CactParser::FunctionTypeContext *ctx) {
    if (ctx->Void()) return Type::getVoid();
    if (ctx->Int()) return Type::getInt();
    if (ctx->Float()) return Type::getFloat();
    if (ctx->Char()) return Type::getChar();
    return Type::getError();
}

// --- Visitor Implementations ---
/**
 * @brief Visits the root compilation unit node
 * 
 * This method processes the entire compilation unit, including:
 * 1. Setting up the global scope
 * 2. Registering built-in functions (print_int, get_int, etc.)
 * 3. Processing global declarations and function definitions
 * 4. Verifying the presence and signature of the main function
 * 
 * @param ctx The compilation unit context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    enterScope();
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getInt() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_int", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_int", funcSymbol);
    }
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getFloat() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_float", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_float", funcSymbol);
    }
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getChar() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_char", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_char", funcSymbol);
    }
    {
        auto returnType = Type::getInt();
        std::vector<std::shared_ptr<Type>> paramTypes = { };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("get_int", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("get_int", funcSymbol);
    }
    {
        auto returnType = Type::getFloat();
        std::vector<std::shared_ptr<Type>> paramTypes = { };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("get_float", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("get_float", funcSymbol);
    }
    {
        auto returnType = Type::getChar();
        std::vector<std::shared_ptr<Type>> paramTypes = { };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("get_char", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("get_char", funcSymbol);
    }
    for (auto* item : ctx->declaration()) {
        visitDeclaration(item);
    }
    for (auto* item : ctx->functionDefinition()) {
        visitFunctionDefinition(item);
    }
    if (!mainFunctionFound) {
        addError("Main function 'int main()' not defined.", ctx->getStop() ? ctx->getStop() : ctx->getStart());
    } else {
        if (mainFunctionSymbol) {
            if (mainFunctionSymbol->type->elementType->baseType != Type::INT) {
                addError("Main function must return 'int'.", mainFunctionSymbol->definitionNode->getStart());
            }
            if (!mainFunctionSymbol->type->paramTypes.empty()) {
                addError("Main function must not have parameters.", mainFunctionSymbol->definitionNode->getStart());
            }
        }
    }
    exitScope();
    return nullptr;
}

/**
 * @brief Processes a function definition
 * 
 * This method:
 * 1. Extracts function name, return type, and parameters
 * 2. Creates a function symbol and adds it to the current scope
 * 3. Sets up a new scope for the function body
 * 4. Processes the function body
 * 5. Verifies that non-void functions have return statements on all paths
 * 
 * @param ctx The function definition context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    std::string funcName = ctx->Identifier()->getText();
    std::shared_ptr<Type> returnType = std::any_cast<std::shared_ptr<Type>>(visitFunctionType(ctx->functionType()));

    std::vector<std::shared_ptr<Type>> paramTypesList;
    std::vector<std::shared_ptr<SymbolInfo>> paramSymbolsList;

    if (ctx->functionFormalParameters()) {
        for (auto* paramCtx : ctx->functionFormalParameters()->functionFormalParameter()) {
            std::shared_ptr<SymbolInfo> paramSymbol = std::any_cast<std::shared_ptr<SymbolInfo>>(visitFunctionFormalParameter(paramCtx));
            if (!paramSymbol || paramSymbol->type->baseType == Type::ERROR_TYPE) {
                 paramTypesList.push_back(Type::getError());
                 continue;
            }
            for(const auto& pSym : paramSymbolsList){
                if(pSym->name == paramSymbol->name){
                    addError("Redefinition of parameter '" + paramSymbol->name + "'.", paramCtx->Identifier()->getSymbol());
                    paramTypesList.push_back(Type::getError());
                    goto next_param;
                }
            }
            paramTypesList.push_back(paramSymbol->type);
            paramSymbolsList.push_back(paramSymbol);
            next_param:;
        }
    }
    
    auto funcType = Type::getFunction(returnType, paramTypesList);
    auto funcSymbol = std::make_shared<SymbolInfo>(funcName, funcType, SymbolInfo::FUNCTION_DEF, ctx);

    if (!currentScope->define(funcName, funcSymbol)) {
        addError("Redefinition of '" + funcName + "'.", ctx->Identifier()->getSymbol());
        return nullptr;
    }
    
    if (funcName == "main") {
        mainFunctionFound = true;
        mainFunctionSymbol = funcSymbol;
    }

    currentFunctionSymbol = funcSymbol;
    currentFunctionHasReturn = false;

    enterScope(true);
    for(const auto& pSym : paramSymbolsList){
        if(!currentScope->define(pSym->name, pSym)){
            addError("Failed to define parameter '" + pSym->name + "' in function scope (should be impossible).", pSym->definitionNode->getStart());
        }
    }
    visitBlock(ctx->block());
    
    if (returnType->baseType != Type::VOID && !currentFunctionHasReturn) {
        addError("Non-void function '" + funcName + "' might not return a value on all paths.", ctx->Identifier()->getSymbol());
    }

    exitScope();
    currentFunctionSymbol = nullptr;
    return nullptr;
}

/**
 * @brief Processes a constant declaration
 * 
 * This method:
 * 1. Extracts the base type for the constants
 * 2. For each constant definition:
 *    - Determines the actual type (basic or array)
 *    - Validates the initializer expression
 *    - Verifies the initializer type matches the constant's type
 *    - Stores the constant value for compile-time evaluation
 * 
 * @param ctx The constant declaration context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    baseType->isConst = true;

    for (auto* constDefCtx : ctx->constantDefinition()) {
        std::string name = constDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType;
        std::vector<int> dimensions;

        if (!constDefCtx->LeftBracket().empty()) {
            for (auto* intConst : constDefCtx->IntegerConstant()) {
                try {
                    dimensions.push_back(std::stoi(intConst->getText()));
                } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0);
                }
            }
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
            actualType->isConst = true;
        } else {
             actualType = std::make_shared<Type>(*baseType);
             actualType->isConst = true;
        }

        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::CONSTANT, constDefCtx);
        
        if (!constDefCtx->constantInitializationValue()) {
             addError("Constant '" + name + "' must be initialized.", constDefCtx->Identifier()->getSymbol());
        } else {
            expectingConstantInitializer = true;
            expectedInitializerType = actualType;
            antlrcpp::Any initValueAny = visitConstantInitializationValue(constDefCtx->constantInitializationValue());
            
            if (actualType->baseType != Type::ARRAY) {
                if (initValueAny.type() == typeid(ConstEvalResult)) {
                    ConstEvalResult initVal = std::any_cast<ConstEvalResult>(initValueAny);
                    if (!initVal.isConst) {
                        addError("Initializer for constant '" + name + "' must be a compile-time constant expression.", 
                                 constDefCtx->constantInitializationValue()->getStart());
                    } else if (!initVal.type->equals(*actualType)) {
                        addError("Initializer type '" + initVal.type->toString() + 
                                    "' does not match constant type '" + actualType->toString() + 
                                    "' for '" + name + "'.", 
                                    constDefCtx->constantInitializationValue()->getStart());
                    } else {
                        symbol->constValue = initVal.value;
                        symbol->hasConstValue = initVal.hasValue;
                    }
                } else {
                     addError("Internal error: Could not evaluate constant initializer for '" + name + "'.", 
                              constDefCtx->constantInitializationValue()->getStart());
                }
            }
            expectingConstantInitializer = false;
            expectedInitializerType = nullptr;
        }
        symbol->isInitialized = true;

        if (!currentScope->define(name, symbol)) {
            addError("Redefinition of constant '" + name + "'.", constDefCtx->Identifier()->getSymbol());
        }
    }
    return nullptr;
}

/**
 * @brief Processes a variable declaration
 * 
 * This method:
 * 1. Extracts the base type for the variables
 * 2. For each variable definition:
 *    - Determines the actual type (basic or array)
 *    - If initialized, validates the initializer expression
 *    - Verifies the initializer type matches the variable's type
 * 
 * @param ctx The variable declaration context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));

    for (auto* varDefCtx : ctx->variableDefinition()) {
        std::string name = varDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType;
        std::vector<int> dimensions;

        if (!varDefCtx->LeftBracket().empty()) {
            for (auto* intConst : varDefCtx->IntegerConstant()) {
                 try {
                    int dim = std::stoi(intConst->getText());
                    dimensions.push_back(dim);
                 } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0);
                 }
            }
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
        } else {
            actualType = std::make_shared<Type>(*baseType);
        }

        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::VARIABLE, varDefCtx);

        if (varDefCtx->constantInitializationValue()) {
            symbol->isInitialized = true;
            expectingConstantInitializer = true;
            expectedInitializerType = actualType;

            antlrcpp::Any initValueAny = visitConstantInitializationValue(varDefCtx->constantInitializationValue());

            if (actualType->baseType == Type::ARRAY) {
                if (initValueAny.type() == typeid(bool) && !std::any_cast<bool>(initValueAny)) {
                }
            } else {
                 if (initValueAny.type() == typeid(ConstEvalResult)) {
                    ConstEvalResult initVal = std::any_cast<ConstEvalResult>(initValueAny);
                    if (!initVal.isConst) {
                        addError("Initializer for variable '" + name + "' must be a compile-time constant expression.", 
                                 varDefCtx->constantInitializationValue()->getStart());
                    } else if (!initVal.type->equals(*actualType) && initVal.type->baseType != Type::ERROR_TYPE) {
                         addError("Initializer type '" + initVal.type->toString() + 
                                 "' does not match variable type '" + actualType->toString() + 
                                 "' for '" + name + "'.", 
                                 varDefCtx->constantInitializationValue()->getStart());
                    }
                } else {
                     addError("Internal error: Could not evaluate variable initializer for '" + name + "'.", 
                              varDefCtx->constantInitializationValue()->getStart());
                }
            }
            expectingConstantInitializer = false;
            expectedInitializerType = nullptr;
        } else {
            symbol->isInitialized = false;
        }

        if (!currentScope->define(name, symbol)) {
            addError("Redefinition of variable '" + name + "'.", varDefCtx->Identifier()->getSymbol());
        }
    }
    return nullptr;
}

/**
 * @brief Processes a basic type node
 * 
 * @param ctx The basic type context
 * @return The corresponding type object
 */
antlrcpp::Any SemanticAnalyzer::visitBasicType(CactParser::BasicTypeContext *ctx) {
    return getTypeFromBasicTypeCtx(ctx);
}

/**
 * @brief Processes a function return type node
 * 
 * @param ctx The function type context
 * @return The corresponding type object
 */
antlrcpp::Any SemanticAnalyzer::visitFunctionType(CactParser::FunctionTypeContext *ctx) {
    return getTypeFromFunctionTypeCtx(ctx);
}

/**
 * @brief Processes a function formal parameter
 * 
 * This method extracts and validates information about a function parameter:
 * 1. Determines the parameter type (basic or array)
 * 2. Handles special array parameter syntax (first dimension can be omitted)
 * 3. Creates a parameter symbol with the determined type
 * 
 * @param ctx The function formal parameter context
 * @return A SymbolInfo object representing the parameter
 */
antlrcpp::Any SemanticAnalyzer::visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> actualType = baseType;

    if (!ctx->LeftBracket().empty()) {
        std::vector<int> dimensions;
        int bracketPairCount = ctx->LeftBracket().size();
        auto intConstants = ctx->IntegerConstant();
        bool firstDimImplicit = intConstants.size() < bracketPairCount;
        for (int i = 0; i < bracketPairCount; i++) {
            int dimension = -1;
            if (i == 0 && firstDimImplicit) {
                dimension = -1;
            } else {
                int constantIndex = firstDimImplicit ? i - 1 : i;
                if (constantIndex >= 0 && constantIndex < intConstants.size()) {
                    try {
                        dimension = std::stoi(intConstants[constantIndex]->getText());
                    } catch (const std::out_of_range& oor) {
                        addError("Integer constant for array dimension is out of range.", intConstants[constantIndex]->getSymbol());
                        dimension = 0;
                    } catch (const std::invalid_argument& ia) {
                        addError("Invalid integer constant for array dimension.", intConstants[constantIndex]->getSymbol());
                        dimension = 0;
                    }
                }
            }
            dimensions.push_back(dimension);
        }
        actualType = std::make_shared<Type>(Type::ARRAY);
        actualType->elementType = baseType;
        actualType->dimensions = dimensions;
    } else {
        actualType = std::make_shared<Type>(*baseType);
    }
    auto paramSymbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::PARAMETER, ctx);
    paramSymbol->isInitialized = true;
    return paramSymbol;
}

/**
 * @brief Processes a code block
 * 
 * This method:
 * 1. Creates a new scope for the block (unless it's the function body block)
 * 2. Processes declarations and statements in the block
 * 3. Tracks return statements for control flow analysis
 * 4. Exits the scope when finished (unless it's the function body block)
 * 
 * @param ctx The block context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitBlock(CactParser::BlockContext *ctx) {
    bool isFunctionBodyBlock = dynamic_cast<CactParser::FunctionDefinitionContext*>(ctx->parent) != nullptr;

    if (!isFunctionBodyBlock) {
        enterScope(false, currentScope ? currentScope->isLoop() : false);
    }

    bool allPathsReturn = true;
    bool hasReturnStatement = false;
    
    for (auto* item : ctx->blockItem()) {
        if (item->declaration()) {
            visitDeclaration(item->declaration());
        } else if (item->statement()) {
            bool prevReturn = currentFunctionHasReturn;
            visitStatement(item->statement());
            if (!prevReturn && currentFunctionHasReturn) {
                hasReturnStatement = true;
            }
            if (item != ctx->blockItem().back() && currentFunctionHasReturn) {
                break;
            }
        }
    }
    
    if (!hasReturnStatement) {
        allPathsReturn = false;
    }

    if (!isFunctionBodyBlock) {
        exitScope();
    }
    return nullptr;
}

/**
 * @brief Processes a statement
 * 
 * This method handles various statement types:
 * 1. Return statements - verifies return type compatibility with function return type
 * 2. Assignment statements - validates LHS and RHS type compatibility
 * 3. Expression statements - evaluates the expression
 * 4. Block statements - processes the nested block
 * 5. If statements - validates condition and processes branches
 * 6. While statements - validates condition and processes loop body
 * 7. Break/continue statements - verifies they are within loops
 * 
 * @param ctx The statement context
 * @return nullptr (no value is returned)
 */
antlrcpp::Any SemanticAnalyzer::visitStatement(CactParser::StatementContext *ctx) {    
    if (ctx->Return()) {
        if (!currentFunctionSymbol) {
            addError("'return' statement outside of function.", ctx->Return()->getSymbol());
            return nullptr;
        }
        currentFunctionHasReturn = true;
        std::shared_ptr<Type> expectedReturnType = currentFunctionSymbol->type->elementType;

        if (ctx->expression()) {
            if (expectedReturnType->baseType == Type::VOID) {
                addError("Cannot return a value from a void function '" + currentFunctionSymbol->name + "'.", ctx->Return()->getSymbol());
            } else {
                std::shared_ptr<Type> actualReturnType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()));
                if (actualReturnType->baseType != Type::ERROR_TYPE) {
                    auto tempExpected = std::make_shared<Type>(*expectedReturnType); tempExpected->isConst = false;
                    auto tempActual = std::make_shared<Type>(*actualReturnType); tempActual->isConst = false;
                    if (!tempExpected->equals(*tempActual)) {
                        addError("Return type mismatch: expected '" + expectedReturnType->toString() +
                                 "', got '" + actualReturnType->toString() + "'.", ctx->expression()->getStart());
                    }
                }
            }
        } else {
            if (expectedReturnType->baseType != Type::VOID) {
                addError("Non-void function '" + currentFunctionSymbol->name + "' must return a value.", ctx->Return()->getSymbol());
            }
        }
    } else if (ctx->leftValue() && ctx->Equal() && ctx->expression()) {
        std::shared_ptr<Type> lvalType = std::any_cast<std::shared_ptr<Type>>(visitLeftValue(ctx->leftValue()));
        std::shared_ptr<Type> expType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()));

        if (lvalType->baseType == Type::ERROR_TYPE || expType->baseType == Type::ERROR_TYPE) {
            return nullptr;
        }

        if (!lvalType->isLValue) {
            addError("Expression is not assignable (not an L-value).", ctx->leftValue()->getStart());
            return nullptr;
        }
        if (lvalType->isConst) {
            addError("Cannot assign to a constant '" + ctx->leftValue()->getText() + "'.", ctx->leftValue()->getStart());
            return nullptr;
        }

        auto tempLval = std::make_shared<Type>(*lvalType); tempLval->isConst = false;
        auto tempExp = std::make_shared<Type>(*expType); tempExp->isConst = false;

        if (!tempLval->equals(*tempExp)) {
             addError("Type mismatch in assignment: cannot assign '" + expType->toString() +
                     "' to '" + lvalType->toString() + "'.", ctx->Equal()->getSymbol());
        }

    } else if (ctx->expression()) {
        visitExpression(ctx->expression());
    } else if (ctx->block()) {
        visitBlock(ctx->block());
    } else if (ctx->If()) {
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
        if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            addError("Condition for 'if' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        bool oldHasReturn = currentFunctionHasReturn;
        bool thenBranchReturns = false;
        bool elseBranchReturns = false;
        
        currentFunctionHasReturn = false;
        visitStatement(ctx->statement(0));
        thenBranchReturns = currentFunctionHasReturn;
        
        currentFunctionHasReturn = false;
        if (ctx->Else()) {
            visitStatement(ctx->statement(1));
            elseBranchReturns = currentFunctionHasReturn;
        }
        
        if (ctx->Else()) {
            currentFunctionHasReturn = thenBranchReturns && elseBranchReturns;
        } else {
            currentFunctionHasReturn = oldHasReturn;
        }
    } else if (ctx->While()) {
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
         if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            addError("Condition for 'while' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        Scope* preLoopScope = currentScope;
        currentScope = new Scope(preLoopScope, preLoopScope->isFunction(), true);

        bool oldHasReturn = currentFunctionHasReturn;
        visitStatement(ctx->statement(0));
        currentFunctionHasReturn = oldHasReturn;

        Scope* temp = currentScope;
        currentScope = preLoopScope;
        delete temp;

    } else if (ctx->Break()) {
        Scope* s = currentScope;
        bool inLoop = false;
        while(s){
            if(s->isLoop()){ inLoop = true; break;}
            if(s->isFunction()) break;
            s = s->getParent();
        }
        if (!inLoop) {
            addError("'break' statement not within a loop.", ctx->Break()->getSymbol());
        }
    } else if (ctx->Continue()) {
         Scope* s = currentScope;
        bool inLoop = false;
        while(s){
            if(s->isLoop()){ inLoop = true; break;}
            if(s->isFunction()) break;
            s = s->getParent();
        }
        if (!inLoop) {
            addError("'continue' statement not within a loop.", ctx->Continue()->getSymbol());
        }
    }
    return nullptr;
}

/**
 * @brief Evaluates an expression to determine if it's a compile-time constant
 * 
 * This method attempts to statically evaluate an expression to determine:
 * 1. Whether it is a constant expression (can be evaluated at compile time)
 * 2. What type the expression has
 * 3. What value the expression evaluates to (if applicable)
 * 
 * Only a limited subset of expressions can be evaluated at compile time:
 * - Literal constants (integers, floats, characters)
 * - References to constant variables
 * - Simple unary operations (+/-)
 * 
 * @param addCtx The expression context to evaluate
 * @return A ConstEvalResult containing type, value, and constness information
 */
/**
 * @brief Evaluates expressions for compile-time constant values
 * 
 * This method attempts to statically evaluate an expression to determine:
 * 1. Whether it is a constant expression (can be evaluated at compile time)
 * 2. What type the expression has
 * 3. What value the expression evaluates to (if applicable)
 * 
 * Only a limited subset of expressions can be evaluated at compile time:
 * - Literal constants (integers, floats, characters)
 * - References to constant variables
 * - Simple unary operations (+/-)
 * 
 * @param addCtx The expression context to evaluate
 * @return A ConstEvalResult containing type, value, and constness information
 */
SemanticAnalyzer::ConstEvalResult SemanticAnalyzer::evaluateAddExpressionAsConstant(CactParser::AddExpressionContext* addCtx) {
    // Return an error result if the input context is null
    if (!addCtx) return {Type::getError(), {}, false, false};
    
    // Initialize result with default error values
    ConstEvalResult result;
    result.type = Type::getError(); 
    result.isConst = false;      // Not a compile-time constant by default
    result.hasValue = false;     // No value available by default

    // Rule 1: Binary operations with '+' or '-' operators cannot be compile-time constants
    // Check if this is a binary expression with an operator
    if (addCtx->addExpression()) { 
        // This is a complex expression involving binary '+' or '-' operations
        // CACT only allows simple expressions to be compile-time constants
        return result; 
    }

    auto currentMulExp = addCtx->multiplicativeExpression();
    // Rule 2: Multiplicative operations ('*', '/', '%') cannot be compile-time constants
    if (currentMulExp->multiplicativeExpression()) { 
        // This is a complex expression involving multiplication/division/modulo
        return result; 
    }

    auto currentUnaryExp = currentMulExp->unaryExpression();
    // Track if we're applying unary + or - to a literal
    bool isNegative = false;     // For applying unary minus to numeric literals
    bool isPositive = false;     // For applying unary plus to numeric literals

    // Rule 3: Function calls cannot be evaluated at compile-time 
    if (currentUnaryExp->Identifier() && currentUnaryExp->LeftParenthesis()) {
        return result;
    }

    // Handle unary +/- operators
    CactParser::UnaryExpressionContext* unaryExpForPrimary = currentUnaryExp;
    if (currentUnaryExp->Plus()) {
        isPositive = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    } else if (currentUnaryExp->Minus()) {
        isNegative = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    }
    
    // Function calls within unary expressions also cannot be evaluated at compile-time
    if (unaryExpForPrimary->Identifier() && unaryExpForPrimary->LeftParenthesis()){
        return result;
    }

    // Logical NOT operations are not supported for compile-time evaluation
    if (unaryExpForPrimary->ExclamationMark()) {
        return result; 
    }
    
    // Now we handle the actual constant evaluation for primary expressions
    if (unaryExpForPrimary->primaryExpression()) {
        auto primExp = unaryExpForPrimary->primaryExpression();
        // Case 1: Numeric or character literals
        if (primExp->number()) {
            // Mark as a compile-time constant since we are processing a literal value
            result.isConst = true;
            
            // Integer constant - handles integer literals like 123, 42, etc.
            if (primExp->number()->IntegerConstant()) {
                try {
                    // Parse the integer value from the token text using standard library
                    // This converts the string representation to an actual int value
                    int val = std::stoi(primExp->number()->IntegerConstant()->getText());
                    // Apply unary minus operator if present in the expression (e.g., -123)
                    if (isNegative) val = -val;
                    // Store the computed value and mark that we have a valid value
                    result.value = val; result.hasValue = true;
                    // Set the type to const int since integer literals are inherently constants
                    result.type = Type::getInt(true); 
                } catch (...) { 
                    // Handle parsing errors, e.g., integer value too large for int type
                    // or malformed integer literal that cannot be parsed
                    result.isConst = false; 
                }
            // Float constant - handles floating point literals like 3.14, 2.5e-10, etc.
            } else if (primExp->number()->FloatConstant()) {
                try {
                    // Parse the floating point value from the token text using standard library
                    // This converts the string representation to an actual float value
                    float val = std::stof(primExp->number()->FloatConstant()->getText());
                    // Apply unary minus operator if present in the expression (e.g., -3.14)
                    if (isNegative) val = -val;
                    // Store the computed value and mark that we have a valid value
                    result.value = val; result.hasValue = true;
                    // Set the type to const float since float literals are inherently constants
                    result.type = Type::getFloat(true);
                } catch (...) { 
                    // Handle parsing errors, e.g., float too large
                    result.isConst = false; 
                }
            // Character constant
            } else if (primExp->number()->CharacterConstant()) {
                // Extract the raw text of the character literal from the token
                // This includes the surrounding single quotes (e.g., 'a', '\n')
                std::string text = primExp->number()->CharacterConstant()->getText();
                
                // In CACT, unary +/- operators are not permitted on character literals
                // For example, +'a' or -'a' are invalid expressions
                if (isNegative || isPositive) { 
                    addError("Unary '+' or '-' cannot be applied to character constant.", primExp->number()->getStart());
                    // Mark as invalid and set error type
                    result.isConst = false; result.hasValue = false; result.type = Type::getError();
                } 
                // Validate the character literal format: must start and end with single quotes
                // and have at least one character between them
                else if (text.length() >= 3 && text.front() == '\'' && text.back() == '\'') {
                    // Case 1: Simple character (e.g., 'a', 'Z', '5')
                    // Format must be exactly 3 characters: opening quote, character, closing quote
                    if (text.length() == 3) { 
                        // Store the character value (the middle character between quotes)
                        result.value = text[1]; 
                        result.hasValue = true;
                        // Set the type to const char
                        result.type = Type::getChar(true);
                    } 
                    // Case 2: Escape sequence (e.g., '\n', '\t', '\\')
                    // Format must be exactly 4 characters: opening quote, backslash, escape char, closing quote
                    else if (text.length() == 4 && text[1] == '\\') { 
                        char unescaped_char;
                        bool recognized_escape = true;
                        
                        // Convert escape sequence to the corresponding character value
                        // CACT supports a standard set of C-style escape sequences
                        switch (text[2]) {
                            case 'n': unescaped_char = '\n'; break;  // Newline
                            case 't': unescaped_char = '\t'; break;  // Tab
                            case 'r': unescaped_char = '\r'; break;  // Carriage return
                            case '\\': unescaped_char = '\\'; break; // Backslash
                            case '\'': unescaped_char = '\''; break; // Single quote
                            case '0': unescaped_char = '\0'; break;  // Null character
                            default: recognized_escape = false; break; // Unrecognized escape sequence
                        }
                        
                        // If the escape sequence is valid, store the character value
                        if (recognized_escape) {
                            result.value = unescaped_char; 
                            result.hasValue = true;
                            result.type = Type::getChar(true);
                        } 
                        // Report error for invalid escape sequences (e.g., '\x')
                        else {
                            addError("Unrecognized character escape sequence: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                            result.isConst = false; result.hasValue = false; result.type = Type::getError();
                        }
                    } 
                    // Case 3: Invalid character format - wrong length or not an escape sequence
                    // For example: 'abc' (too many characters) or '\abc' (invalid escape)
                    else {
                        addError("Invalid character literal format: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                        result.isConst = false; result.hasValue = false; result.type = Type::getError();
                    }
                } 
                // Case 4: Invalid character format - missing quotes or empty character
                // For example: a' or 'a or '' or non-quoted text
                else {
                    addError("Invalid character literal format: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                    result.isConst = false; result.hasValue = false; result.type = Type::getError();
                }
            }
            return result;
        // Case 2: References to constant identifiers
        } else if (primExp->leftValue()) {
            // Cannot apply unary operators to identifiers in compile-time evaluation
            if (isNegative || isPositive) { 
                 return result; 
            }
            // Only simple identifier references (not array elements) can be compile-time constants
            if (primExp->leftValue()->Identifier() && primExp->leftValue()->LeftBracket().empty()) {
                std::string name = primExp->leftValue()->Identifier()->getText();
                auto symbol = currentScope->resolve(name);
                // The referenced identifier must be a constant with a known value
                if (symbol && symbol->kind == SymbolInfo::CONSTANT && symbol->hasConstValue) {
                    result.isConst = true;
                    result.value = symbol->constValue;
                    result.hasValue = true;
                    result.type = symbol->type; 
                    return result;
                }
            }
        }
    }
    return result;
}

/**
 * @brief Validates initializers for constants and variables
 * 
 * This method ensures that:
 * 1. The initializer expression is a compile-time constant
 * 2. The initializer type is compatible with the variable/constant type
 * 3. For arrays, that nested initializer lists match array dimensions
 * 
 * @param ctx The constant initialization value context
 * @return Either a ConstEvalResult for scalar initializers, or a boolean for array initializers
 */
/**
 * @brief Validates initializers for constants and variables
 * 
 * This method ensures that:
 * 1. The initializer expression is a compile-time constant
 * 2. The initializer type is compatible with the variable/constant type
 * 3. For arrays, that nested initializer lists match array dimensions
 * 
 * @param ctx The constant initialization value context
 * @return Either a ConstEvalResult for scalar initializers, or a boolean for array initializers
 */
antlrcpp::Any SemanticAnalyzer::visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) {
    if (!expectingConstantInitializer || !expectedInitializerType) {
        addError("Internal error: visitConstantInitializationValue called without proper context.", ctx->getStart());
        return SemanticAnalyzer::ConstEvalResult{Type::getError(), {}, false, false};
    }

    if (ctx->constantExpression()) {
        // Case 1: Scalar initializer (like '= 5' or '= 'c'')
        // Evaluate the constant expression and verify it's a compile-time constant
        ConstEvalResult evalRes = evaluateAddExpressionAsConstant(ctx->constantExpression()->addExpression()); 
        if (!evalRes.isConst) {
            addError("Initializer must be a compile-time constant.", ctx->constantExpression()->getStart());
            return evalRes; 
        }
        
        if (expectedInitializerType->baseType == Type::ARRAY) { 
            // Arrays cannot be initialized directly with a scalar value
            // For example: int arr[3] = 5; is not allowed
            addError("Cannot initialize array with a scalar value directly in this form (use '{...}').", ctx->getStart());
            return ConstEvalResult{Type::getError(), {}, false, false};
        }
        
        if (expectedInitializerType->baseType != Type::ARRAY) { 
            // For scalar types, verify that the initializer type matches the expected type
            // For example, an int variable must be initialized with an int constant
            if (!evalRes.type->equals(*expectedInitializerType)) {
                addError("Initializer type '" + evalRes.type->toString() + 
                            "' does not match expected type '" + expectedInitializerType->toString() + "'.", 
                            ctx->constantExpression()->getStart());
                ConstEvalResult errorResult = evalRes;
                errorResult.type = Type::getError();
                return errorResult;
            }
        }
        return evalRes;

    } else if (ctx->LeftBrace()) { 
        // Case 2: Array initializer (like '= {1, 2, 3}' or '= {{1, 2}, {3, 4}}')
        if (expectedInitializerType->baseType != Type::ARRAY) {
            // Cannot use array initializer for non-array types
            // For example: int x = {1}; is not allowed
            addError("Array initializer used for non-array type '" + expectedInitializerType->toString() + "'.", ctx->LeftBrace()->getSymbol());
            return false; 
        }
        // For array initializers, we need to check each element recursively
        std::vector<ConstEvalResult> flatInitializers;
        std::shared_ptr<Type> originalExpectedType = expectedInitializerType; 
        // Validate all array elements using recursive checking
        int initCount = checkArrayInitializerRecursive(ctx, expectedInitializerType->elementType, expectedInitializerType->dimensions, 0, flatInitializers);
        expectedInitializerType = originalExpectedType; 
        if (initCount < 0) { 
            // Negative return value indicates an error in the array initializer
            return false; 
        }
        return true; 
    }
    return SemanticAnalyzer::ConstEvalResult{Type::getError(), {}, false, false};
}

/**
 * @brief Recursively validates initializers for multi-dimensional arrays
 * 
 * This method:
 * 1. Verifies that array initializer dimensions match array dimensions
 * 2. Validates that each scalar initializer in the array is a compile-time constant
 * 3. Validates that each scalar initializer type matches the array's element type
 * 4. Collects all initializers in a flattened list for later use
 * 
 * @param initCtx The initializer context to check
 * @param expectedElementType The expected element type for the array
 * @param dimensions The dimensions of the array
 * @param currentDimensionIndex The current dimension being processed
 * @param flatInitializers Output parameter collecting all initializer values
 * @return The number of elements processed at the current level
 */
/**
 * @brief Recursively validates initializers for multi-dimensional arrays
 * 
 * This method:
 * 1. Verifies that array initializer dimensions match array dimensions
 * 2. Validates that each scalar initializer in the array is a compile-time constant
 * 3. Validates that each scalar initializer type matches the array's element type
 * 4. Collects all initializers in a flattened list for later use
 * 
 * @param initCtx The initializer context to check
 * @param expectedElementType The expected element type for the array
 * @param dimensions The dimensions of the array
 * @param currentDimensionIndex The current dimension being processed
 * @param flatInitializers Output parameter collecting all initializer values
 * @return The number of elements processed at the current level, or -1 on error
 */
int SemanticAnalyzer::checkArrayInitializerRecursive(
    CactParser::ConstantInitializationValueContext* initCtx, 
    std::shared_ptr<Type> expectedElementType, 
    const std::vector<int>& dimensions, 
    int currentDimensionIndex,
    std::vector<ConstEvalResult>& flatInitializers) 
{
    
    // Case 1: If we've reached a scalar initializer (not a brace-enclosed list)
    if (!initCtx || !initCtx->LeftBrace()) {
        if (initCtx && initCtx->constantExpression()) {
            // Find the ultimate element type (for multi-dimensional arrays)
            // For example, in int[2][3], the ultimate element type is int
            std::shared_ptr<Type> ultimateElementType = expectedInitializerType;
            while(ultimateElementType->baseType == Type::ARRAY) {
                ultimateElementType = ultimateElementType->elementType;
            }

            if (!ultimateElementType) {
                addError("Internal error: array ultimate element type is null.", initCtx->getStart());
                return -1;
            }

            // Save and restore the expected initializer type during validation
            std::shared_ptr<Type> oldExpected = expectedInitializerType;
            expectedInitializerType = ultimateElementType;

            // Recursively evaluate the constant expression
            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(initCtx));
            
            expectedInitializerType = oldExpected;

            // Check that the expression is a compile-time constant
            if (!val.isConst) { return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;

            // Verify the type matches what we expect at this position in the array
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          initCtx->constantExpression()->getStart());
                 return -1;
            }
            // Add the validated element to our flat list of initializers
            flatInitializers.push_back(val);
            return 1;
        }
        addError("Invalid array initializer: expected '{...}' or constant expression.", initCtx ? initCtx->getStart() : nullptr);
        return -1;
    }

    // Verify we haven't exceeded the number of dimensions of the array
    if (currentDimensionIndex >= dimensions.size()) {
        addError("Too many nested initializers for array.", initCtx->LeftBrace()->getSymbol());
        return -1;
    }

    // Count how many elements we've processed at this dimension level
    int count = 0;
    // Determine the maximum number of elements allowed in this dimension
    // -1 means unlimited (like in function parameter declarations: int func(int arr[][10]))
    int maxElementsInThisDimension = (dimensions[currentDimensionIndex] == -1) ? -1 : dimensions[currentDimensionIndex];

    // Process each sub-initializer in this brace-enclosed list
    for (auto* subInitCtx : initCtx->constantInitializationValue()) {
        // Check if we've exceeded the allowed number of elements in this dimension
        if (maxElementsInThisDimension != -1 && count >= maxElementsInThisDimension) {
            addError("Too many initializers for array dimension of size " + 
                     std::to_string(maxElementsInThisDimension) + ".", subInitCtx->getStart());
            return -1;
        }

        int subCount;
        // Case 2a: This element is itself a brace-enclosed initializer (for multi-dimensional arrays)
        if (subInitCtx->LeftBrace()) {
            // Verify we haven't exceeded the number of dimensions
            if (currentDimensionIndex + 1 >= dimensions.size() && dimensions.size() > 0) { 
                addError("Too many nested initializers for array - array has fewer dimensions than the initializer.", subInitCtx->getStart());
                return -1;
            }

            if (!expectedElementType) {
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }

            // Recursively check the next level of array initializers
            subCount = checkArrayInitializerRecursive(subInitCtx, expectedElementType, dimensions, currentDimensionIndex + 1, flatInitializers);
        } else {
            // Case 2b: This element is a scalar value
            std::shared_ptr<Type> oldExpected = expectedInitializerType;
            
            if (!expectedElementType) {
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }
            
            // Find the ultimate element type for this position in the array
            std::shared_ptr<Type> ultimateElementType = expectedElementType;
            while(ultimateElementType->baseType == Type::ARRAY) {
                ultimateElementType = ultimateElementType->elementType;
            }
            
            expectedInitializerType = ultimateElementType;

            // Validate the scalar element
            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(subInitCtx));
            
            expectedInitializerType = oldExpected;

            // Check that the expression is a compile-time constant
            if (!val.isConst) { return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;
            
            // Verify the type matches what we expect
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          subInitCtx->constantExpression()->getStart());
                 return -1;
            }
            // Add the validated element to our flat list of initializers
            flatInitializers.push_back(val);
            subCount = 1;
        }

        // If any sub-initializer had an error, propagate the error
        if (subCount < 0) return -1;
        // Otherwise, count the elements we've processed
        count += subCount;
    }
    // Return the total number of elements processed at this level
    return count;
}

/**
 * @brief Processes and type-checks expressions
 * 
 * This method evaluates the type of an expression and checks for type errors.
 * It handles various expression types including arithmetic, logical, and relational expressions.
 * 
 * @param ctx The expression context
 * @return The type of the expression
 */
antlrcpp::Any SemanticAnalyzer::visitExpression(CactParser::ExpressionContext *ctx) {
    // This method analyzes general expressions in the CACT language
    // It delegates to visitAddExpression for actual type checking and validation
    if (ctx->addExpression()) {
        return visitAddExpression(ctx->addExpression());
    }
    addError("Invalid expression structure.", ctx->getStart());
    return Type::getError();
}

/**
 * @brief Processes constant expressions
 * 
 * This method analyzes constant expressions, which are used in initializers and array dimensions.
 * It validates that the expression is well-formed and returns its type.
 * 
 * @param ctx The constant expression context
 * @return The type of the constant expression
 */
antlrcpp::Any SemanticAnalyzer::visitConstantExpression(CactParser::ConstantExpressionContext *ctx) {
    // This method analyzes constant expressions, which are used in initializers and array dimensions
    // It validates that the expression is well-formed and returns its type
    if (ctx->addExpression()) {
        auto type = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));
        return type;
    }
    addError("Invalid constant expression structure.", ctx->getStart());
    return Type::getError();
}

/**
 * @brief Processes conditions in if/while statements
 * 
 * This method analyzes conditions in if/while statements by:
 * 1. Setting a flag to indicate we're in a condition context (needed for logical operators)
 * 2. Validating that the condition expression has a valid type that can be evaluated as boolean
 * 3. Restoring the condition context flag when finished
 * 
 * @param ctx The condition context
 * @return The type of the condition expression
 */
antlrcpp::Any SemanticAnalyzer::visitCondition(CactParser::ConditionContext *ctx) {
    // This method analyzes conditions in if/while statements
    // It sets a flag to indicate we're in a condition context (needed for logical operators)
    // and validates that the condition expression has a valid type that can be evaluated as boolean
    bool oldInConditionContext = inConditionContext;
    inConditionContext = true;
    
    std::shared_ptr<Type> result;
    if (ctx->logicalOrExpression()) {
        result = std::any_cast<std::shared_ptr<Type>>(visitLogicalOrExpression(ctx->logicalOrExpression()));
    } else {
        addError("Invalid condition structure.", ctx->getStart());
        result = Type::getError();
    }
    
    inConditionContext = oldInConditionContext;
    return result;
}

/**
 * @brief Processes left-value expressions (variables and array elements)
 * 
 * This method handles variable references (identifiers and array elements) by:
 * 1. Verifying that the referenced identifier exists and has the appropriate type
 * 2. Checking that array accesses have valid indices and dimensions
 * 3. Setting the isLValue flag to indicate the expression can be assigned to
 * 4. Preserving constness information from the original declaration
 * 
 * @param ctx The left value context
 * @return The type of the left value (with isLValue flag set)
 */
antlrcpp::Any SemanticAnalyzer::visitLeftValue(CactParser::LeftValueContext *ctx) {
    // This method handles variable references (identifiers and array elements)
    // It verifies that the referenced identifier exists and has the appropriate type
    // Also checks that array accesses have valid indices and dimensions
    std::string name = ctx->Identifier()->getText();
    auto symbol = currentScope->resolve(name);

    if (!symbol) {
        addError("Identifier '" + name + "' not defined.", ctx->Identifier()->getSymbol());
        return Type::getError();
    }

    if (symbol->kind == SymbolInfo::FUNCTION_DEF) {
        addError("'" + name + "' is a function, cannot be used as a variable.", ctx->Identifier()->getSymbol());
        return Type::getError();
    }
    
    std::shared_ptr<Type> currentType = symbol->type;
    currentType->isLValue = true; 

    if (!ctx->LeftBracket().empty()) { 
        // Handle array element access (e.g., arr[i][j])
        if (currentType->baseType != Type::ARRAY) {
            addError("'" + name + "' is not an array.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }

        if (ctx->expression().size() > currentType->dimensions.size()) {
            addError("Too many array indices for '" + name + "'.", ctx->LeftBracket()[0]->getSymbol());
            return Type::getError();
        }
        
        std::shared_ptr<Type> resultType = currentType->elementType;
        
        if (!resultType) {
            addError("Internal error: array element type is null.", ctx->getStart());
            return Type::getError();
        }
        
        // Validate each array index expression
        for (size_t i = 0; i < ctx->expression().size(); ++i) {
            auto indexType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()[i]));
            
            // Array indices must be integers
            if (indexType->baseType != Type::INT) {
                addError("Array index must be an integer.", ctx->expression()[i]->getStart());
                return Type::getError();
            }
            
            // If the index is a constant, check if it's within the array bounds
            auto indexExp = ctx->expression()[i]->addExpression();
            if (indexExp && indexExp->multiplicativeExpression() && 
                !indexExp->multiplicativeExpression()->multiplicativeExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number()->IntegerConstant()) {
                
                std::string indexStr = indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number()->IntegerConstant()->getText();
                int indexValue;
                
                // Handle hexadecimal (0x...), octal (0...), and decimal number formats
                if (indexStr.size() > 2 && (indexStr.substr(0, 2) == "0x" || indexStr.substr(0, 2) == "0X")) {
                    indexValue = std::stoi(indexStr, nullptr, 16);
                } else if (indexStr.size() > 1 && indexStr[0] == '0') {
                    indexValue = std::stoi(indexStr, nullptr, 8);
                } else {
                    indexValue = std::stoi(indexStr);
                }
                
                // Verify array bounds (unless dimension is -1, which means unrestricted size)
                if (currentType->dimensions[i] != -1 && (indexValue < 0 || indexValue >= currentType->dimensions[i])) {
                    addError("Array index " + std::to_string(indexValue) + " out of bounds [0," + 
                            std::to_string(currentType->dimensions[i]-1) + "].", 
                            ctx->expression()[i]->getStart());
                    return Type::getError();
                }
            }
        }
        
        // Return the appropriate type based on how many dimensions were accessed
        if (ctx->expression().size() == currentType->dimensions.size()) {
            // Accessed all dimensions, return the element type (e.g., int from int[3][4])
            resultType->isLValue = true;
            resultType->isConst = symbol->type->isConst;
            return resultType;
        } else {
            // Accessed some dimensions, return a sub-array type (e.g., int[4] from int[3][4])
            std::shared_ptr<Type> newArrayType = std::make_shared<Type>(Type::ARRAY);
            newArrayType->elementType = currentType->elementType;
            newArrayType->isLValue = true;
            newArrayType->isConst = symbol->type->isConst;
            
            // Include remaining dimensions in the type
            for (size_t i = ctx->expression().size(); i < currentType->dimensions.size(); ++i) {
                newArrayType->dimensions.push_back(currentType->dimensions[i]);
            }
                                  
            return newArrayType;
        }
    }
    // Simple variable reference (not an array element)
    return symbol->type; 
}

/**
 * @brief Processes numeric literals (int, float, char)
 * 
 * This method determines the type of a numeric literal and returns
 * the appropriate built-in type object.
 * 
 * @param ctx The number context
 * @return The type of the number literal (int, float, or char)
 */
antlrcpp::Any SemanticAnalyzer::visitNumber(CactParser::NumberContext *ctx) {
    // This method determines the type of a numeric literal (int, float, or char)
    // It returns the appropriate built-in type object
    if (ctx->IntegerConstant()) return Type::getInt();
    if (ctx->FloatConstant()) return Type::getFloat();
    if (ctx->CharacterConstant()) return Type::getChar();
    return Type::getError();
}

/**
 * @brief Processes primary expressions
 * 
 * This method handles primary expressions, which can be:
 * 1. Parenthesized expressions - (expr)
 * 2. Variable references - x, arr[i]
 * 3. Literals - 42, 3.14, 'c'
 * 
 * Each sub-expression is delegated to the appropriate visitor method.
 * 
 * @param ctx The primary expression context
 * @return The type of the primary expression
 */
antlrcpp::Any SemanticAnalyzer::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
    // This method handles primary expressions, which can be:
    // 1. Parenthesized expressions - (expr)
    // 2. Variable references - x, arr[i]
    // 3. Literals - 42, 3.14, 'c'
    if (ctx->expression()) {
        return visitExpression(ctx->expression());
    }
    if (ctx->leftValue()) {
        return visitLeftValue(ctx->leftValue());
    }
    if (ctx->number()) {
        return visitNumber(ctx->number());
    }
    return Type::getError();
}

/**
 * @brief Processes unary expressions
 * 
 * This method handles:
 * 1. Primary expressions (literals, variables, parenthesized expressions)
 * 2. Unary operators (+, -, !) with type checking
 * 3. Function calls with parameter type validation
 * 
 * For unary operators, it verifies that the operand type is compatible with the operator.
 * For function calls, it checks that the function exists, parameter count and types match,
 * and handles special cases like array parameter passing.
 * 
 * @param ctx The unary expression context
 * @return The type of the unary expression
 */
antlrcpp::Any SemanticAnalyzer::visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) {
    // This method handles unary expressions:
    // 1. Primary expressions (literals, variables, parenthesized expressions)
    // 2. Unary operators (+, -, !)
    // 3. Function calls
    if (ctx->primaryExpression()) {
        return visitPrimaryExpression(ctx->primaryExpression());
    }
    if (ctx->unaryExpression()) {
        std::shared_ptr<Type> operandType = std::any_cast<std::shared_ptr<Type>>(visitUnaryExpression(ctx->unaryExpression()));
        if (operandType->baseType == Type::ERROR_TYPE) return Type::getError();

        // Handle unary plus and minus operators
        if (ctx->Plus() || ctx->Minus()) {
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT) {
                addError("Unary '+' or '-' must be applied to numeric type, got '" + operandType->toString() + "'.", 
                         (ctx->Plus() ? ctx->Plus()->getSymbol() : ctx->Minus()->getSymbol()) );
                return Type::getError();
            }
            return operandType;
        }
        // Handle logical NOT operator
        if (ctx->ExclamationMark()) {
            if (!inConditionContext) {
                addError("Logical NOT '!' operator can only be used in condition expressions.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT && operandType->baseType != Type::CHAR) {
                addError("Logical NOT '!' must be applied to numeric type, got '" + operandType->toString() + "'.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            return Type::getInt();
        }
    }
    // Handle function calls
    if (ctx->Identifier() && ctx->LeftParenthesis()) {
        std::string funcName = ctx->Identifier()->getText();
        auto symbol = currentScope->resolve(funcName);
        if (!symbol) {
            addError("Function '" + funcName + "' not defined.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }
        if (symbol->kind != SymbolInfo::FUNCTION_DEF) {
            addError("'" + funcName + "' is not a function.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }

        std::shared_ptr<Type> funcType = symbol->type;
        std::vector<std::shared_ptr<Type>> expectedParamTypes = funcType->paramTypes;
        std::vector<std::shared_ptr<Type>> actualParamTypes;
        
        // Collect and validate all function arguments
        if (ctx->functionRealParameters()) {
            for (auto* expCtx : ctx->functionRealParameters()->expression()) {
                actualParamTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visitExpression(expCtx)));
            }
        }
        
        // Check if the number of arguments matches the function declaration
        if (actualParamTypes.size() != expectedParamTypes.size()) {
            addError("Function '" + funcName + "' called with incorrect number of arguments. Expected " +
                     std::to_string(expectedParamTypes.size()) + ", got " + std::to_string(actualParamTypes.size()) + ".",
                     ctx->Identifier()->getSymbol());
            return funcType->elementType;
        }

        for (size_t i = 0; i < expectedParamTypes.size(); ++i) {
            if (actualParamTypes[i]->baseType == Type::ERROR_TYPE) continue;
            
            auto tempExpected = std::make_shared<Type>(*expectedParamTypes[i]); tempExpected->isConst = false;
            auto tempActual = std::make_shared<Type>(*actualParamTypes[i]); tempActual->isConst = false;

            bool skipErrorReport = false;
            
            if (tempExpected->baseType == Type::ARRAY && tempActual->baseType == Type::ARRAY) {
                if (tempExpected->dimensions.size() == tempActual->dimensions.size()) {
                    if (tempExpected->dimensions[0] == -1 || tempActual->dimensions[0] == -1) {
                        bool otherDimensionsMatch = true;
                        for (size_t dim = 1; dim < tempExpected->dimensions.size(); ++dim) {
                            if (tempExpected->dimensions[dim] != tempActual->dimensions[dim]) {
                                otherDimensionsMatch = false;
                                break;
                            }
                        }
                        
                        if (otherDimensionsMatch && tempExpected->elementType->equals(*tempActual->elementType)) {
                            skipErrorReport = true;
                        }
                    }
                }
            }
            
            if (!skipErrorReport && !tempExpected->equals(*tempActual)) {
                std::string errorMsg = "Type mismatch for argument " + std::to_string(i + 1) + " of function '" + funcName + "'. ";
                
                errorMsg += "Expected '" + expectedParamTypes[i]->toString() + "', got '" + 
                          actualParamTypes[i]->toString() + "'. ";
                          
                if (tempExpected->baseType == Type::ARRAY && tempActual->baseType == Type::ARRAY) {
                    errorMsg += "Expected dimensions: [";
                    for (size_t dim = 0; dim < tempExpected->dimensions.size(); ++dim) {
                        errorMsg += std::to_string(tempExpected->dimensions[dim]);
                        if (dim < tempExpected->dimensions.size() - 1) {
                            errorMsg += ",";
                        }
                    }
                    errorMsg += "], Actual dimensions: [";
                    for (size_t dim = 0; dim < tempActual->dimensions.size(); ++dim) {
                        errorMsg += std::to_string(tempActual->dimensions[dim]);
                        if (dim < tempActual->dimensions.size() - 1) {
                            errorMsg += ",";
                        }
                    }
                    errorMsg += "]";
                }
                
                addError(errorMsg, ctx->functionRealParameters()->expression(i)->getStart());
            }
        }
        return funcType->elementType;
    }
    return Type::getError();
}

/**
 * @brief Processes multiplicative expressions (*, /, %)
 * 
 * This method handles multiplicative operations by:
 * 1. Verifying that the operands have compatible types
 * 2. Enforcing special rules (e.g., % only works with integer operands)
 * 3. Ensuring no implicit type conversions (operands must be the same type)
 * 4. Determining the result type of the operation
 * 
 * @param ctx The multiplicative expression context
 * @return The type of the multiplicative expression
 */
antlrcpp::Any SemanticAnalyzer::visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) {
    // This method handles multiplicative operations: *, /, and %
    // It verifies that the operands have compatible types and the operation is valid
    // For example, % can only be applied to integer operands, not floating-point values
    if (ctx->multiplicativeExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitMultiplicativeExpression(ctx->multiplicativeExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitUnaryExpression(ctx->unaryExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // Modulo operation only works with integer operands
        if (ctx->Percent() && (left->baseType == Type::FLOAT || right->baseType == Type::FLOAT)) {
            addError("Modulo operator '%' cannot be applied to floating-point operands.", 
                     ctx->Percent()->getSymbol());
            return Type::getError();
        }

        // Verify both operands are numeric (int or float)
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT) && 
              (right->baseType == Type::INT || right->baseType == Type::FLOAT))) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Asterisk()) opToken = ctx->Asterisk()->getSymbol();
            else if (ctx->Slash()) opToken = ctx->Slash()->getSymbol();
            else if (ctx->Percent()) opToken = ctx->Percent()->getSymbol();
            
            addError("Operands for '*, /, %' must be numeric (int or float), got '" + 
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        
        // CACT requires operands of the same type (no implicit type conversion)
        if (left->baseType != right->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Asterisk()) opToken = ctx->Asterisk()->getSymbol();
            else if (ctx->Slash()) opToken = ctx->Slash()->getSymbol();
            else if (ctx->Percent()) opToken = ctx->Percent()->getSymbol();
            
            addError("Type mismatch in multiplication/division: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        
        // Binary operation returns the same type as the operands
        return std::make_shared<Type>(*left);
    } else {
        // If there's no binary operation, just evaluate the unary expression
        return visitUnaryExpression(ctx->unaryExpression());
    }
}

/**
 * @brief Processes additive expressions (+, -)
 * 
 * This method validates addition and subtraction operations by:
 * 1. Ensuring both operands are numeric types (int or float)
 * 2. Checking that operands are of the same type (no implicit conversions)
 * 3. Determining the result type of the operation
 * 
 * CACT does not support automatic type conversions between int and float,
 * so this method enforces strict type compatibility.
 * 
 * @param ctx The add expression context
 * @return The type of the additive expression
 */
antlrcpp::Any SemanticAnalyzer::visitAddExpression(CactParser::AddExpressionContext *ctx) {
    // This method validates addition and subtraction operations
    // It ensures that both operands are numeric types and of the same type (int or float)
    // CACT does not support automatic type conversions between int and float
    if (ctx->addExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitMultiplicativeExpression(ctx->multiplicativeExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // Both operands must be numeric (int or float)
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT) &&
              (right->baseType == Type::INT || right->baseType == Type::FLOAT))) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Plus()) opToken = ctx->Plus()->getSymbol();
            else if (ctx->Minus()) opToken = ctx->Minus()->getSymbol();

            addError("Operands for '+', '-' must be numeric (int or float), got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        
        // Both operands must be of the same type (no implicit conversion)
        if (left->baseType != right->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Plus()) opToken = ctx->Plus()->getSymbol();
            else if (ctx->Minus()) opToken = ctx->Minus()->getSymbol();
            
            addError("Type mismatch in addition/subtraction: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        
        // Result has the same type as the operands
        return std::make_shared<Type>(*left);
    } else {
        // If no binary operation, just evaluate the multiplicative expression
        return visitMultiplicativeExpression(ctx->multiplicativeExpression());
    }
}

/**
 * @brief Processes relational expressions (<, >, <=, >=)
 * 
 * This method validates relational operations by:
 * 1. Ensuring operands are of compatible types (both numeric or both char)
 * 2. Enforcing type-specific rules (e.g., chars can only be compared with chars)
 * 3. Checking that numeric operands are of the same type (no implicit conversions)
 * 4. Setting the result type to int (representing boolean true/false)
 * 
 * @param ctx The relational expression context
 * @return The type of the relational expression (always int)
 */
antlrcpp::Any SemanticAnalyzer::visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) {
    // This method validates relational operations (<, >, <=, >=)
    // It ensures operands are of compatible types (both numeric or both char)
    // and returns an int type representing the boolean result
    if (ctx->relationalExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitRelationalExpression(ctx->relationalExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }
        // Both operands must be numeric (int, float) or character types
        bool left_ok = (left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR);
        bool right_ok = (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR);

        if (!(left_ok && right_ok)) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Less()) opToken = ctx->Less()->getSymbol();
            else if (ctx->Greater()) opToken = ctx->Greater()->getSymbol();
            else if (ctx->LessEqual()) opToken = ctx->LessEqual()->getSymbol();
            else if (ctx->GreaterEqual()) opToken = ctx->GreaterEqual()->getSymbol();
            
            addError("Operands for relational operators ('<', '>', '<=', '>=') must be numeric or char, got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        // If one operand is char, the other must also be char (can't compare char with int/float)
        if ((left->baseType == Type::CHAR && right->baseType != Type::CHAR) ||
            (right->baseType == Type::CHAR && left->baseType != Type::CHAR)) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Less()) opToken = ctx->Less()->getSymbol();
            else if (ctx->Greater()) opToken = ctx->Greater()->getSymbol();
            else if (ctx->LessEqual()) opToken = ctx->LessEqual()->getSymbol();
            else if (ctx->GreaterEqual()) opToken = ctx->GreaterEqual()->getSymbol();

            addError("If one operand of a relational operator is char, the other must also be char. Got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        
        // For numeric types, both operands must be of the same type (no implicit conversion)
        if (left->baseType != Type::CHAR && right->baseType != left->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Less()) opToken = ctx->Less()->getSymbol();
            else if (ctx->Greater()) opToken = ctx->Greater()->getSymbol();
            else if (ctx->LessEqual()) opToken = ctx->LessEqual()->getSymbol();
            else if (ctx->GreaterEqual()) opToken = ctx->GreaterEqual()->getSymbol();
            
            addError("Type mismatch in relational expression: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        // Relational operations always return an int type (representing boolean true/false)
        return Type::getInt();
    } else {
        return visitAddExpression(ctx->addExpression());
    }
}

/**
 * @brief Processes equality expressions (==, !=)
 * 
 * This method validates equality operations by:
 * 1. Ensuring operands are of compatible types (both numeric or both char)
 * 2. Enforcing type-specific rules (e.g., chars can only be compared with chars)
 * 3. Checking that numeric operands are of the same type (no implicit conversions)
 * 4. Setting the result type to int (representing boolean true/false)
 * 
 * @param ctx The equality expression context
 * @return The type of the equality expression (always int)
 */
antlrcpp::Any SemanticAnalyzer::visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) {
    if (ctx->equalityExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitEqualityExpression(ctx->equalityExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitRelationalExpression(ctx->relationalExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        bool left_ok = (left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR);
        bool right_ok = (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR);
        
        if (!(left_ok && right_ok)) {
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();

            addError("Operands for equality operators ('==', '!=') must be numeric or char, got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        if ((left->baseType == Type::CHAR && right->baseType != Type::CHAR) ||
            (right->baseType == Type::CHAR && left->baseType != Type::CHAR)) {
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();
            
            addError("If one operand of an equality operator is char, the other must also be char. Got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        
        if (left->baseType != Type::CHAR && right->baseType != left->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();
            
            addError("Type mismatch in equality expression: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        return Type::getInt();
    } else {
        return visitRelationalExpression(ctx->relationalExpression());
    }
}

/**
 * @brief Processes logical AND expressions (&&)
 * 
 * This method validates logical AND operations by:
 * 1. Ensuring both operands are of numeric or char types
 *    (which can be implicitly converted to boolean values)
 * 2. Setting the result type to int (representing boolean true/false)
 * 
 * In CACT, numeric and char values can be used in logical contexts,
 * but arrays, structs, and other complex types cannot.
 * 
 * @param ctx The logical AND expression context
 * @return The type of the logical AND expression (always int)
 */
antlrcpp::Any SemanticAnalyzer::visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) {
    if (ctx->logicalAndExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitLogicalAndExpression(ctx->logicalAndExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitEqualityExpression(ctx->equalityExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) return Type::getError();
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR) && 
              (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR))) {
            addError("Operands for '&&' must be numeric or char.", ctx->LogicalAnd()->getSymbol());
            return Type::getError();
        }
        return Type::getInt();
    } else {
        return visitEqualityExpression(ctx->equalityExpression());
    }
}

/**
 * @brief Processes logical OR expressions (||)
 * 
 * This method validates logical OR operations by:
 * 1. Ensuring both operands are of numeric or char types
 *    (which can be implicitly converted to boolean values)
 * 2. Setting the result type to int (representing boolean true/false)
 * 
 * In CACT, numeric and char values can be used in logical contexts,
 * but arrays, structs, and other complex types cannot.
 * 
 * @param ctx The logical OR expression context
 * @return The type of the logical OR expression (always int)
 */
antlrcpp::Any SemanticAnalyzer::visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) {
    if (ctx->logicalOrExpression()) {
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitLogicalOrExpression(ctx->logicalOrExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitLogicalAndExpression(ctx->logicalAndExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) return Type::getError();
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR) && 
              (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR))) {
            addError("Operands for '||' must be numeric or char.", ctx->LogicalOr()->getSymbol());
            return Type::getError();
        }
        return Type::getInt();
    } else {
        return visitLogicalAndExpression(ctx->logicalAndExpression());
    }
}

/**
 * @brief Routes declaration processing to the appropriate handler
 * 
 * This method delegates processing to either visitConstantDeclaration
 * or visitVariableDeclaration based on the declaration type.
 * 
 * @param ctx The declaration context
 * @return The result from the delegated visitor method (usually nullptr)
 */
antlrcpp::Any SemanticAnalyzer::visitDeclaration(CactParser::DeclarationContext *ctx) {
    if (ctx->constantDeclaration()) {
        return visitConstantDeclaration(ctx->constantDeclaration());
    } else if (ctx->variableDeclaration()) {
        return visitVariableDeclaration(ctx->variableDeclaration());
    }
    return visitChildren(ctx); 
}

/**
 * @brief Handles terminal nodes in the parse tree
 * 
 * This is a fallback method for handling terminal nodes that don't have
 * specific visitor methods. It delegates to the base visitor implementation.
 * 
 * @param node The terminal node
 * @return The result from the base visitor method
 */
antlrcpp::Any SemanticAnalyzer::visitTerminal(antlr4::tree::TerminalNode *node) {
    return CactParserBaseVisitor::visitTerminal(node); 
}

/**
 * @brief Handles error nodes in the parse tree
 * 
 * This method is called when the parser encounters a syntax error.
 * It records the error and delegates to the base visitor implementation.
 * 
 * @param node The error node
 * @return The result from the base visitor method
 */
antlrcpp::Any SemanticAnalyzer::visitErrorNode(antlr4::tree::ErrorNode *node) {
    addError("Syntax error: unexpected token or parse error near \"" + node->getText() + "\"", node->getSymbol());
    return CactParserBaseVisitor::visitErrorNode(node); 
}
