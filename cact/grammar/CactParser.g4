parser grammar CactParser;

options {
tokenVocab=CactLexer;
}

// declaration & defination
// 编译单元: CompUnit → [ CompUnit ] ( Decl | FuncDef )
compilationUnit: (declaration | functionDefinition)*;
// 声明: Decl → ConstDecl | VarDecl
declaration: constantDeclaration | variableDeclaration;
// 常量声明: ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
constantDeclaration: Const basicType constantDefinition (Comma constantDefinition)* Semicolon;
// 基本类型: BType → 'int' | 'float' | 'char'
basicType: Int | Float | Char;
// 常量定义: ConstDef → Ident { '[' IntConst ']' } '=' ConstInitVal
constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)? Equal constantInitializationValue;
// 初始值: ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
constantInitializationValue: constantExpression | LeftBrace (constantInitializationValue (Comma constantInitializationValue)*)? RightBrace;
// 变量声明: VarDecl → BType VarDef { ',' VarDef } ';'
variableDeclaration: basicType variableDeclaration (Comma variableDefinition)* Semicolon;
// 变量定义: VarDef → Ident { '[' IntConst ']' } [ '=' ConstInitVal ]
variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitializationValue)?;
// 函数定义FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
functionDefinition: functionType Identifier LeftParenthesis (functionParameters)? RightParenthesis block;
// 函数类型FuncType → 'void' | 'int' | 'float' | 'char'
fuctionType: Void | Int | Float | Char;
// 形参列表FuncFParams → FuncFParam { ',' FuncFParam }
functionFormalParameters: functionFormalParameter (Comma functionFormalParameter)*;
// 函数形参FuncFParam → BType Ident [ '[' IntConst? ']' { '[' IntConst ']' } ]
fucntionFormalParameter: basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;

// statement & expression
// 语句块: Block → '{' { BlockItem } '}'
block: LeftBrace (blockItem)* RightBrace;
// 语句块项: BlockItem → Decl | Stmt
blockItem: declaration | statement;
// 语句Stmt → LVal '=' Exp ';' | [ Exp ] ';' | Block | 'return' Exp? | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';
statement: leftValue Equal expression Semicolon
         | (expression)? Semicolon
         | block
         | Return expression? Semicolon
         | If LeftParenthesis condition RightParenthesis statement (Else statement)?
         | While LeftParenthesis condition RightParenthesis statement
         | Break Semicolon
         | Continue Semicolon;
// 表达式: Exp → AddExp
expression: addExpression;
// 常量算式: ConstExp → AddExp
constantExpression: addExpression;
// 条件算式Cond → LOrExp
condition: logicalOrExpression;
// 左值算式LVal → Ident { '[' Exp ']' }
leftValue: Identifier (LeftBracket expression RightBracket)*;
// 数值Number → IntConst | CharConst | FloatConst
number: IntegerConstant | CharacterConstant | FloatConstant;
// 函数实参表FuncRParams → Exp { ',' Exp }
fuctionRealParameters: expression (Comma expression)*;
// PrimaryExp → '(' Exp ')' | LVal | Number
primaryExpression: LeftParenthesis expression RightParenthesis
                  | leftValue
                  | number;
// UnaryExp → PrimaryExp | ('+' | '-' | '!') UnaryExp | Ident '(' [ FuncRParams ] ')' 注：'!'仅出现在条件表达式中
unaryExpression: primaryExpression
                | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (fuctionRealParameters)? RightParenthesis;
// MulExp → UnaryExp | MulExp (' *' | '/' | '%') UnaryExp
multiplicativeExpression: unaryExpression | multiplicativeExpression (Asterisk | Slash | Percent) unaryExpression;
// AddExp → MulExp | AddExp ('+'|'-') MulExp
addExpression: multiplicativeExpression | addExpression (Plus | Minus) multiplicativeExpression;
//  RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
relationalExpression: addExpression | relationalExpression (Less | Greater | LessEqual | GreaterEqual) addExpression;
//  EqExp → RelExp | EqExp ('==' | '!=') RelExp
equalityExpression: relationalExpression | equalityExpression (LogicalEqual | NotEqual) relationalExpression;
//  LAndExp → EqExp | LAndExp '&&' EqExp
logicalAndExpression: equalityExpression | logicalAndExpression LogicalAnd equalityExpression;
//  LOrExp → LAndExp | LOrExp '||' LAndExp
logicalOrExpression: logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;