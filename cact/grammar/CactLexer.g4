lexer grammar CactLexer;

// Keywords
BooleanConstant: 'true' | 'false' ;
Const: 'const' ;
Bool: 'bool' ;
Int32: 'int' ;
Float: 'float' ;
Char: 'char' ;
Void: 'void' ;
If : 'if';
Else : 'else';
While : 'while';
Break : 'break';
Continue : 'continue';
Return : 'return';

// Operators by precedence
// Priority 1
LeftBracket : '[' ;
RightBracket : ']' ;
LeftParenthesis : '(' ;
RightParenthesis : ')' ;

// Operators, ranked from highest to lowest priority
// Priority 2
ExclamationMark: '!';
// Priority 3
Asterisk: '*';
Slash: '/';
Percent: '%';
// Priority 4
// Binary Plus and Minus are also used as unary operators
Minus: '-';
Plus: '+';
// Priority 5
Less: '<' ;
LessEqual: '<=' ;
Greater: '>' ;
GreaterEqual: '>=' ;
// Priority 6
LogicalEqual: '==' ;
NotEqual: '!=' ;
// Priority 7
LogicalAnd: '&&' ;
// Priority 8
LogicalOr: '||' ;

// Assignment, comma does not act as operator
// The use of commas is limited to variable constant declarations, initial values, function declarations, and calls

// Other tokens
LeftBrace : '{' ;
RightBrace : '}' ;
Equal: '=' ;
Comma: ',' ;
Semicolon: ';' ;

// Identifier and constants
// CACT identifiers can consist of uppercase and lowercase letters, numbers, and underscores, but must begin with a letter or underscore
Identifier: [a-zA-Z_][a-zA-Z0-9_]* ;
// IntConst → DecimalConst | OctalConst | HexadecConst
IntegerConstant: ('0' | [1-9][0-9]* | '0'[0-7]+ | '0'[xX][0-9a-fA-F]+);
// CharConst  → "'"character"'"
CharacterConstant: '\'' ( EscapeSequence | ~['\\] ) '\'';
fragment EscapeSequence: '\\' ['"?\\abfnrtv0];
// FloatConst
FloatConstant: ([-]?       '.'[0-9]+                  |
                [-]?[0-9]+ '.'[0-9]*                  |
                [-]?       '.'[0-9]+  [eE][+-]?[0-9]+ |
                [-]?[0-9]+('.'[0-9]*)?[eE][+-]?[0-9]+  )[fF];

// Comments and white spaces
LineComment: '//' ~[\r\n]* -> skip;
BlockComment: '/*' .*? '*/' -> skip;
NewLine: ('\r' ('\n')? | '\n') -> skip;
WhiteSpaces : (' ' | '\t')+ -> skip;