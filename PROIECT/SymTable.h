#include <map>
#include <string>

using namespace std;

class IdInfo{
    int typeTranslation(string type);
    public:
    string type;
    string name;

    IdInfo(string* type,string* name):type(*type),name(*name){if (typeTranslation(*type)!=0) /*eroare la compilare nu exista type mentionat*/;}
};

class SymTable{
    SymTable* parent;
    map<string,IdInfo> ids;
    string name;
    public:
    SymTable(string name,SymTable* parent=nullptr):name(name),parent(parent){}
    bool exists(string name);
    void addVar(string type,string name);
    ~SymTable();
};