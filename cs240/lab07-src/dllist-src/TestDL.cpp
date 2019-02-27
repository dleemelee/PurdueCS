#include <iostream>
#include "DLList.h"

using namespace std;

int main(){
    DLList list1 = DLList();
    list1.insertFront(0);
    list1.insertFront(6);
    list1.insertFront(5);
    list1.insertFront(2);
    list1.insertFront(1);
    list1.insertFront(7);
    list1.insertFront(6);
    list1.insertFront(7);
    list1.insertFront(8);
    list1.insertFront(9);
    list1.insertFront(10);
    list1.print();
    cout<<"3 2 1 0-------------------------------------------"<<endl;
    int data;
    list1.removeLast(data);
    list1.removeLast(data);
    list1.print();
    cout<<"3 2-----------------------------------------------"<<endl;
    list1.removeRange(2,4);
    list1.printSorted();
    cout<<"-----------------------------------------------"<<endl;
    DLList list2 = DLList();
    list2.insertFront(1);
    list2.insertFront(2);
    list2.insertFront(3);
    list2.insertFront(4);
    list2.insertFront(5);
    list2.insertFront(6);
    list2.insertFront(7);
    list2.insertFront(8);
    list2.insertFront(9);
    list2.insertFront(10);
   /* DLList* listInt = list1.intersection(list2);
    listInt->print();
    cout<<"--------------------------------------------"<<endl;
    DLList* listGetRange = list2.getRange(1,5);
    listGetRange->print();
    cout<<"----------------------------------------------"<<endl;
    DLList* listGetDifference = list2.difference(*listInt);
    listGetDifference->print();*/
    list1.~DLList();
    list2.~DLList();
    
    return 0;
}
