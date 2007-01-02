#include "header.h"
#include "item.cpp"
#include "user.cpp"

int main()
{
    string search;
    while(true)
    {
        int choice = mainMenu();
        switch(choice)
        {
            case 1:     addUser(); break;
            case 2: {   
                        cout << "Enter username of person you want to modify: ";
                        cin >> search;
                        User* currUser = findUser(search);
                        if(currUser == NULL)
                            cout << "Could not find that username" << endl;
                        else
                            currUser->modData();
                        cout << endl;
                        break; 
                    }
            case 3: {
                        cout << "Enter the username of person you want to view: ";
                        cin >> search;
                        User* currUser = findUser(search);
                        if(currUser == NULL)
                            cout << "Could not find that user" << endl;
                        else
                            currUser->putData();
                        cout << endl;
                        break;
                    }
            case 4:     showAll(); break;
            case 5: {   string sellerName;
                        Seller* temp = new Seller;                // Used to distinguish size of Seller class
                        cout << "Enter sellers username: ";
                        cin >> sellerName;
                        User* currUser = findUser(sellerName);
                        if(currUser == NULL || currUser->getUserType() != 's')
                            cout << "Invalid username" << endl;
                        else
                            addItem(currUser); 
                        cout << endl;
                        break;
                    }
            case 6: {   // Bid on an item
                        int search;
                        cout << "What item number you would you like to bid on? ";
                        cin >> search;
                        Item* current = findItem(search);
                        if(current == NULL)
                            cout << "No item found" << endl;
                        else
                            current->bidItem();
                        break;
                    }
            case 7: {   // View all Items
                        list<Item*>::iterator i;
                        Item* current;

                        cout << endl;
                        if(I.empty())
                            cout << "There are no items to show!!" << endl;
                        else
                        {
                            for(i = I.begin(); i != I.end(); ++i) 
                            {
                                current = *i;
                                current->putItem();
                                cout << endl;
                            }
                        }
                        cout << endl;
                        break;
                    }
            case 8: {
                        string username;
                        cout << "Enter a users items to view: ";
                        cin >> username;
                        User* tempname = findUser(username);
                        if(tempname == NULL)
                            cout << "Invalid name entered" << endl;
                        else
                            tempname->showItems();
                        cout << endl;
                        break;
                    }
            case 9: {
                        int search;

                        cout << "Enter an item ID to remove: ";
                        cin >> search;
                        Item* current = findItem(search);
                        if(current == NULL)
                            cout << "Item not found" << endl;
                        else
                        {
                            User* tempUser = findUser(current->sellerName);
                            tempUser->delItem(current);
                            I.remove(current);              // Removes all instances of the item pointing
                                                            // that pointer
                        }

                    }
        }
    }
}

// Main menu, courtesy of yours truly :)
// I made it a separate function to help organize a little
// bit better so it wasn't so crowded.
int mainMenu()
{
    int choice = 0;

    while(true)
    {
        cout << "What would you like to do:" << endl;
        cout << "1. Create a user/seller" << endl;
        cout << "2. Modify user/seller information" << endl;
        cout << "3. Look-up a user/seller" << endl;
        cout << "4. View all users/sellers" << endl;
        cout << "5. Add an item" << endl;
        cout << "6. Bid on an item" << endl;
        cout << "7. View all items" << endl;
        cout << "8. View a users items" << endl;
        cout << "9. Remove an item" << endl;
        cout << "10. Quit" << endl;
        cout << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:     return 1; break;
            case 2:     return 2; break;
            case 3:     return 3; break;
            case 4:     return 4; break;
            case 5:     return 5; break;
            case 6:     return 6; break;
            case 7:     return 7; break;
            case 8:     return 8; break;
            case 9:     return 9; break;
            case 10:     exit(0);
            default:    cout << "Invalid choice! Try again" << endl;
        }
    }
}

