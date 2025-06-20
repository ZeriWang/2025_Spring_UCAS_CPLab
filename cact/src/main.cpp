#include <iostream>     // 标准输入输出流
#include <filesystem>   // 文件系统库（C++17）
#include <fstream>      // 文件流

#include "ANTLRInputStream.h"   // ANTLR 输入流
#include "CactLexer.h"          // 词法分析器
#include "CactParser.h"         // 语法分析器
#include "include/syntax_error_listener.h"  // 自定义语法错误监听器
#include "include/SemanticAnalyzer.h"       // 语义分析器
#include "include/IRGenerator.h"            // IR代码生成器

// 递归打印语法树，包含语法单元类型
void printParseTree(antlr4::tree::ParseTree *tree, antlr4::Parser *parser, const std::string &prefix = "", bool isLast = true) {
    // 打印当前节点
    std::cout << prefix << (isLast ? "└── " : "├── ");

    // 获取节点文本和规则名称
    std::string nodeText = tree->getText();
    std::string ruleName = "";
    if (auto *ctx = dynamic_cast<antlr4::ParserRuleContext *>(tree)) {
        ruleName = parser->getRuleNames()[ctx->getRuleIndex()];
    }

    // 打印节点信息
    std::cout << nodeText;
    if (!ruleName.empty()) {
        std::cout << " (" << ruleName << ")";
    }
    std::cout << std::endl;

    // 递归打印子节点
    size_t childCount = tree->children.size();
    for (size_t i = 0; i < childCount; ++i) {
        printParseTree(tree->children[i], parser, prefix + (isLast ? "    " : "│   "), i == childCount - 1);
    }
}

int main(int argc, const char *argv[]) {
    // 检查命令行参数
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl << std::endl;
        return 1;
    }

    // 打开输入文件流
    std::ifstream stream(argv[1]);
    if (!stream) {
        std::cerr << "Error: Could not open file: " << argv[1] << std::endl << std::endl;
        return 1;
    }

    // 获取文件名（不包含路径）
    std::string filename = argv[1];

    // 创建 ANTLR 输入流
    antlr4::ANTLRInputStream input(stream);

    // 创建词法分析器和语法分析器
    CactLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CactParser parser(&tokens);

    // 设置语法错误监听器
    lexer.removeErrorListeners();
    parser.removeErrorListeners();

    cact_parser::CactErrorListener cact_error_listener;
    lexer.addErrorListener(&cact_error_listener);
    parser.addErrorListener(&cact_error_listener);

    try {
        // 解析输入文件
        antlr4::tree::ParseTree *tree = parser.compilationUnit();
        if (!tree) {
            std::cerr << "Error: Failed to parse input file." << std::endl;
            return 1;
        }
        // 检查是否有语法错误
        if (cact_error_listener.hasSyntaxError()) {
            std::cerr << filename << ": Syntax error detected." << std::endl << std::endl;
            std::cerr << "----------------------------------------" << std::endl<< std::endl; // 分隔线
            return 1;
        }

        // 检查是否还有未消费的 token
        if (tokens.LA(1) != antlr4::Token::EOF) {
            std::cerr << filename << ": Error: Unmatched input detected after parsing." << std::endl << std::endl;
            std::cerr << "----------------------------------------" << std::endl<< std::endl; // 分隔线
            return 1;
        }

        // 语义分析
        SemanticAnalyzer analyzer(&parser); // Pass the parser instance
        analyzer.visit(tree);
        if (analyzer.hasSemanticError()) {
            analyzer.printErrors(filename); // Print semantic errors
            std::cerr << filename << ": Semantic error detected." << std::endl << std::endl;
            std::cerr << "----------------------------------------" << std::endl<< std::endl; // 分隔线
            return 1;
        }

        std::cout << filename << ": Parsing and semantic analysis succeeded." << std::endl;

        // IR代码生成
        std::cout << "开始IR代码生成..." << std::endl;
        IRGenerator irGenerator;
        
        // 提取模块名（去除路径和扩展名）
        std::string moduleName = std::filesystem::path(filename).stem().string();
        
        if (irGenerator.generateIR(tree, moduleName)) {
            std::cout << filename << ": IR generation succeeded." << std::endl;
            
            // 输出IR到文件
            std::string irFilename = moduleName + ".ll";
            if (irGenerator.writeIRToFile(irFilename)) {
                std::cout << "IR代码已保存到: " << irFilename << std::endl;
            } else {
                std::cerr << "警告: 无法写入IR文件: " << irFilename << std::endl;
            }
            
            // 也输出到控制台用于调试
            std::cout << "生成的IR代码:" << std::endl;
            std::cout << irGenerator.getIRString() << std::endl;
            
        } else {
            std::cerr << filename << ": IR generation failed." << std::endl;
            irGenerator.printErrors();
            std::cerr << "----------------------------------------" << std::endl<< std::endl; // 分隔线
            return 1;
        }

        std::cerr << "----------------------------------------" << std::endl<< std::endl; // 分隔线
    } catch (const antlr4::RecognitionException &e) {
        // 处理 ANTLR 特定的异常
        std::cerr << "ANTLR Recognition error: " << e.what() << std::endl;
        std::cerr << filename << ": Parsing failed." << std::endl << std::endl;
        return 1;
    } catch (const std::exception &e) {
        // 捕获异常并输出错误信息
        std::cerr << "Error while parsing file '" << argv[1] << "': " << e.what() << std::endl << std::endl;
        return 1;
    }
}