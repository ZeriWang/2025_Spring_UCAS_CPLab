#include "include/SemanticAnalyzer.h"
#include "include/SymbolTable.h"
#include "CactParser.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// --- SemanticAnalyzer Implementation ---

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
 * @brief Performs semantic analysis on the entire compilation unit
 * 
 * This method analyzes the complete program by:
 * 1. Establishing the global scope
 * 2. Registering built-in library functions (I/O operations)
 * 3. Analyzing all global declarations and function definitions
 * 4. Verifying the main function exists and has the correct signature
 * 
 * @param ctx The compilation unit context from the parser
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    // Create the global scope
    enterScope();
    
    // Register built-in print functions
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
    
    // Register built-in input functions
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
    
    // Process all global declarations
    for (auto* item : ctx->declaration()) {
        visitDeclaration(item);
    }
    
    // Process all function definitions
    for (auto* item : ctx->functionDefinition()) {
        visitFunctionDefinition(item);
    }
    
    // Verify main function exists with correct signature
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
    
    // Clean up the global scope
    exitScope();
    return nullptr;
}

/**
 * @brief Processes a function definition
 * 
 * This method performs semantic analysis on function definitions by:
 * 1. Extracting function name, return type, and formal parameters
 * 2. Creating a function type and symbol record
 * 3. Checking for function redefinition
 * 4. Setting up a new scope for the function body
 * 5. Adding parameters to the function scope
 * 6. Validating control flow (ensuring non-void functions return values)
 * 
 * @param ctx The function definition context from the parser
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    // Extract function name and return type
    std::string funcName = ctx->Identifier()->getText();
    std::shared_ptr<Type> returnType = std::any_cast<std::shared_ptr<Type>>(visitFunctionType(ctx->functionType()));

    // Collect parameter information
    std::vector<std::shared_ptr<Type>> paramTypesList;
    std::vector<std::shared_ptr<SymbolInfo>> paramSymbolsList;

    // Process each parameter if present
    if (ctx->functionFormalParameters()) {
        for (auto* paramCtx : ctx->functionFormalParameters()->functionFormalParameter()) {
            // Visit and validate each parameter
            std::shared_ptr<SymbolInfo> paramSymbol = std::any_cast<std::shared_ptr<SymbolInfo>>(visitFunctionFormalParameter(paramCtx));
            if (!paramSymbol || paramSymbol->type->baseType == Type::ERROR_TYPE) {
                 paramTypesList.push_back(Type::getError());
                 continue;
            }
            
            // Check for duplicate parameter names
            for(const auto& pSym : paramSymbolsList){
                if(pSym->name == paramSymbol->name){
                    addError("Redefinition of parameter '" + paramSymbol->name + "'.", paramCtx->Identifier()->getSymbol());
                    paramTypesList.push_back(Type::getError());
                    goto next_param;
                }
            }
            
            // Store parameter information for later use
            paramTypesList.push_back(paramSymbol->type);
            paramSymbolsList.push_back(paramSymbol);
            next_param:;
        }
    }
    
    // Create function type and symbol
    auto funcType = Type::getFunction(returnType, paramTypesList);
    auto funcSymbol = std::make_shared<SymbolInfo>(funcName, funcType, SymbolInfo::FUNCTION_DEF, ctx);

    // Add function to current scope and check for redefinition
    if (!currentScope->define(funcName, funcSymbol)) {
        addError("Redefinition of '" + funcName + "'.", ctx->Identifier()->getSymbol());
        return nullptr;
    }
    
    // Special handling for main function
    if (funcName == "main") {
        mainFunctionFound = true;
        mainFunctionSymbol = funcSymbol;
    }

    // Set current function context for return statement validation
    currentFunctionSymbol = funcSymbol;
    currentFunctionHasReturn = false;

    // Create new scope for function body
    enterScope(true);
    
    // Add parameters to function scope
    for(const auto& pSym : paramSymbolsList){
        if(!currentScope->define(pSym->name, pSym)){
            addError("Failed to define parameter '" + pSym->name + "' in function scope (should be impossible).", pSym->definitionNode->getStart());
        }
    }
    
    // Process function body
    visitBlock(ctx->block());
    
    // Verify return statements for non-void functions
    if (returnType->baseType != Type::VOID && !currentFunctionHasReturn) {
        addError("Non-void function '" + funcName + "' might not return a value on all paths.", ctx->Identifier()->getSymbol());
    }

    // Clean up function scope and context
    exitScope();
    currentFunctionSymbol = nullptr;
    return nullptr;
}

/**
 * @brief Processes constant declarations and performs semantic analysis
 * 
 * This method analyzes constant declarations by:
 * 1. Extracting the base type (int, float, char) and marking it as const
 * 2. Processing each constant definition including array types with dimensions
 * 3. Validating initializer expressions are compile-time constants
 * 4. Verifying type compatibility between initializers and declared constants
 * 5. Storing constant values for use in compile-time expression evaluation
 * 
 * @param ctx The constant declaration context from the parser
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) {
    // Extract the base type from the declaration and mark it as const
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    baseType->isConst = true;

    // Process each constant definition in this declaration
    for (auto* constDefCtx : ctx->constantDefinition()) {
        std::string name = constDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType;
        std::vector<int> dimensions;

        // Handle array type declarations with dimensions
        if (!constDefCtx->LeftBracket().empty()) {
            // Parse and validate each array dimension
            for (auto* intConst : constDefCtx->IntegerConstant()) {
                try {
                    dimensions.push_back(std::stoi(intConst->getText()));
                } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0); // Use fallback value to continue analysis
                }
            }
            // Create array type with the appropriate dimensions
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
            actualType->isConst = true;
        } else {
             // For scalar constants, use the base type directly
             actualType = std::make_shared<Type>(*baseType);
             actualType->isConst = true;
        }

        // Create symbol information for this constant
        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::CONSTANT, constDefCtx);
        
        // Constants must have initializers
        if (!constDefCtx->constantInitializationValue()) {
             addError("Constant '" + name + "' must be initialized.", constDefCtx->Identifier()->getSymbol());
        } else {
            // Set up context for initializer validation
            expectingConstantInitializer = true;
            expectedInitializerType = actualType;
            
            // Validate the initializer expression
            antlrcpp::Any initValueAny = visitConstantInitializationValue(constDefCtx->constantInitializationValue());
            
            // For scalar constants, verify the initializer value and type
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
                        // Store the constant value for future compile-time evaluation
                        symbol->constValue = initVal.value;
                        symbol->hasConstValue = initVal.hasValue;
                    }
                } else {
                     addError("Internal error: Could not evaluate constant initializer for '" + name + "'.", 
                              constDefCtx->constantInitializationValue()->getStart());
                }
            }
            // Reset initializer context
            expectingConstantInitializer = false;
            expectedInitializerType = nullptr;
            isVariableInitializer = false; // 重置标志
        }
        
        // Constants are always considered initialized (even if with error)
        symbol->isInitialized = true;

        // Add symbol to current scope, check for redefinitions
        if (!currentScope->define(name, symbol)) {
            addError("Redefinition of constant '" + name + "'.", constDefCtx->Identifier()->getSymbol());
        }
    }
    return nullptr;
}

/**
 * @brief Processes a variable declaration
 * 
 * This method handles the semantic analysis of variable declarations by:
 * 1. Extracting the base type for the variables
 * 2. Processing each variable definition to determine its complete type (basic or array)
 * 3. Validating initializers when present
 * 4. Checking for type compatibility between variables and their initializers
 * 5. Adding symbols to the current scope with appropriate checking for redefinitions
 * 
 * @param ctx The variable declaration context
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) {
    // Extract the base type from the declaration
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));

    // Process each variable definition in this declaration
    for (auto* varDefCtx : ctx->variableDefinition()) {
        std::string name = varDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType;
        std::vector<int> dimensions;

        // Handle array type declarations with dimensions
        if (!varDefCtx->LeftBracket().empty()) {
            // Parse and validate each array dimension
            for (auto* intConst : varDefCtx->IntegerConstant()) {
                 try {
                    int dim = std::stoi(intConst->getText());
                    dimensions.push_back(dim);
                 } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0); // Use a fallback value to continue analysis
                 }
            }
            // Create array type with appropriate dimensions
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
        } else {
            // For scalar variables, simply use the base type
            actualType = std::make_shared<Type>(*baseType);
        }

        // Create symbol information for this variable
        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::VARIABLE, varDefCtx);

        // Process variable initializer if present
        if (varDefCtx->constantInitializationValue()) {
            symbol->isInitialized = true;
            
            // Set up context for initializer validation
            expectingConstantInitializer = true;
            expectedInitializerType = actualType;
            isVariableInitializer = true; // 标记这是变量初始化

            // Validate the initializer
            antlrcpp::Any initValueAny = visitConstantInitializationValue(varDefCtx->constantInitializationValue());

            if (actualType->baseType == Type::ARRAY) {
                // Array initializer validation is handled by visitConstantInitializationValue
                // Result is a boolean indicating success/failure
                if (initValueAny.type() == typeid(bool) && !std::any_cast<bool>(initValueAny)) {
                    // Error already reported in visitConstantInitializationValue
                }
            } else {
                 // For scalar variables, verify the initializer type and value
                 if (initValueAny.type() == typeid(ConstEvalResult)) {
                    ConstEvalResult initVal = std::any_cast<ConstEvalResult>(initValueAny);
                    
                    // 检查是否是全局作用域 - 只有全局变量需要编译时常量
                    bool isGlobalScope = (currentScope && currentScope->getParent() == nullptr);
                    
                    if (!initVal.isConst && isGlobalScope) {
                        addError("Initializer for global variable '" + name + "' must be a compile-time constant expression.", 
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
            // Reset initializer context
            expectingConstantInitializer = false;
            expectedInitializerType = nullptr;
            isVariableInitializer = false; // 重置标志
        } else {
            // No initializer present - mark as uninitialized
            symbol->isInitialized = false;
        }

        // Add symbol to current scope, check for redefinitions
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
 * This method extracts type information and creates a symbol for a function parameter.
 * 
 * @param ctx The function formal parameter context
 * @return A SymbolInfo object representing the parameter
 */
antlrcpp::Any SemanticAnalyzer::visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) {
    // Extract the base type (int, float, char)
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> actualType = baseType;

    // Handle array parameter types
    if (!ctx->LeftBracket().empty()) {
        std::vector<int> dimensions;
        int bracketPairCount = ctx->LeftBracket().size();
        auto intConstants = ctx->IntegerConstant();
        
        // Check if first dimension is implicit (e.g., int a[][10] vs int a[5][10])
        bool firstDimImplicit = intConstants.size() < bracketPairCount;
        
        // Process each dimension
        for (int i = 0; i < bracketPairCount; i++) {
            int dimension = -1;
            if (i == 0 && firstDimImplicit) {
                // First dimension is unspecified (marked with -1)
                dimension = -1;
            } else {
                // Calculate the index in the IntegerConstant list
                int constantIndex = firstDimImplicit ? i - 1 : i;
                if (constantIndex >= 0 && constantIndex < intConstants.size()) {
                    // Parse the dimension value, handling potential errors
                    try {
                        dimension = std::stoi(intConstants[constantIndex]->getText());
                    } catch (const std::out_of_range& oor) {
                        addError("Integer constant for array dimension is out of range.", intConstants[constantIndex]->getSymbol());
                        dimension = 0; // Fallback to prevent further errors
                    } catch (const std::invalid_argument& ia) {
                        addError("Invalid integer constant for array dimension.", intConstants[constantIndex]->getSymbol());
                        dimension = 0; // Fallback to prevent further errors
                    }
                }
            }
            dimensions.push_back(dimension);
        }
        
        // Create array type with extracted dimensions
        actualType = std::make_shared<Type>(Type::ARRAY);
        actualType->elementType = baseType;
        actualType->dimensions = dimensions;
    } else {
        // For non-array parameters, use the base type
        actualType = std::make_shared<Type>(*baseType);
    }
    
    // Create symbol information for this parameter
    auto paramSymbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::PARAMETER, ctx);
    paramSymbol->isInitialized = true; // Parameters are always considered initialized
    return paramSymbol;
}

/**
 * @brief Processes a code block
 * 
 * This method handles the semantic analysis of code blocks by:
 * 1. Creating a new scope for local declarations (except for function body blocks)
 * 2. Processing all declarations and statements within the block
 * 3. Tracking return statements for control flow analysis
 * 4. Managing scope lifetime appropriately
 * 
 * @param ctx The block context from the parser
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitBlock(CactParser::BlockContext *ctx) {
    // Check if this block is a function body (special case - scope already created in visitFunctionDefinition)
    bool isFunctionBodyBlock = dynamic_cast<CactParser::FunctionDefinitionContext*>(ctx->parent) != nullptr;

    // Only create a new scope if this isn't a function body block
    if (!isFunctionBodyBlock) {
        // Preserve loop context when creating nested scopes within loops
        enterScope(false, currentScope ? currentScope->isLoop() : false);
    }

    // Track return statement analysis for control flow validation
    bool allPathsReturn = true;
    bool hasReturnStatement = false;
    
    // Process each item in the block (declarations and statements)
    for (auto* item : ctx->blockItem()) {
        if (item->declaration()) {
            // Process variable and constant declarations
            visitDeclaration(item->declaration());
        } else if (item->statement()) {
            // Track if this statement introduces a return
            bool prevReturn = currentFunctionHasReturn;
            visitStatement(item->statement());
            
            // Record if we found a new return statement
            if (!prevReturn && currentFunctionHasReturn) {
                hasReturnStatement = true;
            }
            
            // If we encounter a return statement, remaining code is unreachable
            if (item != ctx->blockItem().back() && currentFunctionHasReturn) {
                break;
            }
        }
    }
    
    // Update control flow analysis information
    if (!hasReturnStatement) {
        allPathsReturn = false;
    }

    // Clean up scope (except for function body blocks)
    if (!isFunctionBodyBlock) {
        exitScope();
    }
    return nullptr;
}

/**
 * @brief Processes various statement types in the CACT language
 * 
 * This method performs semantic analysis on statements by:
 * 1. Validating return statements - checks type compatibility with function signatures
 * 2. Verifying assignment operations - ensures LHS is assignable and types match
 * 3. Processing control flow statements - if/while/break/continue with appropriate context checks
 * 4. Tracking function return paths for control flow analysis
 * 
 * @param ctx The statement context from the parser
 * @return nullptr (semantic analysis modifies state but doesn't return values)
 */
antlrcpp::Any SemanticAnalyzer::visitStatement(CactParser::StatementContext *ctx) {    
    if (ctx->Return()) {
        // Return statement validation
        if (!currentFunctionSymbol) {
            addError("'return' statement outside of function.", ctx->Return()->getSymbol());
            return nullptr;
        }
        currentFunctionHasReturn = true;
        std::shared_ptr<Type> expectedReturnType = currentFunctionSymbol->type->elementType;

        if (ctx->expression()) {
            // Check if returning value from void function (error)
            if (expectedReturnType->baseType == Type::VOID) {
                addError("Cannot return a value from a void function '" + currentFunctionSymbol->name + "'.", ctx->Return()->getSymbol());
            } else {
                // Validate return type compatibility
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
            // Check if missing return value in non-void function (error)
            if (expectedReturnType->baseType != Type::VOID) {
                addError("Non-void function '" + currentFunctionSymbol->name + "' must return a value.", ctx->Return()->getSymbol());
            }
        }
    } else if (ctx->leftValue() && ctx->Equal() && ctx->expression()) {
        // Assignment statement validation
        std::shared_ptr<Type> lvalType = std::any_cast<std::shared_ptr<Type>>(visitLeftValue(ctx->leftValue()));
        std::shared_ptr<Type> expType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()));

        if (lvalType->baseType == Type::ERROR_TYPE || expType->baseType == Type::ERROR_TYPE) {
            return nullptr;
        }

        // Verify LHS is assignable (must be an L-value and non-const)
        if (!lvalType->isLValue) {
            addError("Expression is not assignable (not an L-value).", ctx->leftValue()->getStart());
            return nullptr;
        }
        if (lvalType->isConst) {
            addError("Cannot assign to a constant '" + ctx->leftValue()->getText() + "'.", ctx->leftValue()->getStart());
            return nullptr;
        }

        // Check type compatibility (CACT doesn't allow implicit conversions)
        auto tempLval = std::make_shared<Type>(*lvalType); tempLval->isConst = false;
        auto tempExp = std::make_shared<Type>(*expType); tempExp->isConst = false;

        if (!tempLval->equals(*tempExp)) {
             addError("Type mismatch in assignment: cannot assign '" + expType->toString() +
                     "' to '" + lvalType->toString() + "'.", ctx->Equal()->getSymbol());
        }

    } else if (ctx->expression()) {
        // Expression statement (e.g., function call)
        visitExpression(ctx->expression());
    } else if (ctx->block()) {
        // Block statement (compound statement)
        visitBlock(ctx->block());
    } else if (ctx->If()) {
        // If statement validation
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
        if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            addError("Condition for 'if' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        // Track return status for control flow analysis
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
        
        // Function returns only if all branches return
        if (ctx->Else()) {
            currentFunctionHasReturn = thenBranchReturns && elseBranchReturns;
        } else {
            currentFunctionHasReturn = oldHasReturn;
        }
    } else if (ctx->While()) {
        // While loop validation
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
        if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            addError("Condition for 'while' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        // Create a new loop scope for break/continue validation
        Scope* preLoopScope = currentScope;
        currentScope = new Scope(preLoopScope, preLoopScope->isFunction(), true);

        // Loop body may or may not execute, so don't count it for return analysis
        bool oldHasReturn = currentFunctionHasReturn;
        visitStatement(ctx->statement(0));
        currentFunctionHasReturn = oldHasReturn;

        // Restore the pre-loop scope
        Scope* temp = currentScope;
        currentScope = preLoopScope;
        delete temp;

    } else if (ctx->Break()) {
        // Break statement validation - must be within a loop
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
        // Continue statement validation - must be within a loop 
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
 * @brief Evaluates expressions for compile-time constant values
 * 
 * This method determines whether an expression can be evaluated at compile time
 * and if so, computes its value. It analyzes:
 * 1. Whether the expression is a compile-time constant
 * 2. The expression's type
 * 3. The expression's computed value (when applicable)
 * 
 * In CACT, only a limited subset of expressions qualify as compile-time constants:
 * - Literal constants (integers, floats, characters)
 * - Named constant variables
 * - Simple unary operations with +/- applied to literals
 * 
 * @param addCtx The additive expression context to evaluate
 * @return A ConstEvalResult containing type, value, and constness information
 */
SemanticAnalyzer::ConstEvalResult SemanticAnalyzer::evaluateAddExpressionAsConstant(CactParser::AddExpressionContext* addCtx) {
    // Return error result for null input
    if (!addCtx) return {Type::getError(), {}, false, false};
    
    // Initialize result with default error values
    ConstEvalResult result;
    result.type = Type::getError(); 
    result.isConst = false;      // Not a constant expression by default
    result.hasValue = false;     // No evaluated value available by default

    // Check if this is a binary expression with + or - operators
    // CACT doesn't support binary operations as compile-time constants
    if (addCtx->addExpression()) { 
        return result; 
    }

    auto currentMulExp = addCtx->multiplicativeExpression();
    // Multiplicative operations (*, /, %) cannot be compile-time constants
    if (currentMulExp->multiplicativeExpression()) { 
        return result; 
    }

    auto currentUnaryExp = currentMulExp->unaryExpression();
    // Track application of unary operators
    bool isNegative = false;     // For tracking unary minus
    bool isPositive = false;     // For tracking unary plus

    // Function calls cannot be evaluated at compile-time
    if (currentUnaryExp->Identifier() && currentUnaryExp->LeftParenthesis()) {
        // 在变量初始化上下文中，尽管函数调用不是编译时常量，但可以用作局部变量的初始化值
        if (isVariableInitializer) {
            std::string funcName = currentUnaryExp->Identifier()->getText();
            auto symbol = currentScope->resolve(funcName);
            
            if (symbol && symbol->kind == SymbolInfo::FUNCTION_DEF) {
                // 返回函数的返回类型，但标记为非常量
                result.isConst = false;
                result.hasValue = false;
                result.type = symbol->type->elementType; // 函数的返回类型
                return result;
            }
        }
        return result;
    }

    // Process unary operators if present
    CactParser::UnaryExpressionContext* unaryExpForPrimary = currentUnaryExp;
    if (currentUnaryExp->Plus()) {
        isPositive = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    } else if (currentUnaryExp->Minus()) {
        isNegative = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    }
    
    // Nested function calls cannot be compile-time constants
    if (unaryExpForPrimary->Identifier() && unaryExpForPrimary->LeftParenthesis()){
        // 在变量初始化上下文中，处理嵌套函数调用
        if (isVariableInitializer) {
            std::string funcName = unaryExpForPrimary->Identifier()->getText();
            auto symbol = currentScope->resolve(funcName);
            
            if (symbol && symbol->kind == SymbolInfo::FUNCTION_DEF) {
                // 返回函数的返回类型，但标记为非常量
                result.isConst = false;
                result.hasValue = false;
                result.type = symbol->type->elementType; // 函数的返回类型
                return result;
            }
        }
        return result;
    }

    // Logical NOT operations are not supported for compile-time evaluation
    if (unaryExpForPrimary->ExclamationMark()) {
        return result; 
    }
    
    // Process primary expressions for constant evaluation
    if (unaryExpForPrimary->primaryExpression()) {
        auto primExp = unaryExpForPrimary->primaryExpression();
        
        // Case 1: Process numeric or character literals
        if (primExp->number()) {
            // Mark as a constant expression since we're evaluating a literal
            result.isConst = true;
            
            // Process integer literal
            if (primExp->number()->IntegerConstant()) {
                try {
                    // Convert string representation to int value
                    int val = std::stoi(primExp->number()->IntegerConstant()->getText());
                    if (isNegative) val = -val;
                    
                    result.value = val;
                    result.hasValue = true;
                    result.type = Type::getInt(expectingConstantInitializer && 
                                           expectedInitializerType && 
                                           expectedInitializerType->isConst);
                } catch (...) { 
                    // Integer parsing error (e.g., value out of range)
                    result.isConst = false; 
                }
            }
            // Process floating point literal
            else if (primExp->number()->FloatConstant()) {
                try {
                    // Convert string representation to float value
                    float val = std::stof(primExp->number()->FloatConstant()->getText());
                    if (isNegative) val = -val;
                    
                    result.value = val;
                    result.hasValue = true;
                    result.type = Type::getFloat(expectingConstantInitializer && 
                                             expectedInitializerType && 
                                             expectedInitializerType->isConst);
                } catch (...) { 
                    // Float parsing error (e.g., value out of range)
                    result.isConst = false; 
                }
            }
            // Process character literal
            else if (primExp->number()->CharacterConstant()) {
                // Get the raw character literal text (including quotes)
                std::string text = primExp->number()->CharacterConstant()->getText();
                
                // Unary +/- operators cannot be applied to character literals
                if (isNegative || isPositive) { 
                    addError("Unary '+' or '-' cannot be applied to character constant.", primExp->number()->getStart());
                    result.isConst = false;
                    result.hasValue = false;
                    result.type = Type::getError();
                } 
                // Validate character literal format
                else if (text.length() >= 3 && text.front() == '\'' && text.back() == '\'') {
                    // Simple character (e.g., 'a', 'Z', '5')
                    if (text.length() == 3) { 
                        result.value = text[1]; 
                        result.hasValue = true;
                        result.type = Type::getChar(expectingConstantInitializer && 
                                                expectedInitializerType && 
                                                expectedInitializerType->isConst);
                    } 
                    // Escape sequence (e.g., '\n', '\t', '\\')
                    else if (text.length() == 4 && text[1] == '\\') { 
                        char unescaped_char;
                        bool recognized_escape = true;
                        
                        // Convert escape sequence to actual character value
                        switch (text[2]) {
                            case 'n': unescaped_char = '\n'; break;  // Newline
                            case 't': unescaped_char = '\t'; break;  // Tab
                            case 'r': unescaped_char = '\r'; break;  // Carriage return
                            case '\\': unescaped_char = '\\'; break; // Backslash
                            case '\'': unescaped_char = '\''; break; // Single quote
                            case '0': unescaped_char = '\0'; break;  // Null character
                            default: recognized_escape = false; break; // Unrecognized escape
                        }
                        
                        if (recognized_escape) {
                            result.value = unescaped_char; 
                            result.hasValue = true;
                            result.type = Type::getChar(expectingConstantInitializer && 
                                                    expectedInitializerType && 
                                                    expectedInitializerType->isConst);
                        } 
                        else {
                            addError("Unrecognized character escape sequence: '" + text + "'.", 
                                    primExp->number()->CharacterConstant()->getSymbol());
                            result.isConst = false;
                            result.hasValue = false;
                            result.type = Type::getError();
                        }
                    } 
                    // Invalid character format (wrong length or invalid escape sequence)
                    else {
                        addError("Invalid character literal format: '" + text + "'.", 
                                primExp->number()->CharacterConstant()->getSymbol());
                        result.isConst = false;
                        result.hasValue = false;
                        result.type = Type::getError();
                    }
                } 
                // Invalid character format (missing quotes or empty character)
                else {
                    addError("Invalid character literal format: '" + text + "'.", 
                            primExp->number()->CharacterConstant()->getSymbol());
                    result.isConst = false;
                    result.hasValue = false; 
                    result.type = Type::getError();
                }
            }
            return result;
        }
        // Case 2: Process references to named constants
        else if (primExp->leftValue()) {
            // Cannot apply unary operators to identifiers in compile-time evaluation
            if (isNegative || isPositive) { 
                 return result; 
            }
            // Only simple variable references (not array elements) can be compile-time constants
            if (primExp->leftValue()->Identifier() && primExp->leftValue()->LeftBracket().empty()) {
                std::string name = primExp->leftValue()->Identifier()->getText();
                auto symbol = currentScope->resolve(name);
                
                if (symbol) {
                    // 常量符号：如果有已知值，返回编译时常量
                    if (symbol->kind == SymbolInfo::CONSTANT && symbol->hasConstValue) {
                        result.isConst = true;
                        result.value = symbol->constValue;
                        result.hasValue = true;
                        result.type = symbol->type; 
                        return result;
                    }
                    // 变量符号：在变量初始化上下文中，返回类型信息但标记为非常量
                    else if (symbol->kind == SymbolInfo::VARIABLE && isVariableInitializer) {
                        result.isConst = false; // 不是编译时常量
                        result.hasValue = false; // 没有已知值
                        result.type = symbol->type; // 但有正确的类型
                        return result;
                    }
                }
            }
        }
    }
    return result;
}

/**
 * @brief Validates initializers for constants and variables
 * 
 * This method processes initializer expressions by:
 * 1. Verifying the initializer is a compile-time constant
 * 2. Checking type compatibility between initializer and variable/constant
 * 3. For arrays, validating that initializer structure matches array dimensions
 * 
 * @param ctx The constant initialization value context
 * @return Either a ConstEvalResult for scalar initializers, or a boolean for array initializers
 */
antlrcpp::Any SemanticAnalyzer::visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) {
    // Verify proper context is set before processing initializers
    if (!expectingConstantInitializer || !expectedInitializerType) {
        addError("Internal error: visitConstantInitializationValue called without proper context.", ctx->getStart());
        return SemanticAnalyzer::ConstEvalResult{Type::getError(), {}, false, false};
    }

    if (ctx->constantExpression()) {
        // Case 1: Scalar initializer expression (e.g., '= 5', '= x + 2')
        // Attempt to statically evaluate the expression
        ConstEvalResult evalRes = evaluateAddExpressionAsConstant(ctx->constantExpression()->addExpression()); 
        
        // 检查是否需要强制常量
        bool requiresConstant = !isVariableInitializer; // 常量声明需要编译时常量
        if (isVariableInitializer) {
            // 变量初始化：只有全局变量需要编译时常量，局部变量可以用运行时值
            bool isGlobalScope = (currentScope && currentScope->getParent() == nullptr);
            requiresConstant = isGlobalScope;
        }
        
        if (!evalRes.isConst && requiresConstant) {
            if (isVariableInitializer) {
                addError("Initializer for global variable must be a compile-time constant.", ctx->constantExpression()->getStart());
            } else {
                addError("Initializer must be a compile-time constant.", ctx->constantExpression()->getStart());
            }
            return evalRes; 
        }
        
        // Check if trying to initialize an array with a scalar value
        if (expectedInitializerType->baseType == Type::ARRAY) { 
            addError("Cannot initialize array with a scalar value. Use braced initializer list '{...}'.", ctx->getStart());
            return ConstEvalResult{Type::getError(), {}, false, false};
        }
        
        // For scalar types, verify type compatibility between initializer and variable
        if (expectedInitializerType->baseType != Type::ARRAY) { 
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
        // Case 2: Array initializer (e.g., '= {1, 2, 3}', '= {{1, 2}, {3, 4}}')
        if (expectedInitializerType->baseType != Type::ARRAY) {
            // Braced initializer lists are only valid for array types
            addError("Braced initializer list cannot be used with non-array type '" + 
                    expectedInitializerType->toString() + "'.", ctx->LeftBrace()->getSymbol());
            return false; 
        }
        
        // Validate the structure and contents of the array initializer
        std::vector<ConstEvalResult> flatInitializers;
        std::shared_ptr<Type> originalExpectedType = expectedInitializerType; 
        
        // Recursively check the initializer expression structure
        int initCount = checkArrayInitializerRecursive(ctx, expectedInitializerType->elementType, 
                                                      expectedInitializerType->dimensions, 0, flatInitializers);
        
        // Restore the expected type (may have been modified during recursive checks)
        expectedInitializerType = originalExpectedType; 
        
        // Non-negative return value indicates successful validation
        return initCount >= 0;
    }
    
    // Default error case
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
 * @return The number of elements processed at the current level, or -1 on error
 */
int SemanticAnalyzer::checkArrayInitializerRecursive(
    CactParser::ConstantInitializationValueContext* initCtx, 
    std::shared_ptr<Type> expectedElementType, 
    const std::vector<int>& dimensions, 
    int currentDimensionIndex,
    std::vector<ConstEvalResult>& flatInitializers) 
{
    // Case 1: Process a scalar initializer (not a brace-enclosed list)
    if (!initCtx || !initCtx->LeftBrace()) {
        if (initCtx && initCtx->constantExpression()) {
            // Find the ultimate element type for multi-dimensional arrays
            // E.g., for int[2][3], the ultimate element type is int
            std::shared_ptr<Type> ultimateElementType = expectedElementType;
            // For non-braced initialization, get the base type directly
            if (expectedElementType && expectedElementType->baseType == Type::ARRAY) {
                std::shared_ptr<Type> tempType = expectedElementType;
                while(tempType->baseType == Type::ARRAY) {
                    tempType = tempType->elementType;
                }
                ultimateElementType = tempType;
            }

            if (!ultimateElementType) {
                addError("Internal error: array ultimate element type is null.", initCtx->getStart());
                return -1;
            }

            // Save and restore the expected initializer type during validation
            std::shared_ptr<Type> oldExpected = expectedInitializerType;
            expectedInitializerType = ultimateElementType;

            // Evaluate the constant expression
            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(initCtx));
            
            expectedInitializerType = oldExpected;

            // Verify the expression is a compile-time constant
            if (!val.isConst) { return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;

            // Verify type compatibility
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          initCtx->constantExpression()->getStart());
                 return -1;
            }
            // Add the validated element to our collection
            flatInitializers.push_back(val);
            return 1;
        }
        addError("Invalid array initializer: expected '{...}' or constant expression.", initCtx ? initCtx->getStart() : nullptr);
        return -1;
    }

    // Note: CACT allows multi-dimensional arrays to be initialized with 
    // flattened initializers, so we don't check dimension count here

    // Count elements processed at this dimension level
    int count = 0;
    // Get maximum elements allowed in this dimension
    // (-1 means unlimited, as in function parameters: int func(int arr[][10]))
    int maxElementsInThisDimension = (dimensions[currentDimensionIndex] == -1) ? -1 : dimensions[currentDimensionIndex];

    // Calculate total array capacity
    int totalArrayCapacity = 1;
    for (size_t i = 0; i < dimensions.size(); i++) {
        if (dimensions[i] > 0) {
            totalArrayCapacity *= dimensions[i];
        }
    }
    
    // Process each sub-initializer in this brace-enclosed list
    for (auto* subInitCtx : initCtx->constantInitializationValue()) {
        // For flat initialization, check if total initializers exceed array capacity
        if (currentDimensionIndex == 0 && flatInitializers.size() >= totalArrayCapacity) {
            addError("Too many initializers for array with total capacity of " + 
                     std::to_string(totalArrayCapacity) + " elements.", subInitCtx->getStart());
            return -1;
        }

        int subCount;
        // Case 2a: This element is itself a brace-enclosed initializer (nested array)
        if (subInitCtx->LeftBrace()) {
            // Skip dimension check for CACT which allows flexible initialization

            if (!expectedElementType) {
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }

            // Recursively process the next level of initializers
            subCount = checkArrayInitializerRecursive(subInitCtx, expectedElementType, dimensions, currentDimensionIndex + 1, flatInitializers);
        } else {
            // Case 2b: This element is a scalar value
            std::shared_ptr<Type> oldExpected = expectedInitializerType;
            
            if (!expectedElementType) {
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }
            
            // Find the ultimate element type (base type of potentially nested arrays)
            std::shared_ptr<Type> ultimateElementType = expectedElementType;
            while(ultimateElementType->baseType == Type::ARRAY) {
                ultimateElementType = ultimateElementType->elementType;
            }
            
            expectedInitializerType = ultimateElementType;

            // Validate the scalar element
            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(subInitCtx));
            
            expectedInitializerType = oldExpected;

            // Verify compile-time constant status
            if (!val.isConst) { return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;
            
            // Verify type compatibility
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          subInitCtx->constantExpression()->getStart());
                 return -1;
            }
            
            flatInitializers.push_back(val);
            subCount = 1;
        }

        // Propagate errors upward
        if (subCount < 0) return -1;
        // Track element count
        count += subCount;
    }
    
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
 * @brief Processes unary expressions in CACT language
 * 
 * This method handles three types of expressions:
 * 1. Primary expressions (literals, variables, parenthesized expressions)
 * 2. Unary operators (+, -, !) with appropriate type checking
 * 3. Function calls with parameter validation
 * 
 * For unary operators, it verifies type compatibility with the operand.
 * For function calls, it validates existence, parameter count/types, and
 * handles array parameter passing with special dimension checking rules.
 * 
 * @param ctx The unary expression context from the parser
 * @return The type of the unary expression after semantic analysis
 */
antlrcpp::Any SemanticAnalyzer::visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) {
    // Handle primary expressions (literals, variables, etc.)
    if (ctx->primaryExpression()) {
        return visitPrimaryExpression(ctx->primaryExpression());
    }
    
    // Handle unary operators (+, -, !)
    if (ctx->unaryExpression()) {
        std::shared_ptr<Type> operandType = std::any_cast<std::shared_ptr<Type>>(visitUnaryExpression(ctx->unaryExpression()));
        if (operandType->baseType == Type::ERROR_TYPE) return Type::getError();

        // Unary plus and minus require numeric operands (int or float)
        if (ctx->Plus() || ctx->Minus()) {
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT) {
                addError("Unary '+' or '-' must be applied to numeric type, got '" + operandType->toString() + "'.", 
                         (ctx->Plus() ? ctx->Plus()->getSymbol() : ctx->Minus()->getSymbol()) );
                return Type::getError();
            }
            return operandType;
        }
        
        // Logical NOT (!) can only be used in conditional contexts
        if (ctx->ExclamationMark()) {
            if (!inConditionContext) {
                addError("Logical NOT '!' operator can only be used in condition expressions.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            
            // NOT requires numeric or char operands that can be treated as boolean
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT && operandType->baseType != Type::CHAR) {
                addError("Logical NOT '!' must be applied to numeric or char type, got '" + operandType->toString() + "'.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            // Logical operations always yield int (boolean) result
            return Type::getInt();
        }
    }
    
    // Handle function calls
    if (ctx->Identifier() && ctx->LeftParenthesis()) {
        std::string funcName = ctx->Identifier()->getText();
        auto symbol = currentScope->resolve(funcName);
        
        // Verify function exists
        if (!symbol) {
            addError("Function '" + funcName + "' not defined.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }
        
        // Verify identifier refers to a function
        if (symbol->kind != SymbolInfo::FUNCTION_DEF) {
            addError("'" + funcName + "' is not a function.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }

        // Extract function signature information
        std::shared_ptr<Type> funcType = symbol->type;
        std::vector<std::shared_ptr<Type>> expectedParamTypes = funcType->paramTypes;
        std::vector<std::shared_ptr<Type>> actualParamTypes;
        
        // Collect actual parameter types from the function call
        if (ctx->functionRealParameters()) {
            for (auto* expCtx : ctx->functionRealParameters()->expression()) {
                actualParamTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visitExpression(expCtx)));
            }
        }
        
        // Verify parameter count matches the function declaration
        if (actualParamTypes.size() != expectedParamTypes.size()) {
            addError("Function '" + funcName + "' called with incorrect number of arguments. Expected " +
                     std::to_string(expectedParamTypes.size()) + ", got " + std::to_string(actualParamTypes.size()) + ".",
                     ctx->Identifier()->getSymbol());
            return funcType->elementType;
        }

        // Validate each parameter's type
        for (size_t i = 0; i < expectedParamTypes.size(); ++i) {
            if (actualParamTypes[i]->baseType == Type::ERROR_TYPE) continue;
            
            // Create copies of types without const qualifiers for comparison
            auto tempExpected = std::make_shared<Type>(*expectedParamTypes[i]); tempExpected->isConst = false;
            auto tempActual = std::make_shared<Type>(*actualParamTypes[i]); tempActual->isConst = false;

            bool skipErrorReport = false;
            
            // Special handling for array parameters - CACT allows first dimension to be unspecified
            if (tempExpected->baseType == Type::ARRAY && tempActual->baseType == Type::ARRAY) {
                if (tempExpected->dimensions.size() == tempActual->dimensions.size()) {
                    // First dimension can be flexible if marked as -1 in either declaration or call
                    if (tempExpected->dimensions[0] == -1 || tempActual->dimensions[0] == -1) {
                        // But all other dimensions must match exactly
                        bool otherDimensionsMatch = true;
                        for (size_t dim = 1; dim < tempExpected->dimensions.size(); ++dim) {
                            if (tempExpected->dimensions[dim] != tempActual->dimensions[dim]) {
                                otherDimensionsMatch = false;
                                break;
                            }
                        }
                        
                        // If element types also match, then arrays are compatible
                        if (otherDimensionsMatch && tempExpected->elementType->equals(*tempActual->elementType)) {
                            skipErrorReport = true;
                        }
                    }
                }
            }
            
            // Report type mismatch errors for incompatible parameters
            if (!skipErrorReport && !tempExpected->equals(*tempActual)) {
                std::string errorMsg = "Type mismatch for argument " + std::to_string(i + 1) + " of function '" + funcName + "'. ";
                
                errorMsg += "Expected '" + expectedParamTypes[i]->toString() + "', got '" + 
                          actualParamTypes[i]->toString() + "'. ";
                          
                // Provide detailed dimension information for array mismatches
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
        
        // Return the function's return type
        return funcType->elementType;
    }
    
    // Default error case
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
 * This method evaluates and type-checks equality operations by:
 * 1. Recursively processing left and right operands
 * 2. Verifying both operands are of primitive types (int, float, char)
 * 3. Enforcing CACT's strict type matching rules (no implicit conversions)
 * 4. Setting the result type to int (representing boolean true/false)
 * 
 * @param ctx The equality expression context from the parser
 * @return A Type object representing the result type (int for valid expressions)
 */
antlrcpp::Any SemanticAnalyzer::visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) {
    if (ctx->equalityExpression()) {
        // Process both sides of the equality operation
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitEqualityExpression(ctx->equalityExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitRelationalExpression(ctx->relationalExpression()));

        // Skip further checks if either operand has errors
        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // Verify both operands are primitive types that can be compared
        bool left_ok = (left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR);
        bool right_ok = (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR);
        
        if (!(left_ok && right_ok)) {
            // Determine which operator was used (== or !=) for error reporting
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();

            addError("Operands for equality operators ('==', '!=') must be numeric or char, got '" +
                     left->toString() + "' and '" + right->toString() + "'.",
                     opToken);
            return Type::getError();
        }
        
        // CACT rule: char can only be compared with char
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
        
        // CACT rule: numeric types must match exactly (no int/float conversion)
        if (left->baseType != Type::CHAR && right->baseType != left->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();
            
            addError("Type mismatch in equality expression: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        
        // All equality operations yield int result (1 for true, 0 for false)
        return Type::getInt();
    } else {
        // Base case: no equality operator, delegate to relational expression
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
