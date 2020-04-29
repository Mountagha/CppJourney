//#include "vector.h"
#include <vector>
#include <iostream>

using namespace std; 
void print_vector(vector<double> v){
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

int main(){
    vector<double> v;
    v.push_back(6);
    v.push_back(7);
    v.push_back(10);
    //cout << v;
    print_vector(v);
    v[0] = 2;
    //cout << v;
    print_vector(v);
    vector<double> v2 = v;
    v2[2] = 2.3;
    //cout << v2;
    print_vector(v2);
    v2 = v;
    //cout << v2;
    print_vector(v2);
    return 0;
}