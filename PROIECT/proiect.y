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
%token ASSIGN VALUE RETURN
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

func_decl : TIP ID '(' param_list ')' '{' func_statement_list '}'
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

func_statement_list : func_statement ';'
                | func_statement_list func_statement ';'
                ;

func_statement : ID ASSIGN expr
                | RETURN expr
                | var_decl
                ;

statement_list : statement ';'
                | statement_list statement ';'
                ;

statement : ID ASSIGN expr
          | RETURN expr
          | func_call
          | conditional_statement
          | loop_statement
          | object_initialization
          | object_method_call
          | print_call
          ;

expr : expr '+' expr  {$$ = $1 + $3; }
     | expr '*' expr  {$$ = $1 * $3;}
     | expr '-' expr  {$$ = $1 - $3;}
     | expr '/' expr  {$$ = $1 / $3;}
     | VALUE {$$ = $1;}
     | ID {}
     | '(' expr ')' {}
     | func_call
     | object_method_call
     | expr '<' expr {$$ = $1 < $3;}
     | expr '>' expr {$$ = $1 > $3;}
     | expr '>=' expr {$$ = $1 >= $3;}
     | expr '<=' expr {$$ = $1 <= $3;}
     | expr '==' expr {$$ = $1 == $3;}
     | expr '!=' expr {$$ = $1 != $3;}
     ;

func_call : ID '(' arg_list ')'
          ;

arg_list : expr
         | arg_list ',' expr
         ;

conditional_statement : 'if' '(' expr ')' '{' statement_list '}' 
                      | 'if' '(' expr ')' '{' statement_list '}' 'else' '{' statement_list '}'
                      ;

loop_statement : 'while' '(' expr ')' '{' statement_list '}'
               ;

object_initialization : ID ID ';'
                      ;

object_method_call : ID '.' ID '(' arg_list ')'
                    ;

print_call : 'print' '(' expr ')'