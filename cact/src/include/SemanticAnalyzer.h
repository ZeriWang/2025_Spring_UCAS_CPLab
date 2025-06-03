#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "CactParserBaseVisitor.h"
#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <iostream> // For error printing

// Forward declarations
namespace cact_parser {
    class CactParser;
}

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
    bool isVariableInitializer = false; // Flag to distinguish variable vs constant initialization
    
    // Flag to indicate if we are currently evaluating a condition expression
    // This is used to check if logical not (!) operator is used in correct context
    bool inConditionContext = false;
};

#endif // SEMANTIC_ANALYZER_H
