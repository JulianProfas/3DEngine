#include "ListElement.h"

class List
{
public:
	List();
	void addToRoot(const std::string&);
	void printList();

private:
	ListElement* root;
	int size;
};