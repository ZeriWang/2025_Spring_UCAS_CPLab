#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "CactParserBaseVisitor.h"
#include "antlr4-runtime.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <iostream> // For error printing

// Forward declarations
namespace cact_parser {
    class CactParser;
}
class Scope; // Forward declaration

// Type representation
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
        
        // 确保元素类型正确
        if (dims.size() > 1) {
            // 对于多维数组，我们需要确保元素类型是正确的
            // 例如：对于int a[3][2][1]，我们需要确保a的元素类型是int[2][1]
            std::vector<int> subDims(dims.begin() + 1, dims.end());
            t->elementType = getArray(elemType, subDims, is_const);
        }
        
        return t;
    }
    static std::shared_ptr<Type> getFunction(std::shared_ptr<Type> retType, const std::vector<std::shared_ptr<Type>>& pTypes) {
        auto t = std::make_shared<Type>(FUNCTION);
        t->elementType = retType; // Using elementType for return type
        t->paramTypes = pTypes;
        return t;
    }

    std::string toString() const;
    bool equals(const Type& other) const;
};

// Symbol information
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

// Scope management
class Scope {
public:
    Scope(Scope* parent = nullptr, bool isFunctionScope = false, bool isLoopScope = false) 
        : parent_scope(parent), is_function_scope(isFunctionScope), is_loop_scope(isLoopScope) {}

    bool define(const std::string& name, std::shared_ptr<SymbolInfo> symbol);
    std::shared_ptr<SymbolInfo> resolve(const std::string& name) const;
    std::shared_ptr<SymbolInfo> resolveCurrent(const std::string& name) const;
    Scope* getParent() const { return parent_scope; }
    bool isFunction() const { return is_function_scope; }
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

class SemanticAnalyzer : public CactParserBaseVisitor {
public:
    SemanticAnalyzer(CactParser* parser_ptr); // Changed to CactParser*

    bool hasSemanticError() const { return !errors.empty(); }
    void printErrors(const std::string& filename) const;

    antlrcpp::Any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override;
    antlrcpp::Any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override;
    antlrcpp::Any visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) override;
    antlrcpp::Any visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) override;
    // No need to override visitConstantDefinition/visitVariableDefinition if logic is in Decl
    antlrcpp::Any visitBasicType(CactParser::BasicTypeContext *ctx) override;
    antlrcpp::Any visitFunctionType(CactParser::FunctionTypeContext *ctx) override;
    antlrcpp::Any visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) override;
    antlrcpp::Any visitBlock(CactParser::BlockContext *ctx) override;
    antlrcpp::Any visitStatement(CactParser::StatementContext *ctx) override;
    
    antlrcpp::Any visitExpression(CactParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitConstantExpression(CactParser::ConstantExpressionContext *ctx) override;
    antlrcpp::Any visitCondition(CactParser::ConditionContext *ctx) override;
    antlrcpp::Any visitLeftValue(CactParser::LeftValueContext *ctx) override;
    antlrcpp::Any visitNumber(CactParser::NumberContext *ctx) override;
    antlrcpp::Any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override;
    antlrcpp::Any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override;
    antlrcpp::Any visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) override;
    antlrcpp::Any visitAddExpression(CactParser::AddExpressionContext *ctx) override;
    antlrcpp::Any visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) override;
    antlrcpp::Any visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) override;
    antlrcpp::Any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) override;
    antlrcpp::Any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) override;
    
    antlrcpp::Any visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) override;

    // ADDED declarations for overridden methods
    antlrcpp::Any visitDeclaration(CactParser::DeclarationContext *ctx) override;
    antlrcpp::Any visitTerminal(antlr4::tree::TerminalNode *node) override;
    antlrcpp::Any visitErrorNode(antlr4::tree::ErrorNode *node) override;


private:
    Scope* currentScope = nullptr;
    std::vector<std::pair<std::string, antlr4::Token*>> errors;
    CactParser* parser; // Store the parser instance

    // Context for current function being processed
    std::shared_ptr<SymbolInfo> currentFunctionSymbol; 
    bool currentFunctionHasReturn = false;

    // For checking main function properties
    bool mainFunctionFound = false;
    std::shared_ptr<SymbolInfo> mainFunctionSymbol;


    void enterScope(bool isFunctionScope = false, bool isLoopScope = false);
    void exitScope();
    void addError(const std::string& message, antlr4::ParserRuleContext* ctx);
    void addError(const std::string& message, antlr4::Token* token);

    std::shared_ptr<Type> getTypeFromBasicTypeCtx(CactParser::BasicTypeContext *ctx);
    std::shared_ptr<Type> getTypeFromFunctionTypeCtx(CactParser::FunctionTypeContext *ctx);

    // For evaluating constant expressions
    struct ConstEvalResult {
        std::shared_ptr<Type> type;
        std::variant<int, float, char> value;
        bool isConst = false;
        bool hasValue = false;
    };
    ConstEvalResult evaluateAddExpressionAsConstant(CactParser::AddExpressionContext* addCtx); // New helper

    // For array initializers
    int checkArrayInitializerRecursive(CactParser::ConstantInitializationValueContext* initCtx, 
                                       std::shared_ptr<Type> arrayElementType, 
                                       const std::vector<int>& dimensions, 
                                       int currentDimensionIndex, 
                                       std::vector<ConstEvalResult>& flatInitializers);
    
    bool isConvertibleToBool(std::shared_ptr<Type> type);
    std::shared_ptr<Type> commonNumericType(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2, bool allowFloat);

    // Flag to indicate if we are currently parsing an initializer that must be a constant.
    // This helps guide visitConstantExpression and its children.
    bool expectingConstantInitializer = false;
    std::shared_ptr<Type> expectedInitializerType; // Type context for initializer
    
    // Flag to indicate if we are currently evaluating a condition expression
    // This is used to check if logical not (!) operator is used in correct context
    bool inConditionContext = false;
};

#endif // SEMANTIC_ANALYZER_H
