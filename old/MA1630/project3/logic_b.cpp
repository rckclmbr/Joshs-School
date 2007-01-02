// Joshua Braegger
// 10/11/2005
// Program logic_b.cpp 
// Function: f is the truth value of a logical proposition.

#include <iostream>
#include <fstream>
using namespace std;

char LogicProp(int,int,int,int);
char ANDlogic(int,int);
char ORlogic(int,int);
char NOTlogic(int);

int main()
{
	int x,
	    y,
	    z,
	    w,
	    f;

	// Display heading
	cout << "~y(x + ~xz) + ~z(~xy + xw)"<< endl;
	cout << "x y z w | f" << endl;
	cout << "-----------" << endl;

	for(x = 0; x <= 1; x++) 		// First loop
	{
		for(y = 0; y <= 1; y++)		// Second loop
		{
			for(z = 0; z <= 1; z++)	// Third loop
			{
				for(w = 0; w <= 1; w++)	// Fourth loop
				{
					// Output x, y, z, and w
					cout << x << " ";
					cout << y << " ";
					cout << z << " ";
					cout << w << "   ";

					// Find f, then print f
					f = LogicProp(x,y,z,w);
					cout << f << endl;
				}
			}
		}
	}

	return 0;
}

char LogicProp(int x, int y, int z, int w)
{
   // Logical expression
	int  left_side,
	     right_side,
	     not_x = NOTlogic(x),
	     not_y = NOTlogic(y),
	     not_z = NOTlogic(z),
	     not_w = NOTlogic(w),
	     f;

	left_side = ORlogic(x,ANDlogic(not_x,z));
	left_side = ANDlogic(not_y,left_side);

	right_side = ORlogic( ANDlogic(not_x,y),ANDlogic(x,w) );
	right_side = ANDlogic(not_z,right_side);

	f = ORlogic(left_side,right_side);

	return f;
}

char ANDlogic(int p, int q)
{
   // Logical AND function
   int f = 0;
   if(p == 1 && q == 1)
      f = 1;
   return f;
}

char ORlogic(int p, int q)
{
	// Logical OR function
	int f = 0;
	if(p == 1 || q == 1)
		f = 1;
	return f;
}

char NOTlogic(int p)
{
	// Local NOT function
	int f = 0;
	if(p == 0)
		f = 1;
	return f;
}
