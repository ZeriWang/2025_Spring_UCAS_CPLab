// Generated from /Users/zhangjiawei/Desktop/2025_Spring_UCAS_CPLab/cact/grammar/CactParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class CactParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		Const=1, Int=2, Float=3, Char=4, Void=5, If=6, Else=7, While=8, Break=9, 
		Continue=10, Return=11, LeftBracket=12, RightBracket=13, LeftParenthesis=14, 
		RightParenthesis=15, ExclamationMark=16, Asterisk=17, Slash=18, Percent=19, 
		Minus=20, Plus=21, Less=22, LessEqual=23, Greater=24, GreaterEqual=25, 
		LogicalEqual=26, NotEqual=27, LogicalAnd=28, LogicalOr=29, LeftBrace=30, 
		RightBrace=31, Equal=32, Comma=33, Semicolon=34, Identifier=35, IntegerConstant=36, 
		CharacterConstant=37, FloatConstant=38, LineComment=39, BlockComment=40, 
		NewLine=41, WhiteSpaces=42;
	public static final int
		RULE_compilationUnit = 0, RULE_declaration = 1, RULE_constantDeclaration = 2, 
		RULE_basicType = 3, RULE_constantDefinition = 4, RULE_constantInitializationValue = 5, 
		RULE_variableDeclaration = 6, RULE_variableDefinition = 7, RULE_functionDefinition = 8, 
		RULE_functionType = 9, RULE_functionFormalParameters = 10, RULE_functionFormalParameter = 11, 
		RULE_block = 12, RULE_blockItem = 13, RULE_statement = 14, RULE_expression = 15, 
		RULE_constantExpression = 16, RULE_condition = 17, RULE_leftValue = 18, 
		RULE_number = 19, RULE_functionRealParameters = 20, RULE_primaryExpression = 21, 
		RULE_unaryExpression = 22, RULE_multiplicativeExpression = 23, RULE_addExpression = 24, 
		RULE_relationalExpression = 25, RULE_equalityExpression = 26, RULE_logicalAndExpression = 27, 
		RULE_logicalOrExpression = 28;
	private static String[] makeRuleNames() {
		return new String[] {
			"compilationUnit", "declaration", "constantDeclaration", "basicType", 
			"constantDefinition", "constantInitializationValue", "variableDeclaration", 
			"variableDefinition", "functionDefinition", "functionType", "functionFormalParameters", 
			"functionFormalParameter", "block", "blockItem", "statement", "expression", 
			"constantExpression", "condition", "leftValue", "number", "functionRealParameters", 
			"primaryExpression", "unaryExpression", "multiplicativeExpression", "addExpression", 
			"relationalExpression", "equalityExpression", "logicalAndExpression", 
			"logicalOrExpression"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'const'", "'int'", "'float'", "'char'", "'void'", "'if'", "'else'", 
			"'while'", "'break'", "'continue'", "'return'", "'['", "']'", "'('", 
			"')'", "'!'", "'*'", "'/'", "'%'", "'-'", "'+'", "'<'", "'<='", "'>'", 
			"'>='", "'=='", "'!='", "'&&'", "'||'", "'{'", "'}'", "'='", "','", "';'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "Const", "Int", "Float", "Char", "Void", "If", "Else", "While", 
			"Break", "Continue", "Return", "LeftBracket", "RightBracket", "LeftParenthesis", 
			"RightParenthesis", "ExclamationMark", "Asterisk", "Slash", "Percent", 
			"Minus", "Plus", "Less", "LessEqual", "Greater", "GreaterEqual", "LogicalEqual", 
			"NotEqual", "LogicalAnd", "LogicalOr", "LeftBrace", "RightBrace", "Equal", 
			"Comma", "Semicolon", "Identifier", "IntegerConstant", "CharacterConstant", 
			"FloatConstant", "LineComment", "BlockComment", "NewLine", "WhiteSpaces"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "CactParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CactParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CompilationUnitContext extends ParserRuleContext {
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public List<FunctionDefinitionContext> functionDefinition() {
			return getRuleContexts(FunctionDefinitionContext.class);
		}
		public FunctionDefinitionContext functionDefinition(int i) {
			return getRuleContext(FunctionDefinitionContext.class,i);
		}
		public CompilationUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compilationUnit; }
	}

	public final CompilationUnitContext compilationUnit() throws RecognitionException {
		CompilationUnitContext _localctx = new CompilationUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_compilationUnit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(62);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 62L) != 0)) {
				{
				setState(60);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
				case 1:
					{
					setState(58);
					declaration();
					}
					break;
				case 2:
					{
					setState(59);
					functionDefinition();
					}
					break;
				}
				}
				setState(64);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeclarationContext extends ParserRuleContext {
		public ConstantDeclarationContext constantDeclaration() {
			return getRuleContext(ConstantDeclarationContext.class,0);
		}
		public VariableDeclarationContext variableDeclaration() {
			return getRuleContext(VariableDeclarationContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_declaration);
		try {
			setState(67);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Const:
				enterOuterAlt(_localctx, 1);
				{
				setState(65);
				constantDeclaration();
				}
				break;
			case Int:
			case Float:
			case Char:
				enterOuterAlt(_localctx, 2);
				{
				setState(66);
				variableDeclaration();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConstantDeclarationContext extends ParserRuleContext {
		public TerminalNode Const() { return getToken(CactParser.Const, 0); }
		public BasicTypeContext basicType() {
			return getRuleContext(BasicTypeContext.class,0);
		}
		public List<ConstantDefinitionContext> constantDefinition() {
			return getRuleContexts(ConstantDefinitionContext.class);
		}
		public ConstantDefinitionContext constantDefinition(int i) {
			return getRuleContext(ConstantDefinitionContext.class,i);
		}
		public TerminalNode Semicolon() { return getToken(CactParser.Semicolon, 0); }
		public List<TerminalNode> Comma() { return getTokens(CactParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(CactParser.Comma, i);
		}
		public ConstantDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constantDeclaration; }
	}

	public final ConstantDeclarationContext constantDeclaration() throws RecognitionException {
		ConstantDeclarationContext _localctx = new ConstantDeclarationContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_constantDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(69);
			match(Const);
			setState(70);
			basicType();
			setState(71);
			constantDefinition();
			setState(76);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(72);
				match(Comma);
				setState(73);
				constantDefinition();
				}
				}
				setState(78);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(79);
			match(Semicolon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BasicTypeContext extends ParserRuleContext {
		public TerminalNode Int() { return getToken(CactParser.Int, 0); }
		public TerminalNode Float() { return getToken(CactParser.Float, 0); }
		public TerminalNode Char() { return getToken(CactParser.Char, 0); }
		public BasicTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_basicType; }
	}

	public final BasicTypeContext basicType() throws RecognitionException {
		BasicTypeContext _localctx = new BasicTypeContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_basicType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(81);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 28L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConstantDefinitionContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public TerminalNode Equal() { return getToken(CactParser.Equal, 0); }
		public ConstantInitializationValueContext constantInitializationValue() {
			return getRuleContext(ConstantInitializationValueContext.class,0);
		}
		public List<TerminalNode> LeftBracket() { return getTokens(CactParser.LeftBracket); }
		public TerminalNode LeftBracket(int i) {
			return getToken(CactParser.LeftBracket, i);
		}
		public List<TerminalNode> IntegerConstant() { return getTokens(CactParser.IntegerConstant); }
		public TerminalNode IntegerConstant(int i) {
			return getToken(CactParser.IntegerConstant, i);
		}
		public List<TerminalNode> RightBracket() { return getTokens(CactParser.RightBracket); }
		public TerminalNode RightBracket(int i) {
			return getToken(CactParser.RightBracket, i);
		}
		public ConstantDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constantDefinition; }
	}

	public final ConstantDefinitionContext constantDefinition() throws RecognitionException {
		ConstantDefinitionContext _localctx = new ConstantDefinitionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_constantDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(83);
			match(Identifier);
			setState(89);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LeftBracket) {
				{
				{
				setState(84);
				match(LeftBracket);
				setState(85);
				match(IntegerConstant);
				setState(86);
				match(RightBracket);
				}
				}
				setState(91);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(92);
			match(Equal);
			setState(93);
			constantInitializationValue();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConstantInitializationValueContext extends ParserRuleContext {
		public ConstantExpressionContext constantExpression() {
			return getRuleContext(ConstantExpressionContext.class,0);
		}
		public TerminalNode LeftBrace() { return getToken(CactParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(CactParser.RightBrace, 0); }
		public List<ConstantInitializationValueContext> constantInitializationValue() {
			return getRuleContexts(ConstantInitializationValueContext.class);
		}
		public ConstantInitializationValueContext constantInitializationValue(int i) {
			return getRuleContext(ConstantInitializationValueContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(CactParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(CactParser.Comma, i);
		}
		public ConstantInitializationValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constantInitializationValue; }
	}

	public final ConstantInitializationValueContext constantInitializationValue() throws RecognitionException {
		ConstantInitializationValueContext _localctx = new ConstantInitializationValueContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_constantInitializationValue);
		int _la;
		try {
			setState(108);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LeftParenthesis:
			case ExclamationMark:
			case Minus:
			case Plus:
			case Identifier:
			case IntegerConstant:
			case CharacterConstant:
			case FloatConstant:
				enterOuterAlt(_localctx, 1);
				{
				setState(95);
				constantExpression();
				}
				break;
			case LeftBrace:
				enterOuterAlt(_localctx, 2);
				{
				setState(96);
				match(LeftBrace);
				setState(105);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 516473044992L) != 0)) {
					{
					setState(97);
					constantInitializationValue();
					setState(102);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==Comma) {
						{
						{
						setState(98);
						match(Comma);
						setState(99);
						constantInitializationValue();
						}
						}
						setState(104);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(107);
				match(RightBrace);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VariableDeclarationContext extends ParserRuleContext {
		public BasicTypeContext basicType() {
			return getRuleContext(BasicTypeContext.class,0);
		}
		public List<VariableDefinitionContext> variableDefinition() {
			return getRuleContexts(VariableDefinitionContext.class);
		}
		public VariableDefinitionContext variableDefinition(int i) {
			return getRuleContext(VariableDefinitionContext.class,i);
		}
		public TerminalNode Semicolon() { return getToken(CactParser.Semicolon, 0); }
		public List<TerminalNode> Comma() { return getTokens(CactParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(CactParser.Comma, i);
		}
		public VariableDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclaration; }
	}

	public final VariableDeclarationContext variableDeclaration() throws RecognitionException {
		VariableDeclarationContext _localctx = new VariableDeclarationContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_variableDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(110);
			basicType();
			setState(111);
			variableDefinition();
			setState(116);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(112);
				match(Comma);
				setState(113);
				variableDefinition();
				}
				}
				setState(118);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(119);
			match(Semicolon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VariableDefinitionContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public List<TerminalNode> LeftBracket() { return getTokens(CactParser.LeftBracket); }
		public TerminalNode LeftBracket(int i) {
			return getToken(CactParser.LeftBracket, i);
		}
		public List<TerminalNode> IntegerConstant() { return getTokens(CactParser.IntegerConstant); }
		public TerminalNode IntegerConstant(int i) {
			return getToken(CactParser.IntegerConstant, i);
		}
		public List<TerminalNode> RightBracket() { return getTokens(CactParser.RightBracket); }
		public TerminalNode RightBracket(int i) {
			return getToken(CactParser.RightBracket, i);
		}
		public TerminalNode Equal() { return getToken(CactParser.Equal, 0); }
		public ConstantInitializationValueContext constantInitializationValue() {
			return getRuleContext(ConstantInitializationValueContext.class,0);
		}
		public VariableDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDefinition; }
	}

	public final VariableDefinitionContext variableDefinition() throws RecognitionException {
		VariableDefinitionContext _localctx = new VariableDefinitionContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_variableDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(Identifier);
			setState(127);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LeftBracket) {
				{
				{
				setState(122);
				match(LeftBracket);
				setState(123);
				match(IntegerConstant);
				setState(124);
				match(RightBracket);
				}
				}
				setState(129);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(132);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Equal) {
				{
				setState(130);
				match(Equal);
				setState(131);
				constantInitializationValue();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionDefinitionContext extends ParserRuleContext {
		public FunctionTypeContext functionType() {
			return getRuleContext(FunctionTypeContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public TerminalNode LeftParenthesis() { return getToken(CactParser.LeftParenthesis, 0); }
		public TerminalNode RightParenthesis() { return getToken(CactParser.RightParenthesis, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FunctionFormalParametersContext functionFormalParameters() {
			return getRuleContext(FunctionFormalParametersContext.class,0);
		}
		public FunctionDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDefinition; }
	}

	public final FunctionDefinitionContext functionDefinition() throws RecognitionException {
		FunctionDefinitionContext _localctx = new FunctionDefinitionContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_functionDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(134);
			functionType();
			setState(135);
			match(Identifier);
			setState(136);
			match(LeftParenthesis);
			setState(138);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 28L) != 0)) {
				{
				setState(137);
				functionFormalParameters();
				}
			}

			setState(140);
			match(RightParenthesis);
			setState(141);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionTypeContext extends ParserRuleContext {
		public TerminalNode Void() { return getToken(CactParser.Void, 0); }
		public TerminalNode Int() { return getToken(CactParser.Int, 0); }
		public TerminalNode Float() { return getToken(CactParser.Float, 0); }
		public TerminalNode Char() { return getToken(CactParser.Char, 0); }
		public FunctionTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionType; }
	}

	public final FunctionTypeContext functionType() throws RecognitionException {
		FunctionTypeContext _localctx = new FunctionTypeContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_functionType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(143);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 60L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionFormalParametersContext extends ParserRuleContext {
		public List<FunctionFormalParameterContext> functionFormalParameter() {
			return getRuleContexts(FunctionFormalParameterContext.class);
		}
		public FunctionFormalParameterContext functionFormalParameter(int i) {
			return getRuleContext(FunctionFormalParameterContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(CactParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(CactParser.Comma, i);
		}
		public FunctionFormalParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionFormalParameters; }
	}

	public final FunctionFormalParametersContext functionFormalParameters() throws RecognitionException {
		FunctionFormalParametersContext _localctx = new FunctionFormalParametersContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_functionFormalParameters);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145);
			functionFormalParameter();
			setState(150);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(146);
				match(Comma);
				setState(147);
				functionFormalParameter();
				}
				}
				setState(152);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionFormalParameterContext extends ParserRuleContext {
		public BasicTypeContext basicType() {
			return getRuleContext(BasicTypeContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public List<TerminalNode> LeftBracket() { return getTokens(CactParser.LeftBracket); }
		public TerminalNode LeftBracket(int i) {
			return getToken(CactParser.LeftBracket, i);
		}
		public List<TerminalNode> RightBracket() { return getTokens(CactParser.RightBracket); }
		public TerminalNode RightBracket(int i) {
			return getToken(CactParser.RightBracket, i);
		}
		public List<TerminalNode> IntegerConstant() { return getTokens(CactParser.IntegerConstant); }
		public TerminalNode IntegerConstant(int i) {
			return getToken(CactParser.IntegerConstant, i);
		}
		public FunctionFormalParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionFormalParameter; }
	}

	public final FunctionFormalParameterContext functionFormalParameter() throws RecognitionException {
		FunctionFormalParameterContext _localctx = new FunctionFormalParameterContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_functionFormalParameter);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(153);
			basicType();
			setState(154);
			match(Identifier);
			setState(168);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LeftBracket) {
				{
				setState(155);
				match(LeftBracket);
				setState(157);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==IntegerConstant) {
					{
					setState(156);
					match(IntegerConstant);
					}
				}

				setState(159);
				match(RightBracket);
				setState(165);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==LeftBracket) {
					{
					{
					setState(160);
					match(LeftBracket);
					setState(161);
					match(IntegerConstant);
					setState(162);
					match(RightBracket);
					}
					}
					setState(167);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockContext extends ParserRuleContext {
		public TerminalNode LeftBrace() { return getToken(CactParser.LeftBrace, 0); }
		public TerminalNode RightBrace() { return getToken(CactParser.RightBrace, 0); }
		public List<BlockItemContext> blockItem() {
			return getRuleContexts(BlockItemContext.class);
		}
		public BlockItemContext blockItem(int i) {
			return getRuleContext(BlockItemContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(170);
			match(LeftBrace);
			setState(174);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 533652918110L) != 0)) {
				{
				{
				setState(171);
				blockItem();
				}
				}
				setState(176);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(177);
			match(RightBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockItemContext extends ParserRuleContext {
		public DeclarationContext declaration() {
			return getRuleContext(DeclarationContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public BlockItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockItem; }
	}

	public final BlockItemContext blockItem() throws RecognitionException {
		BlockItemContext _localctx = new BlockItemContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_blockItem);
		try {
			setState(181);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Const:
			case Int:
			case Float:
			case Char:
				enterOuterAlt(_localctx, 1);
				{
				setState(179);
				declaration();
				}
				break;
			case If:
			case While:
			case Break:
			case Continue:
			case Return:
			case LeftParenthesis:
			case ExclamationMark:
			case Minus:
			case Plus:
			case LeftBrace:
			case Semicolon:
			case Identifier:
			case IntegerConstant:
			case CharacterConstant:
			case FloatConstant:
				enterOuterAlt(_localctx, 2);
				{
				setState(180);
				statement();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public LeftValueContext leftValue() {
			return getRuleContext(LeftValueContext.class,0);
		}
		public TerminalNode Equal() { return getToken(CactParser.Equal, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode Semicolon() { return getToken(CactParser.Semicolon, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode Return() { return getToken(CactParser.Return, 0); }
		public TerminalNode If() { return getToken(CactParser.If, 0); }
		public TerminalNode LeftParenthesis() { return getToken(CactParser.LeftParenthesis, 0); }
		public ConditionContext condition() {
			return getRuleContext(ConditionContext.class,0);
		}
		public TerminalNode RightParenthesis() { return getToken(CactParser.RightParenthesis, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public TerminalNode Else() { return getToken(CactParser.Else, 0); }
		public TerminalNode While() { return getToken(CactParser.While, 0); }
		public TerminalNode Break() { return getToken(CactParser.Break, 0); }
		public TerminalNode Continue() { return getToken(CactParser.Continue, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_statement);
		int _la;
		try {
			setState(217);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(183);
				leftValue();
				setState(184);
				match(Equal);
				setState(185);
				expression();
				setState(186);
				match(Semicolon);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(189);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 515399303168L) != 0)) {
					{
					setState(188);
					expression();
					}
				}

				setState(191);
				match(Semicolon);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(192);
				block();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(193);
				match(Return);
				setState(195);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 515399303168L) != 0)) {
					{
					setState(194);
					expression();
					}
				}

				setState(197);
				match(Semicolon);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(198);
				match(If);
				setState(199);
				match(LeftParenthesis);
				setState(200);
				condition();
				setState(201);
				match(RightParenthesis);
				setState(202);
				statement();
				setState(205);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
				case 1:
					{
					setState(203);
					match(Else);
					setState(204);
					statement();
					}
					break;
				}
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(207);
				match(While);
				setState(208);
				match(LeftParenthesis);
				setState(209);
				condition();
				setState(210);
				match(RightParenthesis);
				setState(211);
				statement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(213);
				match(Break);
				setState(214);
				match(Semicolon);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(215);
				match(Continue);
				setState(216);
				match(Semicolon);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public AddExpressionContext addExpression() {
			return getRuleContext(AddExpressionContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(219);
			addExpression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConstantExpressionContext extends ParserRuleContext {
		public AddExpressionContext addExpression() {
			return getRuleContext(AddExpressionContext.class,0);
		}
		public ConstantExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constantExpression; }
	}

	public final ConstantExpressionContext constantExpression() throws RecognitionException {
		ConstantExpressionContext _localctx = new ConstantExpressionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_constantExpression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(221);
			addExpression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConditionContext extends ParserRuleContext {
		public LogicalOrExpressionContext logicalOrExpression() {
			return getRuleContext(LogicalOrExpressionContext.class,0);
		}
		public ConditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_condition; }
	}

	public final ConditionContext condition() throws RecognitionException {
		ConditionContext _localctx = new ConditionContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_condition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(223);
			logicalOrExpression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LeftValueContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public List<TerminalNode> LeftBracket() { return getTokens(CactParser.LeftBracket); }
		public TerminalNode LeftBracket(int i) {
			return getToken(CactParser.LeftBracket, i);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> RightBracket() { return getTokens(CactParser.RightBracket); }
		public TerminalNode RightBracket(int i) {
			return getToken(CactParser.RightBracket, i);
		}
		public LeftValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_leftValue; }
	}

	public final LeftValueContext leftValue() throws RecognitionException {
		LeftValueContext _localctx = new LeftValueContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_leftValue);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(225);
			match(Identifier);
			setState(232);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(226);
					match(LeftBracket);
					setState(227);
					expression();
					setState(228);
					match(RightBracket);
					}
					} 
				}
				setState(234);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,22,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NumberContext extends ParserRuleContext {
		public TerminalNode IntegerConstant() { return getToken(CactParser.IntegerConstant, 0); }
		public TerminalNode CharacterConstant() { return getToken(CactParser.CharacterConstant, 0); }
		public TerminalNode FloatConstant() { return getToken(CactParser.FloatConstant, 0); }
		public NumberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number; }
	}

	public final NumberContext number() throws RecognitionException {
		NumberContext _localctx = new NumberContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_number);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(235);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 481036337152L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionRealParametersContext extends ParserRuleContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(CactParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(CactParser.Comma, i);
		}
		public FunctionRealParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionRealParameters; }
	}

	public final FunctionRealParametersContext functionRealParameters() throws RecognitionException {
		FunctionRealParametersContext _localctx = new FunctionRealParametersContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_functionRealParameters);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(237);
			expression();
			setState(242);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(238);
				match(Comma);
				setState(239);
				expression();
				}
				}
				setState(244);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PrimaryExpressionContext extends ParserRuleContext {
		public TerminalNode LeftParenthesis() { return getToken(CactParser.LeftParenthesis, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RightParenthesis() { return getToken(CactParser.RightParenthesis, 0); }
		public LeftValueContext leftValue() {
			return getRuleContext(LeftValueContext.class,0);
		}
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public PrimaryExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primaryExpression; }
	}

	public final PrimaryExpressionContext primaryExpression() throws RecognitionException {
		PrimaryExpressionContext _localctx = new PrimaryExpressionContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_primaryExpression);
		try {
			setState(251);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LeftParenthesis:
				enterOuterAlt(_localctx, 1);
				{
				setState(245);
				match(LeftParenthesis);
				setState(246);
				expression();
				setState(247);
				match(RightParenthesis);
				}
				break;
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(249);
				leftValue();
				}
				break;
			case IntegerConstant:
			case CharacterConstant:
			case FloatConstant:
				enterOuterAlt(_localctx, 3);
				{
				setState(250);
				number();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class UnaryExpressionContext extends ParserRuleContext {
		public PrimaryExpressionContext primaryExpression() {
			return getRuleContext(PrimaryExpressionContext.class,0);
		}
		public UnaryExpressionContext unaryExpression() {
			return getRuleContext(UnaryExpressionContext.class,0);
		}
		public TerminalNode Plus() { return getToken(CactParser.Plus, 0); }
		public TerminalNode Minus() { return getToken(CactParser.Minus, 0); }
		public TerminalNode ExclamationMark() { return getToken(CactParser.ExclamationMark, 0); }
		public TerminalNode Identifier() { return getToken(CactParser.Identifier, 0); }
		public TerminalNode LeftParenthesis() { return getToken(CactParser.LeftParenthesis, 0); }
		public TerminalNode RightParenthesis() { return getToken(CactParser.RightParenthesis, 0); }
		public FunctionRealParametersContext functionRealParameters() {
			return getRuleContext(FunctionRealParametersContext.class,0);
		}
		public UnaryExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unaryExpression; }
	}

	public final UnaryExpressionContext unaryExpression() throws RecognitionException {
		UnaryExpressionContext _localctx = new UnaryExpressionContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_unaryExpression);
		int _la;
		try {
			setState(262);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,26,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(253);
				primaryExpression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(254);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 3211264L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(255);
				unaryExpression();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(256);
				match(Identifier);
				setState(257);
				match(LeftParenthesis);
				setState(259);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 515399303168L) != 0)) {
					{
					setState(258);
					functionRealParameters();
					}
				}

				setState(261);
				match(RightParenthesis);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MultiplicativeExpressionContext extends ParserRuleContext {
		public UnaryExpressionContext unaryExpression() {
			return getRuleContext(UnaryExpressionContext.class,0);
		}
		public MultiplicativeExpressionContext multiplicativeExpression() {
			return getRuleContext(MultiplicativeExpressionContext.class,0);
		}
		public TerminalNode Asterisk() { return getToken(CactParser.Asterisk, 0); }
		public TerminalNode Slash() { return getToken(CactParser.Slash, 0); }
		public TerminalNode Percent() { return getToken(CactParser.Percent, 0); }
		public MultiplicativeExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicativeExpression; }
	}

	public final MultiplicativeExpressionContext multiplicativeExpression() throws RecognitionException {
		return multiplicativeExpression(0);
	}

	private MultiplicativeExpressionContext multiplicativeExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		MultiplicativeExpressionContext _localctx = new MultiplicativeExpressionContext(_ctx, _parentState);
		MultiplicativeExpressionContext _prevctx = _localctx;
		int _startState = 46;
		enterRecursionRule(_localctx, 46, RULE_multiplicativeExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(265);
			unaryExpression();
			}
			_ctx.stop = _input.LT(-1);
			setState(272);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new MultiplicativeExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_multiplicativeExpression);
					setState(267);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(268);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 917504L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(269);
					unaryExpression();
					}
					} 
				}
				setState(274);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AddExpressionContext extends ParserRuleContext {
		public MultiplicativeExpressionContext multiplicativeExpression() {
			return getRuleContext(MultiplicativeExpressionContext.class,0);
		}
		public AddExpressionContext addExpression() {
			return getRuleContext(AddExpressionContext.class,0);
		}
		public TerminalNode Plus() { return getToken(CactParser.Plus, 0); }
		public TerminalNode Minus() { return getToken(CactParser.Minus, 0); }
		public AddExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addExpression; }
	}

	public final AddExpressionContext addExpression() throws RecognitionException {
		return addExpression(0);
	}

	private AddExpressionContext addExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		AddExpressionContext _localctx = new AddExpressionContext(_ctx, _parentState);
		AddExpressionContext _prevctx = _localctx;
		int _startState = 48;
		enterRecursionRule(_localctx, 48, RULE_addExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(276);
			multiplicativeExpression(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(283);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,28,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new AddExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_addExpression);
					setState(278);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(279);
					_la = _input.LA(1);
					if ( !(_la==Minus || _la==Plus) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(280);
					multiplicativeExpression(0);
					}
					} 
				}
				setState(285);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,28,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RelationalExpressionContext extends ParserRuleContext {
		public AddExpressionContext addExpression() {
			return getRuleContext(AddExpressionContext.class,0);
		}
		public RelationalExpressionContext relationalExpression() {
			return getRuleContext(RelationalExpressionContext.class,0);
		}
		public TerminalNode Less() { return getToken(CactParser.Less, 0); }
		public TerminalNode Greater() { return getToken(CactParser.Greater, 0); }
		public TerminalNode LessEqual() { return getToken(CactParser.LessEqual, 0); }
		public TerminalNode GreaterEqual() { return getToken(CactParser.GreaterEqual, 0); }
		public RelationalExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relationalExpression; }
	}

	public final RelationalExpressionContext relationalExpression() throws RecognitionException {
		return relationalExpression(0);
	}

	private RelationalExpressionContext relationalExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		RelationalExpressionContext _localctx = new RelationalExpressionContext(_ctx, _parentState);
		RelationalExpressionContext _prevctx = _localctx;
		int _startState = 50;
		enterRecursionRule(_localctx, 50, RULE_relationalExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(287);
			addExpression(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(294);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,29,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new RelationalExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_relationalExpression);
					setState(289);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(290);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 62914560L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(291);
					addExpression(0);
					}
					} 
				}
				setState(296);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,29,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EqualityExpressionContext extends ParserRuleContext {
		public RelationalExpressionContext relationalExpression() {
			return getRuleContext(RelationalExpressionContext.class,0);
		}
		public EqualityExpressionContext equalityExpression() {
			return getRuleContext(EqualityExpressionContext.class,0);
		}
		public TerminalNode LogicalEqual() { return getToken(CactParser.LogicalEqual, 0); }
		public TerminalNode NotEqual() { return getToken(CactParser.NotEqual, 0); }
		public EqualityExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_equalityExpression; }
	}

	public final EqualityExpressionContext equalityExpression() throws RecognitionException {
		return equalityExpression(0);
	}

	private EqualityExpressionContext equalityExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		EqualityExpressionContext _localctx = new EqualityExpressionContext(_ctx, _parentState);
		EqualityExpressionContext _prevctx = _localctx;
		int _startState = 52;
		enterRecursionRule(_localctx, 52, RULE_equalityExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(298);
			relationalExpression(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(305);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,30,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new EqualityExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_equalityExpression);
					setState(300);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(301);
					_la = _input.LA(1);
					if ( !(_la==LogicalEqual || _la==NotEqual) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(302);
					relationalExpression(0);
					}
					} 
				}
				setState(307);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,30,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LogicalAndExpressionContext extends ParserRuleContext {
		public EqualityExpressionContext equalityExpression() {
			return getRuleContext(EqualityExpressionContext.class,0);
		}
		public LogicalAndExpressionContext logicalAndExpression() {
			return getRuleContext(LogicalAndExpressionContext.class,0);
		}
		public TerminalNode LogicalAnd() { return getToken(CactParser.LogicalAnd, 0); }
		public LogicalAndExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logicalAndExpression; }
	}

	public final LogicalAndExpressionContext logicalAndExpression() throws RecognitionException {
		return logicalAndExpression(0);
	}

	private LogicalAndExpressionContext logicalAndExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		LogicalAndExpressionContext _localctx = new LogicalAndExpressionContext(_ctx, _parentState);
		LogicalAndExpressionContext _prevctx = _localctx;
		int _startState = 54;
		enterRecursionRule(_localctx, 54, RULE_logicalAndExpression, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(309);
			equalityExpression(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(316);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,31,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new LogicalAndExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_logicalAndExpression);
					setState(311);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(312);
					match(LogicalAnd);
					setState(313);
					equalityExpression(0);
					}
					} 
				}
				setState(318);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,31,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LogicalOrExpressionContext extends ParserRuleContext {
		public LogicalAndExpressionContext logicalAndExpression() {
			return getRuleContext(LogicalAndExpressionContext.class,0);
		}
		public LogicalOrExpressionContext logicalOrExpression() {
			return getRuleContext(LogicalOrExpressionContext.class,0);
		}
		public TerminalNode LogicalOr() { return getToken(CactParser.LogicalOr, 0); }
		public LogicalOrExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logicalOrExpression; }
	}

	public final LogicalOrExpressionContext logicalOrExpression() throws RecognitionException {
		return logicalOrExpression(0);
	}

	private LogicalOrExpressionContext logicalOrExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		LogicalOrExpressionContext _localctx = new LogicalOrExpressionContext(_ctx, _parentState);
		LogicalOrExpressionContext _prevctx = _localctx;
		int _startState = 56;
		enterRecursionRule(_localctx, 56, RULE_logicalOrExpression, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(320);
			logicalAndExpression(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(327);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,32,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new LogicalOrExpressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_logicalOrExpression);
					setState(322);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(323);
					match(LogicalOr);
					setState(324);
					logicalAndExpression(0);
					}
					} 
				}
				setState(329);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,32,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 23:
			return multiplicativeExpression_sempred((MultiplicativeExpressionContext)_localctx, predIndex);
		case 24:
			return addExpression_sempred((AddExpressionContext)_localctx, predIndex);
		case 25:
			return relationalExpression_sempred((RelationalExpressionContext)_localctx, predIndex);
		case 26:
			return equalityExpression_sempred((EqualityExpressionContext)_localctx, predIndex);
		case 27:
			return logicalAndExpression_sempred((LogicalAndExpressionContext)_localctx, predIndex);
		case 28:
			return logicalOrExpression_sempred((LogicalOrExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean multiplicativeExpression_sempred(MultiplicativeExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean addExpression_sempred(AddExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean relationalExpression_sempred(RelationalExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean equalityExpression_sempred(EqualityExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean logicalAndExpression_sempred(LogicalAndExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 4:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean logicalOrExpression_sempred(LogicalOrExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 5:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001*\u014b\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0001\u0000\u0001\u0000\u0005\u0000=\b\u0000"+
		"\n\u0000\f\u0000@\t\u0000\u0001\u0001\u0001\u0001\u0003\u0001D\b\u0001"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002"+
		"K\b\u0002\n\u0002\f\u0002N\t\u0002\u0001\u0002\u0001\u0002\u0001\u0003"+
		"\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0005\u0004"+
		"X\b\u0004\n\u0004\f\u0004[\t\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0005\u0005"+
		"e\b\u0005\n\u0005\f\u0005h\t\u0005\u0003\u0005j\b\u0005\u0001\u0005\u0003"+
		"\u0005m\b\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0005"+
		"\u0006s\b\u0006\n\u0006\f\u0006v\t\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0005\u0007~\b\u0007\n\u0007"+
		"\f\u0007\u0081\t\u0007\u0001\u0007\u0001\u0007\u0003\u0007\u0085\b\u0007"+
		"\u0001\b\u0001\b\u0001\b\u0001\b\u0003\b\u008b\b\b\u0001\b\u0001\b\u0001"+
		"\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0005\n\u0095\b\n\n\n\f\n\u0098"+
		"\t\n\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u009e"+
		"\b\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0005\u000b\u00a4"+
		"\b\u000b\n\u000b\f\u000b\u00a7\t\u000b\u0003\u000b\u00a9\b\u000b\u0001"+
		"\f\u0001\f\u0005\f\u00ad\b\f\n\f\f\f\u00b0\t\f\u0001\f\u0001\f\u0001\r"+
		"\u0001\r\u0003\r\u00b6\b\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0003\u000e\u00be\b\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0003\u000e\u00c4\b\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0003\u000e\u00ce\b\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0003\u000e\u00da\b\u000e\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010"+
		"\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0001\u0012\u0005\u0012\u00e7\b\u0012\n\u0012\f\u0012\u00ea\t\u0012\u0001"+
		"\u0013\u0001\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0005\u0014\u00f1"+
		"\b\u0014\n\u0014\f\u0014\u00f4\t\u0014\u0001\u0015\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u00fc\b\u0015\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0003\u0016"+
		"\u0104\b\u0016\u0001\u0016\u0003\u0016\u0107\b\u0016\u0001\u0017\u0001"+
		"\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0005\u0017\u010f"+
		"\b\u0017\n\u0017\f\u0017\u0112\t\u0017\u0001\u0018\u0001\u0018\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0005\u0018\u011a\b\u0018\n\u0018"+
		"\f\u0018\u011d\t\u0018\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019"+
		"\u0001\u0019\u0001\u0019\u0005\u0019\u0125\b\u0019\n\u0019\f\u0019\u0128"+
		"\t\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001"+
		"\u001a\u0005\u001a\u0130\b\u001a\n\u001a\f\u001a\u0133\t\u001a\u0001\u001b"+
		"\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0005\u001b"+
		"\u013b\b\u001b\n\u001b\f\u001b\u013e\t\u001b\u0001\u001c\u0001\u001c\u0001"+
		"\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0005\u001c\u0146\b\u001c\n"+
		"\u001c\f\u001c\u0149\t\u001c\u0001\u001c\u0000\u0006.02468\u001d\u0000"+
		"\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c"+
		"\u001e \"$&(*,.02468\u0000\b\u0001\u0000\u0002\u0004\u0001\u0000\u0002"+
		"\u0005\u0001\u0000$&\u0002\u0000\u0010\u0010\u0014\u0015\u0001\u0000\u0011"+
		"\u0013\u0001\u0000\u0014\u0015\u0001\u0000\u0016\u0019\u0001\u0000\u001a"+
		"\u001b\u0156\u0000>\u0001\u0000\u0000\u0000\u0002C\u0001\u0000\u0000\u0000"+
		"\u0004E\u0001\u0000\u0000\u0000\u0006Q\u0001\u0000\u0000\u0000\bS\u0001"+
		"\u0000\u0000\u0000\nl\u0001\u0000\u0000\u0000\fn\u0001\u0000\u0000\u0000"+
		"\u000ey\u0001\u0000\u0000\u0000\u0010\u0086\u0001\u0000\u0000\u0000\u0012"+
		"\u008f\u0001\u0000\u0000\u0000\u0014\u0091\u0001\u0000\u0000\u0000\u0016"+
		"\u0099\u0001\u0000\u0000\u0000\u0018\u00aa\u0001\u0000\u0000\u0000\u001a"+
		"\u00b5\u0001\u0000\u0000\u0000\u001c\u00d9\u0001\u0000\u0000\u0000\u001e"+
		"\u00db\u0001\u0000\u0000\u0000 \u00dd\u0001\u0000\u0000\u0000\"\u00df"+
		"\u0001\u0000\u0000\u0000$\u00e1\u0001\u0000\u0000\u0000&\u00eb\u0001\u0000"+
		"\u0000\u0000(\u00ed\u0001\u0000\u0000\u0000*\u00fb\u0001\u0000\u0000\u0000"+
		",\u0106\u0001\u0000\u0000\u0000.\u0108\u0001\u0000\u0000\u00000\u0113"+
		"\u0001\u0000\u0000\u00002\u011e\u0001\u0000\u0000\u00004\u0129\u0001\u0000"+
		"\u0000\u00006\u0134\u0001\u0000\u0000\u00008\u013f\u0001\u0000\u0000\u0000"+
		":=\u0003\u0002\u0001\u0000;=\u0003\u0010\b\u0000<:\u0001\u0000\u0000\u0000"+
		"<;\u0001\u0000\u0000\u0000=@\u0001\u0000\u0000\u0000><\u0001\u0000\u0000"+
		"\u0000>?\u0001\u0000\u0000\u0000?\u0001\u0001\u0000\u0000\u0000@>\u0001"+
		"\u0000\u0000\u0000AD\u0003\u0004\u0002\u0000BD\u0003\f\u0006\u0000CA\u0001"+
		"\u0000\u0000\u0000CB\u0001\u0000\u0000\u0000D\u0003\u0001\u0000\u0000"+
		"\u0000EF\u0005\u0001\u0000\u0000FG\u0003\u0006\u0003\u0000GL\u0003\b\u0004"+
		"\u0000HI\u0005!\u0000\u0000IK\u0003\b\u0004\u0000JH\u0001\u0000\u0000"+
		"\u0000KN\u0001\u0000\u0000\u0000LJ\u0001\u0000\u0000\u0000LM\u0001\u0000"+
		"\u0000\u0000MO\u0001\u0000\u0000\u0000NL\u0001\u0000\u0000\u0000OP\u0005"+
		"\"\u0000\u0000P\u0005\u0001\u0000\u0000\u0000QR\u0007\u0000\u0000\u0000"+
		"R\u0007\u0001\u0000\u0000\u0000SY\u0005#\u0000\u0000TU\u0005\f\u0000\u0000"+
		"UV\u0005$\u0000\u0000VX\u0005\r\u0000\u0000WT\u0001\u0000\u0000\u0000"+
		"X[\u0001\u0000\u0000\u0000YW\u0001\u0000\u0000\u0000YZ\u0001\u0000\u0000"+
		"\u0000Z\\\u0001\u0000\u0000\u0000[Y\u0001\u0000\u0000\u0000\\]\u0005 "+
		"\u0000\u0000]^\u0003\n\u0005\u0000^\t\u0001\u0000\u0000\u0000_m\u0003"+
		" \u0010\u0000`i\u0005\u001e\u0000\u0000af\u0003\n\u0005\u0000bc\u0005"+
		"!\u0000\u0000ce\u0003\n\u0005\u0000db\u0001\u0000\u0000\u0000eh\u0001"+
		"\u0000\u0000\u0000fd\u0001\u0000\u0000\u0000fg\u0001\u0000\u0000\u0000"+
		"gj\u0001\u0000\u0000\u0000hf\u0001\u0000\u0000\u0000ia\u0001\u0000\u0000"+
		"\u0000ij\u0001\u0000\u0000\u0000jk\u0001\u0000\u0000\u0000km\u0005\u001f"+
		"\u0000\u0000l_\u0001\u0000\u0000\u0000l`\u0001\u0000\u0000\u0000m\u000b"+
		"\u0001\u0000\u0000\u0000no\u0003\u0006\u0003\u0000ot\u0003\u000e\u0007"+
		"\u0000pq\u0005!\u0000\u0000qs\u0003\u000e\u0007\u0000rp\u0001\u0000\u0000"+
		"\u0000sv\u0001\u0000\u0000\u0000tr\u0001\u0000\u0000\u0000tu\u0001\u0000"+
		"\u0000\u0000uw\u0001\u0000\u0000\u0000vt\u0001\u0000\u0000\u0000wx\u0005"+
		"\"\u0000\u0000x\r\u0001\u0000\u0000\u0000y\u007f\u0005#\u0000\u0000z{"+
		"\u0005\f\u0000\u0000{|\u0005$\u0000\u0000|~\u0005\r\u0000\u0000}z\u0001"+
		"\u0000\u0000\u0000~\u0081\u0001\u0000\u0000\u0000\u007f}\u0001\u0000\u0000"+
		"\u0000\u007f\u0080\u0001\u0000\u0000\u0000\u0080\u0084\u0001\u0000\u0000"+
		"\u0000\u0081\u007f\u0001\u0000\u0000\u0000\u0082\u0083\u0005 \u0000\u0000"+
		"\u0083\u0085\u0003\n\u0005\u0000\u0084\u0082\u0001\u0000\u0000\u0000\u0084"+
		"\u0085\u0001\u0000\u0000\u0000\u0085\u000f\u0001\u0000\u0000\u0000\u0086"+
		"\u0087\u0003\u0012\t\u0000\u0087\u0088\u0005#\u0000\u0000\u0088\u008a"+
		"\u0005\u000e\u0000\u0000\u0089\u008b\u0003\u0014\n\u0000\u008a\u0089\u0001"+
		"\u0000\u0000\u0000\u008a\u008b\u0001\u0000\u0000\u0000\u008b\u008c\u0001"+
		"\u0000\u0000\u0000\u008c\u008d\u0005\u000f\u0000\u0000\u008d\u008e\u0003"+
		"\u0018\f\u0000\u008e\u0011\u0001\u0000\u0000\u0000\u008f\u0090\u0007\u0001"+
		"\u0000\u0000\u0090\u0013\u0001\u0000\u0000\u0000\u0091\u0096\u0003\u0016"+
		"\u000b\u0000\u0092\u0093\u0005!\u0000\u0000\u0093\u0095\u0003\u0016\u000b"+
		"\u0000\u0094\u0092\u0001\u0000\u0000\u0000\u0095\u0098\u0001\u0000\u0000"+
		"\u0000\u0096\u0094\u0001\u0000\u0000\u0000\u0096\u0097\u0001\u0000\u0000"+
		"\u0000\u0097\u0015\u0001\u0000\u0000\u0000\u0098\u0096\u0001\u0000\u0000"+
		"\u0000\u0099\u009a\u0003\u0006\u0003\u0000\u009a\u00a8\u0005#\u0000\u0000"+
		"\u009b\u009d\u0005\f\u0000\u0000\u009c\u009e\u0005$\u0000\u0000\u009d"+
		"\u009c\u0001\u0000\u0000\u0000\u009d\u009e\u0001\u0000\u0000\u0000\u009e"+
		"\u009f\u0001\u0000\u0000\u0000\u009f\u00a5\u0005\r\u0000\u0000\u00a0\u00a1"+
		"\u0005\f\u0000\u0000\u00a1\u00a2\u0005$\u0000\u0000\u00a2\u00a4\u0005"+
		"\r\u0000\u0000\u00a3\u00a0\u0001\u0000\u0000\u0000\u00a4\u00a7\u0001\u0000"+
		"\u0000\u0000\u00a5\u00a3\u0001\u0000\u0000\u0000\u00a5\u00a6\u0001\u0000"+
		"\u0000\u0000\u00a6\u00a9\u0001\u0000\u0000\u0000\u00a7\u00a5\u0001\u0000"+
		"\u0000\u0000\u00a8\u009b\u0001\u0000\u0000\u0000\u00a8\u00a9\u0001\u0000"+
		"\u0000\u0000\u00a9\u0017\u0001\u0000\u0000\u0000\u00aa\u00ae\u0005\u001e"+
		"\u0000\u0000\u00ab\u00ad\u0003\u001a\r\u0000\u00ac\u00ab\u0001\u0000\u0000"+
		"\u0000\u00ad\u00b0\u0001\u0000\u0000\u0000\u00ae\u00ac\u0001\u0000\u0000"+
		"\u0000\u00ae\u00af\u0001\u0000\u0000\u0000\u00af\u00b1\u0001\u0000\u0000"+
		"\u0000\u00b0\u00ae\u0001\u0000\u0000\u0000\u00b1\u00b2\u0005\u001f\u0000"+
		"\u0000\u00b2\u0019\u0001\u0000\u0000\u0000\u00b3\u00b6\u0003\u0002\u0001"+
		"\u0000\u00b4\u00b6\u0003\u001c\u000e\u0000\u00b5\u00b3\u0001\u0000\u0000"+
		"\u0000\u00b5\u00b4\u0001\u0000\u0000\u0000\u00b6\u001b\u0001\u0000\u0000"+
		"\u0000\u00b7\u00b8\u0003$\u0012\u0000\u00b8\u00b9\u0005 \u0000\u0000\u00b9"+
		"\u00ba\u0003\u001e\u000f\u0000\u00ba\u00bb\u0005\"\u0000\u0000\u00bb\u00da"+
		"\u0001\u0000\u0000\u0000\u00bc\u00be\u0003\u001e\u000f\u0000\u00bd\u00bc"+
		"\u0001\u0000\u0000\u0000\u00bd\u00be\u0001\u0000\u0000\u0000\u00be\u00bf"+
		"\u0001\u0000\u0000\u0000\u00bf\u00da\u0005\"\u0000\u0000\u00c0\u00da\u0003"+
		"\u0018\f\u0000\u00c1\u00c3\u0005\u000b\u0000\u0000\u00c2\u00c4\u0003\u001e"+
		"\u000f\u0000\u00c3\u00c2\u0001\u0000\u0000\u0000\u00c3\u00c4\u0001\u0000"+
		"\u0000\u0000\u00c4\u00c5\u0001\u0000\u0000\u0000\u00c5\u00da\u0005\"\u0000"+
		"\u0000\u00c6\u00c7\u0005\u0006\u0000\u0000\u00c7\u00c8\u0005\u000e\u0000"+
		"\u0000\u00c8\u00c9\u0003\"\u0011\u0000\u00c9\u00ca\u0005\u000f\u0000\u0000"+
		"\u00ca\u00cd\u0003\u001c\u000e\u0000\u00cb\u00cc\u0005\u0007\u0000\u0000"+
		"\u00cc\u00ce\u0003\u001c\u000e\u0000\u00cd\u00cb\u0001\u0000\u0000\u0000"+
		"\u00cd\u00ce\u0001\u0000\u0000\u0000\u00ce\u00da\u0001\u0000\u0000\u0000"+
		"\u00cf\u00d0\u0005\b\u0000\u0000\u00d0\u00d1\u0005\u000e\u0000\u0000\u00d1"+
		"\u00d2\u0003\"\u0011\u0000\u00d2\u00d3\u0005\u000f\u0000\u0000\u00d3\u00d4"+
		"\u0003\u001c\u000e\u0000\u00d4\u00da\u0001\u0000\u0000\u0000\u00d5\u00d6"+
		"\u0005\t\u0000\u0000\u00d6\u00da\u0005\"\u0000\u0000\u00d7\u00d8\u0005"+
		"\n\u0000\u0000\u00d8\u00da\u0005\"\u0000\u0000\u00d9\u00b7\u0001\u0000"+
		"\u0000\u0000\u00d9\u00bd\u0001\u0000\u0000\u0000\u00d9\u00c0\u0001\u0000"+
		"\u0000\u0000\u00d9\u00c1\u0001\u0000\u0000\u0000\u00d9\u00c6\u0001\u0000"+
		"\u0000\u0000\u00d9\u00cf\u0001\u0000\u0000\u0000\u00d9\u00d5\u0001\u0000"+
		"\u0000\u0000\u00d9\u00d7\u0001\u0000\u0000\u0000\u00da\u001d\u0001\u0000"+
		"\u0000\u0000\u00db\u00dc\u00030\u0018\u0000\u00dc\u001f\u0001\u0000\u0000"+
		"\u0000\u00dd\u00de\u00030\u0018\u0000\u00de!\u0001\u0000\u0000\u0000\u00df"+
		"\u00e0\u00038\u001c\u0000\u00e0#\u0001\u0000\u0000\u0000\u00e1\u00e8\u0005"+
		"#\u0000\u0000\u00e2\u00e3\u0005\f\u0000\u0000\u00e3\u00e4\u0003\u001e"+
		"\u000f\u0000\u00e4\u00e5\u0005\r\u0000\u0000\u00e5\u00e7\u0001\u0000\u0000"+
		"\u0000\u00e6\u00e2\u0001\u0000\u0000\u0000\u00e7\u00ea\u0001\u0000\u0000"+
		"\u0000\u00e8\u00e6\u0001\u0000\u0000\u0000\u00e8\u00e9\u0001\u0000\u0000"+
		"\u0000\u00e9%\u0001\u0000\u0000\u0000\u00ea\u00e8\u0001\u0000\u0000\u0000"+
		"\u00eb\u00ec\u0007\u0002\u0000\u0000\u00ec\'\u0001\u0000\u0000\u0000\u00ed"+
		"\u00f2\u0003\u001e\u000f\u0000\u00ee\u00ef\u0005!\u0000\u0000\u00ef\u00f1"+
		"\u0003\u001e\u000f\u0000\u00f0\u00ee\u0001\u0000\u0000\u0000\u00f1\u00f4"+
		"\u0001\u0000\u0000\u0000\u00f2\u00f0\u0001\u0000\u0000\u0000\u00f2\u00f3"+
		"\u0001\u0000\u0000\u0000\u00f3)\u0001\u0000\u0000\u0000\u00f4\u00f2\u0001"+
		"\u0000\u0000\u0000\u00f5\u00f6\u0005\u000e\u0000\u0000\u00f6\u00f7\u0003"+
		"\u001e\u000f\u0000\u00f7\u00f8\u0005\u000f\u0000\u0000\u00f8\u00fc\u0001"+
		"\u0000\u0000\u0000\u00f9\u00fc\u0003$\u0012\u0000\u00fa\u00fc\u0003&\u0013"+
		"\u0000\u00fb\u00f5\u0001\u0000\u0000\u0000\u00fb\u00f9\u0001\u0000\u0000"+
		"\u0000\u00fb\u00fa\u0001\u0000\u0000\u0000\u00fc+\u0001\u0000\u0000\u0000"+
		"\u00fd\u0107\u0003*\u0015\u0000\u00fe\u00ff\u0007\u0003\u0000\u0000\u00ff"+
		"\u0107\u0003,\u0016\u0000\u0100\u0101\u0005#\u0000\u0000\u0101\u0103\u0005"+
		"\u000e\u0000\u0000\u0102\u0104\u0003(\u0014\u0000\u0103\u0102\u0001\u0000"+
		"\u0000\u0000\u0103\u0104\u0001\u0000\u0000\u0000\u0104\u0105\u0001\u0000"+
		"\u0000\u0000\u0105\u0107\u0005\u000f\u0000\u0000\u0106\u00fd\u0001\u0000"+
		"\u0000\u0000\u0106\u00fe\u0001\u0000\u0000\u0000\u0106\u0100\u0001\u0000"+
		"\u0000\u0000\u0107-\u0001\u0000\u0000\u0000\u0108\u0109\u0006\u0017\uffff"+
		"\uffff\u0000\u0109\u010a\u0003,\u0016\u0000\u010a\u0110\u0001\u0000\u0000"+
		"\u0000\u010b\u010c\n\u0001\u0000\u0000\u010c\u010d\u0007\u0004\u0000\u0000"+
		"\u010d\u010f\u0003,\u0016\u0000\u010e\u010b\u0001\u0000\u0000\u0000\u010f"+
		"\u0112\u0001\u0000\u0000\u0000\u0110\u010e\u0001\u0000\u0000\u0000\u0110"+
		"\u0111\u0001\u0000\u0000\u0000\u0111/\u0001\u0000\u0000\u0000\u0112\u0110"+
		"\u0001\u0000\u0000\u0000\u0113\u0114\u0006\u0018\uffff\uffff\u0000\u0114"+
		"\u0115\u0003.\u0017\u0000\u0115\u011b\u0001\u0000\u0000\u0000\u0116\u0117"+
		"\n\u0001\u0000\u0000\u0117\u0118\u0007\u0005\u0000\u0000\u0118\u011a\u0003"+
		".\u0017\u0000\u0119\u0116\u0001\u0000\u0000\u0000\u011a\u011d\u0001\u0000"+
		"\u0000\u0000\u011b\u0119\u0001\u0000\u0000\u0000\u011b\u011c\u0001\u0000"+
		"\u0000\u0000\u011c1\u0001\u0000\u0000\u0000\u011d\u011b\u0001\u0000\u0000"+
		"\u0000\u011e\u011f\u0006\u0019\uffff\uffff\u0000\u011f\u0120\u00030\u0018"+
		"\u0000\u0120\u0126\u0001\u0000\u0000\u0000\u0121\u0122\n\u0001\u0000\u0000"+
		"\u0122\u0123\u0007\u0006\u0000\u0000\u0123\u0125\u00030\u0018\u0000\u0124"+
		"\u0121\u0001\u0000\u0000\u0000\u0125\u0128\u0001\u0000\u0000\u0000\u0126"+
		"\u0124\u0001\u0000\u0000\u0000\u0126\u0127\u0001\u0000\u0000\u0000\u0127"+
		"3\u0001\u0000\u0000\u0000\u0128\u0126\u0001\u0000\u0000\u0000\u0129\u012a"+
		"\u0006\u001a\uffff\uffff\u0000\u012a\u012b\u00032\u0019\u0000\u012b\u0131"+
		"\u0001\u0000\u0000\u0000\u012c\u012d\n\u0001\u0000\u0000\u012d\u012e\u0007"+
		"\u0007\u0000\u0000\u012e\u0130\u00032\u0019\u0000\u012f\u012c\u0001\u0000"+
		"\u0000\u0000\u0130\u0133\u0001\u0000\u0000\u0000\u0131\u012f\u0001\u0000"+
		"\u0000\u0000\u0131\u0132\u0001\u0000\u0000\u0000\u01325\u0001\u0000\u0000"+
		"\u0000\u0133\u0131\u0001\u0000\u0000\u0000\u0134\u0135\u0006\u001b\uffff"+
		"\uffff\u0000\u0135\u0136\u00034\u001a\u0000\u0136\u013c\u0001\u0000\u0000"+
		"\u0000\u0137\u0138\n\u0001\u0000\u0000\u0138\u0139\u0005\u001c\u0000\u0000"+
		"\u0139\u013b\u00034\u001a\u0000\u013a\u0137\u0001\u0000\u0000\u0000\u013b"+
		"\u013e\u0001\u0000\u0000\u0000\u013c\u013a\u0001\u0000\u0000\u0000\u013c"+
		"\u013d\u0001\u0000\u0000\u0000\u013d7\u0001\u0000\u0000\u0000\u013e\u013c"+
		"\u0001\u0000\u0000\u0000\u013f\u0140\u0006\u001c\uffff\uffff\u0000\u0140"+
		"\u0141\u00036\u001b\u0000\u0141\u0147\u0001\u0000\u0000\u0000\u0142\u0143"+
		"\n\u0001\u0000\u0000\u0143\u0144\u0005\u001d\u0000\u0000\u0144\u0146\u0003"+
		"6\u001b\u0000\u0145\u0142\u0001\u0000\u0000\u0000\u0146\u0149\u0001\u0000"+
		"\u0000\u0000\u0147\u0145\u0001\u0000\u0000\u0000\u0147\u0148\u0001\u0000"+
		"\u0000\u0000\u01489\u0001\u0000\u0000\u0000\u0149\u0147\u0001\u0000\u0000"+
		"\u0000!<>CLYfilt\u007f\u0084\u008a\u0096\u009d\u00a5\u00a8\u00ae\u00b5"+
		"\u00bd\u00c3\u00cd\u00d9\u00e8\u00f2\u00fb\u0103\u0106\u0110\u011b\u0126"+
		"\u0131\u013c\u0147";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}