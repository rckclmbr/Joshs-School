#include <iostream>
#include <string>
#include <list>
using namespace std;


////////////////////////////////////////////////
// Class declarations                         //
////////////////////////////////////////////////

// User class is in user.cpp
class User {
    protected:
        string userName;
        string userRealName;        // e.g. "Josh Braegger"
        string userPass;
        string userEmail;
        char userType;        // User unless Seller
    public:
        virtual void getData(void);
        virtual void putData(void);
        virtual void modData(void);
        void changeData(void);
        string getuserName(void);
};

// Seller class is in user.cpp (derived from User class)
class Seller : public User {
    private:
        string prefPay;     // Preferred payment method
        string storeName;   // Auction store name
    public:
        void getData(void);     // Gets data not in User class. 
        void putData(void);     // Shows data not in user class
        void modData(void);     // Modifies the data of the current class object
};

// Item class is in item.cpp
class Item {
    private:
        float highBid;
        string highBidder;          // The person with the highest bid
        string itemName;
        string itemDesc;            // A short description of the item
    public:
        Item() : highBidder("none"), highBid(0) { }
        string getItemName(void);
        void bidItem(void);
        void getItem(void);
        void putItem(void);
        template <class T>          // template needed for acceptBid function
        bool acceptBid(T newBid);   // Generated function that uses templates
                                    // to accept either an integer or a double
                                    // value as a parameter
};


////////////////////////////////////////////////
//  Normal function and object declarations  //
///////////////////////////////////////////////

int mainMenu();
void addUser(void);
void addItem(void);
void showAll(void);
list<User*> L;          // Linked list for users
list<Item*> I;          // Linked list for items
User* findUser(string); // Used to find a user by the username
Item* findItem(string); // Used to find an item by the item name
