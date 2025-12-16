%{
#include "proiect.tab.h"
#include <stdlib.h>
#include <string.h>
%}
%option noyywrap

%%
"int"|"float"|"string"|"bool" {
    yylval.strVal = strdup(yytext);
    return TIP;
}

"class"  { return CLASS; }
"main"   { return MAIN; }
"return" { return RETURN; }
"if"     { return IF; }
"while"  { return WHILE; }
"print"  { return PRINT; }

"true"|"false" {
    yylval.strVal = strdup(yytext);
    return BOOL_VAL;
}

[a-zA-Z][a-zA-Z0-9]* {
    yylval.strVal = strdup(yytext);
    return ID;
}

[0-9]+ {
    yylval.intVal = atoi(yytext);
    return INT_VAL;
}

[0-9]+\.[0-9]+ {
    yylval.floatVal = atof(yytext);
    return FLOAT_VAL;
}

\"[^\"]*\" {
    yylval.strVal = strdup(yytext);
    return STRING_VAL;
}

"==" { return EQ; }
"!=" { return NEQ; }
"<=" { return LE; }
">=" { return GE; }
"<"  { return LT; }
">"  { return GT; }
"&&" { return AND; }
"||" { return OR; }
"!"  { return NOT; }
"+"  { return PLUS; }
"-"  { return MINUS; }
"*"  { return MUL; }
"/"  { return DIV; }
"="  { return ASSIGN; }
[ \t]+ ;
\n { yylineno++; }
. { return yytext[0]; }

%%
