%code requires{
}

%{
#include <iostream>
#include <string>
#include <vector>
#include "SymTable.h"
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
int errorCount = 0;
SymTable* currentScope = nullptr;
vector<pair<string, string>> currentParamTypes;
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

progr : 
     {
          currentScope = new SymTable("global");
          ofstream fout("tables.txt",ios::trunc);
     }
     declarations main
     {
          currentScope->printTable();
          cout<<"Program compilat cu succes!"<<endl;
     }
     ;

declarations : 
             | declarations var_decl
             | declarations func_decl
             | declarations class_decl
             ;

var_decl : TIP ID ';' 
         {

          IdInfo var ($2,$1,VARIABLE,"");
          if (!currentScope->addSymbol(var))
               yyerror("Variabila $2 deja declarata!");
         }
         | TIP ID ASSIGN general_expr ';' 
         {
          IdInfo var ($2,$1,VARIABLE,"initializata");
          if (!currentScope->addSymbol(var))
               yyerror("Variabila $2 deja declarata!");
         }
         | ID ID ';' 
         {
          IdInfo var ($2,$1,VARIABLE,"object");
          if (!currentScope->addSymbol(var))
               yyerror("Obiect $2 deja declarat!");
         }
         ;

class_decl : CLASS ID 
           {
               currentScope->addSymbol(IdInfo($2,"class",CLASS_NAME,""));
               currentScope = new SymTable("Class "+string($2),currentScope);
           }
           '{' class_member_list '}' ';'
           {
               currentScope->printTable();
               SymTable* parent = currentScope->getParent();
               delete currentScope;
               currentScope = parent;
           }
           ;

class_member_list : 
                  | class_member_list var_decl
                  | class_member_list func_decl
                  ;

func_decl : TIP ID 
          {
               currentParamTypes.clear();
          }
          '(' param_list ')'
          {
               IdInfo func($2,$1,FUNCTION,"");
               vector<string> types;
               for(const auto& paramType : currentParamTypes){
                    types.push_back(paramType.first);
               }
               func.param_types = types;
               if (!currentScope->addSymbol(func))
                    yyerror("Functia $2 deja declarata!");
               currentScope=new SymTable("Function "+string($2),currentScope);
               for (const auto& param : currentParamTypes){
                    IdInfo paramInfo (param.second,param.first,VARIABLE,"param");
                    if (!currentScope->addSymbol(paramInfo))
                         yyerror("Parametru deja declarat!");
               }
          }
          '{' func_body '}'
          {
               currentScope->printTable();
               SymTable* parent = currentScope->getParent();
               delete currentScope;
               currentScope = parent;
          }
          ;

param_list : 
           | param
           | param_list ',' param
           ;

param : TIP ID
     {
          currentParamTypes.push_back(make_pair(string($1),string($2)));
     }
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
          {
               if(!currentScope->lookup($1))
                    yyerror("Variabila $1 nedeclarata!");
          }
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
           {
                    if(!currentScope->lookup($1))
                         yyerror("Variabila nedeclarata!");
           }
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
    std::cout << "Eroare la linia " << yylineno << ": " << s << std::endl;
}
#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    if(result!=0&&currentScope!=nullptr){
        currentScope->printTable();
    }
    return 0;
}
