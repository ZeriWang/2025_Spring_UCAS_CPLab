#include "include/SemanticAnalyzer.h"

SemanticAnalyzer::SemanticAnalyzer() : symbolTable() {}

antlrcpp::Any SemanticAnalyzer::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    for (auto child : ctx->children) {
        visit(child);
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) {
    std::string typeStr = ctx->basicType()->getText();
    BaseType baseType = strToBaseType(typeStr);

    for (auto varDef : ctx->variableDefinition()) {
        std::string name = varDef->Identifier()->getText();
        // 检查重定义
        if (symbolTable.lookup(name).has_value()) {
            reportError("变量重复定义: " + name, varDef);
            continue;
        }
        Symbol symbol{name, SymbolType::Variable, baseType};
        symbolTable.insert(symbol);
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) {
    std::string typeStr = ctx->basicType()->getText();
    BaseType baseType = strToBaseType(typeStr);

    for (auto constDef : ctx->constantDefinition()) {
        std::string name = constDef->Identifier()->getText();
        // 检查重定义
        if (symbolTable.lookup(name).has_value()) {
            reportError("常量重复定义: " + name, constDef);
            continue;
        }
        Symbol symbol{name, SymbolType::Constant, baseType, false, {}, true};
        symbolTable.insert(symbol);
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    std::string name = ctx->Identifier()->getText();
    std::string typeStr = ctx->functionType()->getText();
    BaseType baseType = strToBaseType(typeStr);

    // 检查函数重定义
    if (symbolTable.lookup(name).has_value()) {
        reportError("函数重复定义: " + name, ctx);
    } else {
        Symbol funcSymbol{name, SymbolType::Function, baseType};
        symbolTable.insert(funcSymbol);
    }

    symbolTable.enterScope(); // 进入函数作用域
    visit(ctx->block());
    symbolTable.exitScope();
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitBlock(CactParser::BlockContext *ctx) {
    symbolTable.enterScope();
    for (auto item : ctx->blockItem()) {
        visit(item);
    }
    symbolTable.exitScope();
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitStatement(CactParser::StatementContext *ctx) {
    // 检查赋值语句左值
    if (ctx->leftValue() && ctx->expression()) {
        std::string name = ctx->leftValue()->Identifier()->getText();
        auto symbolOpt = symbolTable.lookup(name);
        if (!symbolOpt.has_value()) {
            reportError("变量未声明: " + name, ctx->leftValue());
        } else if (symbolOpt->symbolType == SymbolType::Constant) {
            reportError("不能给常量赋值: " + name, ctx->leftValue());
        }
        // 类型检查可在此扩展
    }
    // 递归处理 block/if/while/return 等
    return visitChildren(ctx);
}

bool SemanticAnalyzer::hasSemanticError() const {
    return semanticError;
}

void SemanticAnalyzer::reportError(const std::string& msg, antlr4::ParserRuleContext* ctx) {
    semanticError = true;
    std::cerr << "[Semantic Error] " << msg
              << " (line " << ctx->getStart()->getLine() << ")" << std::endl;
}
