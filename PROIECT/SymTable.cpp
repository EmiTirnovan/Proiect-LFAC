#include "SymTable.h"

using namespace std;

bool SymTable::exists(string name){
    if(ids.find(name)!=ids.end()){
        return true;
    }
    else if(parent!=nullptr){
        return parent->exists(name);
    }
    return false;
}

void SymTable::addVar(string type,string name){
    IdInfo newId(&type,&name);
    ids.insert({name,newId});
}

int IdInfo::typeTranslation(string type){
    if(type=="int"){
        this->type="int";
        return 0;
    }
    else if(type=="float"){
        this->type="float";
        return 0;
    }
    else if(type=="bool"){
        this->type="bool";
        return 0;
    }
    else if(type=="string"){
        this->type="string";
        return 0;   
    }
    else{
        return -1;
    }
}

SymTable::~SymTable(){
    ids.clear();
}