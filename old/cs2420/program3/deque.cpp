void createDeque()
{
    int x;
    
    myDeque.clear();                 // Clears vector for use
    // Inserts random values into vector
    for(int c = 0; c < 5000; c++)
    {
        myDeque.push_back(rand() % 512);
    }
}

void insertDeque(int loc)
{
    createDeque(); // I know it recreates it everytime, but it's ok in this case
    timer t1;
    
    // Inserts a number at the beginning of a vector
    if(loc == 0)
    {
        t1.start();
        myDeque.push_front(rand() % 512);
        myDeque.push_front(rand() % 512);
        myDeque.push_front(rand() % 512);
        t1.stop();
        cout << setw(25) << setprecision(2) << setiosflags(ios::left | ios::fixed) << "Insertion at first: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }

    // Insert a value into the middle of the vector
    else if(loc == 1)
    {
        deque<int>::iterator c = myDeque.begin();

        t1.start();
        myDeque.insert(c + (myDeque.size() / 2),1,rand() % 512);
        myDeque.insert(c + (myDeque.size() / 2),1,rand() % 512);
        myDeque.insert(c + (myDeque.size() / 2),1,rand() % 512);
        t1.stop();
        cout << setw(25) << setiosflags(ios::left) << "Insertion in middle: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }

    // Append a value to the end of a vector
    else if(loc == 2)
    {
        t1.start();
        myDeque.push_back(rand() % 512);
        myDeque.push_back(rand() % 512);
        myDeque.push_back(rand() % 512);
        t1.stop();
        cout << setw(25) << setiosflags(ios::left) << "Insertion at end: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }
}

void deleteDeque(int loc)
{
    createDeque();
    timer t1;
    
    // Removes a number at the beginning of a vector
    if(loc == 0)
    {

        t1.start();
        myDeque.pop_front();
        myDeque.pop_front();
        myDeque.pop_front();
        t1.stop();
        cout << setw(25) << setiosflags(ios::left) << "Removal at Beginning: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }

    // Removes a value into the middle of the vector
    else if(loc == 1)
    {
        deque<int>::iterator c = myDeque.begin();

        t1.start();
        myDeque.erase(c + (myDeque.size() / 2));
        myDeque.erase(c + (myDeque.size() / 2));
        myDeque.erase(c + (myDeque.size() / 2));
        t1.stop();
        cout << setw(25) << setiosflags(ios::left) << "Removal at middle: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }

    // Removes a value from the end of a vector
    else if(loc == 2)
    {
        t1.start();
        myDeque.pop_back();
        myDeque.pop_back();
        myDeque.pop_back();
        t1.stop();

        cout << setw(25) << setiosflags(ios::left) << "Removal at end: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }
}

void walkDeque(int loc)
{
    createDeque();
    timer t1;

    // Walks through the data forwards, printing out everything
    if(loc == 0)
    {
        deque<int>::iterator i;

        t1.start();
        for(i = myDeque.begin(); i != myDeque.end(); ++i)
            // cout << *i;
            int temp  = *i;     // Clean up output
        for(i = myDeque.begin(); i != myDeque.end(); ++i)
            // cout << *i;
            int temp  = *i;     // Clean up output
        for(i = myDeque.begin(); i != myDeque.end(); ++i)
            // cout << *i;
            int temp  = *i;     // Clean up output
        t1.stop();

        cout << setw(25) << setiosflags(ios::left) << "Walk forwards: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }
    else if(loc == 1)
    {
        deque<int>::reverse_iterator i;

        t1.start();
        for(i = myDeque.rbegin(); i != myDeque.rend(); ++i) 
            // cout << *i;
            int temp = *i;      // Clean up output
        for(i = myDeque.rbegin(); i != myDeque.rend(); ++i) 
            // cout << *i;
            int temp = *i;      // Clean up output
        for(i = myDeque.rbegin(); i != myDeque.rend(); ++i) 
            // cout << *i;
            int temp = *i;      // Clean up output
        t1.stop();
        cout << setw(25) << setiosflags(ios::left) << "Walk backwards: " << setw(7) << resetiosflags(ios::left) << t1.putTime() << endl;
    }
}
