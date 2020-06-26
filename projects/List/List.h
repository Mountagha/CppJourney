#include <iostream>
#include <string>

using namespace std;

template<typename Elem>
struct Link{
    Link* prev;
    Link* succ;
    Elem val;
    Link(const Elem v=Elem(), Link* p = nullptr, Link* s=nullptr): val{v}, prev{p}, succ{s} {}

};

template<typename Elem>
class List {
    public:
        
        class iterator; // member type: iterator

        iterator begin(); // iterator to the first element
        iterator end(); // iterator to one beyond the last element

        List(): first{new Link<Elem>()}, last{first} {}
        iterator insert(iterator p, const Elem& v); // insert v into list before p
        iterator erase(iterator p);       // remove p from the list

        void push_back(const Elem& v); // insert v at the end
        void push_front(const Elem& v); // insert v at the front
        void pop_back();                // remove the first element
        void pop_front();               // remove the last element

        Elem& front();                  // the first element
        Elem& back();                   // the last element

        Link<Elem>* first;
        Link<Elem>* last;
};


template<typename T>
void print_all(Link<T>* p);