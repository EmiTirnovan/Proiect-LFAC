#include <iostream>
#include <vector>

using namespace std;


class List {
    vector<int> list;
    public:
    List(int x);
    void add(int x);
    void print();
    ~List();
};

