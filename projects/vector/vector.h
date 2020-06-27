#include <iostream>
//#include <memory>
#include <stdexcept>
#include "allocator.h"

using namespace std;

// class used to report range access error
struct Out_of_range {
    Out_of_range(const string& error_message="out of range error") {}
};

template<typename T, typename A=Allocator<T>>
class vector {
    A alloc;        // allocator to handle the reservation and the freeing of 
                    // unitiliazed memory
    unsigned int sz;        // the size of the vector
    T* elem;      // a pointer to the elements
    unsigned int space;   // number of elements plus "free space"/"slots"
                // for new elements ("the current allocation")
    
    public:

        class iterator; 

        using size_type = unsigned int;
        using value_type = T;
        //using iterator = T*;
        //using const_iterator = const T*;
        using ref_type = T&;
        using const_ref_type = const T&;
        

        vector(): sz{0}, elem{nullptr}, space{0} {}
        explicit vector(unsigned int s, T def=T()): sz{s}, elem{ alloc.allocate(s) }, space{sz} {
            for(int i=0; i<sz; i++)
                alloc.construct(&elem[i], def);
        }
        vector(initializer_list<T> lst): sz(lst.size()), elem{alloc.allocate(lst.size())}, space{sz} {
            copy(lst.begin(), lst.end(), elem);
        }
        
        vector(const vector&); // copy constructor
        vector& operator=(const vector&); // copy assignment
        vector(vector&& ); // move constructor
        vector& operator=(vector&& );
        ~vector() {
            for(int i=0; i<sz; i++) alloc.destroy(&elem[i]);
            alloc.deallocate(elem, sz);
        }

        size_type size() const { return sz; }
        iterator begin();
        const iterator begin() const;
        iterator end();
        const iterator end() const;
        const_ref_type front() const { return elem[0]; } // ref to the first elem
        const_ref_type back() const { return elem[sz-1]; } // ref to the last elem

        // unchecked range
        T& operator[](int n) { return elem[n]; }
        const T& operator[](int n) const { return elem[n]; }
        // checked range
        T& at(int n);
        const T& at(int n) const;

        int capacity() const { return space; }

        void reserve(int newalloc);
        void resize(int newsize, T def=T());
        void push_back(const T& val);

        iterator insert(iterator p, const T& val);
        iterator erase(iterator p);  

};

// helper functions
