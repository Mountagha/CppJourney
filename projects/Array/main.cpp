#include <iostream>
#include "Array.h"

int main(){

    Array<int, 10> a;
    Array<int, 20> b;
	Array<int, 8> c;

	std::cout << a.size() << '\n';
    a.fill(1, 4);
	std::cout << a.size() << '\n';
	//std::cout << a << '\n';
   	for(size_t i=0; i<a.size(); ++i) std::cout << a[i] << " ";
	std::cout << '\n';
	b.fill(2, 7);
	b.fusion(a);
   	for(size_t i=0; i<b.size(); ++i) std::cout << b[i] << " ";
	std::cout << '\n';
    // a.swap(b);
	a.subset(b,1,5);
   	for(size_t i=0; i<a.size(); ++i) std::cout << a[i] << " ";
	std::cout << '\n';
    return 0;
}
