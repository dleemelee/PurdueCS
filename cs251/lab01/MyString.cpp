
// CS251 Data Structures
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include <string.h>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
  //TODO
  
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
  //TODO
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
  //TODO
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  //TODO
}

// Create a MyString with an empty string
MyString::MyString()
{
  //TODO
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  //TODO
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  //TODO
}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
  //TODO
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
  //TODO
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
  //TODO
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
  //TODO
}

// Return true if string "this" and s is less or equal
bool
MyString::operator > (const MyString &s)
{
  //TODO
}

// Return character at position i
char
MyString::operator [] (int i)
{
  //TODO
}

// Return C representation of string
const char *
MyString::cStr()
{
  //TODO
}

// Get string length of this string.
int
MyString::length() const
{
  //TODO
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  //TODO
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
  //TODO
}

/* Break a string into substrings of letters, e.g "A dog and a hyper-sphere"
breaks into <"A", "dog", "and", "a", "hyper", "sphere">.  The input is a string
and the output is a vector of strings. */
std::vector<MyString> words (MyString s) {
  //TODO
}

/*
Convert a roman numberal into a number, e.g. "CLXIV" converts to 164.  The
input is a roman numeral expressed as a string whose characters are "I", "V",
"X", "L", and "C".  The output is a positive integer.
*/
unsigned int roman (MyString s) {
  //TODO
  return 0;
}

