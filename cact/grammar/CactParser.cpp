
// Generated from CactParser.g4 by ANTLR 4.13.1


#include "CactParserVisitor.h"

#include "CactParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CactParserStaticData final {
  CactParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CactParserStaticData(const CactParserStaticData&) = delete;
  CactParserStaticData(CactParserStaticData&&) = delete;
  CactParserStaticData& operator=(const CactParserStaticData&) = delete;
  CactParserStaticData& operator=(CactParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cactparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CactParserStaticData *cactparserParserStaticData = nullptr;

void cactparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cactparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(cactparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CactParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "declaration", "constantDeclaration", "basicType", 
      "constantDefinition", "constantInitializationValue", "variableDeclaration", 
      "variableDefinition", "functionDefinition", "functionType", "functionFormalParameters", 
      "functionFormalParameter", "block", "blockItem", "statement", "expression", 
      "constantExpression", "condition", "leftValue", "number", "functionRealParameters", 
      "primaryExpression", "unaryExpression", "multiplicativeExpression", 
      "addExpression", "relationalExpression", "equalityExpression", "logicalAndExpression", 
      "logicalOrExpression"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'float'", "'char'", "'void'", "'if'", "'else'", 
      "'while'", "'break'", "'continue'", "'return'", "'['", "']'", "'('", 
      "')'", "'!'", "'*'", "'/'", "'%'", "'-'", "'+'", "'<'", "'<='", "'>'", 
      "'>='", "'=='", "'!='", "'&&'", "'||'", "'{'", "'}'", "'='", "','", 
      "';'"
    },
    std::vector<std::string>{
      "", "Const", "Int", "Float", "Char", "Void", "If", "Else", "While", 
      "Break", "Continue", "Return", "LeftBracket", "RightBracket", "LeftParenthesis", 
      "RightParenthesis", "ExclamationMark", "Asterisk", "Slash", "Percent", 
      "Minus", "Plus", "Less", "LessEqual", "Greater", "GreaterEqual", "LogicalEqual", 
      "NotEqual", "LogicalAnd", "LogicalOr", "LeftBrace", "RightBrace", 
      "Equal", "Comma", "Semicolon", "Identifier", "IntegerConstant", "CharacterConstant", 
      "FloatConstant", "LineComment", "BlockComment", "NewLine", "WhiteSpaces"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,42,331,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,5,0,61,8,0,10,0,12,0,64,9,0,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,
  	1,2,1,2,5,2,75,8,2,10,2,12,2,78,9,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,5,
  	4,88,8,4,10,4,12,4,91,9,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,101,8,5,
  	10,5,12,5,104,9,5,3,5,106,8,5,1,5,3,5,109,8,5,1,6,1,6,1,6,1,6,5,6,115,
  	8,6,10,6,12,6,118,9,6,1,6,1,6,1,7,1,7,1,7,1,7,5,7,126,8,7,10,7,12,7,129,
  	9,7,1,7,1,7,3,7,133,8,7,1,8,1,8,1,8,1,8,3,8,139,8,8,1,8,1,8,1,8,1,9,1,
  	9,1,10,1,10,1,10,5,10,149,8,10,10,10,12,10,152,9,10,1,11,1,11,1,11,1,
  	11,3,11,158,8,11,1,11,1,11,1,11,1,11,5,11,164,8,11,10,11,12,11,167,9,
  	11,3,11,169,8,11,1,12,1,12,5,12,173,8,12,10,12,12,12,176,9,12,1,12,1,
  	12,1,13,1,13,3,13,182,8,13,1,14,1,14,1,14,1,14,1,14,1,14,3,14,190,8,14,
  	1,14,1,14,1,14,1,14,3,14,196,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,3,14,206,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	3,14,218,8,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,
  	5,18,231,8,18,10,18,12,18,234,9,18,1,19,1,19,1,20,1,20,1,20,5,20,241,
  	8,20,10,20,12,20,244,9,20,1,21,1,21,1,21,1,21,1,21,1,21,3,21,252,8,21,
  	1,22,1,22,1,22,1,22,1,22,1,22,3,22,260,8,22,1,22,3,22,263,8,22,1,23,1,
  	23,1,23,1,23,1,23,1,23,5,23,271,8,23,10,23,12,23,274,9,23,1,24,1,24,1,
  	24,1,24,1,24,1,24,5,24,282,8,24,10,24,12,24,285,9,24,1,25,1,25,1,25,1,
  	25,1,25,1,25,5,25,293,8,25,10,25,12,25,296,9,25,1,26,1,26,1,26,1,26,1,
  	26,1,26,5,26,304,8,26,10,26,12,26,307,9,26,1,27,1,27,1,27,1,27,1,27,1,
  	27,5,27,315,8,27,10,27,12,27,318,9,27,1,28,1,28,1,28,1,28,1,28,1,28,5,
  	28,326,8,28,10,28,12,28,329,9,28,1,28,0,6,46,48,50,52,54,56,29,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,
  	54,56,0,8,1,0,2,4,1,0,2,5,1,0,36,38,2,0,16,16,20,21,1,0,17,19,1,0,20,
  	21,1,0,22,25,1,0,26,27,342,0,62,1,0,0,0,2,67,1,0,0,0,4,69,1,0,0,0,6,81,
  	1,0,0,0,8,83,1,0,0,0,10,108,1,0,0,0,12,110,1,0,0,0,14,121,1,0,0,0,16,
  	134,1,0,0,0,18,143,1,0,0,0,20,145,1,0,0,0,22,153,1,0,0,0,24,170,1,0,0,
  	0,26,181,1,0,0,0,28,217,1,0,0,0,30,219,1,0,0,0,32,221,1,0,0,0,34,223,
  	1,0,0,0,36,225,1,0,0,0,38,235,1,0,0,0,40,237,1,0,0,0,42,251,1,0,0,0,44,
  	262,1,0,0,0,46,264,1,0,0,0,48,275,1,0,0,0,50,286,1,0,0,0,52,297,1,0,0,
  	0,54,308,1,0,0,0,56,319,1,0,0,0,58,61,3,2,1,0,59,61,3,16,8,0,60,58,1,
  	0,0,0,60,59,1,0,0,0,61,64,1,0,0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,1,1,
  	0,0,0,64,62,1,0,0,0,65,68,3,4,2,0,66,68,3,12,6,0,67,65,1,0,0,0,67,66,
  	1,0,0,0,68,3,1,0,0,0,69,70,5,1,0,0,70,71,3,6,3,0,71,76,3,8,4,0,72,73,
  	5,33,0,0,73,75,3,8,4,0,74,72,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,
  	1,0,0,0,77,79,1,0,0,0,78,76,1,0,0,0,79,80,5,34,0,0,80,5,1,0,0,0,81,82,
  	7,0,0,0,82,7,1,0,0,0,83,89,5,35,0,0,84,85,5,12,0,0,85,86,5,36,0,0,86,
  	88,5,13,0,0,87,84,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,
  	92,1,0,0,0,91,89,1,0,0,0,92,93,5,32,0,0,93,94,3,10,5,0,94,9,1,0,0,0,95,
  	109,3,32,16,0,96,105,5,30,0,0,97,102,3,10,5,0,98,99,5,33,0,0,99,101,3,
  	10,5,0,100,98,1,0,0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,
  	103,106,1,0,0,0,104,102,1,0,0,0,105,97,1,0,0,0,105,106,1,0,0,0,106,107,
  	1,0,0,0,107,109,5,31,0,0,108,95,1,0,0,0,108,96,1,0,0,0,109,11,1,0,0,0,
  	110,111,3,6,3,0,111,116,3,14,7,0,112,113,5,33,0,0,113,115,3,14,7,0,114,
  	112,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,119,1,
  	0,0,0,118,116,1,0,0,0,119,120,5,34,0,0,120,13,1,0,0,0,121,127,5,35,0,
  	0,122,123,5,12,0,0,123,124,5,36,0,0,124,126,5,13,0,0,125,122,1,0,0,0,
  	126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,132,1,0,0,0,129,127,
  	1,0,0,0,130,131,5,32,0,0,131,133,3,10,5,0,132,130,1,0,0,0,132,133,1,0,
  	0,0,133,15,1,0,0,0,134,135,3,18,9,0,135,136,5,35,0,0,136,138,5,14,0,0,
  	137,139,3,20,10,0,138,137,1,0,0,0,138,139,1,0,0,0,139,140,1,0,0,0,140,
  	141,5,15,0,0,141,142,3,24,12,0,142,17,1,0,0,0,143,144,7,1,0,0,144,19,
  	1,0,0,0,145,150,3,22,11,0,146,147,5,33,0,0,147,149,3,22,11,0,148,146,
  	1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,21,1,0,0,
  	0,152,150,1,0,0,0,153,154,3,6,3,0,154,168,5,35,0,0,155,157,5,12,0,0,156,
  	158,5,36,0,0,157,156,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,165,
  	5,13,0,0,160,161,5,12,0,0,161,162,5,36,0,0,162,164,5,13,0,0,163,160,1,
  	0,0,0,164,167,1,0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,169,1,0,0,0,
  	167,165,1,0,0,0,168,155,1,0,0,0,168,169,1,0,0,0,169,23,1,0,0,0,170,174,
  	5,30,0,0,171,173,3,26,13,0,172,171,1,0,0,0,173,176,1,0,0,0,174,172,1,
  	0,0,0,174,175,1,0,0,0,175,177,1,0,0,0,176,174,1,0,0,0,177,178,5,31,0,
  	0,178,25,1,0,0,0,179,182,3,2,1,0,180,182,3,28,14,0,181,179,1,0,0,0,181,
  	180,1,0,0,0,182,27,1,0,0,0,183,184,3,36,18,0,184,185,5,32,0,0,185,186,
  	3,30,15,0,186,187,5,34,0,0,187,218,1,0,0,0,188,190,3,30,15,0,189,188,
  	1,0,0,0,189,190,1,0,0,0,190,191,1,0,0,0,191,218,5,34,0,0,192,218,3,24,
  	12,0,193,195,5,11,0,0,194,196,3,30,15,0,195,194,1,0,0,0,195,196,1,0,0,
  	0,196,197,1,0,0,0,197,218,5,34,0,0,198,199,5,6,0,0,199,200,5,14,0,0,200,
  	201,3,34,17,0,201,202,5,15,0,0,202,205,3,28,14,0,203,204,5,7,0,0,204,
  	206,3,28,14,0,205,203,1,0,0,0,205,206,1,0,0,0,206,218,1,0,0,0,207,208,
  	5,8,0,0,208,209,5,14,0,0,209,210,3,34,17,0,210,211,5,15,0,0,211,212,3,
  	28,14,0,212,218,1,0,0,0,213,214,5,9,0,0,214,218,5,34,0,0,215,216,5,10,
  	0,0,216,218,5,34,0,0,217,183,1,0,0,0,217,189,1,0,0,0,217,192,1,0,0,0,
  	217,193,1,0,0,0,217,198,1,0,0,0,217,207,1,0,0,0,217,213,1,0,0,0,217,215,
  	1,0,0,0,218,29,1,0,0,0,219,220,3,48,24,0,220,31,1,0,0,0,221,222,3,48,
  	24,0,222,33,1,0,0,0,223,224,3,56,28,0,224,35,1,0,0,0,225,232,5,35,0,0,
  	226,227,5,12,0,0,227,228,3,30,15,0,228,229,5,13,0,0,229,231,1,0,0,0,230,
  	226,1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,1,0,0,0,233,37,1,
  	0,0,0,234,232,1,0,0,0,235,236,7,2,0,0,236,39,1,0,0,0,237,242,3,30,15,
  	0,238,239,5,33,0,0,239,241,3,30,15,0,240,238,1,0,0,0,241,244,1,0,0,0,
  	242,240,1,0,0,0,242,243,1,0,0,0,243,41,1,0,0,0,244,242,1,0,0,0,245,246,
  	5,14,0,0,246,247,3,30,15,0,247,248,5,15,0,0,248,252,1,0,0,0,249,252,3,
  	36,18,0,250,252,3,38,19,0,251,245,1,0,0,0,251,249,1,0,0,0,251,250,1,0,
  	0,0,252,43,1,0,0,0,253,263,3,42,21,0,254,255,7,3,0,0,255,263,3,44,22,
  	0,256,257,5,35,0,0,257,259,5,14,0,0,258,260,3,40,20,0,259,258,1,0,0,0,
  	259,260,1,0,0,0,260,261,1,0,0,0,261,263,5,15,0,0,262,253,1,0,0,0,262,
  	254,1,0,0,0,262,256,1,0,0,0,263,45,1,0,0,0,264,265,6,23,-1,0,265,266,
  	3,44,22,0,266,272,1,0,0,0,267,268,10,1,0,0,268,269,7,4,0,0,269,271,3,
  	44,22,0,270,267,1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,0,272,273,1,0,0,
  	0,273,47,1,0,0,0,274,272,1,0,0,0,275,276,6,24,-1,0,276,277,3,46,23,0,
  	277,283,1,0,0,0,278,279,10,1,0,0,279,280,7,5,0,0,280,282,3,46,23,0,281,
  	278,1,0,0,0,282,285,1,0,0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,49,1,
  	0,0,0,285,283,1,0,0,0,286,287,6,25,-1,0,287,288,3,48,24,0,288,294,1,0,
  	0,0,289,290,10,1,0,0,290,291,7,6,0,0,291,293,3,48,24,0,292,289,1,0,0,
  	0,293,296,1,0,0,0,294,292,1,0,0,0,294,295,1,0,0,0,295,51,1,0,0,0,296,
  	294,1,0,0,0,297,298,6,26,-1,0,298,299,3,50,25,0,299,305,1,0,0,0,300,301,
  	10,1,0,0,301,302,7,7,0,0,302,304,3,50,25,0,303,300,1,0,0,0,304,307,1,
  	0,0,0,305,303,1,0,0,0,305,306,1,0,0,0,306,53,1,0,0,0,307,305,1,0,0,0,
  	308,309,6,27,-1,0,309,310,3,52,26,0,310,316,1,0,0,0,311,312,10,1,0,0,
  	312,313,5,28,0,0,313,315,3,52,26,0,314,311,1,0,0,0,315,318,1,0,0,0,316,
  	314,1,0,0,0,316,317,1,0,0,0,317,55,1,0,0,0,318,316,1,0,0,0,319,320,6,
  	28,-1,0,320,321,3,54,27,0,321,327,1,0,0,0,322,323,10,1,0,0,323,324,5,
  	29,0,0,324,326,3,54,27,0,325,322,1,0,0,0,326,329,1,0,0,0,327,325,1,0,
  	0,0,327,328,1,0,0,0,328,57,1,0,0,0,329,327,1,0,0,0,33,60,62,67,76,89,
  	102,105,108,116,127,132,138,150,157,165,168,174,181,189,195,205,217,232,
  	242,251,259,262,272,283,294,305,316,327
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cactparserParserStaticData = staticData.release();
}

}

CactParser::CactParser(TokenStream *input) : CactParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CactParser::CactParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CactParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cactparserParserStaticData->atn, cactparserParserStaticData->decisionToDFA, cactparserParserStaticData->sharedContextCache, options);
}

CactParser::~CactParser() {
  delete _interpreter;
}

const atn::ATN& CactParser::getATN() const {
  return *cactparserParserStaticData->atn;
}

std::string CactParser::getGrammarFileName() const {
  return "CactParser.g4";
}

const std::vector<std::string>& CactParser::getRuleNames() const {
  return cactparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& CactParser::getVocabulary() const {
  return cactparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CactParser::getSerializedATN() const {
  return cactparserParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

CactParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::DeclarationContext *> CactParser::CompilationUnitContext::declaration() {
  return getRuleContexts<CactParser::DeclarationContext>();
}

CactParser::DeclarationContext* CactParser::CompilationUnitContext::declaration(size_t i) {
  return getRuleContext<CactParser::DeclarationContext>(i);
}

std::vector<CactParser::FunctionDefinitionContext *> CactParser::CompilationUnitContext::functionDefinition() {
  return getRuleContexts<CactParser::FunctionDefinitionContext>();
}

CactParser::FunctionDefinitionContext* CactParser::CompilationUnitContext::functionDefinition(size_t i) {
  return getRuleContext<CactParser::FunctionDefinitionContext>(i);
}


size_t CactParser::CompilationUnitContext::getRuleIndex() const {
  return CactParser::RuleCompilationUnit;
}


std::any CactParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

CactParser::CompilationUnitContext* CactParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CactParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 62) != 0)) {
      setState(60);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(58);
        declaration();
        break;
      }

      case 2: {
        setState(59);
        functionDefinition();
        break;
      }

      default:
        break;
      }
      setState(64);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CactParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::ConstantDeclarationContext* CactParser::DeclarationContext::constantDeclaration() {
  return getRuleContext<CactParser::ConstantDeclarationContext>(0);
}

CactParser::VariableDeclarationContext* CactParser::DeclarationContext::variableDeclaration() {
  return getRuleContext<CactParser::VariableDeclarationContext>(0);
}


size_t CactParser::DeclarationContext::getRuleIndex() const {
  return CactParser::RuleDeclaration;
}


std::any CactParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::DeclarationContext* CactParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, CactParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(65);
        constantDeclaration();
        break;
      }

      case CactParser::Int:
      case CactParser::Float:
      case CactParser::Char: {
        enterOuterAlt(_localctx, 2);
        setState(66);
        variableDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDeclarationContext ------------------------------------------------------------------

CactParser::ConstantDeclarationContext::ConstantDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Const() {
  return getToken(CactParser::Const, 0);
}

CactParser::BasicTypeContext* CactParser::ConstantDeclarationContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

std::vector<CactParser::ConstantDefinitionContext *> CactParser::ConstantDeclarationContext::constantDefinition() {
  return getRuleContexts<CactParser::ConstantDefinitionContext>();
}

CactParser::ConstantDefinitionContext* CactParser::ConstantDeclarationContext::constantDefinition(size_t i) {
  return getRuleContext<CactParser::ConstantDefinitionContext>(i);
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDeclarationContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::ConstantDeclarationContext::getRuleIndex() const {
  return CactParser::RuleConstantDeclaration;
}


std::any CactParser::ConstantDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantDeclarationContext* CactParser::constantDeclaration() {
  ConstantDeclarationContext *_localctx = _tracker.createInstance<ConstantDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, CactParser::RuleConstantDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(CactParser::Const);
    setState(70);
    basicType();
    setState(71);
    constantDefinition();
    setState(76);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(72);
      match(CactParser::Comma);
      setState(73);
      constantDefinition();
      setState(78);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(79);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

CactParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BasicTypeContext::Int() {
  return getToken(CactParser::Int, 0);
}

tree::TerminalNode* CactParser::BasicTypeContext::Float() {
  return getToken(CactParser::Float, 0);
}

tree::TerminalNode* CactParser::BasicTypeContext::Char() {
  return getToken(CactParser::Char, 0);
}


size_t CactParser::BasicTypeContext::getRuleIndex() const {
  return CactParser::RuleBasicType;
}


std::any CactParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BasicTypeContext* CactParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, CactParser::RuleBasicType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDefinitionContext ------------------------------------------------------------------

CactParser::ConstantDefinitionContext::ConstantDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ConstantInitializationValueContext* CactParser::ConstantDefinitionContext::constantInitializationValue() {
  return getRuleContext<CactParser::ConstantInitializationValueContext>(0);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}


size_t CactParser::ConstantDefinitionContext::getRuleIndex() const {
  return CactParser::RuleConstantDefinition;
}


std::any CactParser::ConstantDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantDefinitionContext* CactParser::constantDefinition() {
  ConstantDefinitionContext *_localctx = _tracker.createInstance<ConstantDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 8, CactParser::RuleConstantDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    match(CactParser::Identifier);
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::LeftBracket) {
      setState(84);
      match(CactParser::LeftBracket);
      setState(85);
      match(CactParser::IntegerConstant);
      setState(86);
      match(CactParser::RightBracket);
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    match(CactParser::Equal);
    setState(93);
    constantInitializationValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantInitializationValueContext ------------------------------------------------------------------

CactParser::ConstantInitializationValueContext::ConstantInitializationValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::ConstantExpressionContext* CactParser::ConstantInitializationValueContext::constantExpression() {
  return getRuleContext<CactParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CactParser::ConstantInitializationValueContext::LeftBrace() {
  return getToken(CactParser::LeftBrace, 0);
}

tree::TerminalNode* CactParser::ConstantInitializationValueContext::RightBrace() {
  return getToken(CactParser::RightBrace, 0);
}

std::vector<CactParser::ConstantInitializationValueContext *> CactParser::ConstantInitializationValueContext::constantInitializationValue() {
  return getRuleContexts<CactParser::ConstantInitializationValueContext>();
}

CactParser::ConstantInitializationValueContext* CactParser::ConstantInitializationValueContext::constantInitializationValue(size_t i) {
  return getRuleContext<CactParser::ConstantInitializationValueContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantInitializationValueContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::ConstantInitializationValueContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::ConstantInitializationValueContext::getRuleIndex() const {
  return CactParser::RuleConstantInitializationValue;
}


std::any CactParser::ConstantInitializationValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantInitializationValue(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantInitializationValueContext* CactParser::constantInitializationValue() {
  ConstantInitializationValueContext *_localctx = _tracker.createInstance<ConstantInitializationValueContext>(_ctx, getState());
  enterRule(_localctx, 10, CactParser::RuleConstantInitializationValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::LeftParenthesis:
      case CactParser::ExclamationMark:
      case CactParser::Minus:
      case CactParser::Plus:
      case CactParser::Identifier:
      case CactParser::IntegerConstant:
      case CactParser::CharacterConstant:
      case CactParser::FloatConstant: {
        enterOuterAlt(_localctx, 1);
        setState(95);
        constantExpression();
        break;
      }

      case CactParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(96);
        match(CactParser::LeftBrace);
        setState(105);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 516473044992) != 0)) {
          setState(97);
          constantInitializationValue();
          setState(102);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CactParser::Comma) {
            setState(98);
            match(CactParser::Comma);
            setState(99);
            constantInitializationValue();
            setState(104);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(107);
        match(CactParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

CactParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::BasicTypeContext* CactParser::VariableDeclarationContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

std::vector<CactParser::VariableDefinitionContext *> CactParser::VariableDeclarationContext::variableDefinition() {
  return getRuleContexts<CactParser::VariableDefinitionContext>();
}

CactParser::VariableDefinitionContext* CactParser::VariableDeclarationContext::variableDefinition(size_t i) {
  return getRuleContext<CactParser::VariableDefinitionContext>(i);
}

tree::TerminalNode* CactParser::VariableDeclarationContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

std::vector<tree::TerminalNode *> CactParser::VariableDeclarationContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::VariableDeclarationContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::VariableDeclarationContext::getRuleIndex() const {
  return CactParser::RuleVariableDeclaration;
}


std::any CactParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::VariableDeclarationContext* CactParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, CactParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    basicType();
    setState(111);
    variableDefinition();
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(112);
      match(CactParser::Comma);
      setState(113);
      variableDefinition();
      setState(118);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(119);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

CactParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ConstantInitializationValueContext* CactParser::VariableDefinitionContext::constantInitializationValue() {
  return getRuleContext<CactParser::ConstantInitializationValueContext>(0);
}


size_t CactParser::VariableDefinitionContext::getRuleIndex() const {
  return CactParser::RuleVariableDefinition;
}


std::any CactParser::VariableDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitVariableDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::VariableDefinitionContext* CactParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, CactParser::RuleVariableDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(CactParser::Identifier);
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::LeftBracket) {
      setState(122);
      match(CactParser::LeftBracket);
      setState(123);
      match(CactParser::IntegerConstant);
      setState(124);
      match(CactParser::RightBracket);
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(132);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::Equal) {
      setState(130);
      match(CactParser::Equal);
      setState(131);
      constantInitializationValue();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

CactParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::FunctionTypeContext* CactParser::FunctionDefinitionContext::functionType() {
  return getRuleContext<CactParser::FunctionTypeContext>(0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::BlockContext* CactParser::FunctionDefinitionContext::block() {
  return getRuleContext<CactParser::BlockContext>(0);
}

CactParser::FunctionFormalParametersContext* CactParser::FunctionDefinitionContext::functionFormalParameters() {
  return getRuleContext<CactParser::FunctionFormalParametersContext>(0);
}


size_t CactParser::FunctionDefinitionContext::getRuleIndex() const {
  return CactParser::RuleFunctionDefinition;
}


std::any CactParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionDefinitionContext* CactParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 16, CactParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    functionType();
    setState(135);
    match(CactParser::Identifier);
    setState(136);
    match(CactParser::LeftParenthesis);
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28) != 0)) {
      setState(137);
      functionFormalParameters();
    }
    setState(140);
    match(CactParser::RightParenthesis);
    setState(141);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

CactParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::FunctionTypeContext::Void() {
  return getToken(CactParser::Void, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Int() {
  return getToken(CactParser::Int, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Float() {
  return getToken(CactParser::Float, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Char() {
  return getToken(CactParser::Char, 0);
}


size_t CactParser::FunctionTypeContext::getRuleIndex() const {
  return CactParser::RuleFunctionType;
}


std::any CactParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionTypeContext* CactParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, CactParser::RuleFunctionType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 60) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFormalParametersContext ------------------------------------------------------------------

CactParser::FunctionFormalParametersContext::FunctionFormalParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::FunctionFormalParameterContext *> CactParser::FunctionFormalParametersContext::functionFormalParameter() {
  return getRuleContexts<CactParser::FunctionFormalParameterContext>();
}

CactParser::FunctionFormalParameterContext* CactParser::FunctionFormalParametersContext::functionFormalParameter(size_t i) {
  return getRuleContext<CactParser::FunctionFormalParameterContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParametersContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::FunctionFormalParametersContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::FunctionFormalParametersContext::getRuleIndex() const {
  return CactParser::RuleFunctionFormalParameters;
}


std::any CactParser::FunctionFormalParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionFormalParameters(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionFormalParametersContext* CactParser::functionFormalParameters() {
  FunctionFormalParametersContext *_localctx = _tracker.createInstance<FunctionFormalParametersContext>(_ctx, getState());
  enterRule(_localctx, 20, CactParser::RuleFunctionFormalParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    functionFormalParameter();
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(146);
      match(CactParser::Comma);
      setState(147);
      functionFormalParameter();
      setState(152);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFormalParameterContext ------------------------------------------------------------------

CactParser::FunctionFormalParameterContext::FunctionFormalParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::BasicTypeContext* CactParser::FunctionFormalParameterContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

tree::TerminalNode* CactParser::FunctionFormalParameterContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParameterContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::FunctionFormalParameterContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParameterContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::FunctionFormalParameterContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParameterContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::FunctionFormalParameterContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}


size_t CactParser::FunctionFormalParameterContext::getRuleIndex() const {
  return CactParser::RuleFunctionFormalParameter;
}


std::any CactParser::FunctionFormalParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionFormalParameter(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionFormalParameterContext* CactParser::functionFormalParameter() {
  FunctionFormalParameterContext *_localctx = _tracker.createInstance<FunctionFormalParameterContext>(_ctx, getState());
  enterRule(_localctx, 22, CactParser::RuleFunctionFormalParameter);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    basicType();
    setState(154);
    match(CactParser::Identifier);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::LeftBracket) {
      setState(155);
      match(CactParser::LeftBracket);
      setState(157);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CactParser::IntegerConstant) {
        setState(156);
        match(CactParser::IntegerConstant);
      }
      setState(159);
      match(CactParser::RightBracket);
      setState(165);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CactParser::LeftBracket) {
        setState(160);
        match(CactParser::LeftBracket);
        setState(161);
        match(CactParser::IntegerConstant);
        setState(162);
        match(CactParser::RightBracket);
        setState(167);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CactParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BlockContext::LeftBrace() {
  return getToken(CactParser::LeftBrace, 0);
}

tree::TerminalNode* CactParser::BlockContext::RightBrace() {
  return getToken(CactParser::RightBrace, 0);
}

std::vector<CactParser::BlockItemContext *> CactParser::BlockContext::blockItem() {
  return getRuleContexts<CactParser::BlockItemContext>();
}

CactParser::BlockItemContext* CactParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<CactParser::BlockItemContext>(i);
}


size_t CactParser::BlockContext::getRuleIndex() const {
  return CactParser::RuleBlock;
}


std::any CactParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BlockContext* CactParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 24, CactParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(CactParser::LeftBrace);
    setState(174);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 533652918110) != 0)) {
      setState(171);
      blockItem();
      setState(176);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(177);
    match(CactParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

CactParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::DeclarationContext* CactParser::BlockItemContext::declaration() {
  return getRuleContext<CactParser::DeclarationContext>(0);
}

CactParser::StatementContext* CactParser::BlockItemContext::statement() {
  return getRuleContext<CactParser::StatementContext>(0);
}


size_t CactParser::BlockItemContext::getRuleIndex() const {
  return CactParser::RuleBlockItem;
}


std::any CactParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BlockItemContext* CactParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 26, CactParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(181);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Const:
      case CactParser::Int:
      case CactParser::Float:
      case CactParser::Char: {
        enterOuterAlt(_localctx, 1);
        setState(179);
        declaration();
        break;
      }

      case CactParser::If:
      case CactParser::While:
      case CactParser::Break:
      case CactParser::Continue:
      case CactParser::Return:
      case CactParser::LeftParenthesis:
      case CactParser::ExclamationMark:
      case CactParser::Minus:
      case CactParser::Plus:
      case CactParser::LeftBrace:
      case CactParser::Semicolon:
      case CactParser::Identifier:
      case CactParser::IntegerConstant:
      case CactParser::CharacterConstant:
      case CactParser::FloatConstant: {
        enterOuterAlt(_localctx, 2);
        setState(180);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CactParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LeftValueContext* CactParser::StatementContext::leftValue() {
  return getRuleContext<CactParser::LeftValueContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ExpressionContext* CactParser::StatementContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

CactParser::BlockContext* CactParser::StatementContext::block() {
  return getRuleContext<CactParser::BlockContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Return() {
  return getToken(CactParser::Return, 0);
}

tree::TerminalNode* CactParser::StatementContext::If() {
  return getToken(CactParser::If, 0);
}

tree::TerminalNode* CactParser::StatementContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ConditionContext* CactParser::StatementContext::condition() {
  return getRuleContext<CactParser::ConditionContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

std::vector<CactParser::StatementContext *> CactParser::StatementContext::statement() {
  return getRuleContexts<CactParser::StatementContext>();
}

CactParser::StatementContext* CactParser::StatementContext::statement(size_t i) {
  return getRuleContext<CactParser::StatementContext>(i);
}

tree::TerminalNode* CactParser::StatementContext::Else() {
  return getToken(CactParser::Else, 0);
}

tree::TerminalNode* CactParser::StatementContext::While() {
  return getToken(CactParser::While, 0);
}

tree::TerminalNode* CactParser::StatementContext::Break() {
  return getToken(CactParser::Break, 0);
}

tree::TerminalNode* CactParser::StatementContext::Continue() {
  return getToken(CactParser::Continue, 0);
}


size_t CactParser::StatementContext::getRuleIndex() const {
  return CactParser::RuleStatement;
}


std::any CactParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::StatementContext* CactParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 28, CactParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(183);
      leftValue();
      setState(184);
      match(CactParser::Equal);
      setState(185);
      expression();
      setState(186);
      match(CactParser::Semicolon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(189);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515399303168) != 0)) {
        setState(188);
        expression();
      }
      setState(191);
      match(CactParser::Semicolon);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(192);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(193);
      match(CactParser::Return);
      setState(195);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515399303168) != 0)) {
        setState(194);
        expression();
      }
      setState(197);
      match(CactParser::Semicolon);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(198);
      match(CactParser::If);
      setState(199);
      match(CactParser::LeftParenthesis);
      setState(200);
      condition();
      setState(201);
      match(CactParser::RightParenthesis);
      setState(202);
      statement();
      setState(205);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(203);
        match(CactParser::Else);
        setState(204);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(207);
      match(CactParser::While);
      setState(208);
      match(CactParser::LeftParenthesis);
      setState(209);
      condition();
      setState(210);
      match(CactParser::RightParenthesis);
      setState(211);
      statement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(213);
      match(CactParser::Break);
      setState(214);
      match(CactParser::Semicolon);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(215);
      match(CactParser::Continue);
      setState(216);
      match(CactParser::Semicolon);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CactParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AddExpressionContext* CactParser::ExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}


size_t CactParser::ExpressionContext::getRuleIndex() const {
  return CactParser::RuleExpression;
}


std::any CactParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ExpressionContext* CactParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, CactParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    addExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

CactParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AddExpressionContext* CactParser::ConstantExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}


size_t CactParser::ConstantExpressionContext::getRuleIndex() const {
  return CactParser::RuleConstantExpression;
}


std::any CactParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantExpressionContext* CactParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, CactParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    addExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

CactParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LogicalOrExpressionContext* CactParser::ConditionContext::logicalOrExpression() {
  return getRuleContext<CactParser::LogicalOrExpressionContext>(0);
}


size_t CactParser::ConditionContext::getRuleIndex() const {
  return CactParser::RuleCondition;
}


std::any CactParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConditionContext* CactParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 34, CactParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    logicalOrExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftValueContext ------------------------------------------------------------------

CactParser::LeftValueContext::LeftValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::LeftValueContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::LeftValueContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::LeftValueContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<CactParser::ExpressionContext *> CactParser::LeftValueContext::expression() {
  return getRuleContexts<CactParser::ExpressionContext>();
}

CactParser::ExpressionContext* CactParser::LeftValueContext::expression(size_t i) {
  return getRuleContext<CactParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::LeftValueContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::LeftValueContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}


size_t CactParser::LeftValueContext::getRuleIndex() const {
  return CactParser::RuleLeftValue;
}


std::any CactParser::LeftValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLeftValue(this);
  else
    return visitor->visitChildren(this);
}

CactParser::LeftValueContext* CactParser::leftValue() {
  LeftValueContext *_localctx = _tracker.createInstance<LeftValueContext>(_ctx, getState());
  enterRule(_localctx, 36, CactParser::RuleLeftValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(CactParser::Identifier);
    setState(232);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(226);
        match(CactParser::LeftBracket);
        setState(227);
        expression();
        setState(228);
        match(CactParser::RightBracket); 
      }
      setState(234);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

CactParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::NumberContext::IntegerConstant() {
  return getToken(CactParser::IntegerConstant, 0);
}

tree::TerminalNode* CactParser::NumberContext::CharacterConstant() {
  return getToken(CactParser::CharacterConstant, 0);
}

tree::TerminalNode* CactParser::NumberContext::FloatConstant() {
  return getToken(CactParser::FloatConstant, 0);
}


size_t CactParser::NumberContext::getRuleIndex() const {
  return CactParser::RuleNumber;
}


std::any CactParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

CactParser::NumberContext* CactParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 38, CactParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 481036337152) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionRealParametersContext ------------------------------------------------------------------

CactParser::FunctionRealParametersContext::FunctionRealParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::ExpressionContext *> CactParser::FunctionRealParametersContext::expression() {
  return getRuleContexts<CactParser::ExpressionContext>();
}

CactParser::ExpressionContext* CactParser::FunctionRealParametersContext::expression(size_t i) {
  return getRuleContext<CactParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionRealParametersContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::FunctionRealParametersContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::FunctionRealParametersContext::getRuleIndex() const {
  return CactParser::RuleFunctionRealParameters;
}


std::any CactParser::FunctionRealParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionRealParameters(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionRealParametersContext* CactParser::functionRealParameters() {
  FunctionRealParametersContext *_localctx = _tracker.createInstance<FunctionRealParametersContext>(_ctx, getState());
  enterRule(_localctx, 40, CactParser::RuleFunctionRealParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    expression();
    setState(242);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(238);
      match(CactParser::Comma);
      setState(239);
      expression();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

CactParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::PrimaryExpressionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ExpressionContext* CactParser::PrimaryExpressionContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}

tree::TerminalNode* CactParser::PrimaryExpressionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::LeftValueContext* CactParser::PrimaryExpressionContext::leftValue() {
  return getRuleContext<CactParser::LeftValueContext>(0);
}

CactParser::NumberContext* CactParser::PrimaryExpressionContext::number() {
  return getRuleContext<CactParser::NumberContext>(0);
}


size_t CactParser::PrimaryExpressionContext::getRuleIndex() const {
  return CactParser::RulePrimaryExpression;
}


std::any CactParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::PrimaryExpressionContext* CactParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, CactParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::LeftParenthesis: {
        enterOuterAlt(_localctx, 1);
        setState(245);
        match(CactParser::LeftParenthesis);
        setState(246);
        expression();
        setState(247);
        match(CactParser::RightParenthesis);
        break;
      }

      case CactParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(249);
        leftValue();
        break;
      }

      case CactParser::IntegerConstant:
      case CactParser::CharacterConstant:
      case CactParser::FloatConstant: {
        enterOuterAlt(_localctx, 3);
        setState(250);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

CactParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::PrimaryExpressionContext* CactParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<CactParser::PrimaryExpressionContext>(0);
}

CactParser::UnaryExpressionContext* CactParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<CactParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Plus() {
  return getToken(CactParser::Plus, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Minus() {
  return getToken(CactParser::Minus, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::ExclamationMark() {
  return getToken(CactParser::ExclamationMark, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::FunctionRealParametersContext* CactParser::UnaryExpressionContext::functionRealParameters() {
  return getRuleContext<CactParser::FunctionRealParametersContext>(0);
}


size_t CactParser::UnaryExpressionContext::getRuleIndex() const {
  return CactParser::RuleUnaryExpression;
}


std::any CactParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::UnaryExpressionContext* CactParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, CactParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(253);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(254);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3211264) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(255);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(256);
      match(CactParser::Identifier);
      setState(257);
      match(CactParser::LeftParenthesis);
      setState(259);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 515399303168) != 0)) {
        setState(258);
        functionRealParameters();
      }
      setState(261);
      match(CactParser::RightParenthesis);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

CactParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::UnaryExpressionContext* CactParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContext<CactParser::UnaryExpressionContext>(0);
}

CactParser::MultiplicativeExpressionContext* CactParser::MultiplicativeExpressionContext::multiplicativeExpression() {
  return getRuleContext<CactParser::MultiplicativeExpressionContext>(0);
}

tree::TerminalNode* CactParser::MultiplicativeExpressionContext::Asterisk() {
  return getToken(CactParser::Asterisk, 0);
}

tree::TerminalNode* CactParser::MultiplicativeExpressionContext::Slash() {
  return getToken(CactParser::Slash, 0);
}

tree::TerminalNode* CactParser::MultiplicativeExpressionContext::Percent() {
  return getToken(CactParser::Percent, 0);
}


size_t CactParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return CactParser::RuleMultiplicativeExpression;
}


std::any CactParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::MultiplicativeExpressionContext* CactParser::multiplicativeExpression() {
   return multiplicativeExpression(0);
}

CactParser::MultiplicativeExpressionContext* CactParser::multiplicativeExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, parentState);
  CactParser::MultiplicativeExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CactParser::RuleMultiplicativeExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(265);
    unaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(272);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MultiplicativeExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMultiplicativeExpression);
        setState(267);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(268);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 917504) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(269);
        unaryExpression(); 
      }
      setState(274);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddExpressionContext ------------------------------------------------------------------

CactParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::MultiplicativeExpressionContext* CactParser::AddExpressionContext::multiplicativeExpression() {
  return getRuleContext<CactParser::MultiplicativeExpressionContext>(0);
}

CactParser::AddExpressionContext* CactParser::AddExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}

tree::TerminalNode* CactParser::AddExpressionContext::Plus() {
  return getToken(CactParser::Plus, 0);
}

tree::TerminalNode* CactParser::AddExpressionContext::Minus() {
  return getToken(CactParser::Minus, 0);
}


size_t CactParser::AddExpressionContext::getRuleIndex() const {
  return CactParser::RuleAddExpression;
}


std::any CactParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitAddExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::AddExpressionContext* CactParser::addExpression() {
   return addExpression(0);
}

CactParser::AddExpressionContext* CactParser::addExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, parentState);
  CactParser::AddExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CactParser::RuleAddExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(276);
    multiplicativeExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(283);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExpression);
        setState(278);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(279);
        _la = _input->LA(1);
        if (!(_la == CactParser::Minus

        || _la == CactParser::Plus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(280);
        multiplicativeExpression(0); 
      }
      setState(285);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

CactParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AddExpressionContext* CactParser::RelationalExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}

CactParser::RelationalExpressionContext* CactParser::RelationalExpressionContext::relationalExpression() {
  return getRuleContext<CactParser::RelationalExpressionContext>(0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::Less() {
  return getToken(CactParser::Less, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::Greater() {
  return getToken(CactParser::Greater, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::LessEqual() {
  return getToken(CactParser::LessEqual, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::GreaterEqual() {
  return getToken(CactParser::GreaterEqual, 0);
}


size_t CactParser::RelationalExpressionContext::getRuleIndex() const {
  return CactParser::RuleRelationalExpression;
}


std::any CactParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::RelationalExpressionContext* CactParser::relationalExpression() {
   return relationalExpression(0);
}

CactParser::RelationalExpressionContext* CactParser::relationalExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, parentState);
  CactParser::RelationalExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CactParser::RuleRelationalExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(287);
    addExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(294);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
        setState(289);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(290);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 62914560) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(291);
        addExpression(0); 
      }
      setState(296);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

CactParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::RelationalExpressionContext* CactParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContext<CactParser::RelationalExpressionContext>(0);
}

CactParser::EqualityExpressionContext* CactParser::EqualityExpressionContext::equalityExpression() {
  return getRuleContext<CactParser::EqualityExpressionContext>(0);
}

tree::TerminalNode* CactParser::EqualityExpressionContext::LogicalEqual() {
  return getToken(CactParser::LogicalEqual, 0);
}

tree::TerminalNode* CactParser::EqualityExpressionContext::NotEqual() {
  return getToken(CactParser::NotEqual, 0);
}


size_t CactParser::EqualityExpressionContext::getRuleIndex() const {
  return CactParser::RuleEqualityExpression;
}


std::any CactParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::EqualityExpressionContext* CactParser::equalityExpression() {
   return equalityExpression(0);
}

CactParser::EqualityExpressionContext* CactParser::equalityExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, parentState);
  CactParser::EqualityExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CactParser::RuleEqualityExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(298);
    relationalExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(305);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqualityExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqualityExpression);
        setState(300);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(301);
        _la = _input->LA(1);
        if (!(_la == CactParser::LogicalEqual

        || _la == CactParser::NotEqual)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(302);
        relationalExpression(0); 
      }
      setState(307);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

CactParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::EqualityExpressionContext* CactParser::LogicalAndExpressionContext::equalityExpression() {
  return getRuleContext<CactParser::EqualityExpressionContext>(0);
}

CactParser::LogicalAndExpressionContext* CactParser::LogicalAndExpressionContext::logicalAndExpression() {
  return getRuleContext<CactParser::LogicalAndExpressionContext>(0);
}

tree::TerminalNode* CactParser::LogicalAndExpressionContext::LogicalAnd() {
  return getToken(CactParser::LogicalAnd, 0);
}


size_t CactParser::LogicalAndExpressionContext::getRuleIndex() const {
  return CactParser::RuleLogicalAndExpression;
}


std::any CactParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::LogicalAndExpressionContext* CactParser::logicalAndExpression() {
   return logicalAndExpression(0);
}

CactParser::LogicalAndExpressionContext* CactParser::logicalAndExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, parentState);
  CactParser::LogicalAndExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CactParser::RuleLogicalAndExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(309);
    equalityExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(316);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalAndExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalAndExpression);
        setState(311);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(312);
        match(CactParser::LogicalAnd);
        setState(313);
        equalityExpression(0); 
      }
      setState(318);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

CactParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LogicalAndExpressionContext* CactParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContext<CactParser::LogicalAndExpressionContext>(0);
}

CactParser::LogicalOrExpressionContext* CactParser::LogicalOrExpressionContext::logicalOrExpression() {
  return getRuleContext<CactParser::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* CactParser::LogicalOrExpressionContext::LogicalOr() {
  return getToken(CactParser::LogicalOr, 0);
}


size_t CactParser::LogicalOrExpressionContext::getRuleIndex() const {
  return CactParser::RuleLogicalOrExpression;
}


std::any CactParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::LogicalOrExpressionContext* CactParser::logicalOrExpression() {
   return logicalOrExpression(0);
}

CactParser::LogicalOrExpressionContext* CactParser::logicalOrExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, parentState);
  CactParser::LogicalOrExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CactParser::RuleLogicalOrExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(320);
    logicalAndExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(327);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalOrExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalOrExpression);
        setState(322);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(323);
        match(CactParser::LogicalOr);
        setState(324);
        logicalAndExpression(0); 
      }
      setState(329);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CactParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 23: return multiplicativeExpressionSempred(antlrcpp::downCast<MultiplicativeExpressionContext *>(context), predicateIndex);
    case 24: return addExpressionSempred(antlrcpp::downCast<AddExpressionContext *>(context), predicateIndex);
    case 25: return relationalExpressionSempred(antlrcpp::downCast<RelationalExpressionContext *>(context), predicateIndex);
    case 26: return equalityExpressionSempred(antlrcpp::downCast<EqualityExpressionContext *>(context), predicateIndex);
    case 27: return logicalAndExpressionSempred(antlrcpp::downCast<LogicalAndExpressionContext *>(context), predicateIndex);
    case 28: return logicalOrExpressionSempred(antlrcpp::downCast<LogicalOrExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CactParser::multiplicativeExpressionSempred(MultiplicativeExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::addExpressionSempred(AddExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::equalityExpressionSempred(EqualityExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::logicalAndExpressionSempred(LogicalAndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::logicalOrExpressionSempred(LogicalOrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CactParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cactparserParserInitialize();
#else
  ::antlr4::internal::call_once(cactparserParserOnceFlag, cactparserParserInitialize);
#endif
}
