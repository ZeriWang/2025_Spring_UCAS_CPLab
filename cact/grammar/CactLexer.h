
// Generated from CactLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"

class  CactLexer : public antlr4::Lexer {
public:
  enum {
    Const = 1, Int = 2, Float = 3, Char = 4, Void = 5, If = 6, Else = 7, 
    While = 8, Break = 9, Continue = 10, Return = 11, LeftBracket = 12, 
    RightBracket = 13, LeftParenthesis = 14, RightParenthesis = 15, ExclamationMark = 16, 
    Asterisk = 17, Slash = 18, Percent = 19, Minus = 20, Plus = 21, Less = 22, 
    LessEqual = 23, Greater = 24, GreaterEqual = 25, LogicalEqual = 26, 
    NotEqual = 27, LogicalAnd = 28, LogicalOr = 29, LeftBrace = 30, RightBrace = 31, 
    Equal = 32, Comma = 33, Semicolon = 34, Identifier = 35, IntegerConstant = 36, 
    CharacterConstant = 37, FloatConstant = 38, LineComment = 39, BlockComment = 40, 
    NewLine = 41, WhiteSpaces = 42
  };

  explicit CactLexer(antlr4::CharStream *input);

  ~CactLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  };


