//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #8
//			Mr. Hart
//			Due:  11/14/05
// -----------------------------------------------------
// Creates a linked list of members, retrieves data from
// a file on startup, and also able to add data manually
// -----------------------------------------------------


// Compiler directives
#include <iostream>
#include <fstream>
#include <iomanip>	// for manipulators
using namespace std;

int menu(void);
void error(int);

struct NodeType
{
	long Id_Num;        // Member ID Number (primary)
	string Name;        // Members name
	string Phone;       // Members phone number
	char Status;        // Male or Female (M or F)
	float Income;       // Income of member
	NodeType *Next;		// Pointer to the next NodeType
};

class Nodes
{
	private:
        NodeType *first;
        NodeType *last;
        NodeType* search(unsigned int search);
	public:
        Nodes() : first(NULL), last(NULL) { }
        void get_datafile();
        void add_member();
        void rm_member();
        void disp_member();
        void dispall_members();
};

int main()
{
    Nodes mynode;
    int choice = 0;

    mynode.get_datafile();

    // I separated the actual menu from the choices for ease of
    // editability/readability
    while(choice != 5)
    {
        choice = menu();

        if(choice == 1)
            mynode.add_member();
        else if(choice == 2)
            mynode.rm_member();
        else if(choice == 3)
            mynode.disp_member();
        else if(choice == 4)
            mynode.dispall_members();
    }
    return 0;

}

int menu()
{
    int choice;

    cout << "Menu" << endl;
    cout << "1. Add a member" << endl;
    cout << "2. Remove a member" << endl;
    cout << "3. Display a member" << endl;
    cout << "4. Display all members" << endl;
    cout << "5. Quit" << endl;
    cout << "> ";
    cin >> choice;
    
    switch(choice)
    {
        case 1:     return 1;   break;
        case 2:     return 2;   break;
        case 3:     return 3;   break;
        case 4:     return 4;   break;
        case 5:     exit(0);
        default:    error(1);   break;
    }
}

// Searches for a record based on Id_Num, and returns the pointer
// to that node
NodeType* Nodes::search(unsigned int search)
{
    NodeType *current = first;

    while(current != NULL)
    {
        if(current->Id_Num == search)
            return current;
        else
            current = current->Next;
    }
    return NULL;
}

void Nodes::get_datafile()
{
    NodeType *newmember;
    ifstream infile;

    infile.open("member.dat");

    while( !infile.eof() )          // Keep us in loop until EOF
    {
        newmember = new NodeType;
        infile >> newmember->Id_Num;
        infile >> newmember->Name;
        infile >> newmember->Phone;
        infile >> newmember->Status;
        infile >> newmember->Income;
        //infile.ignore(80);
        
        if(!infile.eof())           // Don't update linked list if EOF
        {
            if(first == NULL)
               first = newmember;
            else
            {
                last = first;
                while(last->Next != NULL)
                    last = last->Next;
                last->Next = newmember;
            }
        }
    }

    infile.close();

}
void Nodes::add_member()
{
    NodeType *newmember;
    NodeType *current;
    newmember = new NodeType;
   
    // Retrieve and check ID number.  If it matches,
    // then continue.  If not, asks to re-enter.
    cout << "\n Add a Member" << endl;
    cout << "Id Number> ";
    cin >> newmember->Id_Num;
    if(search(newmember->Id_Num) != NULL)
       error(2);
    else
    {
        // Get the rest of the data
        cout << "Name> ";
        cin >> newmember->Name;
        cout << "Phone> ";
        cin >> newmember->Phone;
        cout << "Status (M or F)> ";
        cin >> newmember->Status;
        cout << "Income> ";
        cin >> newmember->Income;

        // Update the linked list
        if(first == NULL)
            first = newmember;
        else
        {
            last = first;
            while(last->Next != NULL)
                last = last->Next;
            last->Next = newmember;
        }
    }
}

void Nodes::disp_member()
{
    unsigned int dispid;
    NodeType *current = NULL;

    cout << "Enter member Id for display> ";
    cin >> dispid;
    
    current = search(dispid);

    if(current == NULL)
        error(4);
    else
    {
        cout << "Id Number: " << current->Id_Num << endl;
        cout << "Name:      " << current->Name << endl;
        cout << "Phone:     " << current->Phone << endl;
        cout << "Status:    " << current->Status << endl;
        cout << "Income:    " << current->Income << endl;
        cout << endl;
    }
}

// Removes a member from the linked list
void Nodes::rm_member()
{
    unsigned int tempid;
    NodeType *prev = NULL;
    NodeType *current = first;

    cout << "Enter a member Id to remove> ";
    cin >> tempid;
    
    // Cannot use the search utility, as we need the previous value as well
    while(current != NULL)
    {
        if(tempid == current->Id_Num)
        {
            if(prev == NULL)
                first = current->Next;
            else
                prev->Next = current->Next; // The previous node equals the
                                            // next node, removing the node
            break;
        }
        else
        {
            prev = current;
            current = current->Next;
        }
    }

    if(current == NULL)
        error(3);
}

// Displays all member data to the screen
void Nodes::dispall_members()
{
    NodeType *current = first;

    cout << endl << endl;
    while(current != NULL)
    {   
        cout << "Id Number: " << current->Id_Num << endl;
        cout << "Name:      " << current->Name << endl;
        cout << "Phone:     " << current->Phone << endl;
        cout << "Status:    " << current->Status << endl;
        cout << "Income:    " << current->Income << endl;
        cout << endl;
        current = current->Next;
    }
}

// List of errors that can happen
void error(int error_code)
{
    switch(error_code)
    {
        case 1: cout << "Invalid menu option\n\n"; break;
        case 2: cout << "Member already exists\n"; break;
        case 3: cout << "Member does not exist\n\n"; break;
        case 4: cout << "Cannot display member (doesn't exist)\n\n";
                break;
        default:    cout << "An error occured\n\n";
    }
}
