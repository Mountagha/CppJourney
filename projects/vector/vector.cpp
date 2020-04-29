#include "vector.h"

vector::vector(): sz{0}, elem{nullptr}, space{0} {}

vector::vector(int s): sz{s}, elem{new double[s]}, space{sz} {
    for(int i=0; i<sz; i++)
        elem[i] = 0; //initialize elements
}

// copy constructor
vector::vector(const vector& v): sz{v.size()}, elem{new double[v.size()]}{
    //copy(v, v+sz, elem);
    for(int i=0; i<sz; i++){
        elem[i] = v.elem[i];
    }
}

// copy assignment
vector& vector::operator=(const vector& v){
    // make this vector a copy of v

    if(this==&v) return *this;  // self assignment, no work needed
    if(v.size()<=space){          // enough space no need for allocation just copy
        for(int i=0; i<v.size(); i++)
            elem[i] = v.elem[i];
        sz = v.size();
        return *this;
    } 
    double *p = new double[v.size()];
    for(int i=0; i<v.size(); i++) p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = sz = v.size();
    return *this;
}

// move 
vector::vector(vector&& v): sz{v.sz}, elem{v.elem} {
    v.sz = 0;
    v.elem = nullptr;
} 
vector& vector::operator=(vector&& v){
    //move v to this vector
    delete [] elem;
    elem = v.elem;
    sz = v.sz;
    v.elem = nullptr;
    v.sz = 0;
    return *this;
}

void vector::reserve(int newalloc){
    if(newalloc<=space) return; // never decrease allocation
    double *p = new double[newalloc];
    for(int i=0; i<sz; i++) p[i] = elem[i];
    delete [] elem;
    elem = p;
    space = newalloc;
}

void vector::resize(int newsize){
    reserve(newsize);
    for(int i=sz; i<newsize; i++) elem[i]=0; //initialize new elmts
    sz = newsize;
}

void vector::push_back(double d){
    //increase vector size by one initialize the new elem with d
    if(space==0)
        reserve(8); //start with space of 8 elements
    else if(space == sz) // no more space then get more space
        reserve(2*space);
    elem[sz] = d;
    sz++; 
}


ostream& operator<<(ostream& os, const vector& v){
    for(int i=0; i<v.size(); i++){
        os << v[i] << " ";
    }
    os << "\n";
    return os;
}



