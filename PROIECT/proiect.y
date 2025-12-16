%code requires{
}

%{
#include <iostream>
#include <string>
#include <vector>
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
int errorCount = 0;
%}

%union {
     char* strVal;
     int intVal;
     float floatVal;
}

%token <strVal> ID TIP STRING_VAL BOOL_VAL
%token <intVal> INT_VAL
%token <floatVal> FLOAT_VAL
%token ASSIGN CLASS MAIN IF WHILE PRINT RETURN
%token PLUS MINUS MUL DIV AND OR NOT EQ NEQ LT GT LE GE

%left OR
%left AND
%left EQ NEQ
%left LT GT LE GE
%left PLUS MINUS
%left MUL DIV
%right NOT

%start progr

%%

progr : declarations main { std::cout << "Program corect sintactic!" << std::endl; }
      ;

declarations : 
             | declarations var_decl
             | declarations func_decl
             | declarations class_decl
             ;

var_decl : TIP ID ';' 
         | TIP ID ASSIGN expr ';' 
         | ID ID ';' 
         ;

class_decl : CLASS ID '{' class_member_list '}' ';'
           ;

class_member_list : 
                  | class_member_list var_decl
                  | class_member_list func_decl
                  ;

func_decl : TIP ID '(' param_list ')' '{' func_body '}'
          ;

param_list : 
           | param
           | param_list ',' param
           ;

param : TIP ID
      ;

main : MAIN '{' statement_list '}'
     ;

func_body : func_statement_list
          ;

func_statement_list : 
                    | func_statement_list func_statement
                    ;

func_statement : statement
               | var_decl 
               ;

statement_list : 
               | statement_list statement
               ;

statement : ID ASSIGN expr ';' 
          | ID '(' call_args ')' ';' 
          | ID '.' ID '(' call_args ')' ';' 
          | ID '.' ID ASSIGN expr ';' 
          | RETURN expr ';' 
          | print_call ';' 
          | if_statement 
          | while_statement 
          ;

expr : INT_VAL
     | FLOAT_VAL
     | STRING_VAL
     | BOOL_VAL
     | ID
     | ID '.' ID 
     | ID '(' call_args ')' 
     | ID '.' ID '(' call_args ')' 
     | expr PLUS expr
     | expr MINUS expr
     | expr MUL expr
     | expr DIV expr
     | expr AND expr
     | expr OR expr
     | expr EQ expr
     | expr NEQ expr
     | expr LT expr
     | expr GT expr
     | expr LE expr
     | expr GE expr
     | expr NOT expr
     | '(' expr ')'
     ;

call_args : 
          | args_list
          ;

args_list : expr
          | args_list ',' expr
          ;

if_statement : IF '(' expr ')' '{' statement_list '}'
             ;

while_statement : WHILE '(' expr ')' '{' statement_list '}'
                ;

print_call : PRINT '(' expr ')'
           ;

%%

void yyerror(const char * s){
    std::cout << "Eroare de sintaxa la linia " << yylineno << ": " << s << std::endl;
}