#include "include/syntax_error_listener.h"
#include "antlr4-runtime.h"
#include <iostream>

namespace cact_parser {
    // 语法错误监听器的构造函数
    void CactErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
        size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
        has_syntax_error = true; // 设置语法错误标志为true
        std::cerr << "Syntax Error Message: " << msg << std::endl; // 输出语法错误信息
        std::cerr << "Line: " << line << ", Position: " << charPositionInLine << std::endl; // 输出错误位置
        std::cerr << "Offending Symbol: " << (offendingSymbol ? offendingSymbol->getText() : "null") << std::endl; // 输出错误的符号
    }
    bool CactErrorListener::hasSyntaxError() {
        return has_syntax_error; // 返回语法错误标志
    }
}
