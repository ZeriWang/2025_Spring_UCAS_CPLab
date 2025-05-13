#include "include/SymbolTable.h"

Scope::Scope(std::shared_ptr<Scope> parent) : parent(parent) {}

bool Scope::insert(const Symbol& symbol) {
    if (table.count(symbol.name)) return false;
    table[symbol.name] = symbol;
    return true;
}

std::optional<Symbol> Scope::lookup(const std::string& name) const {
    auto it = table.find(name);
    if (it != table.end()) return it->second;
    if (parent) return parent->lookup(name);
    return std::nullopt;
}

std::shared_ptr<Scope> Scope::getParent() const {
    return parent;
}

SymbolTable::SymbolTable() {
    currentScope = std::make_shared<Scope>(nullptr);
}

void SymbolTable::enterScope() {
    currentScope = std::make_shared<Scope>(currentScope);
}

void SymbolTable::exitScope() {
    if (currentScope->getParent()) {
        currentScope = currentScope->getParent();
    }
}

bool SymbolTable::insert(const Symbol& symbol) {
    return currentScope->insert(symbol);
}

std::optional<Symbol> SymbolTable::lookup(const std::string& name) const {
    return currentScope->lookup(name);
}

BaseType strToBaseType(const std::string& typeStr) {
    if (typeStr == "int") return BaseType::Int;
    if (typeStr == "float") return BaseType::Float;
    if (typeStr == "char") return BaseType::Char;
    if (typeStr == "void") return BaseType::Void;
}

std::string baseTypeToStr(BaseType type) {
    switch (type) {
        case BaseType::Int: return "int";
        case BaseType::Float: return "float";
        case BaseType::Char: return "char";
        case BaseType::Void: return "void";
    }
}