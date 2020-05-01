#include "vector.h"

// copy constructor
template<typename T>
vector<T>::vector(const vector& v): sz{v.size()}, elem{new T[v.size()]}{
    //copy(v, v+sz, elem);
    for(int i=0; i<sz; i++){
        elem[i] = v.elem[i];
    }
}

// copy assignment
template<typename T>
vector<T>& vector<T>::operator=(const vector& v){
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
template<typename T>
vector<T>::vector(vector&& v): sz{v.sz}, elem{v.elem} {
    v.sz = 0;
    v.elem = nullptr;
} 

template<typename T>
vector<T>& vector<T>::operator=(vector&& v){
    //move v to this vector
    delete [] elem;
    elem = v.elem;
    sz = v.sz;
    v.elem = nullptr;
    v.sz = 0;
    return *this;
}

template<typename T>
void vector<T>::reserve(int newalloc){
    if(newalloc<=space) return; // never decrease allocation
    T *p = new T[newalloc];
    for(int i=0; i<sz; i++) p[i] = elem[i];
    delete [] elem;
    elem = p;
    space = newalloc;
}

template<typename T>
void vector<T>::resize(int newsize){
    reserve(newsize);
    for(int i=sz; i<newsize; i++) elem[i]=0; //initialize new elmts
    sz = newsize;
}

template<typename T>
void vector<T>::push_back(T d){
    //increase vector size by one initialize the new elem with d
    if(space==0)
        reserve(8); //start with space of 8 elements
    else if(space == sz) // no more space then get more space
        reserve(2*space);
    elem[sz] = d;
    sz++; 
}

// To avoid the template linker error
template class vector<double>;


