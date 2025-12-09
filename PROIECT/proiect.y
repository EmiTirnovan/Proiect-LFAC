%code requires{
    #include <string>
    using namespace std;
}

%{
#include <iostream>
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
int errorCount = 0;
%}

%union {
     std::string* Str;
}

%token 
%token<Str> ID TIP
%start progr
%%
progr : declarations main {if (errorCount == 0) cout<< "The program is correct!" << endl;}
      ;

declarations : var_decl
            | declarations var_decl
            | func_decl
            | declarations func_decl
            | class_decl
            |declarations class_decl
            ;

var_decl : TIP ID ';' {}
        | TIP ID ASSIGN VALUE ':'{}
        ;

func_decl : TIP ID '(' param_list')' '{' statement_list '}'
          ;

param_list : param
           | param_list ',' param
           ;

param : TIP ID
      ;

class_decl : 'class' ID '{' class_decl_list '}'
           ;

class_decl_list : var_decl
                | class_decl_list var_decl
                | func_decl
                | class_decl_list func_decl
                ;

main : 'main' '{' statement_list '}'
  ;

