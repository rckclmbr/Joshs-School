#ifndef MYSET
#define MYSET 1

#include <iostream>
#include <set>
#include <iomanip>
using namespace std;

#endif

template<typename Type>
class MySet : std::set<Type> {
    private:
        int count;
    protected:
        std::set<Type> set1;
    public:
        MySet();            // Constructor
        int Cardinality();  // Returns number of items in the set
        void PrintElements();   // Prints, in order from least to greatest, 
                                // all items in a list
        void AddElement(Type newElement);
                                // Adds element to set if it is not already
                                // contained in the set
        bool IsSubset(MySet<Type> *B);   // Returns true if Set A is a subset of Set B
        MySet<Type>* Intersect(MySet<Type> *B);   // Return the intersection of Set A and Set B
        MySet<Type>* Union(MySet<Type> *B);       // Returns the union of Set A and Set B
        std::set<Type> GetSet(void);


};

template <typename Type>
MySet<Type>::MySet<Type>()
{
    set1.erase(set1.begin(), set1.end());   // Erase set
}

template <typename Type>
int MySet<Type>::Cardinality()
{
    return (set1.size());
}

template <typename Type>
void MySet<Type>::PrintElements()
{
    if(set1.empty())
        cout << "No data to print!" << endl;
    else{
        typename MySet<Type>::iterator i;
        cout << "{";
        for(i = set1.begin(); i != set1.end(); i++)
            cout << *i << ",";
        cout << "}" << endl;
    }

}

template <typename Type>
void MySet<Type>::AddElement(Type newElement)
{
    set1.insert(newElement);
}

template <typename Type>
bool MySet<Type>::IsSubset(MySet<Type> *B)
{
    typename MySet<Type>::iterator i;
    typename MySet<Type>::iterator j;
    std::set<Type> setB = B->GetSet();
    MySet<Type> *tempSet = new MySet<Type>;
    
    for(i = setB.begin(); i != setB.end(); i++)
    {
        bool issubset = false;
        for(j = set1.begin(); j!= set1.end(); j++)
            if(*i == *j)
                issubset = true;
        if(!issubset)
            return false;
    }
    return true;

}

template <typename Type>
MySet<Type>* MySet<Type>::Intersect(MySet<Type> *B)
{
    typename MySet<Type>::iterator i;
    typename MySet<Type>::iterator j;
    std::set<Type> setB = B->GetSet();
    MySet<Type> *tempSet = new MySet<Type>;
    
    for(i = set1.begin(); i != set1.end(); i++)
        for(j = setB.begin(); j != setB.end(); j++)
            if(*i == *j)
                tempSet->AddElement(*i);
    return tempSet;
}

template <typename Type>
MySet<Type>* MySet<Type>::Union(MySet<Type> *B)
{
    typename MySet<Type>::iterator i;
    std::set<Type> setB = B->GetSet();
    MySet<Type> *tempSet = new MySet<Type>;

    for(i = set1.begin(); i != set1.end(); i++)
        tempSet->AddElement(*i);
    for(i = setB.begin(); i != setB.end(); i++)
        tempSet->AddElement(*i);
    return tempSet;
}

template <typename Type>
std::set<Type> MySet<Type>::GetSet()
{
    return set1;
}
