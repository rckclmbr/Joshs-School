// Joshua Braegger
// 10/11/2005
// Program logic_a.cpp
// Function: f is the truth value of a logical proposition.

#include <iostream>
#include <fstream>
using namespace std;

char LogicProp(char,char,char);
char ANDlogic(char,char);
char ORlogic(char,char);
char NOTlogic(char);
char convert(int);	// Converts 0/1 to T/F

int main()
{
	char f;
	int  p,
	     q,
	     r;

	// Display heading
	cout << "(~q AND r AND ~p) OR (~(r OR ~p))" << endl;
	cout << "p\tq\tr\t|\tf" << endl;
	cout << "----------------------------------" << endl;

	for(p = 0; p <= 1; p++) 		// First loop
	{
		for(q = 0; q <= 1; q++)		// Second loop
		{
			for(r = 0; r <= 1; r++)	// Third loop
			{
				// Output p q and r
				cout << convert(p) << "\t";
				cout << convert(q) << "\t";
				cout << convert(r) << "\t|\t";

				// Find f, then print f
				f = LogicProp(convert(p),convert(q),convert(r));
				cout << f << endl;
			}
		}
	}

	return 0;
}

char LogicProp(char p, char q, char r)
{
   // Logical expression
	char temp,
	     temp2,
	     f;

	// (~q AND r AND ~p)
	temp = ANDlogic(NOTlogic(q),r);
	temp = ANDlogic(temp,NOTlogic(p));

	// (~(r OR ~p))
	temp2 = NOTlogic(ORlogic(r,NOTlogic(p)));
	
	// (~q AND r AND ~p) OR (~(r OR ~p))
	f = ORlogic(temp,temp2);

	return f;
}

char ANDlogic(char p, char q)
{
   // Logical AND function
   char f = 'F';
   if(p == 'T' && q == 'T')
      f = 'T';
   return f;
}

char ORlogic(char p, char q)
{
	// Logical OR function
	char f = 'F';
	if(p == 'T' || q == 'T')
		f = 'T';
	return f;
}

char NOTlogic(char p)
{
	// Local NOT function
	char f = 'F';
	if(p == 'F')
		f = 'T';
	return f;
}

char convert(int x)
{
	if(x == 0)		// If a 0, then return F
		return 'F';
	else			// Everything is else is T
		return 'T';
}
