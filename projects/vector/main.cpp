#include "vector.h"

int main(){
    vector v(5);
    v[0] =  2.2;
    v[1] = 1.2;
    cout << v;
    vector v2 = v;
    v2[3] = 2.3;
    cout << v2;
    v2 = v;
    cout << v2;
    return 0;
}