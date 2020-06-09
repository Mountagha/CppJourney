#include "List.h"

int main(){
    Link<string>* l = new Link<string>("B");
    l = l->insert(new Link<string>("A"));
    l = l->find("B");
    l = l->add(new Link<string>("C"));
    l = l->add(new Link<string>("E"));
    print_all(l);
    l = l->advance(-1);
    l = l->add(new Link<string>("D"));
    l = l->advance(1);
    l = l->add(new Link<string>("F"));
    print_all(l);
    l = l->advance(-2);
    l = l->erase();
    print_all(l);

    return 0;
}