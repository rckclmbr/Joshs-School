#include <iostream>
using namespace std;

struct link {
	int data;
	link *next;
};

class linklist {
	private:
		link *first;
		link *last;
	public:
		linklist() : first(NULL), last(NULL) { }	// first allocated with a null in it.
		void display();
		void additem(int);
};

int main() {
	linklist mylink;
	mylink.additem(44);
	mylink.additem(77);
	mylink.additem(22);

	mylink.display();
}

void linklist::display()
{
	link *current = first;
	while(current != NULL)		// Keep us in the loop until we reach the end
	{
		cout << current->data << endl;
		current = current->next;
	}
	cout << "first: " << first->data << endl;
	cout << "last: " << last->data << endl;
}

void linklist::additem(int D)
{
	link *newlink;
	link *current;
	newlink = new link;	// newlink = memory address 8000.

	newlink->data = D;	// Insert into memory address 8000 value D
	newlink->next = NULL;

	// If there's no data in there
	if(first == NULL)
		first = newlink;
	// Otherwise, we keep going
	else
	{
		last = first;
		while (last->next != NULL)
			last = last->next;
		last->next = newlink;
	}
}
