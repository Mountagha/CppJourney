#include "vector.h"
#include <string>

template<typename T, typename A>
class vector<T, A>::iterator {
    private:
        T* curr;
    public:
        iterator(T* curr_elem): curr{curr_elem} {}
        iterator& operator++() { curr++; return *this; }
        iterator& operator--() { curr--; return *this; }
        iterator& operator+(int n){ curr += n; return *this; }
        iterator& operator-(int n){ curr -= n; return *this; }
        T& operator*() { return *curr; }
        T& operator[](int n) { return curr[n]; }
        const T& operator[](int n) const { return curr[n]; }
        friend bool operator==(const iterator&a, const iterator& b){
            return a.curr == b.curr;
        }
        friend bool operator!=(const iterator&a, const iterator& b){
            return a.curr != b.curr;
        }
        friend int operator-(const iterator&a, const iterator& b){
            return a.curr - b.curr;
        }

};


template<typename T, typename A>
typename vector<T, A>::iterator vector<T,A>::begin() { return iterator(elem); }

template<typename T, typename A>
typename vector<T, A>::iterator vector<T,A>::end() { return iterator(elem+sz); }

template<typename T, typename A>
const typename vector<T, A>::iterator vector<T,A>::begin() const { return iterator(elem); }

template<typename T, typename A>
const typename vector<T, A>::iterator vector<T,A>::end() const { return iterator(elem+sz); }

// copy constructor
template<typename T, typename A>
vector<T,A>::vector(const vector& v): sz{v.size()}, elem{alloc.allocate(v.size())}{
    //copy(v, v+sz, elem);
    for(int i=0; i<sz; i++){
        alloc.construct(&elem[i], v.elem[i]);
        //elem[i] = v.elem[i];
    }
}

// copy assignment
template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector& v){
    // make this vector a copy of v

    if(this==&v) return *this;  // self assignment, no work needed
    if(v.size()<=space){          // enough space no need for allocation just copy
        for(int i=0; i<v.size(); i++)
            alloc.construct(&elem[i], v.elem[i]); // elem[i] = v.elem[i];
        sz = v.size();
        return *this;
    } 
    T *p = alloc.allocate(v.size()); //new T[v.size()];
    for(int i=0; i<v.size(); i++) alloc.construct(&p[i], v.elem[i]); //p[i] = elem[i];
    for(int i=0; i<sz; i++) alloc.destroy(&elem[i]);
    alloc.deallocate(elem, sz);
    //delete[] elem;
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

template<typename T, typename A>
T& vector<T, A>::at(int n) {
    if(n<0||sz<=n) throw Out_of_range();
    return elem[n];
}

template<typename T, typename A>
const T& vector<T, A>::at(int n) const {
    if(n<0||sz<=n) throw Out_of_range();
    return elem[n];
}


template<typename T, typename A>
typename vector<T, A>::iterator vector<T,A>::erase(iterator p){
    if(p==end()) return p;
    for(auto pos=p+1; pos!=end(); ++p)
        *(pos-1) = *pos;        // copy element "one position to the left"
    alloc.destroy(&*(end()-1)); // destroy surplus copy of last element
    --sz;
    return p;
}

template<typename T, typename A>
typename vector<T, A>::iterator vector<T, A>::insert(iterator p, const T& val){
    int index = p-begin();
    if(size()==capacity()) 
        reserve(size()==0?8:size()*2); // make sure we have enough space
    //first copy last element into unitialized space
    alloc.construct(elem+sz, back());
    ++sz;

    iterator pp = begin()+index; // the place to put val
    for(auto pos=end()-1; pos!=pp; --pos)
        *pos = *(pos-1);
    *(begin()+index) = val;       // insert val
    return pp;

}

// To avoid the template linker error
template class vector<string>;

/******************************************************************************
 * Testing
 */

void print_vector(vector<string> v){
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

int main(){
   
    vector<string> vs;
    vs.push_back("mamadou");
    vs.push_back("mountagha");
    vs.push_back("bah");
    print_vector(vs);

    auto it = vs.insert(vs.begin()+1, "Elhadj");
    print_vector(vs);

    vector<string> vs2;
    vs2.resize(2);
    vs2 = vs;
    print_vector(vs2);
    vs2.push_back("Sow");
    print_vector(vs2); 
    cout << vs2.front() << "\n";
    cout << vs2.back() << "\n";
    auto it2 = vs2.erase(vs2.end()-1);
    print_vector(vs2);

    /****************************/
    vector<string> v_str;
    v_str.push_back("ab");
    v_str.push_back("cd");
    v_str.push_back("ef");
    v_str.push_back("gh");
    
    auto it3 = v_str.begin();
    cout << *it3 << "\n";
    ++it3;
    cout << *it3 << "\n";
    it3 = it3 + 2;
    cout << *it3 << "\n";
    it3 = it3 - 2;
    cout << it3[1] << "\n";
    it3[1] = "efi";
    cout << it3[1] << "\n";
    auto it_a=v_str.begin(), it_b=v_str.begin();
    cout << (it_a == it_b) << "\n";
    it_b = v_str.end();
    cout << it_a - it_b << "\n";

    for(auto it=v_str.begin(); it != v_str.end(); ++it)
        cout << *it << " ";
    cout << "\n";
    return 0;

}