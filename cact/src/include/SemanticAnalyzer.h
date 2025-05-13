#pragma once
#include "CactParserBaseVisitor.h"
#include "SymbolTable.h"
#include <iostream>

class SemanticAnalyzer : public CactParserBaseVisitor {
public:
    SemanticAnalyzer();

    // 入口
    antlrcpp::Any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override;

    // 声明、定义相关
    antlrcpp::Any visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) override;
    antlrcpp::Any visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) override;
    antlrcpp::Any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override;
    antlrcpp::Any visitBlock(CactParser::BlockContext *ctx) override;
    antlrcpp::Any visitStatement(CactParser::StatementContext *ctx) override;

    // 错误标志
    bool hasSemanticError() const;

private:
    SymbolTable symbolTable;
    bool semanticError = false;

    void reportError(const std::string& msg, antlr4::ParserRuleContext* ctx);
};
