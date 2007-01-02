#include "header.h"

int main()
{
    srand(time(NULL));

    cout << "Vector:" << endl << endl;
    insertVector(0);    // Insert at start
    insertVector(1);    // Insert at middle
    insertVector(2);    // Insert at end
    deleteVector(0);    // Removes at first
    deleteVector(1);
    deleteVector(2);
    walkVector(0);
    walkVector(1);

    cout << endl;

    cout << "Deque:" << endl << endl;
    insertDeque(0);    // Insert at start
    insertDeque(1);    // Insert at middle
    insertDeque(2);    // Insert at end
    deleteDeque(0);    // Removes at first
    deleteDeque(1);
    deleteDeque(2);
    walkDeque(0);
    walkDeque(1);

    // START OF ASSIGNMENT 4

	linkedListType<int> *temp1;
	temp1 = new linkedListType<int>;

	timer t1;

	cout << endl << "Linked List" << endl;
	t1.start();
	for(int c = 0; c<=5000; c++)
			temp1->insertLast(rand() % 512);
	t1.stop();

	t1.start();
	temp1->insertFirst(1);	// Insert at first
	temp1->insertFirst(2);	// Insert at first
	temp1->insertFirst(3);	// Insert at first
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Insertion at first: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
	// Test to see if it was inserted correctly
	if(temp1->getType(0) != 3)	// It should equal 3
		cout << "There was an error" << endl;

	t1.start();
	temp1->insertMiddle(13);	// Insert at middle
	temp1->insertMiddle(14);	// Insert at middle
	temp1->insertMiddle(15);	// Insert at middle
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Insertion at middle: " << setw(7) << resetiosflags(ios::left) <<  t1.putTime() << endl;
	// Test to see if it was inserted correctly
	// ... the middle should be 15
	if(temp1->getType((temp1->length() / 2)) != 15)
		cout << "There was an error!" << endl;


	t1.start();
	temp1->insertLast(20);		// Insert at last
	temp1->insertLast(21);		// Insert at last
	temp1->insertLast(22);		// Insert at last
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Insertion at last: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
	// Test the insertion
	if(temp1->getType(temp1->length() - 1) != 22)
	{
		cout << "There was an error!" << endl;
	}

	t1.start();
	temp1->deleteLocation(0);	// Removal at first
	temp1->deleteLocation(0);	// Removal at first
	temp1->deleteLocation(0);	// Removal at first
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Removal at first: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
	// Test the removal
	// it cannot be 3, because that's what was there before
	if(temp1->getType(temp1->length()) == 3)
		cout << "There was an error!" << endl;

	t1.start();
	temp1->deleteLocation(temp1->length() / 2);	// Removal at middle
	temp1->deleteLocation(temp1->length() / 2);	// Removal at middle
	temp1->deleteLocation(temp1->length() / 2);	// Removal at middle
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Removal at middle: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;

	t1.start();
	temp1->deleteLocation(temp1->length());	// Removal at end
	temp1->deleteLocation(temp1->length());	// Removal at end
	temp1->deleteLocation(temp1->length());	// Removal at end
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Removal at end: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
	// Test the removal
	// It shouldn't equal 22, because that's what was there
	if(temp1->getType(temp1->length()) == 22)
		cout << "There was an error" << endl;

// Walk forwards	
	t1.start();
	for(int temp = 0; temp < temp1->length(); temp++)
		// cout << temp << ": " << temp1->getType(temp) << endl;
		int x = temp1->getType(temp);	// Clean up output a bit
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Walk forwards: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
	
// Walk backwards
	t1.start();
	temp1->reverseList();
	for(int temp = 0; temp < temp1->length(); temp++)
		// cout << temp << ": " << temp1->getType(temp) << endl;
		int x = temp1->getType(temp); // clean up output
	t1.stop();
	cout << setw(25) << setiosflags(ios::left) << "Walk backwards: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;


    return(0);
}
