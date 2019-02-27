/*******************************************************
 * For the detailed Task description, go to MyVector.h *
 *******************************************************/

 #include "MyVector.h"
 #include "MyException.h"
#include <iostream>
 MyVector &
 MyVector::operator=(const MyVector & v){
    delete[] data;
    vector_size = v.vector_size;
    data = new int[vector_size];
    for(unsigned int i = 0 ; i < vector_size; i++){
	data[i] = v.data[i];
    }
    return *this;
 }
MyVector&
MyVector::operator*(const int s){
    MyVector* temp  = new MyVector();
    temp->vector_size = this->vector_size;
    temp->data = new int[temp->vector_size];
    for(unsigned int i = 0 ; i < vector_size;i++) {
	temp->data[i]*=s;
    }
    return *temp;
}


MyVector& 
friend MyVector::operator*(MyVector& v){
    if(vector_size != v.vector_size){
	throw MyException();
    }
    MyVector* temp = new MyVector();
    temp->vector_size = this->vector_size;
    temp->data = new int[temp->vector_size];
    for(unsigned int i = 0 ; i < temp->vector_size; i++){
	temp->data[i] = this->data[i]* v.data[i];
    }
    return *temp;
 }

MyVector& operator*(const int s, const MyVector& v){
     MyVector* temp  = new MyVector();
         temp->vector_size = v.vector_size;
	     temp->data = new int[temp->vector_size];
	         for(unsigned int i = 0 ; i < v.vector_size;i++) {
		         temp->data[i]*=s;
			     }
			         return *temp;

 }
