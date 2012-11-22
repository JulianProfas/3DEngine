#include "List.h"
using namespace std;

List::List():root(NULL),size(0)
{}

void List::addToRoot(const string& name)
{
	ListElement* newOne = new ListElement(name);

	if(root == 0)
	{
		root = newOne;
	}
	else
	{
		newOne->next = root;
		root = newOne;
	}
	size++;
}

void List::printList()
{
	ListElement* temporaryPointer = root;

	while(temporaryPointer != NULL)
	{
		cout << *temporaryPointer << endl;
		temporaryPointer = temporaryPointer->next;
	} 
}