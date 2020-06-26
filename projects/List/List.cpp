#include "List.h"

template<class Elem>
class List<Elem>::iterator{
    public:    
        Link<Elem>* curr;
        iterator(Link<Elem>* p): curr{p} {}
        iterator& operator++() { curr = curr->succ; return *this; } // forward
        iterator& operator--() { curr = curr->prev; return *this; } // backward
        Elem& operator*() { return curr->val; } // deferencement
        friend bool operator==(const iterator& a, const iterator& b){
            return a.curr == b.curr;
        }
        friend bool operator!=(const iterator& a, const iterator& b){
            return a.curr != b.curr;
        }

};

template<class Elem>
typename List<Elem>::iterator List<Elem>::begin(){
    return iterator(first);
}

template<class Elem>
typename List<Elem>::iterator List<Elem>::end(){
    return iterator(last);
}

template<class Elem>
typename List<Elem>::iterator List<Elem>::insert(iterator p, const Elem& v){  // insert v before p
    cout << "aussi" << "\n";
    Link<Elem>* new_elem = new Link<Elem>(v, p.curr->prev, p.curr);
    p.curr->prev = new_elem;

    if(p.curr->prev) p.curr->prev->succ = new_elem;
    if(p.curr == first){
        cout << "yes: " << *p << "\n";
        --p;
        first = p.curr;
        return p;
    } 
    return --p;             // return inserted elem
}


template<class Elem>
typename List<Elem>::iterator List<Elem>::erase(iterator p){  // remove p from the list
    if(p.curr->prev) p.curr->prev->succ = p.curr->succ;
    if(p.curr->succ) p.curr->succ->prev = p.curr->prev;
    auto new_iter = ++p;
    delete p;
    return new_iter;
}

template<class Elem>
void List<Elem>::push_back(const Elem& v){
    Link<Elem>* new_elem = new Link<Elem>(v, last->prev, last);
    last->prev->succ = new_elem;
    last->prev = new_elem;
}

template<class Elem>
void List<Elem>::push_front(const Elem& v){
    first = new Link<Elem>(v, nullptr, first);
}

template<class Elem>
void List<Elem>::pop_back(){
    auto elem_to_pop = last->prev;
    last->prev->prev->succ = last;
    last->prev = last->prev->prev;
    delete elem_to_pop;
}

template<class Elem>
void List<Elem>::pop_front(){
    auto elem_to_pop = first;
    first = first->succ;
    delete elem_to_pop;
}

template<class Elem>
Elem& List<Elem>::front(){
    return first->val;
}

template<class Elem>
Elem& List<Elem>::back(){
    return last->prev->val;
}


// To avoid the template linker error
template class Link<string>;


int main(){
    List<string> list;
    cout << (list.begin() == list.end()) << "\n";
    auto it = list.insert(list.begin(), "tete");
    cout << (list.begin() == list.end()) << "\n";
    cout << list.front() << "\n";
    cout << list.back() << "\n";
    //it = list.insert(it, "tete1");
    //it = list.insert(it, "tete2");
    cout << *it << "\n";
    list.push_back("other_end");
    //list.push_front("other_front");
    //List<string>::iterator it3 = list.begin();
    
    //for(auto it = list.begin(); it != list.end(); ++it)
    //    cout << *it << "\n";

    return 0;
}

