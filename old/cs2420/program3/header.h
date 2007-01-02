#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include "windows.h"

using namespace std;

class timer {
    private:
        // struct timeb startTimeBuffer, endTimeBuffer;
        LARGE_INTEGER start_time, end_time, freq;
    public:
        void start(void);
        void stop(void);
        double putTime(void);
};

vector<int> myVect;
void createVector(void);
void insertVector(int);
void deleteVector(int);
void walkVector(int);

deque<int> myDeque;
void createDeque(void);
void insertDeque(int);
void deleteDeque(int);
void walkDeque(int);


#include "timer.cpp"
#include "vector.cpp"
#include "deque.cpp"
