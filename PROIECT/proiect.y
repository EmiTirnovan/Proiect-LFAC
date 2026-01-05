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
         | TIP ID ASSIGN general_expr ';' 
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
               | RETURN general_expr ';'
               | var_decl
               ;

statement_list : 
               | statement_list statement
               ;

statement : ID ASSIGN general_expr ';' 
          | ID '(' call_args ')' ';' 
          | ID '.' ID '(' call_args ')' ';' 
          | ID '.' ID ASSIGN general_expr ';'  
          | print_call ';' 
          | if_statement 
          | while_statement 
          ;

general_expr : arith_expr
             | bool_expr
             ;

arith_expr : INT_VAL
           | FLOAT_VAL
           | STRING_VAL
           | ID
           | ID '.' ID 
           | ID '(' call_args ')' 
           | ID '.' ID '(' call_args ')' 
           | arith_expr PLUS arith_expr
           | arith_expr MINUS arith_expr
           | arith_expr MUL arith_expr
           | arith_expr DIV arith_expr
           | '(' arith_expr ')'
           ;

bool_expr : BOOL_VAL
          | arith_expr EQ arith_expr
          | arith_expr NEQ arith_expr
          | arith_expr LT arith_expr
          | arith_expr GT arith_expr
          | arith_expr LE arith_expr
          | arith_expr GE arith_expr
          | bool_expr AND bool_expr
          | bool_expr OR bool_expr
          | bool_expr EQ bool_expr
          | bool_expr NEQ bool_expr
          | NOT bool_expr
          | '(' bool_expr ')'
          ;           

call_args : 
          | args_list
          ;

args_list : general_expr
          | args_list ',' general_expr
          ;

if_statement : IF '(' bool_expr ')' '{' statement_list '}'
             ;

while_statement : WHILE '(' bool_expr ')' '{' statement_list '}'
                ;

print_call : PRINT '(' general_expr ')' 
           ;

%%

void yyerror(const char * s){
    std::cout << "Eroare de sintaxa la linia " << yylineno << ": " << s << std::endl;
}
#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
