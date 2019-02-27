#include <iostream>
#include "ArrayList.h"

using namespace std;


int main() {
    cout<<"HELLO"<<endl;
    ArrayList<int> list1 = *(new ArrayList<int>());
    list1.add(0);
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list1.add(8);
    list1.add(7);
    list1.add(4);
    list1.add(2);
    list1.add(9);
    cout<<"JELLO"<<endl;
    list1.print();
    return 0;
}
