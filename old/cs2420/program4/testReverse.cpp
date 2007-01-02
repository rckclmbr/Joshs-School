// This program tests the output of the reverseList() function

#include "header.h"


int main()
{
	linkedListType<int> *temp1;
	temp1 = new linkedListType<int>;
	
	// Create a list, easily numbered
	temp1->insertLast(1);
	temp1->insertLast(2);
	temp1->insertLast(3);
	temp1->insertLast(4);
	temp1->insertLast(5);

	// Display the list
	cout << "Forward List: " << endl;
	cout << "first: " << temp1->putFirst() << endl;
	cout << "last: " << temp1->putLast() << endl;
	for(int temp = 0; temp < temp1->length(); temp++)
		cout << temp << ": " << temp1->getType(temp) << endl;

	// Reverse the list
	temp1->reverseList();
	cout << endl << endl;

	// Display the list again, reversed
	cout << "Reverse list: " << endl;
	cout << "first: " << temp1->putFirst() << endl;
	cout << "last: " << temp1->putLast() << endl;
	for(int temp = 0; temp < temp1->length(); temp++)
		cout << temp << ": " << temp1->getType(temp) << endl;

	return 0;

}
