%{
#include <stdlib.h>
#include <string.h>

#include "plinf.tab.h"
#include "intermediate.h"
%}

%option noyywrap
%option yylineno

digit [0-9]
letter [a-zA-Z]

%%

(?i:"const") { return CONST; }
(?i:"type") { return TYPE; }
(?i:"var") { return VAR; }
(?i:"procedure") { return PROCEDURE; }
(?i:"function") { return FUNCTION; }

(?i:"integer") {
  TYPE_VALUE *temp = (TYPE_VALUE *)calloc(1, sizeof(TYPE_VALUE));
  temp->type = tt_int;
  yylval.type_value = temp;
  return INTEGER;
}
(?i:"real") {
  TYPE_VALUE *temp = (TYPE_VALUE *)calloc(1, sizeof(TYPE_VALUE));
  temp->type = tt_real;
  yylval.type_value = temp;
  return REAL;
}
(?i:"boolean") {
  TYPE_VALUE *temp = (TYPE_VALUE *)calloc(1, sizeof(TYPE_VALUE));
  temp->type = tt_bool;
  yylval.type_value = temp;
  return BOOLEAN;
}
(?i:"array") {
  TYPE_VALUE *temp = (TYPE_VALUE *)calloc(1, sizeof(TYPE_VALUE));
  temp->type = tt_array;
  yylval.type_value = temp;
  return ARRAY;
}
(?i:"of") { return OF; }
(?i:"true") {
  CONST_VALUE *temp = (CONST_VALUE *)calloc(1, sizeof(CONST_VALUE));
  temp->type = ct_bool;
  temp->num = 1;
  yylval.const_value = temp;
  return TRUE;
}
(?i:"false") {
  CONST_VALUE *temp = (CONST_VALUE *)calloc(1, sizeof(CONST_VALUE));
  temp->type = ct_bool;
  temp->num = 0;
  yylval.const_value = temp;
  return FALSE;
}

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
".." { return PERIOD_PERIOD; }
":" { return COLON; }
";" { return SEMI; }
"," { return COMMA; }
"(" { return LPAREN; }
")" { return RPAREN; }
"[" { return LBRACE; }
"]" { return RBRACE; }

{digit}+ 	{
  CONST_VALUE *temp = (CONST_VALUE *)calloc(1, sizeof(CONST_VALUE));
  temp->type = ct_int;
  temp->num = atoi(yytext);
  yylval.const_value = temp;
  return NUMBER;
}
{digit}+\.{digit}*/[^.] {
  char *eptr;
  CONST_VALUE *temp = (CONST_VALUE *)calloc(1, sizeof(CONST_VALUE));
  temp->type = ct_real;
  temp->real_num = strtod(yytext, &eptr);
  yylval.const_value = temp;
  return REAL_NUMBER;
}

{letter}({letter}|{digit})*  {
  yylval.id = strdup(yytext);
  return IDENTIFIER;
}


"//".* /* ignore comments */;
"/*" {
  for (;;) {
    switch (input()) {
      case EOF:
        yy_fatal_error("unterminated comment");
        break;
      case '*':
        if (input() == '/') goto done;
        unput(yytext[yyleng - 1]);
        break;
      default:
        break;
    }
  }

  done:
    /* exit entry */;
}

[ \t\n] ;

%%
