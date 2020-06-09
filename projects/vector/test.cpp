#include "vector.h"
//#include <vector>
#include <iostream>

using namespace std;

void print_vector(vector<double> v){
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

void print_vector(vector<string> v){
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

int main(){
    /*vector<double> v;
    v.push_back(6);
    v.push_back(7);
    v.push_back(10);
    print_vector(v);
    v[0] = 2;
    print_vector(v);
    vector<double> v2 = v;
    v2[2] = 2.3;
    print_vector(v2);
    v2 = v;
    print_vector(v2); */
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
    return 0;

}