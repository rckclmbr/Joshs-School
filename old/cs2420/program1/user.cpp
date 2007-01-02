User* findUser(string search)
{

    list<User*>::iterator i;
    User* current;

    cout << endl;
    for(i = L.begin(); i != L.end(); ++i) 
    {
        current = *i;
        if(current->getuserName() == search)
            return current;
    }
    return NULL;
}

void addUser()
{
    User* newUser;          // Points to a new user
    char seller = 'n';      // 'y' for seller
        
    cout << "Is this user a seller? (y/n)> ";
    cin >> seller;
    if(seller == 'y')
        newUser = new Seller;     // Create user if Seller
    else
        newUser = new User;       // Create user if Buyer
    newUser->getData();

    L.push_back(newUser);

    cout << endl;
    cout << "A new user has been created" << endl << endl;
}

void showAll()
{
    list<User*>::iterator i;
    User* current;

    cout << endl;
    if(L.empty())
        cout << "There is nobody to show!" << endl;
    else
    {
        for(i = L.begin(); i != L.end(); ++i) 
        {
            current = *i;
            current->putData();
            cout << endl;
        }
    }
}

void User::getData()
{
    userType = 'u';             // "User" unless changed by Seller
    cout << "Enter a username: ";
    cin >> userName;
    cout << "Enter the real name: ";
    cin.ignore();
    getline(cin,userRealName,'\n');
    cout << "Enter a password: ";
    cin >> userPass;
    cout << "Enter email address: ";
    cin >> userEmail;
}

void User::putData()
{
    cout << "Type of user: ";
    if(userType == 'u')
        cout << "User" << endl;
    else
        cout << "Seller" << endl;
    cout << "Username: " << userName << endl;
    cout << "Real name: " << userRealName << endl;
    cout << "Password: " << userPass << endl;
    cout << "Email address: " << userEmail << endl;
}
void User::modData()
{
    int choice;
    cout << "What would you like to modify?" << endl;
    cout << "1. Username" << endl;
    cout << "2. Real name" << endl;
    cout << "3. Password" << endl;
    cout << "4. Email" << endl;
    cout << "> ";
    cin >> choice;
    switch(choice)
    {
        case 1: cout << "New username: "; cin >> userName; break;
        case 2: cout << "New real name: "; cin.ignore(); getline(cin,userRealName,'\n'); break;
        case 3: cout << "New password: "; cin >> userPass; break;
        case 4: cout << "New email: "; cin >> userEmail; break;
        default: cout << "Invalid option, returning to menu" << endl;
    }
}
string User::getuserName()
{
    return userName;
}


void Seller::getData()
{
    User::getData();
    userType = 's';
    cout << "Enter preferred payment method: ";
    cin >> prefPay;
    cout << "Enter store name: ";
    cin.ignore(); 
    getline(cin,storeName,'\n');
}

void Seller::putData()
{
    User::putData();
    cout << "Store Name: " << storeName << endl; 
    cout << "Prefered payment method: " << prefPay << endl;
}

void Seller::modData()
{
    int choice;
    cout << "What would you like to modify?" << endl;
    cout << "1. Username" << endl;
    cout << "2. Real name" << endl;
    cout << "3. Password" << endl;
    cout << "4. Email" << endl;
    cout << "5. Store name" << endl;
    cout << "6. Prefered payment method: " << endl;
    cout << "> ";
    cin >> choice;
    switch(choice)
    {
        case 1: cout << "New username: "; cin >> userName; break;
        case 2: cout << "New real name: "; cin.ignore(); getline(cin,userRealName,'\n'); break;
        case 3: cout << "New password: "; cin >> userPass; break;
        case 4: cout << "New email: "; cin >> userEmail; break;
        case 5: cout << "New store name: "; cin.ignore(); getline(cin,storeName,'\n'); break;
        case 6: cout << "New payment method: "; cin >> prefPay; break;
        default: cout << "Invalid option, returning to menu" << endl;
    }
    cout << endl;
}

