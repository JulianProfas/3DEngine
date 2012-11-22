#include "ListElement.h"

using namespace std;

ListElement::ListElement(string n):name(n), next(NULL)
{}

ostream& operator<<(ostream& os, const ListElement& l)
{
	return os << "Name: " << l.name;
}