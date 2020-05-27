#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Allocator{
    public:
        Allocator() {}
        ~Allocator() {}

        template<typename U>
        struct rebind { using other = Allocator<U>; };

        T* allocate(int n){  // allocate space for n objects of type T
            return reinterpret_cast<T*>(malloc(n*sizeof(T)));
        } 
        void deallocate(T* p, int n) { // deallocate n objects of type T starting at p
            free(reinterpret_cast<T*>(p));
        } 

        void construct(T* p, const T& v){ // construct a T with the value in p
            new(p) T(v);
        } 
        void destroy(T* p){ // destroy the T in p
            p->~T();
        }         
};