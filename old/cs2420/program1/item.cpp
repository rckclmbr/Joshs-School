void addItem()
{
    Item* newItem;          // Points to a new user
        
    newItem = new Item;     // Create user if Seller
    newItem->getItem();

    I.push_back(newItem);

    cout << endl;
    cout << "A new item has been created" << endl << endl;
}

Item* findItem(string search)
{

    list<Item*>::iterator i;
    Item* current;

    cout << endl;
    for(i = I.begin(); i != I.end(); ++i) 
    {
        current = *i;
        if(current->getItemName() == search)
            return current;
    }
    return NULL;
}

string Item::getItemName()
{
    return itemName;
}

void Item::getItem()     // Insert bid information
{
    cout << "Enter item name: ";
    cin.ignore();
    getline(cin,itemName,'\n');
    cout << "Enter item description: ";
    getline(cin,itemDesc,'\n');
}

void Item::putItem()
{
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
