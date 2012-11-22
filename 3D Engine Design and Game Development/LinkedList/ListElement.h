#include <iostream>
#include <string>

class ListElement
{
	friend std::ostream& operator<<(std::ostream& os, const ListElement& l);
	friend class List;

public:
	ListElement(std::string name = "none");

private:
	std::string name;
	ListElement* next;
};