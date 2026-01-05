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

// --- Helper pentru transformarea vectorului de statement-uri in arbore ---
ASTNode* createSequence(std::vector<ASTNode*>* stmts) {
    if (!stmts || stmts->empty()) return nullptr;
    
    // Construim un arbore dreapta-recursiv: SEQ(stmt1, SEQ(stmt2, ...))
    // Luam ultimul element
    ASTNode* root = stmts->back();
    
    // Iteram invers de la penultimul la inceput
    for (int i = stmts->size() - 2; i >= 0; --i) {
        ASTNode* current = (*stmts)[i];
        // Cream un nod SEQ: stanga e instructiunea curenta, dreapta e restul secventei
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
               yyerror("Variabila deja declarata!");
         }
         | TIP ID ASSIGN general_expr ';'
         {
          if (!currentScope->addSymbol(IdInfo($2,$1,VARIABLE,"initializata")))
               yyerror("Variabila deja declarata!");
          if ($4 && $4->exprType != stringToType($1)) yyerror("Tip incorect init");
          if($4) delete $4; // Aici e ok sa stergem init-ul static din declaratii, AST-ul executabil e in main
         }
         | ID ID ';'
         {
          IdInfo* cls = currentScope->lookup($1);
          if(!cls || cls->kind != CLASS_NAME) yyerror("Clasa nedefinita");
          if (!currentScope->addSymbol(IdInfo($2,$1,VARIABLE,"object")))
               yyerror("Obiect deja declarat!");
         }
         ;

class_decl : CLASS ID
           {
               if(!currentScope->addSymbol(IdInfo($2, "class", CLASS_NAME, "")))
                    yyerror("Clasa deja existenta!");
               currentScope = new SymTable("Class "+std::string($2), currentScope);
           }
           '{' class_member_list '}' ';'
           {
               SymTable* clsScope = currentScope; 
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
               if (!currentScope->addSymbol(func)) yyerror("Functia deja declarata!");
               currentScope = new SymTable("Function "+std::string($2), currentScope);
               for (auto& p : currentParamTypes)
                    if (!currentScope->addSymbol(IdInfo(p.second, p.first, VARIABLE, "param")))
                         yyerror("Parametru deja declarat!");
          }
          '{' func_body '}'
          {
               SymTable* fnScope = currentScope;
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
func_statement : statement { $$ = $1; } | RETURN general_expr ';' { $$ = $2; } | var_decl { $$ = nullptr; } ;

statement_list : { $$ = new std::vector<ASTNode*>(); } 
               | statement_list statement { $$ = $1; if($2) $$->push_back($2); } ;

statement : ID ASSIGN general_expr ';'
          {
               IdInfo* info = currentScope->lookup($1);
               if(!info){ yyerror("Var nedeclarata"); if($3) delete $3; $$=nullptr; }
               else {
                    std::string err;
                    $$ = ASTNode::makeAssign(ASTNode::id($1, stringToType(info->type)), $3, yylineno, err);
                    if(!err.empty()) { yyerror(err.c_str()); delete $$; $$=nullptr; }
               }
          }
          | ID '(' call_args ')' ';'
          {
               IdInfo* f = currentScope->lookup($1);
               if(!f || f->kind!=FUNCTION) yyerror("Functie invalida");
               else if($3->size() != f->param_types.size()) yyerror("Nr param incorect");
               else {
                   for(size_t i=0; i<$3->size(); ++i) 
                       if((*$3)[i]->exprType != stringToType(f->param_types[i])) yyerror("Tip param incorect");
               }
               // Aici, daca am vrea apeluri de functii void, ar trebui facut nod Call.
               // Deocamdata doar curatam memoria pentru ca nu ai implementat Call statement in AST.
               for(auto n:*$3) delete n; delete $3; $$=nullptr; 
          }
          | ID '.' ID ASSIGN general_expr ';'
          {
                IdInfo* o = currentScope->lookup($1);
                std::string fieldType = "unknown";

                if(!o || o->kind!=VARIABLE) yyerror("Nu e obiect");
                else {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(!c || !c->defScope) yyerror("Clasa invalida");
                     else {
                         IdInfo* f = c->defScope->lookup($3);
                         if(!f) yyerror("Camp inexistent");
                         else {
                            if($5->exprType != stringToType(f->type)) yyerror("Tip incompatibil");
                            fieldType = f->type;
                         }
                     }
                }
                
                // MODIFICARE: Construim nodul, NU returnam nullptr
                std::string err;
                ASTNode* objectNode = ASTNode::id($1, stringToType(o ? o->type : "unknown"));
                ASTNode* fieldNode = ASTNode::id($3, stringToType(fieldType));
                // Folosim operatorul "." pentru acces membru
                ASTNode* memberAccess = new ASTNode(".", stringToType(fieldType), objectNode, fieldNode);
                
                $$ = ASTNode::makeAssign(memberAccess, $5, yylineno, err);
                
                if(!err.empty()) { yyerror(err.c_str()); delete $$; $$=nullptr; }
          }
          | print_call ';' { $$ = $1; }
          | if_statement { $$ = $1; } // MODIFICARE: Propagam nodul If
          | while_statement { $$ = $1; } // MODIFICARE: Propagam nodul While
          ;

general_expr : arith_expr { $$ = $1; } | bool_expr { $$ = $1; } ;

arith_expr : INT_VAL { $$ = ASTNode::literal(Value::fromInt($1)); }
           | FLOAT_VAL { $$ = ASTNode::literal(Value::fromFloat($1)); }
           | STRING_VAL { std::string s($1); $$ = ASTNode::literal(Value::fromString(s.substr(1, s.size()-2))); }
           | ID {
                IdInfo* i = currentScope->lookup($1);
                $$ = i ? ASTNode::id($1, stringToType(i->type)) : ASTNode::other(ValueType::UNKNOWN);
                if(!i) yyerror("Var nedeclarata");
           }
           | ID '.' ID {
                IdInfo* o = currentScope->lookup($1);
                ValueType t = ValueType::UNKNOWN;
                if(o && o->kind==VARIABLE) {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(c && c->defScope) {
                         IdInfo* f = c->defScope->lookup($3);
                         if(f) t = stringToType(f->type); else yyerror("Camp lipsa");
                     } else yyerror("Clasa lipsa");
                } else yyerror("Nu e obiect");
                // Aici construim un nod de acces membru pentru read
                ASTNode* obj = ASTNode::id($1, stringToType(o ? o->type : "unknown"));
                ASTNode* field = ASTNode::id($3, t);
                $$ = new ASTNode(".", t, obj, field);
           }
           | ID '(' call_args ')' {
                IdInfo* f = currentScope->lookup($1);
                ValueType t = ValueType::UNKNOWN;
                if(f && f->kind==FUNCTION) {
                    t = stringToType(f->type);
                    if($3->size() != f->param_types.size()) yyerror("Nr param gresit");
                } else yyerror("Functie lipsa");
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
          | '(' bool_expr ')' { $$ = $2; }
          ;

call_args : { $$ = new std::vector<ASTNode*>(); } | args_list { $$ = $1; } ;
args_list : general_expr { $$ = new std::vector<ASTNode*>(); $$->push_back($1); }
          | args_list ',' general_expr { $$ = $1; $$->push_back($3); } ;

if_statement : IF '(' bool_expr ')' '{' statement_list '}' 
             { 
                // MODIFICARE: Construim nodul IF in loc sa stergem
                ASTNode* block = createSequence($6);
                delete $6; // Stergem vectorul, dar pastram nodurile in 'block'
                $$ = new ASTNode("If", ValueType::VOID, $3, block);
             } 
             ;

while_statement : WHILE '(' bool_expr ')' '{' statement_list '}'
                { 
                // MODIFICARE: Construim nodul WHILE in loc sa stergem
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
    yyparse();
    return (errorCount == 0 ? 0 : 1);
}