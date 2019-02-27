#ifndef ENGINEER_H
#define ENGINEER_H

#include <iostream>
#include <algorithm>
#include <vector>

#include "../arraylist-src/ArrayList.h"
#include "Employee.h"

struct Product{
	int data;
	float cost;
};

class Engineer: public Employee
{
public:
	Engineer(int id, char* name, double salary);

	bool addProduct(const Product& product);
	bool removeProduct(const Product& product);

	void print();
	double valueOf();

protected:
	ArrayList<Product> Products;
};

#endif
