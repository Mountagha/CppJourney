#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Link {
    public:
        T value;
        Link(const T& v, Link* p=nullptr, Link* s=nullptr): value{v}, prev{p}, succ{s} {}
        Link* insert(Link* n); // insert n before this object
        Link* add(Link* n);   // insert n after this object
        Link* erase();       // erase this object from the list
        Link* find(const T& v); // find s in the const list

        Link* advance(int n); // move n positions in list

        Link* next() const { return succ; }; 
        Link* previous() const { return prev; }
    
    private:
        Link* prev;
        Link* succ;
};

template<typename T>
void print_all(Link<T>* p);