#include "vector.h"

vector::vector(): sz{0}, elem{nullptr} {}

vector::vector(int s): sz{s}, elem{new double[s]} {
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
    double *p = new double[v.size()];
    copy(v.elem, v.elem+v.size(), p);
    delete[] elem;
    elem = p;
    sz = v.size();
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

ostream& operator<<(ostream& os, const vector& v){
    for(int i=0; i<v.size(); i++){
        os << v[i] << " ";
    }
    os << "\n";
    return os;
}



