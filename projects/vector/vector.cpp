#include "vector.h"

// copy constructor
template<typename T, typename A>
vector<T,A>::vector(const vector& v): sz{v.size()}, elem{new T[v.size()]}{
    //copy(v, v+sz, elem);
    for(int i=0; i<sz; i++){
        elem[i] = v.elem[i];
    }
}

// copy assignment
template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector& v){
    // make this vector a copy of v

    if(this==&v) return *this;  // self assignment, no work needed
    if(v.size()<=space){          // enough space no need for allocation just copy
        for(int i=0; i<v.size(); i++)
            elem[i] = v.elem[i];
        sz = v.size();
        return *this;
    } 
    T *p = new T[v.size()];
    for(int i=0; i<v.size(); i++) p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = sz = v.size();
    return *this;
}

// move 
template<typename T, typename A>
vector<T, A>::vector(vector&& v): sz{v.sz}, elem{v.elem} {
    v.sz = 0;
    v.elem = nullptr;
} 

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector&& v){
    //move v to this vector
    delete [] elem;
    elem = v.elem;
    sz = v.sz;
    v.elem = nullptr;
    v.sz = 0;
    return *this;
}

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc){
    if(newalloc<=space) return; // never decrease allocation
    T *p = alloc.allocate(newalloc); // allocate new space
    for(int i=0; i<sz; i++)
        alloc.construct(&p[i], elem[i]); // copy
    for(int i=0; i<sz; i++)
        alloc.destroy(&elem[i]);    // destroy
    alloc.deallocate(elem, space);
    elem = p;
    space = newalloc;
}

template<typename T, typename A>
void vector<T, A>::resize(int newsize, T def){
    reserve(newsize);
    for(int i=sz; i<newsize; i++) //initialize new elmts
        alloc.construct(&elem[i], def);
    for(int i=newsize; i<sz; i++)
        alloc.destroy(&elem[i]);
    sz = newsize;
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val){
    //increase vector size by one initialize the new elem with d
    if(space==0)
        reserve(8); //start with space of 8 elements
    else if(space == sz) // no more space then get more space
        reserve(2*space);
    alloc.construct(&elem[sz], val);
    sz++; 
}

// To avoid the template linker error
template class vector<double>;


