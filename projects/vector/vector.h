#include <iostream>

using namespace std;

class vector {
    int sz;        // the size of the vector
    double *elem;  // a pointer to the elements
    
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

};

// helper functions
ostream& operator<<(ostream& os, const vector& v);