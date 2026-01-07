%code requires{
    #include <vector>
    #include "AST.h"
}

%{
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "SymTable.h"
#include "AST.h"
#include "Value.h"

std::ofstream runtimeOut;
extern FILE* yyin;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

int errorCount = 0;
SymTable* currentScope = nullptr;
std::vector<std::pair<std::string, std::string>> currentParamTypes;

ASTNode* createSequence(std::vector<ASTNode*>* stmts) {
    if (!stmts || stmts->empty()) return nullptr;
    ASTNode* root = stmts->back();
    for (int i = stmts->size() - 2; i >= 0; --i) {
        ASTNode* current = (*stmts)[i];
        root = new ASTNode("SEQ", ValueType::VOID, current, root);
    }
    return root;
}
%}

%union {
     char* strVal;
     int intVal;
     float floatVal;
     ASTNode* node;
     std::vector<ASTNode*>* nodeList;
}

%token <strVal> ID TIP STRING_VAL BOOL_VAL
%token <intVal> INT_VAL
%token <floatVal> FLOAT_VAL
%token ASSIGN CLASS MAIN IF WHILE PRINT RETURN
%token PLUS MINUS MUL DIV AND OR NOT EQ NEQ LT GT LE GE

%type <node> general_expr arith_expr bool_expr statement print_call func_statement if_statement while_statement
%type <nodeList> statement_list call_args args_list func_statement_list

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
          yylineno = 1;
          currentScope = new SymTable("global");
          std::ofstream fout("tables.txt", std::ios::trunc);
          fout.close();
          runtimeOut.open("runtime.txt", std::ios::trunc);
     }
     declarations main
     {
          currentScope->printTable();
          runtimeOut.close();
          if(errorCount == 0) std::cout<<"Program compilat cu succes!"<<std::endl;
          else std::cout<<"Programul contine erori!"<<std::endl;
     }
     ;

declarations : | declarations var_decl | declarations func_decl | declarations class_decl ;

var_decl : TIP ID ';'
         {
          if (!currentScope->addSymbol(IdInfo($2,$1,VARIABLE,"")))
          {
               std::string msg = "Variabila '" + std::string($2) + "' a fost deja declarata in acest scope.";
               yyerror(msg.c_str());
          }
         }
         | TIP ID ASSIGN general_expr ';'
         {
          if (!currentScope->addSymbol(IdInfo($2,$1,VARIABLE,"initializata")))
               {
                    std::string msg = "Variabila '" + std::string($2) + "' a fost deja declarata in acest scope.";
                    yyerror(msg.c_str());
               }
          if ($4 && $4->exprType != stringToType($1))
          {
               std::string msg = "Tip incompatibil la initializarea variabilei '" + std::string($2) + 
                                 "': s-a asteptat '" + std::string($1) + "', dar s-a primit '" + 
                                 typeToString($4->exprType) + "'.";
               yyerror(msg.c_str());
          }
          if($4) delete $4;
         }
         | ID ID ';'
         {
          IdInfo* cls = currentScope->lookup($1);
          if(!cls || cls->kind != CLASS_NAME)
          {
               std::string msg = "Tipul '" + std::string($1) + "' nu este definit ca o clasa.";
               yyerror(msg.c_str());
          }
          if (!currentScope->addSymbol(IdInfo($2,$1,VARIABLE,"object")))
               {
                    std::string msg = "Obiectul '" + std::string($2) + "' a fost deja declarat.";
                    yyerror(msg.c_str());
               }
         }
         ;

class_decl : CLASS ID
           {
               if(!currentScope->addSymbol(IdInfo($2, "class", CLASS_NAME, "")))
                    {
                         std::string msg = "Clasa '" + std::string($2) + "' este deja definita.";
                         yyerror(msg.c_str());
                    }
               currentScope = new SymTable("Class "+std::string($2), currentScope);
           }
           '{' class_member_list '}' ';'
           {
               SymTable* clsScope = currentScope; 
               currentScope->printTable();
               currentScope = currentScope->getParent(); 
               IdInfo* clsInfo = currentScope->lookup($2);
               if(clsInfo) { clsInfo->defScope = clsScope; currentScope->updateSymbol(*clsInfo); }
           }
           ;

class_member_list : | class_member_list var_decl | class_member_list func_decl ;

func_decl : TIP ID { currentParamTypes.clear(); } '(' param_list ')'
          {
               IdInfo func($2, $1, FUNCTION, "");
               for(auto& p : currentParamTypes) func.param_types.push_back(p.first);
               if (!currentScope->addSymbol(func)) {
                    std::string msg = "Functia '" + std::string($2) + "' este deja definita in acest scope.";
                    yyerror(msg.c_str());
               }
               currentScope = new SymTable("Function "+std::string($2), currentScope);
               for (auto& p : currentParamTypes)
                    if (!currentScope->addSymbol(IdInfo(p.second, p.first, VARIABLE, "param")))
                         {
                              std::string msg = "Parametrul '" + p.second + "' este deja definit in functia '" + std::string($2) + "'.";
                              yyerror(msg.c_str());
                         }
          }
          '{' func_body '}'
          {
               SymTable* fnScope = currentScope;
               currentScope->printTable();
               currentScope = currentScope->getParent(); 
               IdInfo* funcInfo = currentScope->lookup($2);
               if(funcInfo) { funcInfo->defScope = fnScope; currentScope->updateSymbol(*funcInfo); }
          }
          ;

param_list : | param | param_list ',' param ;
param : TIP ID { currentParamTypes.push_back({$1, $2}); } ;

main : MAIN '{' statement_list '}'
     {
          for(ASTNode* st : *$3){
               if(!st) continue;
               std::string err;
               st->eval(currentScope, runtimeOut, err, yylineno);
               if(!err.empty()) yyerror(err.c_str());
               delete st;
          }
          delete $3;
     }
     ;

func_body : func_statement_list { if($1) { for(auto n:*$1) if(n) delete n; delete $1; } } ;

func_statement_list : { $$ = new std::vector<ASTNode*>(); } 
                    | func_statement_list func_statement { $$ = $1; if($2) $$->push_back($2); } ;

func_statement : statement { $$ = $1; } 
               | RETURN general_expr ';' { $$ = $2; } 
               | var_decl { $$ = nullptr; } ;

statement_list : { $$ = new std::vector<ASTNode*>(); } 
               | statement_list statement { $$ = $1; if($2) $$->push_back($2); } ;

statement : ID ASSIGN general_expr ';'
          {
               IdInfo* info = currentScope->lookup($1);
               if(!info){ std::string msg = "Variabila '" + std::string($1) + "' nu a fost declarata.";
                    yyerror(msg.c_str()); if($3) delete $3; $$=nullptr; }
               else {
                    std::string err;
                    $$ = ASTNode::makeAssign(ASTNode::id($1, stringToType(info->type)), $3, yylineno, err);
                    if(!err.empty()) { yyerror(err.c_str()); delete $$; $$=nullptr; }
               }
          }
          | ID '(' call_args ')' ';'
          {
               IdInfo* f = currentScope->lookup($1);
               if(!f || f->kind!=FUNCTION) {
                    std::string msg = "Functia '" + std::string($1) + "' nu este declarata.";
                    yyerror(msg.c_str());
               }
               else if($3->size() != f->param_types.size()) {
                    std::string msg = "Functia '" + std::string($1) + "' asteapta " + std::to_string(f->param_types.size()) + 
                                      " parametri, dar i s-au dat " + std::to_string($3->size()) + ".";
                    yyerror(msg.c_str());
               }
               else {
                   for(size_t i=0; i<$3->size(); ++i) 
                       if((*$3)[i]->exprType != stringToType(f->param_types[i])){
                               std::string msg = "Tip incompatibil la apelul functiei '" + std::string($1) + 
                                              "' pentru parametrul " + std::to_string(i+1) + 
                                              ": s-a asteptat '" + f->param_types[i] + "', dar s-a primit '" + 
                                              typeToString((*$3)[i]->exprType) + "'.";
                               yyerror(msg.c_str());
                       }
               }
               for(auto n:*$3) delete n; delete $3; $$=nullptr; 
          }
          | ID '.' ID ASSIGN general_expr ';'
          {
                IdInfo* o = currentScope->lookup($1);
                std::string fieldType = "unknown";

                if(!o || o->kind!=VARIABLE) {
                    std::string msg = "Obiectul '" + std::string($1) + "' nu este declarat sau nu este un obiect.";
                    yyerror(msg.c_str());
                }
                else {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(!c || !c->defScope) {
                         std::string msg = "Clasa obiectului '" + std::string($1) + "' nu este definita.";
                         yyerror(msg.c_str());
                     }
                     else {
                         IdInfo* f = c->defScope->lookup($3);
                         if(!f) {
                               std::string msg = "Campul '" + std::string($3) + "' nu exista in clasa '" + o->type + "'.";
                               yyerror(msg.c_str());
                         }
                         else {
                            if($5->exprType != stringToType(f->type)) {
                                   std::string msg = "Tip incompatibil la atribuirea campului '" + std::string($3) + 
                                                       "' al obiectului '" + std::string($1) + "': s-a asteptat '" + f->type + 
                                                       "', dar s-a primit '" + typeToString($5->exprType) + "'.";
                                   yyerror(msg.c_str());
                            }
                            fieldType = f->type;
                         }
                     }
                }
                std::string err;
                ASTNode* objectNode = ASTNode::id($1, stringToType(o ? o->type : "unknown"));
                ASTNode* fieldNode = ASTNode::id($3, stringToType(fieldType));
                ASTNode* memberAccess = new ASTNode(".", stringToType(fieldType), objectNode, fieldNode);
                $$ = ASTNode::makeAssign(memberAccess, $5, yylineno, err);
                if(!err.empty()) { yyerror(err.c_str()); delete $$; $$=nullptr; }
          }
          | print_call ';' { $$ = $1; }
          | if_statement { $$ = $1; }
          | while_statement { $$ = $1; }
          ;

general_expr : arith_expr { $$ = $1; } | bool_expr { $$ = $1; } ;

arith_expr : INT_VAL { $$ = ASTNode::literal(Value::fromInt($1)); }
           | FLOAT_VAL { $$ = ASTNode::literal(Value::fromFloat($1)); }
           | STRING_VAL { std::string s($1); $$ = ASTNode::literal(Value::fromString(s.substr(1, s.size()-2))); }
           | ID {
                IdInfo* i = currentScope->lookup($1);
                $$ = i ? ASTNode::id($1, stringToType(i->type)) : ASTNode::other(ValueType::UNKNOWN);
                if(!i) {
                    std::string msg = "Variabila '" + std::string($1) + "' nu a fost declarata.";
                    yyerror(msg.c_str());
                }
           }
           | ID '.' ID {
                IdInfo* o = currentScope->lookup($1);
                ValueType t = ValueType::UNKNOWN;
                if(o && o->kind==VARIABLE) {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(c && c->defScope) {
                         IdInfo* f = c->defScope->lookup($3);
                         if(f) t = stringToType(f->type); else {
                               std::string msg = "Campul '" + std::string($3) + "' nu exista in clasa '" + o->type + "'.";
                               yyerror(msg.c_str());
                         }
                     } else {
                         std::string msg = "Clasa obiectului '" + std::string($1) + "' nu este definita.";
                         yyerror(msg.c_str());
                     }
                } else {
                         std::string msg = "Obiectul '" + std::string($1) + "' nu este declarat sau nu este un obiect.";
                         yyerror(msg.c_str());
                }
                ASTNode* obj = ASTNode::id($1, stringToType(o ? o->type : "unknown"));
                ASTNode* field = ASTNode::id($3, t);
                $$ = new ASTNode(".", t, obj, field);
           }
           | ID '(' call_args ')' {
                IdInfo* f = currentScope->lookup($1);
                ValueType t = ValueType::UNKNOWN;
                if(f && f->kind==FUNCTION) {
                    t = stringToType(f->type);
                    if($3->size() != f->param_types.size()) {
                         std::string msg = "Apel invalid functie '" + std::string($1) + "': numar parametri gresit.";
                         yyerror(msg.c_str());
                    }
                } else {
                         std::string msg = "Functia '" + std::string($1) + "' nu este declarata.";
                         yyerror(msg.c_str());
                }
                for(auto n:*$3) delete n; delete $3; $$=ASTNode::other(t);
           }
           | arith_expr PLUS arith_expr { std::string e; $$=ASTNode::makeBinary("+",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
           | arith_expr MINUS arith_expr { std::string e; $$=ASTNode::makeBinary("-",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
           | arith_expr MUL arith_expr { std::string e; $$=ASTNode::makeBinary("*",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
           | arith_expr DIV arith_expr { std::string e; $$=ASTNode::makeBinary("/",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
           | '(' arith_expr ')' { $$ = $2; }
           ;

bool_expr : BOOL_VAL { $$ = ASTNode::literal(Value::fromBool(std::string($1)=="true")); }
          | arith_expr EQ arith_expr { std::string e; $$=ASTNode::makeCompare("==",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | arith_expr LT arith_expr { std::string e; $$=ASTNode::makeCompare("<",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | arith_expr GT arith_expr { std::string e; $$=ASTNode::makeCompare(">",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | arith_expr LE arith_expr { std::string e; $$=ASTNode::makeCompare("<=",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | arith_expr GE arith_expr { std::string e; $$=ASTNode::makeCompare(">=",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | arith_expr NEQ arith_expr { std::string e; $$=ASTNode::makeCompare("!=",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | bool_expr AND bool_expr { std::string e; $$=ASTNode::makeBinary("AND",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | bool_expr OR bool_expr { std::string e; $$=ASTNode::makeBinary("OR",$1,$3,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | NOT bool_expr { std::string e; $$=ASTNode::makeUnary("NOT",$2,yylineno,e); if(e.size()) yyerror(e.c_str()); }
          | '(' bool_expr ')' { $$ = $2; }
          ;

call_args : { $$ = new std::vector<ASTNode*>(); } | args_list { $$ = $1; } ;
args_list : general_expr { $$ = new std::vector<ASTNode*>(); $$->push_back($1); }
          | args_list ',' general_expr { $$ = $1; $$->push_back($3); } ;

if_statement : IF '(' bool_expr ')' '{' statement_list '}' 
             { 
                ASTNode* block = createSequence($6);
                delete $6;
                $$ = new ASTNode("If", ValueType::VOID, $3, block);
             } 
             ;

while_statement : WHILE '(' bool_expr ')' '{' statement_list '}'
                { 
                ASTNode* block = createSequence($6);
                delete $6;
                $$ = new ASTNode("While", ValueType::VOID, $3, block);
                } 
                ;

print_call : PRINT '(' general_expr ')' { $$ = ASTNode::makePrint($3); } ;
%%

void yyerror(const char * s){ std::cout << "Eroare la linia " << yylineno << ": " << s << std::endl; errorCount++; }
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    if (result != 0) {
        currentScope->printTable();
    }
    return (errorCount == 0 ? 0 : 1);
}