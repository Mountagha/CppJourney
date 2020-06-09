#include "List.h"


template<typename T>
Link<T>* Link<T>::insert(Link* n){  // insert n before this object
    if(n == nullptr) return this; //nothing to insert
    //if(this == nullptr) return n; // nothing to insert into;
    n->succ = this;
    if(prev) prev->succ = n;
    n->prev = prev;
    prev = n;
    return n;
}

template<typename T>
Link<T>* Link<T>::add(Link* n) { // insert n after this object
    if(n==nullptr) return this;
    n->succ = succ;
    n->prev = this;
    if(succ) succ->prev = n;
    this->succ = n;
    return n;
}

template<typename T>
Link<T>* Link<T>::erase(){  // erase this from list return succ (or the prev if the last elem)
    if(succ) succ->prev = prev;
    if(prev) prev->succ = succ;
    return succ;
}

template<typename T>
Link<T>* Link<T>::find(const T& s) {
    Link* p = this;
    while(p){
        if(p->value == s) return p;
        p=p->succ;
    }
    return nullptr;
}

template<typename T>
Link<T>* Link<T>::advance(int n) {
    Link* p = this;
    //  positive n moves forward, negative backward
    if(0<n) {
        while(n--){
            if(p->succ == nullptr) return nullptr;
            p = p->succ;
        }
    }
    else if(n < 0){
        while(n++){
            if(p->prev == nullptr) return nullptr;
            p = p->prev;
        }
    }
    return p;

}

template<typename T>
void print_all(Link<T>* p){
    while(p->previous()) p = p->previous(); // go back to the beginning of the list
    while (p)
    {
        cout << p->value << " ";
        p = p->next();
    }
    cout << "\n";
}

// To avoid the template linker error
template class Link<string>;


int main(){
    Link<string>* l = new Link<string>("B");
    l = l->insert(new Link<string>("A"));
    l = l->find("B");
    l = l->add(new Link<string>("C"));
    l = l->add(new Link<string>("E"));
    print_all(l);
    l = l->advance(-1);
    l = l->add(new Link<string>("D"));
    l = l->advance(1);
    l = l->add(new Link<string>("F"));
    print_all(l);
    l = l->advance(-2);
    l = l->erase();
    print_all(l);

    return 0;
}

