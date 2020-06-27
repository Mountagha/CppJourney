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
    Link<Elem>* new_elem = new Link<Elem>(v, p.curr->prev, p.curr);
    
    if(p.curr->prev) p.curr->prev->succ = new_elem;
    p.curr->prev = new_elem;

    if(p.curr == first){
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
    auto to_delete = p.curr;
    ++p;
    delete to_delete;
    return p;
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
    if(first->succ) first->succ->prev = first;
}

template<class Elem>
void List<Elem>::pop_back(){
    auto to_delete = last->prev;
    if(last->prev->prev) last->prev->prev->succ = last;
    last->prev = last->prev->prev;
    delete to_delete;
}

template<class Elem>
void List<Elem>::pop_front(){
    auto to_delete = first;
    first = first->succ;
    first->prev = nullptr;
    delete to_delete;
}

template<class Elem>
Elem& List<Elem>::front(){
    return first->val;
}

template<class Elem>
Elem& List<Elem>::back(){
    if(last->prev) return last->prev->val;
    return last->val; // no elem in the list
}


// To avoid the template linker error
template class Link<string>;

template<class IterF, class IterL>
void print_all(IterF f, IterL l){
    for(auto it = f; it != l; ++it)
        cout << *it << " ";
    cout << "\n";
}

int main(){
    List<string> list;
    auto it = list.insert(list.begin(), "tete");
    it = list.insert(it, "tete1");
    it = list.insert(it, "tete2");
    list.push_back("other_end");
    list.push_front("head");
    
    print_all(list.begin(), list.end());
    auto it_next = list.erase(it); 
    print_all(list.begin(), list.end());
    list.pop_back();
    print_all(list.begin(), list.end());
    list.pop_front();
    print_all(list.begin(), list.end());

    cout << list.front() << "\n";
    cout << list.back() << "\n";

    list.pop_front();

    cout << list.front() << "\n";
    cout << list.back() << "\n";

    list.pop_front();

    cout << list.front() << "\n";
    cout << list.back() << "\n";

    cout << (list.begin() == list.end()) << "\n";
    list.push_front("another_head");
    cout << (list.begin() == list.end()) << "\n";
    cout << list.front() << "\n";
    cout << list.back() << "\n";
    list.push_back("another_head2");
    print_all(list.begin(), list.end());



    return 0;
}

