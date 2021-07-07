%{
#include <stdlib.h>
#include <string.h>

#include "plinf.tab.h"
%}

%option noyywrap

digit [0-9]
letter [a-zA-Z]

%%

(?i:"const") { return CONST; }
(?i:"type") { return TYPE; }
(?i:"var") { return VAR; }
(?i:"procedure") { return PROCEDURE; }
(?i:"function") { return FUNCTION; }

(?i:"integer") { return INTEGER; }
(?i:"real") { return REAL; }
(?i:"boolean") { return BOOLEAN; }
(?i:"array") { return ARRAY; }
(?i:"of") { return OF; }
"true" { return TRUE; }
"false" { return FALSE; }

(?i:"if") { return IF; }
(?i:"then") { return THEN; }
(?i:"else") { return ELSE; }

(?i:"write") { return WRITE; }
(?i:"read") { return READ; }

(?i:"while") { return WHILE; }
(?i:"do") { return DO; }
(?i:"exit") { return EXIT; }

(?i:"or") { return OR; }
(?i:"and") { return AND; }
(?i:"not") { return NOT; }

(?i:"div") { return DIV; }
(?i:"mod") { return MOD; }

(?i:"call") { return CALL; }

(?i:"odd") { return ODD; }

(?i:"begin") { return BLOCK_BEGIN; }
(?i:"end") { return BLOCK_END; }

"<>" { return RELOP; }
">=" { return RELOP; }
"<=" { return RELOP; }
">" { return RELOP; }
"<" { return RELOP; }
"=" { return EQ; }

"+" { return PLUS; }
"-" { return MINUS; }
"/" { return DIVIDE; }
"*" { return TIMES; }

":=" { return ASSIGN; }
"." { return PERIOD; }
":" { return COLON; }
";" { return SEMI; }
"," { return COMMA; }
"(" { return LPAREN; }
")" { return RPAREN; }
"[" { return LBRACE; }
"]" { return RBRACE; }

{digit}+ 	{
  yylval.num = atoi(yytext);
  return NUMBER;
}

{letter}({letter}|{digit})*  {
  yylval.id = strdup(yytext);
  return IDENTIFIER;
}


"//".*/\n|<<EOF>> /* ignore comments */;
"/*" {
  for (;;) {
    while (input() != '*');
    if (input() != '/') unput(yytext[yyleng - 1]);
    break;
  }
}

[ \t\n] ;

%%
