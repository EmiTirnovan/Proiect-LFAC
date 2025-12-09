%{
#include <stdio.h>
#include "proiect.tab.h"
#include <string>
%}
%option noyywrap
%option noyywrap
%%
"int"|"float"|"string"|"bool"  {yylval.Str = new std::string(yytext);return TIP;}
"class" {return CLASS;}
"main" {return MAIN;}
"return" {return RETURN;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"print" {return PRINT;}

"true"|"false" { yylval.Str = new std::string(yytext); return BOOL_VAL;}
[a-zA-Z][a-zA-Z0-9]* {yylval.Str = new std::string(yytext); return ID;}
[0-9]+ {yylval.Str = new std::string(yytext); return CONST_INT;}
[0-9]+\.[0-9]+ {yylval.Str = new std::string(yytext); return CONST_FLOAT;}
\"[^\"]*\" { yylval.Str = new std::string(yytext); return CONST_STRING; }

"==" { return EQ; }
"!=" {return NEQ; }
"<=" {return LEQ; }
">=" { return GEQ; }
"&&" { return AND; }
"||" { return OR; }
"=" {return ASSIGN;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}

%%
