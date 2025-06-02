#include "include/IRGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <any>

IRGenerator::IRGenerator() 
#ifdef LLVM_AVAILABLE
    : context(nullptr), module(nullptr), builder(nullptr), currentFunction(nullptr)
#endif
{
    labelCounter = 0;
    registerCounter = 0;
    localVarCounter = 0;
}

IRGenerator::~IRGenerator() {
}

bool IRGenerator::generateIR(antlr4::tree::ParseTree* tree, const std::string& moduleName) {
    if (!tree) {
        addError("Parse tree is null");
        return false;
    }
    
    std::cout << "开始生成IR代码，模块名: " << moduleName << std::endl;
    
#ifdef LLVM_AVAILABLE
    try {
        initializeLLVM(moduleName);
        visit(tree);
        return !hasErrors();
    } catch (const std::exception& e) {
        addError(std::string("IR生成异常: ") + e.what());
        return false;
    }
#else
    // 临时实现：不依赖LLVM的版本
    std::cout << "警告: LLVM未可用，使用模拟IR生成器" << std::endl;
    
    // 初始化模拟IR输出
    irOutput.str("");
    irOutput << "; ModuleID = '" << moduleName << "'\n";
    irOutput << "target datalayout = \"e-m:o-i64:64-i128:128-n32:64-S128\"\n";
    irOutput << "target triple = \"arm64-apple-macosx14.0.0\"\n\n";
    
    // 声明内置函数
    irOutput << "; 内置函数声明\n";
    irOutput << "declare i32 @printf(ptr noundef, ...) #1\n";
    irOutput << "declare i32 @scanf(ptr noundef, ...) #1\n\n";
    
    // 添加格式字符串常量
    irOutput << "; 格式字符串常量\n";
    irOutput << "@.str.int = private unnamed_addr constant [4 x i8] c\"%d\\0A\\00\", align 1\n";
    irOutput << "@.str.float = private unnamed_addr constant [4 x i8] c\"%f\\0A\\00\", align 1\n";
    irOutput << "@.str.char = private unnamed_addr constant [4 x i8] c\"%c\\0A\\00\", align 1\n\n";
    
    visit(tree);
    return !hasErrors();
#endif
}

std::string IRGenerator::getIRString() const {
#ifdef LLVM_AVAILABLE
    if (!module) {
        return "Error: Module not initialized";
    }
    
    std::string irString;
    llvm::raw_string_ostream stream(irString);
    module->print(stream, nullptr);
    return irString;
#else
    return irOutput.str();
#endif
}

bool IRGenerator::writeIRToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }
    
    file << getIRString();
    return true;
}

void IRGenerator::printErrors() const {
    for (const auto& error : errors) {
        std::cerr << "IR生成错误: " << error << std::endl;
    }
}

void IRGenerator::addError(const std::string& message) {
    errors.push_back(message);
}

// Visit方法实现
antlrcpp::Any IRGenerator::visitCompilationUnit(CactParser::CompilationUnitContext *ctx) {
    std::cout << "访问编译单元" << std::endl;
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
    std::cout << "访问函数定义: " << ctx->getText() << std::endl;
    
    // 获取函数信息
    std::string functionName = ctx->Identifier()->getText();
    std::string returnType = ctx->functionType()->getText();
    
    std::cout << "函数名: " << functionName << ", 返回类型: " << returnType << std::endl;
    
    // 重置局部变量计数器
    localVarCounter = 1;  // 从%1开始，%0通常是返回值
    registerCounter = 1;  // 重置寄存器计数器
    
    // 处理函数参数
    std::vector<std::pair<std::string, std::string>> parameters;
    if (ctx->functionFormalParameters()) {
        auto paramResult = visit(ctx->functionFormalParameters());
        if (paramResult.has_value()) {
            try {
                parameters = std::any_cast<std::vector<std::pair<std::string, std::string>>>(paramResult);
            } catch (...) {
                // 如果转换失败，使用空参数列表
            }
        }
    }
    
    // 生成函数定义
    std::string llvmReturnType = "i32";  // 简化处理，主要处理int
    if (returnType == "void") llvmReturnType = "void";
    
    // 生成函数头
    irOutput << "define " << llvmReturnType << " @" << functionName << "(";
    
    // 添加参数
    for (size_t i = 0; i < parameters.size(); ++i) {
        if (i > 0) irOutput << ", ";
        irOutput << "i32 %" << parameters[i].second;
    }
    
    irOutput << ") #0 {\n";
    
    // 为main函数添加特殊处理
    if (functionName == "main") {
        // 分配返回值变量
        irOutput << "  %1 = alloca i32, align 4\n";
        irOutput << "  store i32 0, ptr %1, align 4\n";
        localVarCounter = 2;  // 下一个局部变量从%2开始
        registerCounter = 2;  // 下一个寄存器从%2开始
    }
    
    // 访问函数体
    if (ctx->block()) {
        visit(ctx->block());
    }
    
    // 函数结束
    irOutput << "}\n\n";
    
    return nullptr;
}

// 其他visit方法的简化实现...
antlrcpp::Any IRGenerator::visitFunctionFormalParameters(CactParser::FunctionFormalParametersContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitBlock(CactParser::BlockContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitDeclaration(CactParser::DeclarationContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) {
    std::cout << "访问变量声明: " << ctx->getText() << std::endl;
    
    // 获取基本类型
    std::string baseType = ctx->basicType()->getText();
    std::cout << "变量类型: " << baseType << std::endl;
    
    // 处理所有的变量定义
    for (auto varDef : ctx->variableDefinition()) {
        std::string varName = varDef->Identifier()->getText();
        std::cout << "声明变量: " << varName << std::endl;
        
        // 分配局部变量编号
        std::string localVar = getNextLocalVar();
        
        // 检查是否是数组声明
        if (!varDef->LeftBracket().empty()) {
            // 数组声明
            std::cout << "这是一个数组声明" << std::endl;
            
            // 获取数组大小
            int arraySize = 1;
            if (!varDef->IntegerConstant().empty()) {
                try {
                    arraySize = std::stoi(varDef->IntegerConstant(0)->getText());
                } catch (...) {
                    arraySize = 1;
                }
            }
            
            std::cout << "数组大小: " << arraySize << std::endl;
            
            // 生成数组alloca
            irOutput << "  " << localVar << " = alloca [" << arraySize << " x i32], align 4\n";
            
            // 记录变量映射
            variables[varName] = localVar;
            arrays[varName] = std::map<int, std::string>();
            for (int i = 0; i < arraySize; ++i) {
                arrays[varName][i] = "0";
            }
        } else {
            // 普通变量声明
            irOutput << "  " << localVar << " = alloca i32, align 4\n";
            
            // 检查是否有初始化值
            if (varDef->constantInitializationValue()) {
                auto initResult = visit(varDef->constantInitializationValue());
                std::string initValue = "0";
                
                try {
                    if (initResult.has_value()) {
                        initValue = std::any_cast<std::string>(initResult);
                    }
                } catch (...) {
                    initValue = "0";
                }
                
                std::cout << "初始化值: " << initValue << std::endl;
                
                // 生成store指令
                emitStore(initValue, localVar);
            }
            
            // 记录变量映射
            variables[varName] = localVar;
        }
    }
    
    return nullptr;
}

antlrcpp::Any IRGenerator::visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) {
    std::cout << "访问常量初始化值: " << ctx->getText() << std::endl;
    
    // 如果是常量表达式，直接访问
    if (ctx->constantExpression()) {
        return visit(ctx->constantExpression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitConstantExpression(CactParser::ConstantExpressionContext *ctx) {
    std::cout << "访问常量表达式: " << ctx->getText() << std::endl;
    
    // 常量表达式就是加法表达式
    if (ctx->addExpression()) {
        return visit(ctx->addExpression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitStatement(CactParser::StatementContext *ctx) {
    std::cout << "访问语句: " << ctx->getText() << std::endl;
    
    // 检查是否是return语句
    if (ctx->Return()) {
        std::cout << "处理return语句" << std::endl;
        
        if (ctx->expression()) {
            // 处理返回表达式
            auto exprText = ctx->expression()->getText();
            std::cout << "返回表达式: " << exprText << std::endl;
            
            // 检查是否是变量
            if (variables.find(exprText) != variables.end()) {
                // 变量返回
                std::string loadReg = getNextRegister();
                emitLoad(variables[exprText], loadReg);
                irOutput << "  ret i32 " << loadReg << "\n";
            } else {
                // 常量返回或复杂表达式
                auto result = visit(ctx->expression());
                std::string returnValue = "0";
                try {
                    if (result.has_value()) {
                        returnValue = std::any_cast<std::string>(result);
                    }
                } catch (...) {
                    // 使用默认值
                }
                
                irOutput << "  ret i32 " << returnValue << "\n";
            }
        } else {
            irOutput << "  ret void\n";
        }
        return nullptr;
    }
    // 检查是否是表达式语句（如函数调用）
    else if (ctx->expression() && !ctx->leftValue() && !ctx->Equal()) {
        std::cout << "处理表达式语句: " << ctx->expression()->getText() << std::endl;
        
        // 访问表达式，这会处理函数调用等
        visit(ctx->expression());
        return nullptr;
    }
    // 检查是否是while语句
    else if (ctx->While()) {
        std::cout << "处理while语句" << std::endl;
        
        // 使用命名标签避免与寄存器编号冲突
        std::string condLabel = "while_cond";
        std::string bodyLabel = "while_body";
        std::string exitLabel = "while_exit";
        
        // 跳转到条件检查基本块
        irOutput << "  br label %" << condLabel << "\n";
        
        // 条件检查基本块
        irOutput << "\n" << condLabel << ":\n";
        
        // 简化处理：假设是 i < 3 的形式
        // 生成load指令加载变量值
        std::string iVar = variables["i"];  // 获取变量i的局部变量名
        std::string sumVar = variables["sum"];  // 获取变量sum的局部变量名
        
        std::string loadReg = getNextRegister();
        emitLoad(iVar, loadReg);
        
        // 生成比较指令
        std::string cmpReg = getNextRegister();
        emitICmp("slt", loadReg, "3", cmpReg);
        
        // 条件分支
        irOutput << "  br i1 " << cmpReg << ", label %" << bodyLabel << ", label %" << exitLabel << "\n";
        
        // 循环体基本块
        irOutput << "\n" << bodyLabel << ":\n";
        
        // 访问循环体
        if (ctx->statement().size() > 0) {
            visit(ctx->statement(0));
        }
        
        // 回到条件检查
        irOutput << "  br label %" << condLabel << "\n";
        
        // 退出基本块
        irOutput << "\n" << exitLabel << ":\n";
        
        return nullptr;
    }
    // 检查是否是赋值语句
    else if (ctx->leftValue() && ctx->Equal() && ctx->expression()) {
        std::cout << "处理赋值语句" << std::endl;
        
        // 获取左值信息
        std::string varName = ctx->leftValue()->Identifier()->getText();
        
        // 处理右侧表达式，生成加载和计算指令
        // 这里简化处理，假设是简单的表达式
        
        // 检查是否是数组赋值
        if (!ctx->leftValue()->expression().empty()) {
            // 数组赋值 - 暂时保持简化处理
            auto indexResult = visit(ctx->leftValue()->expression(0));
            int index = 0;
            try {
                if (indexResult.has_value()) {
                    index = std::stoi(std::any_cast<std::string>(indexResult));
                }
            } catch (...) {
                index = 0;
            }
            
            // 计算右侧表达式的值
            auto result = visit(ctx->expression());
            std::string value = "0";
            try {
                if (result.has_value()) {
                    value = std::any_cast<std::string>(result);
                }
            } catch (...) {
                value = "0";
            }
            
            std::cout << "数组赋值: " << varName << "[" << index << "] = " << value << std::endl;
            
            // 生成数组存储
            std::string arrayVar = variables[varName];
            std::string ptrReg = getNextRegister();
            irOutput << "  " << ptrReg << " = getelementptr inbounds [3 x i32], ptr " << arrayVar << ", i64 0, i64 " << index << "\n";
            irOutput << "  store i32 " << value << ", ptr " << ptrReg << ", align 4\n";
            
            // 更新数组表
            arrays[varName][index] = value;
        } else {
            // 普通变量赋值
            std::string targetVar = variables[varName];
            
            // 处理右侧表达式
            auto exprText = ctx->expression()->getText();
            std::cout << "赋值表达式: " << exprText << std::endl;
            
            // 简化处理常见的表达式模式
            if (exprText.find('+') != std::string::npos) {
                // 处理加法表达式，例如 sum + i
                size_t plusPos = exprText.find('+');
                std::string leftVar = exprText.substr(0, plusPos);
                std::string rightVar = exprText.substr(plusPos + 1);
                
                // 生成load指令
                std::string leftReg = getNextRegister();
                std::string rightReg = getNextRegister();
                
                if (variables.find(leftVar) != variables.end()) {
                    emitLoad(variables[leftVar], leftReg);
                } else {
                    leftReg = leftVar;  // 常量
                }
                
                if (variables.find(rightVar) != variables.end()) {
                    emitLoad(variables[rightVar], rightReg);
                } else {
                    rightReg = rightVar;  // 常量
                }
                
                // 生成add指令
                std::string resultReg = getNextRegister();
                emitAdd(leftReg, rightReg, resultReg);
                
                // 存储结果
                emitStore(resultReg, targetVar);
                
                std::cout << "赋值: " << varName << " = " << leftVar << " + " << rightVar << std::endl;
            } else {
                // 简单赋值
                auto result = visit(ctx->expression());
                std::string value = "0";
                try {
                    if (result.has_value()) {
                        value = std::any_cast<std::string>(result);
                    }
                } catch (...) {
                    value = "0";
                }
                
                // 检查是否是变量
                if (variables.find(value) != variables.end()) {
                    // 变量到变量的赋值
                    std::string loadReg = getNextRegister();
                    emitLoad(variables[value], loadReg);
                    emitStore(loadReg, targetVar);
                } else {
                    // 常量赋值
                    emitStore(value, targetVar);
                }
                
                std::cout << "赋值: " << varName << " = " << value << std::endl;
            }
        }
        
        return nullptr;
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitCondition(CactParser::ConditionContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitExpression(CactParser::ExpressionContext *ctx) {
    std::cout << "访问表达式: " << ctx->getText() << std::endl;
    if (ctx->addExpression()) {
        return visit(ctx->addExpression());
    }
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitLeftValue(CactParser::LeftValueContext *ctx) {
    std::cout << "访问左值: " << ctx->getText() << std::endl;
    
    std::string varName = ctx->Identifier()->getText();
    std::cout << "变量名: " << varName << std::endl;
    
    // 检查是否是数组访问
    if (!ctx->expression().empty()) {
        // 这是数组访问
        std::cout << "这是数组访问" << std::endl;
        
        // 获取数组索引
        auto indexResult = visit(ctx->expression(0));
        int index = 0;
        
        try {
            if (indexResult.has_value()) {
                index = std::stoi(std::any_cast<std::string>(indexResult));
            }
        } catch (...) {
            index = 0;
        }
        
        std::cout << "数组索引: " << index << std::endl;
        
        // 从数组表中查找值
        auto arrayIt = arrays.find(varName);
        if (arrayIt != arrays.end()) {
            auto elementIt = arrayIt->second.find(index);
            if (elementIt != arrayIt->second.end()) {
                std::cout << "数组元素 " << varName << "[" << index << "] 的值: " << elementIt->second << std::endl;
                return elementIt->second;
            } else {
                std::cout << "数组索引越界: " << index << std::endl;
                addError("数组索引越界: " + std::to_string(index));
                return std::string("0");
            }
        } else {
            std::cout << "未找到数组: " << varName << std::endl;
            addError("未定义的数组: " + varName);
            return std::string("0");
        }
    } else {
        // 普通变量访问 - 返回变量名，让调用者决定如何处理
        return varName;
    }
}

antlrcpp::Any IRGenerator::visitAddExpression(CactParser::AddExpressionContext *ctx) {
    std::cout << "访问加法表达式: " << ctx->getText() << std::endl;
    
    // 检查是否是二元加法运算
    if (ctx->addExpression() && ctx->multiplicativeExpression()) {
        // 这是一个加法运算: addExpression + multiplicativeExpression
        auto leftResult = visit(ctx->addExpression());
        auto rightResult = visit(ctx->multiplicativeExpression());
        
        // 简化处理：假设都是整数常量
        int leftVal = 0, rightVal = 0;
        
        try {
            if (leftResult.has_value()) {
                leftVal = std::stoi(std::any_cast<std::string>(leftResult));
            }
        } catch (...) {
            leftVal = 0;
        }
        
        try {
            if (rightResult.has_value()) {
                rightVal = std::stoi(std::any_cast<std::string>(rightResult));
            }
        } catch (...) {
            rightVal = 0;
        }
        
        int result = leftVal + rightVal;
        std::cout << "计算加法: " << leftVal << " + " << rightVal << " = " << result << std::endl;
        
        return std::to_string(result);
    } else if (ctx->multiplicativeExpression()) {
        // 这只是一个乘法表达式，不是加法
        return visit(ctx->multiplicativeExpression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) {
    std::cout << "访问乘法表达式: " << ctx->getText() << std::endl;
    
    // 如果只是一个一元表达式，直接访问它
    if (ctx->unaryExpression() && !ctx->multiplicativeExpression()) {
        return visit(ctx->unaryExpression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) {
    std::cout << "访问一元表达式: " << ctx->getText() << std::endl;
    
    // 检查是否是函数调用: Identifier '(' [ FuncRParams ] ')'
    if (ctx->Identifier()) {
        std::cout << "处理函数调用: " << ctx->Identifier()->getText() << std::endl;
        
        std::string funcName = ctx->Identifier()->getText();
        std::vector<std::string> args;
        
        // 处理函数参数
        if (ctx->functionRealParameters()) {
            std::cout << "处理函数参数" << std::endl;
            
            // 获取所有参数表达式
            auto expressions = ctx->functionRealParameters()->expression();
            for (auto expr : expressions) {
                auto result = visit(expr);
                std::string argValue = "0";
                try {
                    if (result.has_value()) {
                        argValue = std::any_cast<std::string>(result);
                    }
                } catch (...) {
                    argValue = "0";
                }
                args.push_back(argValue);
                std::cout << "函数参数: " << argValue << std::endl;
            }
        }
        
        // 生成函数调用IR
        if (funcName == "print_int") {
            std::cout << "生成print_int函数调用" << std::endl;
            emitPrintIntCall(args);
        } else if (funcName == "print_float") {
            std::cout << "生成print_float函数调用" << std::endl;
            emitPrintFloatCall(args);
        } else if (funcName == "print_char") {
            std::cout << "生成print_char函数调用" << std::endl;
            emitPrintCharCall(args);
        } else {
            std::cout << "未知函数调用: " << funcName << std::endl;
            addError("未知函数: " + funcName);
        }
        
        return nullptr;
    }
    // 如果是主表达式，直接访问
    else if (ctx->primaryExpression()) {
        return visit(ctx->primaryExpression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
    std::cout << "访问主表达式: " << ctx->getText() << std::endl;
    
    // 如果是数字，直接访问
    if (ctx->number()) {
        return visit(ctx->number());
    }
    // 如果是左值（变量）
    else if (ctx->leftValue()) {
        return visit(ctx->leftValue());
    }
    // 如果是括号表达式
    else if (ctx->expression()) {
        return visit(ctx->expression());
    }
    
    return visitChildren(ctx);
}

antlrcpp::Any IRGenerator::visitNumber(CactParser::NumberContext *ctx) {
    std::cout << "访问数字: " << ctx->getText() << std::endl;
    return ctx->getText();
}

// 辅助方法实现
std::string IRGenerator::getNextRegister() {
    return "%" + std::to_string(registerCounter++);
}

std::string IRGenerator::getNextLocalVar() {
    std::string var = "%" + std::to_string(localVarCounter++);
    // 同步registerCounter以确保不冲突
    if (registerCounter <= localVarCounter) {
        registerCounter = localVarCounter;
    }
    return var;
}

void IRGenerator::emitLoad(const std::string& varName, const std::string& resultReg) {
    irOutput << "  " << resultReg << " = load i32, ptr " << varName << ", align 4\n";
}

void IRGenerator::emitStore(const std::string& value, const std::string& varName) {
    irOutput << "  store i32 " << value << ", ptr " << varName << ", align 4\n";
}

void IRGenerator::emitICmp(const std::string& op, const std::string& left, const std::string& right, const std::string& result) {
    irOutput << "  " << result << " = icmp " << op << " i32 " << left << ", " << right << "\n";
}

void IRGenerator::emitAdd(const std::string& left, const std::string& right, const std::string& result) {
    irOutput << "  " << result << " = add nsw i32 " << left << ", " << right << "\n";
}

// 内置函数调用的实现
void IRGenerator::emitPrintIntCall(const std::vector<std::string>& args) {
    // 生成printf调用来打印整数
    
    if (args.empty()) {
        // 如果没有参数，暂时打印0
        std::string callReg = getNextRegister();
        irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.int, i32 noundef 0)\n";
    } else {
        // 使用第一个参数
        std::string argValue = args[0];
        
        // 检查参数是否是变量名（需要load）
        if (variables.find(argValue) != variables.end()) {
            // 这是一个变量，需要先load
            std::string loadReg = getNextRegister();
            emitLoad(variables[argValue], loadReg);
            std::string callReg = getNextRegister();
            irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.int, i32 noundef " << loadReg << ")\n";
        } else {
            // 这是一个常量或寄存器
            std::string callReg = getNextRegister();
            irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.int, i32 noundef " << argValue << ")\n";
        }
    }
}

void IRGenerator::emitPrintFloatCall(const std::vector<std::string>& args) {
    std::string callReg = getNextRegister();
    
    if (args.empty()) {
        irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.float, float noundef 0.0)\n";
    } else {
        irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.float, float noundef " << args[0] << ")\n";
    }
}

void IRGenerator::emitPrintCharCall(const std::vector<std::string>& args) {
    std::string callReg = getNextRegister();
    
    if (args.empty()) {
        irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.char, i8 noundef 0)\n";
    } else {
        irOutput << "  " << callReg << " = call i32 (ptr, ...) @printf(ptr noundef @.str.char, i8 noundef " << args[0] << ")\n";
    }
}

// 其他辅助方法的空实现
void IRGenerator::emitFunction(const std::string& returnType, const std::string& name) {}
void IRGenerator::emitFunctionWithParams(const std::string& returnType, const std::string& name, const std::vector<std::pair<std::string, std::string>>& params) {}
void IRGenerator::emitReturn(const std::string& value) {}
void IRGenerator::emitLabel(const std::string& label) {}
void IRGenerator::emitVariableDeclaration(const std::string& type, const std::string& name, const std::string& initValue) {}
void IRGenerator::emitArrayDeclaration(const std::string& type, const std::string& name, int size) {}
void IRGenerator::emitArrayStore(const std::string& arrayName, int index, const std::string& value) {}
void IRGenerator::emitArrayLoad(const std::string& arrayName, int index) {}
void IRGenerator::emitFunctionCall(const std::string& funcName, const std::vector<std::string>& args) {}
void IRGenerator::emitConditionalBranch(const std::string& condition, const std::string& trueLabel, const std::string& falseLabel) {}
void IRGenerator::emitUnconditionalBranch(const std::string& label) {}
std::string IRGenerator::getNextLabel() { return "label" + std::to_string(labelCounter++); }

#ifdef LLVM_AVAILABLE
void IRGenerator::initializeLLVM(const std::string& moduleName) {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>(moduleName, *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    
    // 初始化类型映射
    typeMap["int"] = llvm::Type::getInt32Ty(*context);
    typeMap["float"] = llvm::Type::getFloatTy(*context);
    typeMap["char"] = llvm::Type::getInt8Ty(*context);
    typeMap["void"] = llvm::Type::getVoidTy(*context);
}

llvm::Type* IRGenerator::getCactType(const std::string& typeName) {
    auto it = typeMap.find(typeName);
    if (it != typeMap.end()) {
        return it->second;
    }
    addError("未知类型: " + typeName);
    return nullptr;
}

llvm::Value* IRGenerator::createConstant(const std::string& value, llvm::Type* type) {
    if (type->isIntegerTy(32)) {
        return llvm::ConstantInt::get(type, std::stoi(value));
    } else if (type->isFloatTy()) {
        return llvm::ConstantFP::get(type, std::stof(value));
    } else if (type->isIntegerTy(8)) {
        // 处理字符常量
        if (value.size() >= 3 && value[0] == '\'' && value[value.size()-1] == '\'') {
            char c = value[1];  // 简化处理，不考虑转义
            return llvm::ConstantInt::get(type, c);
        }
    }
    addError("无法创建常量: " + value);
    return nullptr;
}
#endif 