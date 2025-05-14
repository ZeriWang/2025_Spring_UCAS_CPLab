#include "include/SemanticAnalyzer.h"
#include <unordered_set>

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
        // 只检查当前作用域是否有重定义
        if (symbolTable.containsInCurrentScope(name)) {
            reportError("变量重复定义: " + name, varDef);
            continue;
        }
        Symbol symbol{name, SymbolType::Variable, baseType};
        symbolTable.insert(symbol);
        
        // 记录已声明的变量
        if (currentDeclaredNames) {
            currentDeclaredNames->insert(name);
        }
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) {
    std::string typeStr = ctx->basicType()->getText();
    BaseType baseType = strToBaseType(typeStr);

    for (auto constDef : ctx->constantDefinition()) {
        std::string name = constDef->Identifier()->getText();
        // 只检查当前作用域是否有重定义
        if (symbolTable.containsInCurrentScope(name)) {
            reportError("常量重复定义: " + name, constDef);
            continue;
        }
        Symbol symbol{name, SymbolType::Constant, baseType, false, {}, true};
        symbolTable.insert(symbol);
        
        // 记录已声明的变量
        if (currentDeclaredNames) {
            currentDeclaredNames->insert(name);
        }
    }
    return nullptr;
}

antlrcpp::Any SemanticAnalyzer::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    std::string name = ctx->Identifier()->getText();
    std::string typeStr = ctx->functionType()->getText();
    BaseType baseType = strToBaseType(typeStr);

    // 检查函数重定义
    if (symbolTable.containsInCurrentScope(name)) {
        reportError("函数重复定义: " + name, ctx);
    } else {
        Symbol funcSymbol{name, SymbolType::Function, baseType};
        symbolTable.insert(funcSymbol);
    }

    symbolTable.enterScope(); // 进入函数作用域
    
    // 处理函数形参
    std::unordered_set<std::string> declaredNames;
    std::unordered_set<std::string> functionParams; // 专门用于存储函数参数名
    std::unordered_set<std::string>* prevDeclaredNames = currentDeclaredNames;
    currentDeclaredNames = &declaredNames;
    
    // 如果存在形参，处理形参
    if (ctx->functionFormalParameters()) {
        for (auto param : ctx->functionFormalParameters()->functionFormalParameter()) {
            std::string paramName = param->Identifier()->getText();
            functionParams.insert(paramName); // 记录函数参数名
            visit(param);
        }
    }
    
    // 记录函数参数名，供后续检查局部变量与参数是否同名
    functionParamNames = &functionParams;
    
    visit(ctx->block());
    
    // 恢复之前的变量集合指针
    currentDeclaredNames = prevDeclaredNames;
    functionParamNames = nullptr;
    
    symbolTable.exitScope();
    return nullptr;
}

// 实现对函数形参的处理
antlrcpp::Any SemanticAnalyzer::visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) {
    std::string name = ctx->Identifier()->getText();
    std::string typeStr = ctx->basicType()->getText();
    BaseType baseType = strToBaseType(typeStr);
    
    // 检查形参重复定义
    if (symbolTable.containsInCurrentScope(name)) {
        reportError("函数形参重复定义: " + name, ctx);
        return nullptr;
    }
    
    // 创建符号并添加到符号表
    Symbol symbol{name, SymbolType::Variable, baseType};
    symbolTable.insert(symbol);
    
    // 记录已声明的变量
    if (currentDeclaredNames) {
        currentDeclaredNames->insert(name);
    }
    
    return nullptr;
}

// 新增检查变量使用的方法
void SemanticAnalyzer::checkVariableUsage(const std::string& name, antlr4::ParserRuleContext* ctx, const std::unordered_set<std::string>& declaredNames) {
    if (name.empty()) return;
    
    // 检查变量是否已声明
    if (!declaredNames.count(name) && !symbolTable.lookup(name)) {
        reportError("变量未声明就使用: " + name, ctx);
    }
}

// 重写leftValue访问函数，检查变量是否已声明
antlrcpp::Any SemanticAnalyzer::visitLeftValue(CactParser::LeftValueContext *ctx) {
    if (ctx->Identifier()) {
        std::string name = ctx->Identifier()->getText();
        // 这里我们检查变量使用时是否已经声明，但只在需要的地方才进行检查
        // 此处不检查，因为左值可能出现在赋值语句左侧
    }
    return visitChildren(ctx);
}

// 重写expression访问函数
antlrcpp::Any SemanticAnalyzer::visitExpression(CactParser::ExpressionContext *ctx) {
    return visitChildren(ctx);
}

// 重写primaryExpression访问函数，检查变量引用
antlrcpp::Any SemanticAnalyzer::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
    if (ctx->leftValue()) {
        auto leftVal = ctx->leftValue();
        std::string name = leftVal->Identifier()->getText();
        if (currentDeclaredNames) {
            checkVariableUsage(name, leftVal, *currentDeclaredNames);
        }
    }
    return visitChildren(ctx);
}

antlrcpp::Any SemanticAnalyzer::visitBlock(CactParser::BlockContext *ctx) {
    symbolTable.enterScope();
    std::unordered_set<std::string> declaredNames;
    
    // 保存当前声明的变量集合的指针，以便在表达式访问中使用
    std::unordered_set<std::string>* prevDeclaredNames = currentDeclaredNames;
    currentDeclaredNames = &declaredNames;
    
    for (auto item : ctx->blockItem()) {
        if (item->declaration()) {
            auto decl = item->declaration();
            if (decl->variableDeclaration()) {
                auto varDecl = decl->variableDeclaration();
                std::string typeStr = varDecl->basicType()->getText();
                BaseType baseType = strToBaseType(typeStr);
                for (auto varDef : varDecl->variableDefinition()) {
                    std::string name = varDef->Identifier()->getText();
                    // 检查当前作用域中是否有同名变量
                    if (symbolTable.containsInCurrentScope(name)) {
                        reportError("变量重复定义: " + name, varDef);
                        continue;
                    }
                    
                    // 特殊检查：如果是函数的第一层作用域，检查变量是否与函数参数同名
                    if (functionParamNames && functionParamNames->count(name)) {
                        reportError("局部变量与函数参数同名: " + name, varDef);
                        continue;
                    }
                    
                    Symbol symbol{name, SymbolType::Variable, baseType};
                    symbolTable.insert(symbol);
                    declaredNames.insert(name);
                }
            } else if (decl->constantDeclaration()) {
                auto constDecl = decl->constantDeclaration();
                std::string typeStr = constDecl->basicType()->getText();
                BaseType baseType = strToBaseType(typeStr);
                for (auto constDef : constDecl->constantDefinition()) {
                    std::string name = constDef->Identifier()->getText();
                    // 只检查当前作用域是否有重定义
                    if (symbolTable.containsInCurrentScope(name)) {
                        reportError("常量重复定义: " + name, constDef);
                        continue;
                    }
                    
                    // 特殊检查：如果有函数参数集合，检查常量是否与函数参数同名
                    if (functionParamNames && functionParamNames->count(name)) {
                        reportError("局部常量与函数参数同名: " + name, constDef);
                        continue;
                    }
                    
                    Symbol symbol{name, SymbolType::Constant, baseType, false, {}, true};
                    symbolTable.insert(symbol);
                    declaredNames.insert(name);
                }
            }
        } else if (item->statement()) {
            auto stmt = item->statement();
            // 检查赋值语句左值
            if (stmt->leftValue() && stmt->expression()) {
                std::string name = stmt->leftValue()->Identifier()->getText();
                if (!declaredNames.count(name)) {
                    reportError("变量未声明: " + name, stmt->leftValue());
                } else {
                    auto symbolOpt = symbolTable.lookup(name);
                    if (symbolOpt && symbolOpt->symbolType == SymbolType::Constant) {
                        reportError("不能给常量赋值: " + name, stmt->leftValue());
                    }
                }
                
                // 检查表达式中的变量引用
                visit(stmt->expression());
            }
            // 如果是子 block，递归调用 visitBlock
            if (stmt->block()) {
                visitBlock(stmt->block());
            } else {
                // 递归处理其它子语句（如if/while/return等）
                for (auto child : stmt->children) {
                    if (auto childBlock = dynamic_cast<CactParser::BlockContext*>(child)) {
                        visitBlock(childBlock);
                    } else {
                        visit(child);
                    }
                }
            }
        }
    }
    
    // 恢复之前的声明变量集合指针
    currentDeclaredNames = prevDeclaredNames;
    
    symbolTable.exitScope();
    return nullptr;
}

// visitStatement 只递归，不做变量声明检查
antlrcpp::Any SemanticAnalyzer::visitStatement(CactParser::StatementContext *ctx) {
    return nullptr;
}

bool SemanticAnalyzer::hasSemanticError() const {
    return semanticError;
}

void SemanticAnalyzer::reportError(const std::string& msg, antlr4::ParserRuleContext* ctx) {
    semanticError = true;
    std::cerr << "[Semantic Error] " << msg
              << " (line " << ctx->getStart()->getLine() << ")" << std::endl;
}

// 添加对一元表达式和条件表达式的访问处理
antlrcpp::Any SemanticAnalyzer::visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) {
    // 检查是否使用 ! 运算符而且不在条件表达式上下文中
    if (ctx->ExclamationMark() && !inConditionContext) {
        reportError("逻辑非操作符 ! 只能在条件表达式中使用", ctx);
    }
    return visitChildren(ctx);
}

antlrcpp::Any SemanticAnalyzer::visitCondition(CactParser::ConditionContext *ctx) {
    // 设置进入条件表达式上下文
    bool oldInConditionContext = inConditionContext;
    inConditionContext = true;
    
    // 访问条件表达式内容
    auto result = visitChildren(ctx);
    
    // 恢复之前的上下文状态
    inConditionContext = oldInConditionContext;
    
    return result;
}
