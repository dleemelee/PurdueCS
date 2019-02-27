#include <iostream>
#include <algorithm>
#include <vector>

struct Product{
	int data;
	float cost;
};

class Employee {
public:
	Employee(int id, char* name, double salary);
	~Employee();
	
	virtual void print() const;
	virtual double valueOf()=0 const;

protected:
	int Id;
	char* Name;
	double Salary;
};



class Manager: public Employee
{
	public:
	Manager(int id, char* name, double salary);
	~Manager();

	bool addEmployeeToManage(const Engineer&);
	bool stopManagingEmployee(const Employee&);
	
	virtual void print() const;
	virtual double valueOf() const;

protected:
	Engineer* Engineers;
	int num_engineers;
};


class Engineer: public Employee
{
	public:
	Engineer(int id, char* name, double salary);
	~Engineer();

	bool addProject(const Product&);
	bool removeProject(const Product&);

	
	virtual void print() const;
	virtual double valueOf() const;

protected:
	Product* Products;
	int num_products;
};