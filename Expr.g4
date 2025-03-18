grammar Expr;

// Parser rules
program  : expr (';' program)? ;
expr     : sum comp sum ;
sum      : num ('+' sum)? ;
comp     : '<' | '>' | '=' | '!=' ;
num      : INT ;

// Lexer rules
INT      : [0-9]+ ;
WS       : [ \t\r\n]+ -> skip ; 