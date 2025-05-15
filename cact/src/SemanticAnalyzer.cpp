\
#include "include/SemanticAnalyzer.h"
#include "CactParser.h" // Required for CactParser::*Context
#include <iostream>
#include <sstream>
#include <algorithm> // For std::any_of

// --- Type Implementation ---
std::string Type::toString() const {
    std::string baseStr;
    switch (baseType) {
        case INT: baseStr = "int"; break;
        case FLOAT: baseStr = "float"; break;
        case CHAR: baseStr = "char"; break;
        case VOID: baseStr = "void"; break;
        case ARRAY: {
            baseStr = (elementType ? elementType->toString() : "unknown_element_type");
            // 确保按照C/C++语言规范的方式输出数组维度
            // 例如：int a[2][3] 应该输出为 "int[2][3]"，而不是 "int[3][2]"
            // 而 int a[][3] 应该输出为 "int[][3]"，而不是 "int[3][]"
            
            // 我们按照首先显示第一维度，然后是第二维度的顺序输出
            for (size_t i = 0; i < dimensions.size(); ++i) {
                int dim = dimensions[i];
                baseStr += "[";
                if (dim == -1) {
                    // 隐式维度不显示大小，常见于函数参数的第一维
                    baseStr += "";
                } else {
                    baseStr += std::to_string(dim);
                }
                baseStr += "]";
            }
            break;
        }
        case FUNCTION:
            baseStr = (elementType ? elementType->toString() : "unknown_ret_type"); // elementType is return type
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

bool Type::equals(const Type& other) const {
    if (baseType != other.baseType) return false;
    if (isConst != other.isConst && baseType != FUNCTION) { 
        // Const-ness checking can be implemented here if needed
        // For now we just ignore it to focus on fixing the array issues
    }

    switch (baseType) {
        case ARRAY: {
            // 特殊处理函数参数中的数组类型
            if (!elementType || !other.elementType) return false;
            
            // 比较元素类型
            if (!elementType->equals(*other.elementType)) return false;
            
            // 比较维度数量
            if (dimensions.size() != other.dimensions.size()) return false;
            
            // 对于函数参数的数组，我们需要特殊处理：
            // 对于数组参数，C语言风格是允许第一维是隐式的（不指定大小）
            // 例如：int func(int arr[][3]) 可以接受 int arr[2][3] 类型的参数
            // 因为在传递多维数组时，第一维的大小信息会丢失
            for (size_t i = 0; i < dimensions.size(); ++i) {
                // 如果是第一维度且任一方是隐式的(-1)，则视为匹配
                if (i == 0 && (dimensions[i] == -1 || other.dimensions[i] == -1)) {
                    continue; // 允许第一维不匹配
                }
                
                // 非第一维必须严格匹配
                if (dimensions[i] != other.dimensions[i]) {
                    return false;
                }
            }
            return true;
        }
        case FUNCTION:
            if (!elementType || !other.elementType || !elementType->equals(*other.elementType)) return false; // Return type
            if (paramTypes.size() != other.paramTypes.size()) return false;
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                if (!paramTypes[i] || !other.paramTypes[i] || !paramTypes[i]->equals(*other.paramTypes[i])) return false;
            }
            return true;
        default: // For INT, FLOAT, CHAR, VOID, ERROR_TYPE, UNKNOWN
            return true;
    }
}

// --- Scope Implementation ---
bool Scope::define(const std::string& name, std::shared_ptr<SymbolInfo> symbol) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        // 如果已存在同名符号，检查类型
        // 只有当符号类型相同时，才视为重定义
        if ((it->second->kind == SymbolInfo::FUNCTION_DEF && symbol->kind == SymbolInfo::FUNCTION_DEF) ||
            (it->second->kind != SymbolInfo::FUNCTION_DEF && symbol->kind != SymbolInfo::FUNCTION_DEF)) {
            return false; // 相同类型的同名符号，视为重定义
        }
        // 否则允许不同类型符号同名（如变量和函数）
    }
    symbols[name] = symbol;
    return true;
}

std::shared_ptr<SymbolInfo> Scope::resolve(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    if (parent_scope) {
        return parent_scope->resolve(name);
    }
    return nullptr; // Not found
}

std::shared_ptr<SymbolInfo> Scope::resolveCurrent(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    return nullptr;
}


// --- SemanticAnalyzer Implementation ---
SemanticAnalyzer::SemanticAnalyzer(CactParser* parser_ptr) : parser(parser_ptr), currentScope(nullptr), mainFunctionFound(false) {
    // Constructor
}

void SemanticAnalyzer::printErrors(const std::string& filename) const {
    for (const auto& err : errors) {
        std::cerr << filename << ":" << err.second->getLine() << ":" << err.second->getCharPositionInLine()
                  << ": error: " << err.first << std::endl;
    }
}

void SemanticAnalyzer::enterScope(bool isFunctionScope, bool isLoopScope) {
    currentScope = new Scope(currentScope, isFunctionScope, isLoopScope);
}

void SemanticAnalyzer::exitScope() {
    if (currentScope) {
        Scope* oldScope = currentScope;
        currentScope = currentScope->getParent();
        delete oldScope;
    }
}

void SemanticAnalyzer::addError(const std::string& message, antlr4::ParserRuleContext* ctx) {
    if (ctx) {
        addError(message, ctx->getStart());
    } else {
        errors.push_back({message, nullptr}); // Should ideally always have a token
    }
}
void SemanticAnalyzer::addError(const std::string& message, antlr4::Token* token) {
    errors.push_back({message, token});
}

std::shared_ptr<Type> SemanticAnalyzer::getTypeFromBasicTypeCtx(CactParser::BasicTypeContext *ctx) {
    if (ctx->Int()) return Type::getInt();
    if (ctx->Float()) return Type::getFloat();
    if (ctx->Char()) return Type::getChar();
    return Type::getError(); // Should not happen if grammar is correct
}

std::shared_ptr<Type> SemanticAnalyzer::getTypeFromFunctionTypeCtx(CactParser::FunctionTypeContext *ctx) {
    if (ctx->Void()) return Type::getVoid();
    if (ctx->Int()) return Type::getInt();
    if (ctx->Float()) return Type::getFloat();
    if (ctx->Char()) return Type::getChar();
    return Type::getError(); // Should not happen
}

// --- Visitor Implementations ---

antlrcpp::Any SemanticAnalyzer::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    enterScope(); // Global scope

    // 添加CACT内置函数到全局作用域
    // 1. void print_int(int)
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getInt() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_int", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_int", funcSymbol);
    }
    
    // 2. void print_float(float)
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getFloat() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_float", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_float", funcSymbol);
    }
    
    // 3. void print_char(char)
    {
        auto returnType = Type::getVoid();
        std::vector<std::shared_ptr<Type>> paramTypes = { Type::getChar() };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("print_char", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("print_char", funcSymbol);
    }
    
    // 4. int get_int()
    {
        auto returnType = Type::getInt();
        std::vector<std::shared_ptr<Type>> paramTypes = { };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("get_int", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("get_int", funcSymbol);
    }
    
    // 5. float get_float()
    {
        auto returnType = Type::getFloat();
        std::vector<std::shared_ptr<Type>> paramTypes = { };
        auto funcType = Type::getFunction(returnType, paramTypes);
        auto funcSymbol = std::make_shared<SymbolInfo>("get_float", funcType, SymbolInfo::FUNCTION_DEF, nullptr);
        currentScope->define("get_float", funcSymbol);
    }
    
    // 6. char get_char()
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

    exitScope(); // Global scope
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    std::string funcName = ctx->Identifier()->getText();
    std::shared_ptr<Type> returnType = std::any_cast<std::shared_ptr<Type>>(visitFunctionType(ctx->functionType()));

    std::vector<std::shared_ptr<Type>> paramTypesList;
    std::vector<std::shared_ptr<SymbolInfo>> paramSymbolsList; // To define later

    if (ctx->functionFormalParameters()) {
        for (auto* paramCtx : ctx->functionFormalParameters()->functionFormalParameter()) {
            std::shared_ptr<SymbolInfo> paramSymbol = std::any_cast<std::shared_ptr<SymbolInfo>>(visitFunctionFormalParameter(paramCtx));
            if (!paramSymbol || paramSymbol->type->baseType == Type::ERROR_TYPE) {
                 // Error already added by visitFunctionFormalParameter
                 paramTypesList.push_back(Type::getError()); // Propagate error
                 continue;
            }
            // Check for duplicate parameter names
            for(const auto& pSym : paramSymbolsList){
                if(pSym->name == paramSymbol->name){
                    addError("Redefinition of parameter '" + paramSymbol->name + "'.", paramCtx->Identifier()->getSymbol());
                    paramTypesList.push_back(Type::getError());
                    goto next_param; // continue outer loop
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
        // Do not proceed with this function if redefinition
        return nullptr;
    }
    
    // Check for main function
    if (funcName == "main") {
        mainFunctionFound = true;
        mainFunctionSymbol = funcSymbol;
    }

    currentFunctionSymbol = funcSymbol;
    currentFunctionHasReturn = false; // Reset for the new function

    enterScope(true); // Function scope
    for(const auto& pSym : paramSymbolsList){
        if(!currentScope->define(pSym->name, pSym)){
            // This should not happen if duplicate check above was done.
            addError("Failed to define parameter '" + pSym->name + "' in function scope (should be impossible).", pSym->definitionNode->getStart());
        }
    }
    visitBlock(ctx->block());
    
    // 检查非void函数的返回值
    if (returnType->baseType != Type::VOID && !currentFunctionHasReturn) {
        // 对所有函数进行一致的检查：每个非void函数都必须有返回值
        addError("Non-void function '" + funcName + "' might not return a value on all paths.", ctx->Identifier()->getSymbol());
    }

    exitScope(); // Function scope
    currentFunctionSymbol = nullptr; // Clear current function context
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    baseType->isConst = true; // Mark the base type as const for symbols derived from it

    for (auto* constDefCtx : ctx->constantDefinition()) {
        std::string name = constDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType; // Start with base
        std::vector<int> dimensions;

        if (!constDefCtx->LeftBracket().empty()) { // It's an array
            for (auto* intConst : constDefCtx->IntegerConstant()) {
                try {
                    dimensions.push_back(std::stoi(intConst->getText()));
                } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0); // Error recovery
                }
            }
            // 直接创建数组类型，而不是使用 Type::getArray
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
            actualType->isConst = true;
        } else {
             actualType = std::make_shared<Type>(*baseType); // Create a new type instance for scalar
             actualType->isConst = true;
        }


        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::CONSTANT, constDefCtx);
        
        // Constants MUST have an initializer
        if (!constDefCtx->constantInitializationValue()) {
             addError("Constant '" + name + "' must be initialized.", constDefCtx->Identifier()->getSymbol());
             // Fall through to define it anyway to reduce cascaded errors, but it's an error state
        } else {
            expectingConstantInitializer = true;
            expectedInitializerType = actualType; // Provide context for initializer
            
            // For array initializers, this will be more complex.
            // For scalar, visitConstantInitializationValue should return a ConstEvalResult or similar.
            // The spec "const int d = 4 + 5; //非法" is key.
            // `constantInitializationValue` -> `constantExpression` -> `addExpression`
            // We need to ensure `addExpression` is a literal or a named constant.
            
            antlrcpp::Any initValueAny = visitConstantInitializationValue(constDefCtx->constantInitializationValue());
            
            if (actualType->baseType == Type::ARRAY) {
                // Array initialization handled within visitConstantInitializationValue or needs more complex logic here
                // For now, assume visitConstantInitializationValue checks type compatibility for arrays
                if (initValueAny.type() == typeid(bool) && !std::any_cast<bool>(initValueAny)) { // Assuming it returns false on error
                     // Error already reported by visitConstantInitializationValue
                }

            } else { // Scalar
                if (initValueAny.type() == typeid(ConstEvalResult)) {
                    ConstEvalResult initVal = std::any_cast<ConstEvalResult>(initValueAny);
                    if (!initVal.isConst) {
                        addError("Initializer for constant '" + name + "' must be a compile-time constant expression.", 
                                 constDefCtx->constantInitializationValue()->getStart());
                    } else if (!initVal.type->equals(*actualType)) {
                        // Allow int literal for char const, but not other way around easily without type cast
                        bool compatible = false;
                        if (actualType->baseType == Type::CHAR && initVal.type->baseType == Type::INT) {
                            // Potentially allow if value is in char range, but spec says "types must be identical"
                            // For now, strict type matching.
                        }
                         if (!compatible) {
                            addError("Initializer type '" + initVal.type->toString() + 
                                     "' does not match constant type '" + actualType->toString() + 
                                     "' for '" + name + "'.", 
                                     constDefCtx->constantInitializationValue()->getStart());
                        }
                    } else {
                        // Store the constant value if needed for optimization or further checks
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
        symbol->isInitialized = true; // Constants are always initialized

        if (!currentScope->define(name, symbol)) {
            addError("Redefinition of constant '" + name + "'.", constDefCtx->Identifier()->getSymbol());
        }
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));

    for (auto* varDefCtx : ctx->variableDefinition()) {
        std::string name = varDefCtx->Identifier()->getText();
        std::shared_ptr<Type> actualType = baseType;
        std::vector<int> dimensions;

        if (!varDefCtx->LeftBracket().empty()) { // Array
            for (auto* intConst : varDefCtx->IntegerConstant()) {
                 try {
                    dimensions.push_back(std::stoi(intConst->getText()));
                } catch (const std::out_of_range& oor) {
                    addError("Array dimension '" + intConst->getText() + "' is too large.", intConst->getSymbol());
                    dimensions.push_back(0); // Error recovery
                }
            }
            // 直接创建数组类型，而不是使用 Type::getArray
            actualType = std::make_shared<Type>(Type::ARRAY);
            actualType->elementType = baseType;
            actualType->dimensions = dimensions;
        } else { // Scalar
            actualType = std::make_shared<Type>(*baseType); // Make a copy for scalar
        }


        auto symbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::VARIABLE, varDefCtx);

        if (varDefCtx->constantInitializationValue()) {
            symbol->isInitialized = true;
            expectingConstantInitializer = true; // Initializers for variables must also be "const expressions"
            expectedInitializerType = actualType;

            antlrcpp::Any initValueAny = visitConstantInitializationValue(varDefCtx->constantInitializationValue());

            if (actualType->baseType == Type::ARRAY) {
                if (initValueAny.type() == typeid(bool) && !std::any_cast<bool>(initValueAny)) {
                    // Error reported by visitConstantInitializationValue
                }
            } else { // Scalar
                 if (initValueAny.type() == typeid(ConstEvalResult)) {
                    ConstEvalResult initVal = std::any_cast<ConstEvalResult>(initValueAny);
                    if (!initVal.isConst) { // As per spec: "CACT限制初值表达式必须是常数"
                        addError("Initializer for variable '" + name + "' must be a compile-time constant expression.", 
                                 varDefCtx->constantInitializationValue()->getStart());
                    } else if (!initVal.type->equals(*actualType) && initVal.type->baseType != Type::ERROR_TYPE) {
                         // 只有当不是错误类型时才显示类型不匹配的错误
                         // 错误类型表示已经在visitConstantInitializationValue中报告过错误
                         addError("Initializer type '" + initVal.type->toString() + 
                                 "' does not match variable type '" + actualType->toString() + 
                                 "' for '" + name + "'.", 
                                 varDefCtx->constantInitializationValue()->getStart());
                    }
                    // Variable doesn't store constValue in symbol typically, unless for const propagation if it were const.
                } else {
                     addError("Internal error: Could not evaluate variable initializer for '" + name + "'.", 
                              varDefCtx->constantInitializationValue()->getStart());
                }
            }
            expectingConstantInitializer = false;
            expectedInitializerType = nullptr;
        } else {
            symbol->isInitialized = false; // Implicitly initialized to 0/false at runtime
                                          // For semantic analysis, just note it's not explicitly initialized here.
        }

        if (!currentScope->define(name, symbol)) {
            addError("Redefinition of variable '" + name + "'.", varDefCtx->Identifier()->getSymbol());
        }
    }
    return nullptr;
}


antlrcpp::Any SemanticAnalyzer::visitBasicType(CactParser::BasicTypeContext *ctx) {
    return getTypeFromBasicTypeCtx(ctx);
}

antlrcpp::Any SemanticAnalyzer::visitFunctionType(CactParser::FunctionTypeContext *ctx) {
    return getTypeFromFunctionTypeCtx(ctx);
}

antlrcpp::Any SemanticAnalyzer::visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) {
    std::shared_ptr<Type> baseType = std::any_cast<std::shared_ptr<Type>>(visitBasicType(ctx->basicType()));
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> actualType = baseType;

    if (!ctx->LeftBracket().empty()) { // Array parameter
        std::vector<int> dimensions;
        
        // 处理数组参数
        // 在C/C++中，数组参数如 int arr[][3] 表示第一维度不固定，第二维度是3
        // 维度顺序应该与声明顺序一致
        for (size_t i = 0; i < ctx->LeftBracket().size(); ++i) {
            int dimension = -1; // 默认为隐式维度
            
            // 如果有明确的维度值
            if (i < ctx->IntegerConstant().size() && ctx->IntegerConstant(i) != nullptr && 
                !ctx->IntegerConstant(i)->getText().empty()) {
                try {
                    dimension = std::stoi(ctx->IntegerConstant(i)->getText());
                } catch (const std::out_of_range& oor) {
                    addError("Integer constant for array dimension is out of range.", ctx->IntegerConstant(i)->getSymbol());
                    dimension = 0; // 错误标记
                } catch (const std::invalid_argument& ia) {
                    addError("Invalid integer constant for array dimension.", ctx->IntegerConstant(i)->getSymbol());
                    dimension = 0;
                }
            }
            
            dimensions.push_back(dimension);
        }
        
        // 直接创建数组类型，确保维度顺序正确
        actualType = std::make_shared<Type>(Type::ARRAY);
        actualType->elementType = baseType;
        actualType->dimensions = dimensions;
    } else { // Scalar parameter
        actualType = std::make_shared<Type>(*baseType); // Make a copy
    }
    
    auto paramSymbol = std::make_shared<SymbolInfo>(name, actualType, SymbolInfo::PARAMETER, ctx);
    paramSymbol->isInitialized = true; // Considered initialized by function call mechanism
    return paramSymbol;
}


antlrcpp::Any SemanticAnalyzer::visitBlock(CactParser::BlockContext *ctx) {
    // If current scope is already a function scope AND this block is the direct body of the function,
    // don't create a new scope. The function definition already created it.
    // This check is a bit tricky. A simple heuristic: if parent is FuncDef, this block is the func body.
    bool isFunctionBodyBlock = dynamic_cast<CactParser::FunctionDefinitionContext*>(ctx->parent) != nullptr;

    if (!isFunctionBodyBlock) {
        enterScope(false, currentScope ? currentScope->isLoop() : false); // Inherit loop status
    }

    // 先遍历所有blockItem执行语义检查
    bool allPathsReturn = true; // 假设所有路径都返回，除非我们发现一个未返回的路径
    bool hasReturnStatement = false; // 是否有任何return语句
    
    for (auto* item : ctx->blockItem()) {
        if (item->declaration()) {
            visitDeclaration(item->declaration());
        } else if (item->statement()) {
            // 记录每条语句前的返回状态
            bool prevReturn = currentFunctionHasReturn;
            
            visitStatement(item->statement());
            
            // 如果这条语句包含return，记录下来
            if (!prevReturn && currentFunctionHasReturn) {
                hasReturnStatement = true;
            }
            
            // 如果语句改变了返回状态并且不是块的最后一条语句，则不是所有路径都返回
            if (item != ctx->blockItem().back() && currentFunctionHasReturn) {
                // 后面的语句永远不会被执行，所以我们已经知道所有路径都返回了
                break;
            }
        }
    }
    
    // 如果块中有return语句但不是所有路径都返回，则块整体不保证返回
    if (!hasReturnStatement) {
        allPathsReturn = false;
    }

    if (!isFunctionBodyBlock) {
        exitScope();
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitStatement(CactParser::StatementContext *ctx) {    
    // 先检查Return语句，因为Return语句也可能包含expression
    if (ctx->Return()) { // Return statement: 'return' Exp? ';'
        if (!currentFunctionSymbol) {
            addError("'return' statement outside of function.", ctx->Return()->getSymbol());
            return nullptr;
        }
        currentFunctionHasReturn = true; // Mark that a return statement was encountered
        std::shared_ptr<Type> expectedReturnType = currentFunctionSymbol->type->elementType; // elementType holds return type for functions

        if (ctx->expression()) { // return Exp;
            if (expectedReturnType->baseType == Type::VOID) {
                addError("Cannot return a value from a void function '" + currentFunctionSymbol->name + "'.", ctx->Return()->getSymbol());
            } else {
                std::shared_ptr<Type> actualReturnType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()));
                if (actualReturnType->baseType != Type::ERROR_TYPE) {
                    // Create temporary non-const versions for comparison
                    auto tempExpected = std::make_shared<Type>(*expectedReturnType); tempExpected->isConst = false;
                    auto tempActual = std::make_shared<Type>(*actualReturnType); tempActual->isConst = false;
                    if (!tempExpected->equals(*tempActual)) {
                        addError("Return type mismatch: expected '" + expectedReturnType->toString() +
                                 "', got '" + actualReturnType->toString() + "'.", ctx->expression()->getStart());
                    }
                }
            }
        } else { // return;
            if (expectedReturnType->baseType != Type::VOID) {
                addError("Non-void function '" + currentFunctionSymbol->name + "' must return a value.", ctx->Return()->getSymbol());
            }
        }
    } else if (ctx->leftValue() && ctx->Equal() && ctx->expression()) { // Assignment: LVal '=' Exp ';'
        std::shared_ptr<Type> lvalType = std::any_cast<std::shared_ptr<Type>>(visitLeftValue(ctx->leftValue()));
        std::shared_ptr<Type> expType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()));

        if (lvalType->baseType == Type::ERROR_TYPE || expType->baseType == Type::ERROR_TYPE) {
            return nullptr; // Error already reported
        }

        if (!lvalType->isLValue) {
            // This should be caught by visitLeftValue if it's not an LValue (e.g. literal)
            // but as a safeguard:
            addError("Expression is not assignable (not an L-value).", ctx->leftValue()->getStart());
            return nullptr;
        }
        if (lvalType->isConst) {
            addError("Cannot assign to a constant '" + ctx->leftValue()->getText() + "'.", ctx->leftValue()->getStart());
            return nullptr;
        }

        // Type checking: "LVal与Exp类型必须完全相同"
        // Create temporary non-const versions for comparison if strict const matching is not desired for assignment
        auto tempLval = std::make_shared<Type>(*lvalType); tempLval->isConst = false;
        auto tempExp = std::make_shared<Type>(*expType); tempExp->isConst = false;

        if (!tempLval->equals(*tempExp)) {
             addError("Type mismatch in assignment: cannot assign '" + expType->toString() +
                     "' to '" + lvalType->toString() + "'.", ctx->Equal()->getSymbol());
        }

    } else if (ctx->expression()) { // Expression statement: [Exp] ';'
        visitExpression(ctx->expression()); // Evaluate for side effects and errors
    } else if (ctx->block()) { // Block statement
        visitBlock(ctx->block());
    } else if (ctx->If()) { // If statement: 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
        if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            // CACT does not have a boolean type. Conditions are numeric.
            addError("Condition for 'if' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        // 记录访问前的返回状态
        bool oldHasReturn = currentFunctionHasReturn;
        bool thenBranchReturns = false;
        bool elseBranchReturns = false;
        
        currentFunctionHasReturn = false; // 重置为分支分析
        visitStatement(ctx->statement(0)); // Then branch
        thenBranchReturns = currentFunctionHasReturn;
        
        currentFunctionHasReturn = false; // 为else分支重置
        if (ctx->Else()) {
            visitStatement(ctx->statement(1)); // Else branch
            elseBranchReturns = currentFunctionHasReturn;
        }
        
        // 只有当两个分支都返回时，或者恢复到调用前的状态
        if (ctx->Else()) {
            // 有else分支时，只有两个分支都返回才算整体有返回
            currentFunctionHasReturn = thenBranchReturns && elseBranchReturns;
        } else {
            // 没有else分支时，不能保证有返回（因为if条件可能为假）
            currentFunctionHasReturn = oldHasReturn;
        }
    } else if (ctx->While()) { // While statement: 'while' '(' Cond ')' Stmt
        std::shared_ptr<Type> condType = std::any_cast<std::shared_ptr<Type>>(visitCondition(ctx->condition()));
         if (condType->baseType != Type::ERROR_TYPE && 
            !(condType->baseType == Type::INT || condType->baseType == Type::FLOAT || condType->baseType == Type::CHAR)) {
            addError("Condition for 'while' statement must be a numeric type, got '" + condType->toString() + "'.", ctx->condition()->getStart());
        }
        
        // Enter loop scope for break/continue
        // The scope should be around the statement, not the condition
        Scope* preLoopScope = currentScope;
        currentScope = new Scope(preLoopScope, preLoopScope->isFunction(), true); // New scope is a loop scope

        // 对于while循环，不能保证循环体会执行，因此不会影响返回状态
        bool oldHasReturn = currentFunctionHasReturn;
        visitStatement(ctx->statement(0)); // Loop body
        currentFunctionHasReturn = oldHasReturn; // 恢复到之前的返回状态

        Scope* temp = currentScope;
        currentScope = preLoopScope; // Restore previous scope
        delete temp; // Clean up loop scope

    } else if (ctx->Break()) { // Break statement: 'break' ';'
        Scope* s = currentScope;
        bool inLoop = false;
        while(s){
            if(s->isLoop()){ inLoop = true; break;}
            if(s->isFunction()) break; // Stop at function boundary
            s = s->getParent();
        }
        if (!inLoop) {
            addError("'break' statement not within a loop.", ctx->Break()->getSymbol());
        }
    } else if (ctx->Continue()) { // Continue statement: 'continue' ';'
         Scope* s = currentScope;
        bool inLoop = false;
        while(s){
            if(s->isLoop()){ inLoop = true; break;}
            if(s->isFunction()) break; // Stop at function boundary
            s = s->getParent();
        }
        if (!inLoop) {
            addError("'continue' statement not within a loop.", ctx->Continue()->getSymbol());
        }
    }
    return nullptr;
}


// --- Expression Visitors (Simplified stubs, need full implementation) ---

// Helper for checking if an expression results in a compile-time constant literal or named constant
// This is based on the "const int d = 4 + 5; //非法" rule.
SemanticAnalyzer::ConstEvalResult SemanticAnalyzer::evaluateAddExpressionAsConstant(CactParser::AddExpressionContext* addCtx) { 
    if (!addCtx) return {Type::getError(), {}, false, false};
    
    ConstEvalResult result;
    result.type = Type::getError(); 
    result.isConst = false;
    result.hasValue = false;

    if (addCtx->addExpression()) { 
        return result; 
    }

    auto currentMulExp = addCtx->multiplicativeExpression();
    if (currentMulExp->multiplicativeExpression()) { 
        return result; 
    }

    auto currentUnaryExp = currentMulExp->unaryExpression();
    bool isNegative = false;
    bool isPositive = false; 

    // Check for function call first, as it's a distinct alternative in unaryExpression rule
    if (currentUnaryExp->Identifier() && currentUnaryExp->LeftParenthesis()) {
        // This is a function call, not a constant expression for initialization
        return result;
    }

    // Now handle unary operators or primary expression
    CactParser::UnaryExpressionContext* unaryExpForPrimary = currentUnaryExp;
    if (currentUnaryExp->Plus()) {
        isPositive = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    } else if (currentUnaryExp->Minus()) {
        isNegative = true;
        unaryExpForPrimary = currentUnaryExp->unaryExpression(); 
    }
    
    // After stripping optional unary +/-, unaryExpForPrimary should be a PrimaryExpression or another function call.
    // Re-check for function call if unary operators were stripped
    if (unaryExpForPrimary->Identifier() && unaryExpForPrimary->LeftParenthesis()){
        return result; // Function call after unary op, not a const
    }

    if (unaryExpForPrimary->ExclamationMark()) {
        return result; 
    }
    
    if (unaryExpForPrimary->primaryExpression()) {
        auto primExp = unaryExpForPrimary->primaryExpression();
        if (primExp->number()) {
            result.isConst = true;
            if (primExp->number()->IntegerConstant()) {
                try {
                    int val = std::stoi(primExp->number()->IntegerConstant()->getText());
                    if (isNegative) val = -val;
                    result.value = val; result.hasValue = true;
                    result.type = Type::getInt(true); 
                } catch (...) { result.isConst = false; }
            } else if (primExp->number()->FloatConstant()) {
                 try {
                    float val = std::stof(primExp->number()->FloatConstant()->getText());
                    if (isNegative) val = -val;
                    result.value = val; result.hasValue = true;
                    result.type = Type::getFloat(true);
                } catch (...) { result.isConst = false; }
            } else if (primExp->number()->CharacterConstant()) {
                std::string text = primExp->number()->CharacterConstant()->getText();
                if (isNegative || isPositive) { 
                    addError("Unary '+' or '-' cannot be applied to character constant.", primExp->number()->getStart());
                    result.isConst = false; result.hasValue = false; result.type = Type::getError();
                } else if (text.length() >= 3 && text.front() == '\'' && text.back() == '\'') {
                    if (text.length() == 3) { 
                        result.value = text[1]; result.hasValue = true;
                        result.type = Type::getChar(true);
                    } else if (text.length() == 4 && text[1] == '\\') { 
                        char unescaped_char;
                        bool recognized_escape = true;
                        switch (text[2]) {
                            case 'n': unescaped_char = '\n'; break;
                            case 't': unescaped_char = '\t'; break;
                            case 'r': unescaped_char = '\r'; break;
                            case '\\': unescaped_char = '\\'; break;
                            case '\'': unescaped_char = '\''; break;
                            case '0': unescaped_char = '\0'; break;
                            default: recognized_escape = false; break;
                        }
                        if (recognized_escape) {
                            result.value = unescaped_char; result.hasValue = true;
                            result.type = Type::getChar(true);
                        } else {
                            addError("Unrecognized character escape sequence: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                            result.isConst = false; result.hasValue = false; result.type = Type::getError();
                        }
                    } else {
                        addError("Invalid character literal format: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                        result.isConst = false; result.hasValue = false; result.type = Type::getError();
                    }
                } else {
                    addError("Invalid character literal format: '" + text + "'.", primExp->number()->CharacterConstant()->getSymbol());
                    result.isConst = false; result.hasValue = false; result.type = Type::getError();
                }
            }
            return result;
        } else if (primExp->leftValue()) {
            if (isNegative || isPositive) { 
                 return result; 
            }
            if (primExp->leftValue()->Identifier() && primExp->leftValue()->LeftBracket().empty()) {
                std::string name = primExp->leftValue()->Identifier()->getText();
                auto symbol = currentScope->resolve(name);
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


antlrcpp::Any SemanticAnalyzer::visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) {
    if (!expectingConstantInitializer || !expectedInitializerType) {
        addError("Internal error: visitConstantInitializationValue called without proper context.", ctx->getStart());
        return SemanticAnalyzer::ConstEvalResult{Type::getError(), {}, false, false};
    }

    if (ctx->constantExpression()) {
        ConstEvalResult evalRes = evaluateAddExpressionAsConstant(ctx->constantExpression()->addExpression()); 
        if (!evalRes.isConst) {
            addError("Initializer must be a compile-time constant.", ctx->constantExpression()->getStart());
            return evalRes; 
        }
        
        // 检查：不允许直接使用标量值初始化数组（必须用大括号）
        // 例如：int d[4] = 1; 是非法的，应该报错
        if (expectedInitializerType->baseType == Type::ARRAY) { 
            addError("Cannot initialize array with a scalar value directly in this form (use '{...}').", ctx->getStart());
            return ConstEvalResult{Type::getError(), {}, false, false};
        }
        
        if (expectedInitializerType->baseType != Type::ARRAY) { 
            if (!evalRes.type->equals(*expectedInitializerType)) {
                bool compatible = false;
                if (expectedInitializerType->baseType == Type::CHAR && evalRes.type->baseType == Type::INT) {
                    // Spec: "types must be identical"
                }
                if (!compatible) {
                    addError("Initializer type '" + evalRes.type->toString() + 
                             "' does not match expected type '" + expectedInitializerType->toString() + "'.", 
                             ctx->constantExpression()->getStart());
                    // 返回一个带有错误类型但保留原始常量属性的结果
                    // 这样可以避免触发"必须是编译时常量"的错误
                    ConstEvalResult errorResult = evalRes;
                    errorResult.type = Type::getError();
                    return errorResult;
                }
            }
        }
        return evalRes;

    } else if (ctx->LeftBrace()) { 
        if (expectedInitializerType->baseType != Type::ARRAY) {
            addError("Array initializer used for non-array type '" + expectedInitializerType->toString() + "'.", ctx->LeftBrace()->getSymbol());
            return false; 
        }
        std::vector<ConstEvalResult> flatInitializers;
        std::shared_ptr<Type> originalExpectedType = expectedInitializerType; 
        int initCount = checkArrayInitializerRecursive(ctx, expectedInitializerType->elementType, expectedInitializerType->dimensions, 0, flatInitializers);
        expectedInitializerType = originalExpectedType; 
        if (initCount < 0) { 
            return false; 
        }
        return true; 
    }
    return SemanticAnalyzer::ConstEvalResult{Type::getError(), {}, false, false};
}

// Recursive helper for array initializers
// Returns number of elements successfully processed, or -1 on error.
int SemanticAnalyzer::checkArrayInitializerRecursive(
    CactParser::ConstantInitializationValueContext* initCtx, 
    std::shared_ptr<Type> expectedElementType, // Expected type of elements at current nesting level
    const std::vector<int>& dimensions, 
    int currentDimensionIndex,
    std::vector<ConstEvalResult>& flatInitializers) 
{
    if (!initCtx || !initCtx->LeftBrace()) { // Should be a braced list for recursive calls
        // This case handles a scalar value within a list, e.g., {1, 2} where 1 and 2 are ConstExp
        if (initCtx && initCtx->constantExpression()) {
            // 扁平化初始化：这里我们需要确保能够处理不管嵌套多少层的初始化
            // Get the base element type of the array (the ultimate scalar type)
            std::shared_ptr<Type> ultimateElementType = expectedInitializerType; // The overall array type
            while(ultimateElementType->baseType == Type::ARRAY) {
                ultimateElementType = ultimateElementType->elementType;
            }

            if (!ultimateElementType) {
                // Ensure elementType is not null - this fixes the "array element type is null" error
                addError("Internal error: array ultimate element type is null.", initCtx->getStart());
                return -1;
            }

            std::shared_ptr<Type> oldExpected = expectedInitializerType; // Save context
            expectedInitializerType = ultimateElementType; // Set context for scalar element

            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(initCtx));
            
            expectedInitializerType = oldExpected; // Restore context

            if (!val.isConst) { /* Error already reported by deeper call */ return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;

            // Type check val.type against ultimateElementType (the actual element type of the array)
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          initCtx->constantExpression()->getStart());
                 return -1;
            }
            flatInitializers.push_back(val);
            return 1; // 1 element processed
        }
        addError("Invalid array initializer: expected '{...}' or constant expression.", initCtx ? initCtx->getStart() : nullptr);
        return -1;
    }

    // We are at LeftBrace context.
    if (currentDimensionIndex >= dimensions.size()) {
        addError("Too many nested initializers for array.", initCtx->LeftBrace()->getSymbol());
        return -1;
    }

    int count = 0;
    int maxElementsInThisDimension = (dimensions[currentDimensionIndex] == -1) ? -1 : dimensions[currentDimensionIndex]; // -1 for implicit first dim of param

    for (auto* subInitCtx : initCtx->constantInitializationValue()) {
        // 允许部分初始化: 移除对元素数量的严格限制，允许少于维度大小的元素
        // 注意：我们仍然检查是否超过最大元素数量，但不再将其作为错误处理
        if (maxElementsInThisDimension != -1 && count >= maxElementsInThisDimension) {
            // 这里不再报错，而是直接返回已处理的元素数量
            // 允许部分初始化，未初始化的元素默认设为0
            return count;
        }

        int subCount;
        if (subInitCtx->LeftBrace()) { // Nested initializer: { ... }
            // This means we are initializing a sub-array.
            // The expected element type for this level is an array of one less dimension.
            if (currentDimensionIndex + 1 >= dimensions.size() && dimensions.size() > 0) { 
                // 不再将过深的初始化列表视为错误，而是尝试扁平处理
                // 这种情况可能是用户提供了比数组维度更深的嵌套，例如 int a[2] = {{1}}
                // 我们可以考虑将其展平处理为 a[0] = 1，但目前简单地返回已处理的元素数
                return count;
            }

            if (!expectedElementType) {
                // Ensure elementType is not null
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }

            subCount = checkArrayInitializerRecursive(subInitCtx, expectedElementType, dimensions, currentDimensionIndex + 1, flatInitializers);
        } else { // Scalar initializer: ConstExp
             // This scalar should initialize an element of the current sub-array.
             // The expected type for this scalar is `expectedElementType`.
            std::shared_ptr<Type> oldExpected = expectedInitializerType; // Save context
            
            // 确保元素类型不为空
            if (!expectedElementType) {
                addError("Internal error: array element type is null.", subInitCtx->getStart());
                return -1;
            }
            
            // 如果我们正在处理数组，我们需要获取最基本的元素类型
            std::shared_ptr<Type> ultimateElementType = expectedElementType;
            while(ultimateElementType->baseType == Type::ARRAY) {
                ultimateElementType = ultimateElementType->elementType;
            }
            
            expectedInitializerType = ultimateElementType; // Set context for scalar element

            ConstEvalResult val = std::any_cast<ConstEvalResult>(visitConstantInitializationValue(subInitCtx));
            
            expectedInitializerType = oldExpected; // Restore context

            if (!val.isConst) { /* error reported */ return -1; }
            if (val.type->baseType == Type::ERROR_TYPE) return -1;
            
            // Type check val.type against expectedElementType
            if (!val.type->equals(*ultimateElementType)) {
                 addError("Type mismatch in array initializer: expected element of type '" + 
                          ultimateElementType->toString() + "', got '" + val.type->toString() + "'.", 
                          subInitCtx->constantExpression()->getStart());
                 return -1;
            }
            flatInitializers.push_back(val);
            subCount = 1;
        }

        if (subCount < 0) return -1; // Propagate error
        count += subCount;
    }
    return count;
}


antlrcpp::Any SemanticAnalyzer::visitExpression(CactParser::ExpressionContext *ctx) {
    if (ctx->addExpression()) {
        return visitAddExpression(ctx->addExpression());
    }
    addError("Invalid expression structure.", ctx->getStart());
    return Type::getError();
}

antlrcpp::Any SemanticAnalyzer::visitConstantExpression(CactParser::ConstantExpressionContext *ctx) {
    if (ctx->addExpression()) {
        auto type = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));
        // Const-ness is checked by evaluateAddExpressionAsConstant during initializer processing.
        return type;
    }
    addError("Invalid constant expression structure.", ctx->getStart());
    return Type::getError();
}

antlrcpp::Any SemanticAnalyzer::visitCondition(CactParser::ConditionContext *ctx) {
    // 保存旧的上下文状态
    bool oldInConditionContext = inConditionContext;
    // 设置为条件表达式上下文
    inConditionContext = true;
    
    std::shared_ptr<Type> result;
    if (ctx->logicalOrExpression()) {
        result = std::any_cast<std::shared_ptr<Type>>(visitLogicalOrExpression(ctx->logicalOrExpression()));
    } else {
        addError("Invalid condition structure.", ctx->getStart());
        result = Type::getError();
    }
    
    // 恢复原来的上下文状态
    inConditionContext = oldInConditionContext;
    return result;
}

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
        if (currentType->baseType != Type::ARRAY) {
            addError("'" + name + "' is not an array.", ctx->Identifier()->getSymbol());
            return Type::getError();
        }

        if (ctx->expression().size() > currentType->dimensions.size()) {
            addError("Too many array indices for '" + name + "'.", ctx->LeftBracket()[0]->getSymbol());
            return Type::getError();
        }
        
        std::shared_ptr<Type> resultType = currentType->elementType;
        
        // 确保元素类型不为空
        if (!resultType) {
            addError("Internal error: array element type is null.", ctx->getStart());
            return Type::getError();
        }
        
        // 检查所有数组索引的类型和范围
        for (size_t i = 0; i < ctx->expression().size(); ++i) {
            auto indexType = std::any_cast<std::shared_ptr<Type>>(visitExpression(ctx->expression()[i]));
            
            if (indexType->baseType != Type::INT) {
                addError("Array index must be an integer.", ctx->expression()[i]->getStart());
                return Type::getError();
            }
            
            // 检查是否为整数常量，如果是，检查范围
            auto indexExp = ctx->expression()[i]->addExpression();
            if (indexExp && indexExp->multiplicativeExpression() && 
                !indexExp->multiplicativeExpression()->multiplicativeExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number() &&
                indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number()->IntegerConstant()) {
                
                // 提取数组索引常量值
                std::string indexStr = indexExp->multiplicativeExpression()->unaryExpression()->primaryExpression()->number()->IntegerConstant()->getText();
                int indexValue;
                
                // 解析整数值（处理十进制、八进制和十六进制）
                if (indexStr.size() > 2 && (indexStr.substr(0, 2) == "0x" || indexStr.substr(0, 2) == "0X")) {
                    // 十六进制
                    indexValue = std::stoi(indexStr, nullptr, 16);
                } else if (indexStr.size() > 1 && indexStr[0] == '0') {
                    // 八进制
                    indexValue = std::stoi(indexStr, nullptr, 8);
                } else {
                    // 十进制
                    indexValue = std::stoi(indexStr);
                }
                
                // 检查数组索引是否越界
                if (currentType->dimensions[i] != -1 && (indexValue < 0 || indexValue >= currentType->dimensions[i])) {
                    addError("Array index " + std::to_string(indexValue) + " out of bounds [0," + 
                            std::to_string(currentType->dimensions[i]-1) + "].", 
                            ctx->expression()[i]->getStart());
                    return Type::getError();
                }
            }
        }
        
        // 返回数组的元素类型
        resultType->isLValue = true;
        resultType->isConst = symbol->type->isConst;
        return resultType;
    }
    return symbol->type; 
}

antlrcpp::Any SemanticAnalyzer::visitNumber(CactParser::NumberContext *ctx) {
    if (ctx->IntegerConstant()) return Type::getInt();
    if (ctx->FloatConstant()) return Type::getFloat();
    if (ctx->CharacterConstant()) return Type::getChar();
    return Type::getError();
}

antlrcpp::Any SemanticAnalyzer::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
    if (ctx->expression()) { // ( Exp )
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

antlrcpp::Any SemanticAnalyzer::visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) {
    if (ctx->primaryExpression()) {
        return visitPrimaryExpression(ctx->primaryExpression());
    }
    if (ctx->unaryExpression()) { // Unary op UnaryExp
        std::shared_ptr<Type> operandType = std::any_cast<std::shared_ptr<Type>>(visitUnaryExpression(ctx->unaryExpression()));
        if (operandType->baseType == Type::ERROR_TYPE) return Type::getError();

        if (ctx->Plus() || ctx->Minus()) { // +Exp, -Exp
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT) {
                addError("Unary '+' or '-' must be applied to numeric type, got '" + operandType->toString() + "'.", 
                         (ctx->Plus() ? ctx->Plus()->getSymbol() : ctx->Minus()->getSymbol()) );
                return Type::getError();
            }
            return operandType; // Type remains the same
        }
        if (ctx->ExclamationMark()) { // !Exp
            // Spec: "!仅出现在条件表达式中" - implies it operates on something bool-like (numeric in CACT)
            if (!inConditionContext) {
                addError("Logical NOT '!' operator can only be used in condition expressions.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            
            if (operandType->baseType != Type::INT && operandType->baseType != Type::FLOAT && operandType->baseType != Type::CHAR) {
                addError("Logical NOT '!' must be applied to numeric type, got '" + operandType->toString() + "'.", ctx->ExclamationMark()->getSymbol());
                return Type::getError();
            }
            return Type::getInt(); // Result of logical NOT is effectively an int (0 or 1)
        }
    }
    if (ctx->Identifier() && ctx->LeftParenthesis()) { // Function call: Ident '(' [FuncRParams] ')'
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

        if (ctx->functionRealParameters()) {
            for (auto* expCtx : ctx->functionRealParameters()->expression()) {
                actualParamTypes.push_back(std::any_cast<std::shared_ptr<Type>>(visitExpression(expCtx)));
            }
        }

        if (actualParamTypes.size() != expectedParamTypes.size()) {
            addError("Function '" + funcName + "' called with incorrect number of arguments. Expected " +
                     std::to_string(expectedParamTypes.size()) + ", got " + std::to_string(actualParamTypes.size()) + ".",
                     ctx->Identifier()->getSymbol());
            return funcType->elementType; // Return function's return type to reduce cascaded errors
        }

        for (size_t i = 0; i < expectedParamTypes.size(); ++i) {
            if (actualParamTypes[i]->baseType == Type::ERROR_TYPE) continue; // Error in arg already reported
            
            // Type check: "实参和形参类型必须完全相同"
            // Create temporary non-const versions for comparison
            auto tempExpected = std::make_shared<Type>(*expectedParamTypes[i]); tempExpected->isConst = false;
            auto tempActual = std::make_shared<Type>(*actualParamTypes[i]); tempActual->isConst = false;

            // 针对数组类型参数错误提供更友好的错误信息
            if (!tempExpected->equals(*tempActual)) {
                std::string errorMsg = "Type mismatch for argument " + std::to_string(i + 1) + " of function '" + funcName + "'. ";
                
                // 对于数组参数，我们特别检查维度是否匹配
                if (tempExpected->baseType == Type::ARRAY && tempActual->baseType == Type::ARRAY) {
                    // 检查是否是维度的问题
                    if (tempExpected->dimensions.size() == tempActual->dimensions.size()) {
                        // 仅第一维不匹配但其它维度匹配的情况
                        bool onlyFirstDimensionMismatch = true;
                        for (size_t dim = 1; dim < tempExpected->dimensions.size(); ++dim) {
                            if (tempExpected->dimensions[dim] != tempActual->dimensions[dim]) {
                                onlyFirstDimensionMismatch = false;
                                break;
                            }
                        }
                        
                        if (onlyFirstDimensionMismatch) {
                            if (tempExpected->dimensions[0] == -1 || tempActual->dimensions[0] == -1) {
                                // 这种情况应该在equals方法中已经允许，不应该走到这里
                                errorMsg += "For array parameters, the first dimension should be ignored. ";
                            } else {
                                errorMsg += "For array parameters, only first dimension mismatch detected. ";
                            }
                        }
                    }
                    
                    errorMsg += "Expected '" + expectedParamTypes[i]->toString() + "', got '" + 
                              actualParamTypes[i]->toString() + "'.";
                } else {
                    errorMsg += "Expected '" + expectedParamTypes[i]->toString() + "', got '" + 
                              actualParamTypes[i]->toString() + "'.";
                }
                
                addError(errorMsg, ctx->functionRealParameters()->expression(i)->getStart());
            }
        }
        return funcType->elementType; // Return type of the function
    }
    return Type::getError();
}

// Default implementations for other expression types, can be overridden if specific logic is needed
antlrcpp::Any SemanticAnalyzer::visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) {
    if (ctx->multiplicativeExpression()) { // MulExp ('*' | '/' | '%') UnaryExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitMultiplicativeExpression(ctx->multiplicativeExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitUnaryExpression(ctx->unaryExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // 特别检查：取余(%)运算符不能用于浮点数
        if (ctx->Percent() && (left->baseType == Type::FLOAT || right->baseType == Type::FLOAT)) {
            addError("Modulo operator '%' cannot be applied to floating-point operands.", 
                     ctx->Percent()->getSymbol());
            return Type::getError();
        }

        // Check types: must be numeric, result type is usually common type (e.g. float if one is float)
        // CACT spec: "操作数必须是int或float类型"
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
        
        // CACT不支持任何形式的类型转换，确保操作数类型相同
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
        
        // 现在，左右操作数类型一定相同
        return std::make_shared<Type>(*left);
    } else { // UnaryExp
        return visitUnaryExpression(ctx->unaryExpression());
    }
}

antlrcpp::Any SemanticAnalyzer::visitAddExpression(CactParser::AddExpressionContext *ctx) {
    if (ctx->addExpression()) { // AddExp ('+' | '-') MulExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitMultiplicativeExpression(ctx->multiplicativeExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // CACT spec: "操作数必须是int或float类型"
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
        
        // CACT不支持任何形式的类型转换，确保操作数类型相同
        if (left->baseType != right->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->Plus()) opToken = ctx->Plus()->getSymbol();
            else if (ctx->Minus()) opToken = ctx->Minus()->getSymbol();
            
            addError("Type mismatch in addition/subtraction: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        
        // 现在，左右操作数类型一定相同
        return std::make_shared<Type>(*left);
    } else { // MulExp
        return visitMultiplicativeExpression(ctx->multiplicativeExpression());
    }
}

antlrcpp::Any SemanticAnalyzer::visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) {
    if (ctx->relationalExpression()) { // RelExp ('<' | '>' | '<=' | '>=') AddExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitRelationalExpression(ctx->relationalExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitAddExpression(ctx->addExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }
        // CACT spec: "操作数必须是int、float或char类型"
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
        // Spec: "如果操作数之一是char类型，则另一个操作数也必须是char类型"
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
        
        // CACT不支持任何形式的类型转换，确保非char操作数类型相同
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
        return Type::getInt(); // Result of relational expression is int (boolean)
    } else { // AddExp
        return visitAddExpression(ctx->addExpression());
    }
}

antlrcpp::Any SemanticAnalyzer::visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) {
    if (ctx->equalityExpression()) { // EqExp ('==' | '!=') RelExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitEqualityExpression(ctx->equalityExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitRelationalExpression(ctx->relationalExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) {
            return Type::getError();
        }

        // CACT spec: "操作数必须是int、float或char类型"
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
        // Spec: "如果操作数之一是char类型，则另一个操作数也必须是char类型"
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
        
        // CACT不支持任何形式的类型转换，确保非char操作数类型相同
        if (left->baseType != Type::CHAR && right->baseType != left->baseType) {
            antlr4::Token* opToken = nullptr;
            if (ctx->LogicalEqual()) opToken = ctx->LogicalEqual()->getSymbol();
            else if (ctx->NotEqual()) opToken = ctx->NotEqual()->getSymbol();
            
            addError("Type mismatch in equality expression: CACT does not support type conversion, got '" +
                     left->toString() + "' and '" + right->toString() + "'.", 
                     opToken);
            return Type::getError();
        }
        return Type::getInt(); // Result of equality expression is int (boolean)
    } else { // RelExp
        return visitRelationalExpression(ctx->relationalExpression());
    }
}

antlrcpp::Any SemanticAnalyzer::visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) {
    if (ctx->logicalAndExpression()) { // LAndExp '&&' EqExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitLogicalAndExpression(ctx->logicalAndExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitEqualityExpression(ctx->equalityExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) return Type::getError();
        // Operands must be convertible to bool (numeric in CACT)
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR) && 
              (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR))) {
            addError("Operands for '&&' must be numeric or char.", ctx->LogicalAnd()->getSymbol());
            return Type::getError();
        }
        return Type::getInt(); // Result is int (0 or 1)
    } else { // EqExp
        return visitEqualityExpression(ctx->equalityExpression());
    }
}

antlrcpp::Any SemanticAnalyzer::visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) {
    if (ctx->logicalOrExpression()) { // LOrExp '||' LAndExp
        std::shared_ptr<Type> left = std::any_cast<std::shared_ptr<Type>>(visitLogicalOrExpression(ctx->logicalOrExpression()));
        std::shared_ptr<Type> right = std::any_cast<std::shared_ptr<Type>>(visitLogicalAndExpression(ctx->logicalAndExpression()));

        if (left->baseType == Type::ERROR_TYPE || right->baseType == Type::ERROR_TYPE) return Type::getError();
        // Operands must be convertible to bool (numeric in CACT)
        if (!((left->baseType == Type::INT || left->baseType == Type::FLOAT || left->baseType == Type::CHAR) && 
              (right->baseType == Type::INT || right->baseType == Type::FLOAT || right->baseType == Type::CHAR))) {
            addError("Operands for '||' must be numeric or char.", ctx->LogicalOr()->getSymbol());
            return Type::getError();
        }
        return Type::getInt(); // Result is int (0 or 1)
    } else { // LAndExp
        return visitLogicalAndExpression(ctx->logicalAndExpression());
    }
}

// visitTerminal, visitErrorNode, visitDeclaration should be correctly defined as before
antlrcpp::Any SemanticAnalyzer::visitDeclaration(CactParser::DeclarationContext *ctx) {
    if (ctx->constantDeclaration()) {
        return visitConstantDeclaration(ctx->constantDeclaration());
    } else if (ctx->variableDeclaration()) {
        return visitVariableDeclaration(ctx->variableDeclaration());
    }
    return visitChildren(ctx); 
}

antlrcpp::Any SemanticAnalyzer::visitTerminal(antlr4::tree::TerminalNode *node) {
    return CactParserBaseVisitor::visitTerminal(node); 
}

antlrcpp::Any SemanticAnalyzer::visitErrorNode(antlr4::tree::ErrorNode *node) {
    addError("Syntax error: unexpected token or parse error near \"" + node->getText() + "\"", node->getSymbol());
    return CactParserBaseVisitor::visitErrorNode(node); 
}
