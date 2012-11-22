#include "List.h"
using namespace std;

int main()
{
	List* myContactList = new List();

	string name;

	while(true)
	{
		cout << "Enter the name of the contact or q to quit." << endl;
		cin >> name;
		if (name == "q")
		{
			break;
		}
		else
		{
			myContactList->addToRoot(name);
		}
		myContactList->printList();
	}
}