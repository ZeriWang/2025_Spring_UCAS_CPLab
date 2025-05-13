#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>

// 符号类型
enum class SymbolType {
    Variable,
    Constant,
    Function
};

// 支持的基本类型
enum class BaseType {
    Int,
    Float,
    Char,
    Void
};

// 符号信息
struct Symbol {
    std::string name;
    SymbolType symbolType;
    BaseType baseType;
    bool isArray = false;
    std::vector<int> arrayDims; // 支持多维数组
    bool isInitialized = false;
    // 函数参数类型
    std::vector<BaseType> paramTypes;
};

// 单个作用域
class Scope {
public:
    Scope(std::shared_ptr<Scope> parent = nullptr);

    bool insert(const Symbol& symbol);
    std::optional<Symbol> lookup(const std::string& name) const;
    std::shared_ptr<Scope> getParent() const;

private:
    std::unordered_map<std::string, Symbol> table;
    std::shared_ptr<Scope> parent;
};

// 符号表管理器，支持作用域嵌套
class SymbolTable {
public:
    SymbolTable();

    void enterScope();
    void exitScope();
    bool insert(const Symbol& symbol);
    std::optional<Symbol> lookup(const std::string& name) const;

private:
    std::shared_ptr<Scope> currentScope;
};

BaseType strToBaseType(const std::string& typeStr);
std::string baseTypeToStr(BaseType type);
