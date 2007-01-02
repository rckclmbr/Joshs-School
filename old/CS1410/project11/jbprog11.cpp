// Joshua Braegger
// Project 11
// 11/8/2005
///////////////////////////////////////////////
// This program demonstrates the uses of the //
// STL                                       // 
///////////////////////////////////////////////

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

const int SIZE = 5;
void use_find(void);
void use_count(void);
void use_sort_asc(void);
void use_search(void);
void use_merge(void);
void use_foreach(void);

int main()
{
    use_find();
    use_count();
    use_sort_asc();
    use_search();
    use_merge();
    use_foreach();

    return 0;
}

void use_find()
{
    // Demonstrates the "find" using integers
    int x[SIZE] = { 1, 2, 3, 4, 4 }; 
    int* location;

    cout << "find() function: " << endl;
    cout << "x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    location =  find(x, x + SIZE, 4);     // Should show where in the array
                                          // 4 is located
    cout << "First element that matches 4 is at location " << location - x << endl;
    cout << endl;
}

void use_count()
{
    // Demonstrates use of the count() using int
    int x[SIZE] = { 2, 4, 5, 6, 5 };

    cout << "count() function: " << endl;
    cout << "x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    int acount = count(x, x + SIZE, 5);     // Should set acount to 2
    cout << "The number of 5's in x[] is: " << acount << endl;
    cout << endl;
}

void use_sort_asc()
{
    // Demonstrates the use of the sort()(ascending) using strings
    string x[SIZE] = { "Mike", "Joe", "Josh", "David", "Harry" };

    cout << "sort() (ascending) function: " << endl;
    cout << "x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    sort(x, x + SIZE);          // Should put names in abc order

    cout << "sort() of x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;
    cout << endl;
}

void use_search()
{
    // Demonstrates the use of the search() function using float
    float x[] = { 1.23, 1.45, 2.5, 6, 2.56 };
    float x2[] = { 2.5, 6};
    
    cout << "search() function:" << endl;
    cout << "x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    cout << "x2 = { ";
    for(int i = 0; i < 2; i++)
        cout << x2[i] << ", ";
    cout << "}" << endl;

    float *y = search(x, x + SIZE, x2, x2 + 2);

    cout << "First location of searching for x2 in x1 is: " << y - x << endl;
    cout << endl;
}

void use_merge()
{
    // Demonstrates the use of the merge() function using ints 
    int x[] = { 1, 2, 5, 6, 9};
    int x2[] = { 7, 12};
    const int n = sizeof(x) / sizeof(int);
    const int n2 = sizeof(x2) / sizeof(int);
    
    cout << "merge() function:" << endl;
    cout << "x = { ";
    for(int i = 0; i < SIZE; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    cout << "x2 = { ";
    for(int i = 0; i < 2; i++)
        cout << x2[i] << ", ";
    cout << "}" << endl;

    cout << "merged x1 and x2 = { ";
    merge(x, x + n,  x2, x2 +n2, 
            ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;
    cout << endl;
}

void for_foreach(int x)
{
    cout << x * 2 << " ";
}

void use_foreach()
{
    // Demonstrates the use of the for_each() function using ints
    int x[] = { 1, 2, 3, 4, 5 };

    cout << "for_each() function:" << endl;
    cout << "x = { ";
    for(int i = 0; i < 5; i++)
        cout << x[i] << ", ";
    cout << "}" << endl;

    for_each(x, x+5, for_foreach);  // Should multiply each value by 2
    cout << endl;

}
