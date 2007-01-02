#include <iostream>
#include <fstream>
#include <string>
#include "binarySearchTree.h"

using namespace std;

int main()
{
    bSearchTreeType<string> btree;

    ifstream infile;
    infile.open("data.dat");
    if(infile.fail())
        cout << "Data file not present" << endl;
    else
    {
        while(!infile.eof())
        {
            string name;
            string desc;
            getline(infile,name,' ');
            getline(infile,desc);

            btree.insert(name,desc);
        }
    }

    infile.close();

    int choice = 0;
    while(choice != 4)
    {
        string name;
        string desc;
        cout << "1.  Add an item to the dictionary." << endl
             << "2.  Remove an item from the dictionary." << endl
             << "3.  Lookup definition / description" << endl
             << "4.  Quit" << endl;
        cout << "Choice: "; cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Enter dictionary name: ";
                cin >> name;
                cout << "Enter dictionary definition: ";
                cin.ignore();
                getline(cin,desc);
                btree.insert(name,desc);
                break;

            case 2:
                cout << "Enter the item you want to delete: ";
                cin >> name;
                btree.deleteNode(name);
                break;

            case 3:
                cout << "Enter an item to lookup: ";
                cin >> name;
                btree.search(name);
                break;
            case 4:
                cout << "Quitting";
                break;

//            case 5:
//                btree.inorderTraversal(); // Testing only
//                break;
            default:    cout << "Invalid choice, try again" << endl; break;
        }
        cout << endl;
    }

    return 0;
}
