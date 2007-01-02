/* Program P1MAIN.CPP
   Function: y is the sum of the squared integers from 1 to x.
   Domain: all integers >= 1.
   This program demonstrates 2 algorithms and 1 datatype:
     1. Sum of squares algorithm  - int variables
     2. Multiply/divide algorithm - int variables
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int f1(int);
int f2(int);

int main(int argc, char *argv[])
{
   int  xI, y1I, y2I;
		xI = atoi(argv[1]);
   if(xI >= 2)
   {

      cout << "\n Input   x = " << xI << endl;
      if (xI >= 1)
      {
         // Sum of squares algorithm
         y1I = f1(xI);
         cout << " Sum of squares    y = " << y1I << endl;

         // Multiply/divide algorithm
         y2I = f2(xI);
         cout << " Multiply/divide   y = " << y2I << endl;
      }
      else
      {
         cout << "\n Output  y = Undefined \n";
      }
   }
   return 0;
}

int f1(int x)
{
   // Sum of squares algorithm
   int y = 0;
   int n;
   for(n=1; n<=x; n++)
		y += pow(n,2);
   return y;
}

int f2(int x)
{
   // Multiply/divide algorithm
   int y = 0;
		y = ((x * ((x + 1) * (2 * x + 1))) / 6);
   return y;
}
