#ifndef CPLAB_SYNTAX_ERROR_LISTENER
#define CPLAB_SYNTAX_ERROR_LISTENER

#include "BaseErrorListener.h"

namespace cact_parser
{
    class CactErrorListener final : public antlr4::BaseErrorListener
    {
    public:
        // 语法错误监听器的构造函数
        void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                         size_t line, size_t charPositionInLine, const std::string &msg,
                         std::exception_ptr e) override;

        // 检查是否有语法错误
        bool hasSyntaxError();

    private:
        bool has_syntax_error = false; // 标志是否有语法错误
    };
} // namespace cact_parser
#endif // CPLAB_SYNTAX_ERROR_LISTENER