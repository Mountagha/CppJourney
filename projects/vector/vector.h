#include <iostream>

using namespace std;

class vector {
    int sz;        // the size of the vector
    double *elem;  // a pointer to the elements
    int space;   // number of elements plus "free space"/"slots"
                // for new elements ("the current allocation")
    
    public:
        vector();
        explicit vector(int s);
        vector(const vector&); // copy constructor
        vector& operator=(const vector&); // copy assignment
        vector(vector&& ); // move constructor
        vector& operator=(vector&& );
        ~vector() { delete [] elem; } 

        int size() const { return sz; }
        double& operator[](int n) { return elem[n]; }
        double operator[](int n) const { return elem[n]; }
        int capacity() const { return space; }

        void reserve(int newalloc);
        void resize(int newsize);
        void push_back(double d);  

};

// helper functions
ostream& operator<<(ostream& os, const vector& v);