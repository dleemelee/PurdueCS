#include "DLList.h"

DLList::DLList()
{
    head = NULL;
}

DLList::~DLList()
{
    for();
}

void DLList::print()
{

}

void DLList::printSorted()
{

}

void DLList::insertFront(int data)
{
    DLNode * x = new DLNode();
    x->data = data;
    x->next = head->next;
    x->prev = head;
    x->next->prev = x;
    x->prev->next = x;
}

bool DLList::removeLast(int & data)
{
	return true;
}

DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	return diff;
}

DLList * DLList::getRange(int start, int end)
{
	return this;
}

DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	return  inter;
}

void DLList::removeRange(int start, int end)
{

}
