#include <iostream>

using namespace std;

template<typename T>
class vector {
    int sz;        // the size of the vector
    T *elem;      // a pointer to the elements
    int space;   // number of elements plus "free space"/"slots"
                // for new elements ("the current allocation")
    
    public:
        vector(): sz{0}, elem{nullptr}, space{0} {}
        explicit vector(int s): sz{s}, elem{new T[s]}, space{sz} {
            for(int i=0; i<sz; i++)
                elem[i] = 0; //initialize elements
        }
        vector(const vector&); // copy constructor
        vector& operator=(const vector&); // copy assignment
        vector(vector&& ); // move constructor
        vector& operator=(vector&& );
        ~vector() { delete [] elem; } 

        int size() const { return sz; }
        T& operator[](int n) { return elem[n]; }
        const T& operator[](int n) const { return elem[n]; }
        int capacity() const { return space; }

        void reserve(int newalloc);
        void resize(int newsize);
        void push_back(T d);  

};

// helper functions