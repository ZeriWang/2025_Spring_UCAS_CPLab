#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "CactParserBaseVisitor.h"
#include "antlr4-runtime.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <stack>
#include <sstream>

// LLVM headers (will be included after LLVM is installed)
#ifdef LLVM_AVAILABLE
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Verifier.h"
#endif

// Forward declarations
namespace cact_parser {
    class CactParser;
}

class IRGenerator : public CactParserBaseVisitor {
public:
    IRGenerator();
    ~IRGenerator();

    // Main entry point for IR generation
    bool generateIR(antlr4::tree::ParseTree* tree, const std::string& moduleName);
    
    // Output IR to string or file
    std::string getIRString() const;
    bool writeIRToFile(const std::string& filename) const;
    
    // Check if there are any IR generation errors
    bool hasErrors() const { return !errors.empty(); }
    void printErrors() const;

    // Visit methods for AST nodes
    antlrcpp::Any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override;
    antlrcpp::Any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override;
    antlrcpp::Any visitFunctionFormalParameters(CactParser::FunctionFormalParametersContext *ctx) override;
    antlrcpp::Any visitFunctionFormalParameter(CactParser::FunctionFormalParameterContext *ctx) override;
    antlrcpp::Any visitBlock(CactParser::BlockContext *ctx) override;
    antlrcpp::Any visitDeclaration(CactParser::DeclarationContext *ctx) override;
    antlrcpp::Any visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) override;
    antlrcpp::Any visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) override;
    antlrcpp::Any visitConstantInitializationValue(CactParser::ConstantInitializationValueContext *ctx) override;
    antlrcpp::Any visitConstantExpression(CactParser::ConstantExpressionContext *ctx) override;
    antlrcpp::Any visitStatement(CactParser::StatementContext *ctx) override;
    antlrcpp::Any visitCondition(CactParser::ConditionContext *ctx) override;
    antlrcpp::Any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) override;
    antlrcpp::Any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) override;
    antlrcpp::Any visitEqualityExpression(CactParser::EqualityExpressionContext *ctx) override;
    antlrcpp::Any visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) override;
    antlrcpp::Any visitExpression(CactParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitLeftValue(CactParser::LeftValueContext *ctx) override;
    antlrcpp::Any visitAddExpression(CactParser::AddExpressionContext *ctx) override;
    antlrcpp::Any visitMultiplicativeExpression(CactParser::MultiplicativeExpressionContext *ctx) override;
    antlrcpp::Any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override;
    antlrcpp::Any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override;
    antlrcpp::Any visitNumber(CactParser::NumberContext *ctx) override;

private:
#ifdef LLVM_AVAILABLE
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    
    // Type mapping
    std::map<std::string, llvm::Type*> typeMap;
    
    // Current function being processed
    llvm::Function* currentFunction;
    
    // 作用域栈：每个作用域维护一个变量表
    std::stack<std::map<std::string, llvm::Value*>> variableScopes;
    
    // 当前作用域的变量表的引用（指向栈顶）
    std::map<std::string, llvm::Value*>* currentVariables;
    
    // 全局变量表：变量名 -> GlobalVariable*
    std::map<std::string, llvm::GlobalVariable*> globalVariables;
    
    // 函数参数数组类型信息：参数名 -> 维度列表
    std::map<std::string, std::vector<int>> functionParameterArrayTypes;
    
    // 循环控制块跟踪（用于break/continue语句）
    std::stack<std::pair<llvm::BasicBlock*, llvm::BasicBlock*>> loopStack; // (continue_target, break_target)
#else
    // 作用域栈：每个作用域维护一个变量表
    std::stack<std::map<std::string, std::string>> variableScopes;
    
    // 当前作用域的变量表的引用（指向栈顶）
    std::map<std::string, std::string>* currentVariables;
#endif
    
    std::vector<std::string> errors;
    std::stringstream irOutput;  // 用于模拟IR输出
    
    // 数组表：数组名 -> 元素值映射
    std::map<std::string, std::map<int, std::string>> arrays;
    
    // 函数表：函数名 -> 参数列表（用于函数调用）
    std::map<std::string, std::vector<std::string>> functions;
    
    // 标签计数器（用于生成唯一的基本块标签）
    int labelCounter;
    
    // 寄存器计数器（用于生成SSA形式的寄存器）
    int registerCounter;
    
    // 当前函数的局部变量计数器
    int localVarCounter;
    
    void addError(const std::string& message);
    
    // 作用域管理方法
    void enterScope();
    void exitScope();
#ifdef LLVM_AVAILABLE
    llvm::Value* findVariable(const std::string& name);
    void defineVariable(const std::string& name, llvm::Value* value);
#else
    std::string findVariable(const std::string& name);
    void defineVariable(const std::string& name, const std::string& localVar);
#endif
    
#ifdef LLVM_AVAILABLE
    // Helper methods for LLVM operations
    llvm::Type* getCactType(const std::string& typeName);
    llvm::Value* createConstant(const std::string& value, llvm::Type* type);
    
    // Initialize LLVM components
    void initializeLLVM(const std::string& moduleName);
    
    // 全局变量声明处理
    antlrcpp::Any visitGlobalVariableDeclaration(CactParser::VariableDeclarationContext *ctx);
    
    // 全局常量声明处理
    antlrcpp::Any visitGlobalConstantDeclaration(CactParser::ConstantDeclarationContext *ctx);
#endif

    // 模拟IR生成的辅助方法
    void emitFunction(const std::string& returnType, const std::string& name);
    void emitFunctionWithParams(const std::string& returnType, const std::string& name, const std::vector<std::pair<std::string, std::string>>& params);
    void emitReturn(const std::string& value);
    void emitLabel(const std::string& label);
    void emitVariableDeclaration(const std::string& type, const std::string& name, const std::string& initValue = "");
    void emitArrayDeclaration(const std::string& type, const std::string& name, int size);
    void emitArrayStore(const std::string& arrayName, int index, const std::string& value);
    void emitArrayLoad(const std::string& arrayName, int index);
    void emitFunctionCall(const std::string& funcName, const std::vector<std::string>& args);
    void emitConditionalBranch(const std::string& condition, const std::string& trueLabel, const std::string& falseLabel);
    void emitUnconditionalBranch(const std::string& label);
    std::string getNextLabel();
    std::string getNextRegister();
    std::string getNextLocalVar();
    void emitLoad(const std::string& varName, const std::string& resultReg);
    void emitStore(const std::string& value, const std::string& varName);
    void emitICmp(const std::string& op, const std::string& left, const std::string& right, const std::string& result);
    void emitAdd(const std::string& left, const std::string& right, const std::string& result);
    
    // 内置函数调用的emit方法
    void emitPrintIntCall(const std::vector<std::string>& args);
    void emitPrintFloatCall(const std::vector<std::string>& args);
    void emitPrintCharCall(const std::vector<std::string>& args);
};

#endif // IR_GENERATOR_H 