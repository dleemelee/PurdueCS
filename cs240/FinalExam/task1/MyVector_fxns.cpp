/*******************************************************
 * For the detailed Task description, go to MyVector.h *
 *******************************************************/
 
 
#include <iostream>
#include "MyVector.h"
#include "MyException.h"
 
unsigned int MyVector::get_size() const{
    return vector_size;
}
 
bool MyVector::get_num_at_idx(unsigned int index, int *ptr_num) const throw(MyException){
    if(index < 0 || index >= vector_size){
	throw MyException();
    }
    *(ptr_num) = data[index];
    return true;
}
 
bool MyVector::set_num_at_idx(unsigned int index, int value){
    if(index < 0 || index >= vector_size){
	throw MyException();
    }
    data[index] = value;
    return true;
}
