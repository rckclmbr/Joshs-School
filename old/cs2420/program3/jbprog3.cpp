#include "header.h"

int main()
{
    srand(time(NULL));

    cout << "Vector:" << endl << endl;
    insertVector(0);    // Insert at start
    insertVector(1);    // Insert at middle
    insertVector(2);    // Insert at end
    deleteVector(0);    // Removes at first
    deleteVector(1);
    deleteVector(2);
    walkVector(0);
    walkVector(1);

    cout << endl;

    cout << "Deque:" << endl << endl;
    insertDeque(0);    // Insert at start
    insertDeque(1);    // Insert at middle
    insertDeque(2);    // Insert at end
    deleteDeque(0);    // Removes at first
    deleteDeque(1);
    deleteDeque(2);
    walkDeque(0);
    walkDeque(1);

    return(0);
}
