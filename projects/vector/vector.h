#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

// class used to report range access error
struct Out_of_range {
    Out_of_range(const string& error_message="out of range error") {}
};

template<typename T, typename A=allocator<T>>
class vector {
    A alloc;        // allocator to handle the reservation and the freeing of 
                    // unitiliazed memory
    int sz;        // the size of the vector
    T *elem;      // a pointer to the elements
    int space;   // number of elements plus "free space"/"slots"
                // for new elements ("the current allocation")
    
    public:
        vector(): sz{0}, elem{nullptr}, space{0} {}
        explicit vector(int s, T def=T()): sz{s}, elem{ alloc.allocate(s) }, space{sz} {
            for(int i=0; i<sz; i++)
                alloc.construct(&elem[i], def);
                //elem[i] = 0; //initialize elements
        }
        vector(const vector&); // copy constructor
        vector& operator=(const vector&); // copy assignment
        vector(vector&& ); // move constructor
        vector& operator=(vector&& );
        //~vector() { delete [] elem; }
        ~vector() {
            for(int i=0; i<sz; i++) alloc.destroy(&elem[i]);
            alloc.deallocate(elem, sz);
        }

        int size() const { return sz; }

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

};

// helper functions