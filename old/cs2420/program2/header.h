#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

int NUMITEMS = 500;
int ITEMID = 1;

////////////////////////////////////////////////
// Class declarations                         //
////////////////////////////////////////////////
//
// Item class is in item.cpp
class Item {
    private:
        int itemId;
        float highBid;
        string highBidder;          // The person with the highest bid
        string itemName;
        string itemDesc;            // A short description of the item
    public:
        string sellerName;
        Item() : highBidder("none"), highBid(0) { }
        int getItemId(void) { return itemId; };
        void bidItem(void);
        void getItem(void);
        void putItem(void);
        template <class T>          // template needed for acceptBid function
        bool acceptBid(T newBid);   // Generated function that uses templates
                                    // to accept either an integer or a double
                                    // value as a parameter
};


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
        virtual void addItem(Item*) { };     // Virtual function for seller class
        virtual void delItem(Item*) { };    // Virtual function for seller class
        virtual void showItems(void) { };
        virtual int getSellingSize(void) { };
        void changeData(void);
        char getUserType(void) { return userType; }
        string getuserName(void);
};

// Seller class is in user.cpp (derived from User class)
class Seller : public User {
    private:
        string prefPay;     // Preferred payment method
        string storeName;   // Auction store name
        vector<Item*> sellerItems;
    public:
        void getData(void);     // Gets data not in User class. 
        void putData(void);     // Shows data not in user class
        void modData(void);     // Modifies the data of the current class object
        void addItem(Item*);     // Adds an item to sellers vector
        void delItem(Item*);    // Removes an item from sellers vector
        void showItems(void);   // Shows all the users items for sale
        int getSellingSize(void) { return sellerItems.size(); }  // Returns size of sellerItems vector
};


////////////////////////////////////////////////
//  Normal function and object declarations  //
///////////////////////////////////////////////

int mainMenu();
void addUser(void);
void addItem(User*);   // Adds item, and updates Seller info
void showAll(void);
list<User*> L;          // Linked list for users
list<Item*> I;          // Linked list for items
User* findUser(string); // Used to find a user by the username
Item* findItem(int); // Used to find an item by the item number
