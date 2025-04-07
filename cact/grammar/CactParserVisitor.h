
// Generated from CactParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CactParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CactParser.
 */
class  CactParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CactParser.
   */
    virtual std::any visitCompilationUnit(CactParser::CompilationUnitContext *context) = 0;

    virtual std::any visitDeclaration(CactParser::DeclarationContext *context) = 0;

    virtual std::any visitConstantDeclaration(CactParser::ConstantDeclarationContext *context) = 0;

    virtual std::any visitBasicType(CactParser::BasicTypeContext *context) = 0;

    virtual std::any visitConstantDefinition(CactParser::ConstantDefinitionContext *context) = 0;

    virtual std::any visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *context) = 0;

    virtual std::any visitVariableDeclaration(CactParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitVariableDefinition(CactParser::VariableDefinitionContext *context) = 0;

    virtual std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionType(CactParser::FunctionTypeContext *context) = 0;

    virtual std::any visitFunctionFormalParameters(CactParser::FunctionFormalParametersContext *context) = 0;

    virtual std::any visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *context) = 0;

    virtual std::any visitBlock(CactParser::BlockContext *context) = 0;

    virtual std::any visitBlockItem(CactParser::BlockItemContext *context) = 0;

    virtual std::any visitStatement(CactParser::StatementContext *context) = 0;

    virtual std::any visitExpression(CactParser::ExpressionContext *context) = 0;

    virtual std::any visitConstantExpression(CactParser::ConstantExpressionContext *context) = 0;

    virtual std::any visitCondition(CactParser::ConditionContext *context) = 0;

    virtual std::any visitLeftValue(CactParser::LeftValueContext *context) = 0;

    virtual std::any visitNumber(CactParser::NumberContext *context) = 0;

    virtual std::any visitFunctionRealParameters(CactParser::FunctionRealParametersContext *context) = 0;

    virtual std::any visitPrimaryExpression(CactParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(CactParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitAddExpression(CactParser::AddExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(CactParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(CactParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *context) = 0;


};

