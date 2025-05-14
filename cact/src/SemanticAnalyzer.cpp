#include "include/SemanticAnalyzer.h"
#include <unordered_set>

SemanticAnalyzer::SemanticAnalyzer() : symbolTable() {
    // 初始化全局作用域的声明变量集合
    globalDeclaredNames = std::make_unique<std::unordered_set<std::string>>();
    currentDeclaredNames = globalDeclaredNames.get();
}

antlrcpp::Any SemanticAnalyzer::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    // 处理全局作用域
    for (auto child : ctx->children) {
        // 全局级别只能有声明和函数定义
        if (auto decl = dynamic_cast<CactParser::DeclarationContext*>(child)) {
            // 全局变量或常量声明
            visit(decl);
        } else if (auto funcDef = dynamic_cast<CactParser::FunctionDefinitionContext*>(child)) {
            // 函数定义
            visit(funcDef);
        }
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
    
    // 检查变量是否已声明（包括局部变量和全局变量）
    if (!declaredNames.count(name) && 
        !(globalDeclaredNames && globalDeclaredNames->count(name)) && 
        !symbolTable.lookup(name)) {
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

// 重写expression访问函数，检查类型
antlrcpp::Any SemanticAnalyzer::visitExpression(CactParser::ExpressionContext *ctx) {
    // 调用默认的访问方法
    return visitChildren(ctx);
}

// 添加对加法表达式的访问处理
antlrcpp::Any SemanticAnalyzer::visitAddExpression(CactParser::AddExpressionContext *ctx) {
    // 调用默认的访问方法
    return visitChildren(ctx);
}

// 添加对乘法表达式的访问处理  
antlrcpp::Any SemanticAnalyzer::visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) {
    // 调用默认的访问方法
    return visitChildren(ctx);
}

// 重写primaryExpression访问函数，检查变量引用
antlrcpp::Any SemanticAnalyzer::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
    if (ctx->leftValue()) {
        auto leftVal = ctx->leftValue();
        std::string name = leftVal->Identifier()->getText();
        
        // 检查局部变量和全局变量
        bool isDeclared = false;
        if (currentDeclaredNames && currentDeclaredNames->count(name)) {
            isDeclared = true;
        } else if (globalDeclaredNames && globalDeclaredNames->count(name)) {
            isDeclared = true;
        } else {
            // 通过符号表全局查找
            auto symbolOpt = symbolTable.lookup(name);
            if (symbolOpt) {
                isDeclared = true;
            }
        }
        
        if (!isDeclared) {
            reportError("变量未声明就使用: " + name, leftVal);
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
                
                // 先检查变量是否声明
                bool isDeclared = false;
                std::optional<Symbol> symbolOpt;
                
                // 在当前作用域和全局作用域中查找
                if (declaredNames.count(name) || (globalDeclaredNames && globalDeclaredNames->count(name))) {
                    isDeclared = true;
                    symbolOpt = symbolTable.lookup(name);
                }
                
                if (!isDeclared) {
                    reportError("变量未声明: " + name, stmt->leftValue());
                } else if (symbolOpt && symbolOpt->symbolType == SymbolType::Constant) {
                    reportError("不能给常量赋值: " + name, stmt->leftValue());
                } else {
                    // 获取左值和表达式的类型
                    BaseType leftType = getLeftValueType(stmt->leftValue());
                    BaseType rightType = getExpressionType(stmt->expression());
                    
                    // 检查类型是否兼容
                    if (!areTypesCompatible(leftType, rightType)) {
                        std::string leftTypeStr = baseTypeToStr(leftType);
                        std::string rightTypeStr = baseTypeToStr(rightType);
                        reportError("类型不匹配: 不能将" + rightTypeStr + "类型的值赋给" + leftTypeStr + "类型的变量 " + name, stmt);
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

// 获取左值的类型
BaseType SemanticAnalyzer::getLeftValueType(CactParser::LeftValueContext *ctx) {
    if (!ctx) return BaseType::Int; // 默认返回Int类型

    std::string name = ctx->Identifier()->getText();
    auto symbolOpt = symbolTable.lookup(name);
    
    if (symbolOpt) {
        return symbolOpt->baseType;
    }
    
    // 如果找不到符号，默认返回Int类型（应该不会发生，因为之前会检查变量是否已声明）
    return BaseType::Int;
}

// 获取表达式的类型
BaseType SemanticAnalyzer::getExpressionType(CactParser::ExpressionContext *ctx) {
    if (!ctx) return BaseType::Int; // 默认返回Int类型
    
    // 表达式类型由加法表达式决定
    auto addExpr = ctx->addExpression();
    
    // 处理基本字面量
    std::string exprText = addExpr->getText();
    
    // 检查函数调用
    // 如果表达式包含'('和')'且不包含算术运算符，可能是函数调用
    if (exprText.find('(') != std::string::npos && exprText.find(')') != std::string::npos) {
        // 提取函数名（简化处理，假设'('之前的部分是函数名）
        std::string funcName = exprText.substr(0, exprText.find('('));
        
        // 在符号表中查找函数
        auto funcSymbol = symbolTable.lookup(funcName);
        if (funcSymbol && funcSymbol->symbolType == SymbolType::Function) {
            // 返回函数的返回类型
            return funcSymbol->baseType;
        }
        
        // 如果不能确定函数返回类型，继续检查其他可能性
    }
    
    // 检查浮点数字面量
    if (exprText.find('.') != std::string::npos || 
        (exprText.find('f') != std::string::npos && exprText.find("func") == std::string::npos)) {
        return BaseType::Float;
    }
    
    // 检查字符字面量
    if (exprText.find('\'') != std::string::npos) {
        return BaseType::Char;
    }
    
    // 处理变量引用
    // 如果表达式是简单的标识符，可能是变量引用
    if (exprText.find_first_of("+-*/()[]") == std::string::npos) {
        auto symbolOpt = symbolTable.lookup(exprText);
        if (symbolOpt) {
            return symbolOpt->baseType;
        }
    }
    
    // 默认返回Int类型
    return BaseType::Int;
}

// 检查类型是否兼容（用于赋值）
bool SemanticAnalyzer::areTypesCompatible(BaseType leftType, BaseType rightType) {
    // 相同类型是兼容的
    if (leftType == rightType) {
        return true;
    }
    
    // int类型不能接收float类型
    if (leftType == BaseType::Int && rightType == BaseType::Float) {
        return false;
    }
}
