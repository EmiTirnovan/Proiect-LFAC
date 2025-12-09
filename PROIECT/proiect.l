%{
#include <stdio.h>
#include "proiect.tab.h"
#include <string>
%}
%option noyywrap
%%
"int"|"float"|"string"|"bool"  {yylval.Str = new std::string(yytext);return TIP;}
"main" {return MAIN;}
