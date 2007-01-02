// Joshua Braegger
// 10/11/2005
// Program logic_c.cpp 
// Function: f is the truth value of a logical proposition.

#include <iostream>
#include <cmath>		// For sqrt
using namespace std;

bool EvenInt(long);		// Returns true if x is an integer
bool SquareInt(long);		// Returns true if x is a perfect square
bool SymmetricInt(long);	// Returns true if x is summetric (palindrome)
bool KNumber(long);		// Returns true is x is a k-number

int main(int argc, char *argv[])
{
	long num1,
	     num2,
	     x;

	if(argc == 3)
	{
		num1 = atol(argv[1]);
		num2 = atol(argv[2]);

		for(x = num1; x <= num2; x++)
		{
			if(KNumber(x))
				cout << x << endl;
		}

	}

	else
		cout << "Two arguments required. Exiting." << endl;

}

// Returns true if x is an integer
bool EvenInt(long x)
{
	x = x % 2;
	if(x == 0)		// If no remainder, it's even
		return true;
	return false;		// Otherwise return false


}

bool SquareInt(long x)
{
	int square_root;

	square_root = (int)sqrt((long double)x);	// If it's a squareroot
	if(x == square_root * square_root)
	       return true;			// return true
	return false;				// or return false	

}

bool SymmetricInt(long x)
{
	long x_temp,
       	     temp,
	     x_final = 0;

	x_temp = x;	// Set temporary variable equal to x

	while(x_temp > 0)
	{
		temp = x_temp % 10;			// Get the first integer to add
		x_final = (x_final * 10) + temp;	// multiply by ten and add next digit
		x_temp = x_temp / 10;			// decrement x for next iteration
	}

	if(x == x_final)		// If you can reverse it and it's the same
		return true;	// then return true
	return false;		// else return false

}

bool KNumber(long x)
{
//	cout << "------" << endl << "x: " << x << endl;
//	cout << "EvenInt: " << EvenInt(x) << endl;
//	cout << "square: " << SquareInt(x) << endl;
//	cout << "symmetric: " << SymmetricInt(x) << endl;
	if(EvenInt(x) && SquareInt(x) && SymmetricInt(x))
		return true;
	return false;
}
