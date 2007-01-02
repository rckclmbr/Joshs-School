#ifndef MYSET
#define MYSET 1

#include <iostream>
#include <set>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

#include "myset.cpp"

#endif


void EnterSet(string,MySet<int>*);

int main()
{
    // Create set A data
    MySet<int> *setA = new MySet<int>;
    string setdata; 
    
    cout << "Enter the set A data: ";
    cin >> setdata;
    EnterSet(setdata, setA);

    // Create set B data
    MySet<int> *setB = new MySet<int>;
    cout << "Enter the set B data: ";
    cin >> setdata;
    EnterSet(setdata, setB);
    cout << endl;

    cout << "A contains: ";
    setA->PrintElements();

    cout << "B contains: ";
    setB->PrintElements();
    
    cout << endl;

    cout << "A has cardinality: " << setA->Cardinality() << endl;
    cout << "B has cardinality: " << setB->Cardinality() << endl;
   
    cout << endl;

    cout << "A ";
    if(setB->IsSubset(setA))
        cout << "is ";
    else
        cout << "is NOT ";
    cout << "a subset of B" << endl;

    cout << "B ";
    if(setA->IsSubset(setB))
        cout << "is ";
    else
        cout << "is NOT ";
    cout << "a subset of A" << endl;
    cout << endl;

    cout << "The intersection of A and B is: ";
    MySet<int> *setC = new MySet<int>;
    setC = setA->Intersect(setB);
    setC->PrintElements();
    cout << endl;

    MySet<int> *setD = new MySet<int>;
    setD = setA->Union(setB);
    cout << "The union of A and B is: ";
    setD->PrintElements();
    cout << endl;
    return 0;
}

void EnterSet(string setdata,MySet<int> *theSet)
{
    setdata.erase(0,1);
    setdata.erase(setdata.length() - 1, 1);

    char str[80];
    memset(str,'\0',80);
    setdata.copy(str,75);
    char * pch;
    pch = strtok(str,",");
    while(pch != NULL)
    {
        theSet->AddElement(atoi(pch));
        pch = strtok(NULL, ",");
    }
}
