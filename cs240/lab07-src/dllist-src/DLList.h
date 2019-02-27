#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>
#include <algorithm>

struct DLNode {
	int data;
	DLNode * next;
	DLNode * prev;
};

class DLList {
public:
	DLList();
	~DLList();
	void print();
	void printSorted();

	void insertFront(int data);
	bool removeLast(int & data);
	DLList * difference(DLList & rhs);
	DLList * getRange(int start, int end);
	DLList * intersection(DLList & rhs);
	void removeRange(int start, int end);
	/**
	 * @brief      This operator does insert front.
	 * 
	 * Please, please, please do not remove it or change it.
	 * This is for testing purposes only.
	 *
	 * @param[in]  data  Thing to insert front.
	 *
	 * @return     Returns a reference to this.
	 */
	DLList & operator << (int data) {
		this->insertFront(data);
		return *this;
	}

	/**
	 * Difference operator
	 * 
	 * Please, please, please do not remove or change this code.
	 * This is for testing purposes only.
	 *
	 * Params:
	 *       rhs - List to remove.
	 *
	 * @return     *this - 
	 */
	DLList & operator - (DLList & rhs) {
		return *difference(rhs);
	}

private:
	DLNode * head;
};
#endif
