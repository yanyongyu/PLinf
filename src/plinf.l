%{
#include <stdlib.h>
#include <string.h>

#include "intermediate.h"
#include "plinf.tab.h"
%}

%option noyywrap
%option yylineno

digit [0-9]
letter [a-zA-Z]

%%

(?i:"const") { return CONST_; }
(?i:"type") { return TYPE_; }
(?i:"var") { return VAR_; }
(?i:"procedure") { return PROCEDURE_; }
(?i:"function") { return FUNCTION_; }

(?i:"integer") {
  TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
  temp->type = tt_int;
  yylval.type = temp;
  return INTEGER;
}
(?i:"real") {
  TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
  temp->type = tt_real;
  yylval.type = temp;
  return REAL;
}
(?i:"boolean") {
  TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
  temp->type = tt_bool;
  yylval.type = temp;
  return BOOLEAN;
}
(?i:"array") {
  TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
  ARRAY_INFO *info = (ARRAY_INFO *)calloc(1, sizeof(ARRAY_INFO));
  temp->type = tt_array;
  temp->array = info;
  yylval.type = temp;
  return ARRAY;
}
(?i:"of") { return OF; }
(?i:"true") {
  CONST *temp = (CONST *)calloc(1, sizeof(CONST));
  temp->type = ct_bool;
  temp->num = 1;
  yylval.const_value = temp;
  return TRUE;
}
(?i:"false") {
  CONST *temp = (CONST *)calloc(1, sizeof(CONST));
  temp->type = ct_bool;
  temp->num = 0;
  yylval.const_value = temp;
  return FALSE;
}

(?i:"if") { return IF; }
(?i:"then") { return THEN; }
(?i:"else") { return ELSE; }

(?i:"write") {
  IDENTIFIER *temp = (IDENTIFIER *)calloc(1, sizeof(IDENTIFIER));
  temp->type = it_identifier;
  temp->name = strdup("write");
  yylval.id = temp;
  return WRITE;
}
(?i:"read") {
  IDENTIFIER *temp = (IDENTIFIER *)calloc(1, sizeof(IDENTIFIER));
  temp->type = it_identifier;
  temp->name = strdup("read");
  yylval.id = temp;
  return READ;
}

(?i:"while") { return WHILE; }
(?i:"do") { return DO; }
(?i:"continue") { return CONTINUE; }
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

"<>" { return NEQ; }
">=" { return GEQ; }
"<=" { return LEQ; }
">" { return GE; }
"<" { return LE; }
"=" { return EQ; }

"+" { return PLUS; }
"-" { return MINUS; }
"/" { return DIVIDE; }
"*" { return TIMES; }

":=" { return ASSIGN_; }
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
  CONST *temp = (CONST *)calloc(1, sizeof(CONST));
  temp->type = ct_int;
  temp->num = atol(yytext);
  yylval.const_value = temp;
  return NUMBER;
}
{digit}+\.{digit}*/[^.] {
  char *eptr;
  CONST *temp = (CONST *)calloc(1, sizeof(CONST));
  temp->type = ct_real;
  temp->real_num = strtod(yytext, &eptr);
  yylval.const_value = temp;
  return REAL_NUMBER;
}

{letter}({letter}|{digit})* {
  IDENTIFIER *temp = (IDENTIFIER *)calloc(1, sizeof(IDENTIFIER));
  temp->type = it_identifier;
  temp->name = strdup(yytext);
  yylval.id = temp;
  return IDENTIFIER_;
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
