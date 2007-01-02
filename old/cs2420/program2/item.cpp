void addItem(User* currUser)
{
    if( currUser->getSellingSize()  <= NUMITEMS)
    {
        Item* newItem;
        
        newItem = new Item;             // Create user if Seller
        newItem->getItem();             // Get item information
        newItem->sellerName = currUser->getuserName();
        I.push_back(newItem);           // Add a pointer of an item to the Item list
        currUser->addItem(I.back());    // Add pointer of item to user vector

        cout << endl;
        cout << "A new item has been created" << endl << endl;
    }
    else
        cout << "You already have 500 bidding items!" << endl << endl;
}

Item* findItem(int search)
{

    list<Item*>::iterator i;
    Item* current;

    cout << endl;
    for(i = I.begin(); i != I.end(); ++i) 
    {
        current = *i;
        if(current->getItemId() == search)
            return current;
    }
    return NULL;
}

void Item::getItem()     // Insert bid information
{
    itemId = ITEMID;
    ITEMID++;
    cout << "Enter item name: ";
    cin.ignore();
    getline(cin,itemName,'\n');
    cout << "Enter item description: ";
    getline(cin,itemDesc,'\n');
}

void Item::putItem()
{
    cout << "Item ID: " << itemId << endl;
    cout << "Item owner: " << sellerName << endl;
    cout << "Item Name: " << itemName << endl;
    cout << "High Bidder: " << highBidder << endl;
    cout << "Current high bid: "; 
    if(highBid == 0)
        cout << "none" << endl;
    else
        cout << highBid << endl;
    cout << "Item Description: " << itemDesc << endl;
}

void Item::bidItem()
{
    string tempUserName;
    float tempBid;
    cout << "Enter your username: ";
    cin >> tempUserName;;
    cout << "Enter your bid amount: ";
    cin >> tempBid;
    if(acceptBid(tempBid))
    {
        highBidder = tempUserName;
        highBid = tempBid;
    }
    else
        cout << "You didn't bid enough!" << endl << endl;
    
}

template <class T>
bool Item::acceptBid(T newBid)
{
    if(newBid > highBid)
        return true;
    else
        return false;
}
