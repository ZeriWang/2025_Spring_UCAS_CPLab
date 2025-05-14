#pragma once
#include "CactParserBaseVisitor.h"
#include "SymbolTable.h"
#include <iostream>
#include <unordered_set>

class SemanticAnalyzer : public CactParserBaseVisitor {
public:
    SemanticAnalyzer();
    ~SemanticAnalyzer() override = default;

    // 入口
    antlrcpp::Any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override;

    // 声明、定义相关
    antlrcpp::Any visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) override;
    antlrcpp::Any visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) override;
    antlrcpp::Any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override;
    antlrcpp::Any visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) override;
    antlrcpp::Any visitBlock(CactParser::BlockContext *ctx) override;
    antlrcpp::Any visitStatement(CactParser::StatementContext *ctx) override;
    
    // 表达式相关
    antlrcpp::Any visitLeftValue(CactParser::LeftValueContext *ctx) override;
    antlrcpp::Any visitExpression(CactParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override;
    antlrcpp::Any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override;
    antlrcpp::Any visitCondition(CactParser::ConditionContext *ctx) override;
    antlrcpp::Any visitAddExpression(CactParser::AddExpressionContext *ctx) override;
    antlrcpp::Any visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) override;
    
    // 辅助函数声明
    void checkVariableUsage(const std::string& name, antlr4::ParserRuleContext* ctx, const std::unordered_set<std::string>& declaredNames);

    // 错误标志
    bool hasSemanticError() const;

private:
    SymbolTable symbolTable;
    bool semanticError = false;
    std::unique_ptr<std::unordered_set<std::string>> globalDeclaredNames; // 全局作用域声明的变量
    std::unordered_set<std::string>* currentDeclaredNames = nullptr; // 当前作用域已声明的变量
    std::unordered_set<std::string>* functionParamNames = nullptr; // 当前函数的参数名
    bool inConditionContext = false; // 标记是否在条件表达式上下文中

    // 获取表达式的类型
    BaseType getExpressionType(CactParser::ExpressionContext *ctx);
    // 获取左值的类型
    BaseType getLeftValueType(CactParser::LeftValueContext *ctx);
    // 检查类型是否兼容（用于赋值）
    bool areTypesCompatible(BaseType leftType, BaseType rightType);

    void reportError(const std::string& msg, antlr4::ParserRuleContext* ctx);
};
