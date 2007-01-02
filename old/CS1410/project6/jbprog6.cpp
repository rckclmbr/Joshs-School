//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #6
//			Mr. Hart
//			Due:  10/24/05
//------------------------------------------------------
// This program improves the String class on page 348
// by deriving it with PString.
// -----------------------------------------------------


// Compiler directives
#include <iostream>
#include <iomanip>	// for manipulators
using namespace std;

class String
{
	protected:
		enum {SZ = 80};
		char str[SZ];
	public:
		String()
			{ str[0] = '\0'; }
		String( char s[] )
			{ strcpy(str, s); }
		void display() const
			{ cout << str; }
		operator char*()
			{ return str; }
};

class PString : public String
{

	public:
		PString() : String()		// Same default constructor as String
			{ }
		PString( char s[] );

};

class PString2 : public PString
{

	public:
		PString2() : PString()			// Same default constructer as String
			{ }
		PString2( char s[] ) : PString( s )	// Same non-default constructor as PString
			{ }
		void left(PString2 Text1,int N);
		void mid(PString2 Text1,int S,int N);
		void right(PString2 Text1,int N);
};

int main()
{
	PString2 s1,		// Shorter than SZ
	 	 s2,		// Longer than SZ
		 s3,		// Sentence to demonstrate left, mid, right
		 s4,		// Leftmost 10 characters
		 s5,		// Middle characters
		 s6;		// Right-most characters

	s1 = "Never read the instructions.";
	s2 = "I would have to say that the greatest single achievement of the American medical field is blah blah";
	s3 = "A long time ago in a galaxy far, far away.";
	s4.left(s3,10);
	s5.mid(s3,16,10);
	s6.right(s3,14);

	cout << "THIS SENTENCE IS SHORTER THAN SZ:" << endl;
	cout << static_cast<char*>(s1);
	cout << endl << endl;

	cout << "THIS SENTENCE IS LONGER THAN SZ:" << endl;
	cout << static_cast<char*>(s2);
	cout << endl << endl;

	cout << "THIS SENTENCE DEMONSTRATES THE LEFT, MID, AND RIGHT FUNCTIONS:" << endl;
	cout << static_cast<char*>(s3);
	cout << endl << endl;

	cout << "THE LEFTMOST 10 CHARACTERS ARE:" << endl;
	cout << static_cast<char*>(s4);
	cout << endl << endl;

	cout << "THE SUBSTRING BEGINNING IN POSITION 16 FOR A LENGTH OF 10 IS:" << endl;
	cout << static_cast<char*>(s5);
	cout << endl << endl;

	cout << "THE RIGHTMOST 14 CHARACTERS ARE:" << endl;
	cout << static_cast<char*>(s6);
	cout << endl << endl;


	return 0;
}


PString::PString( char s[] )
{ 
	int string_length;

	string_length = strlen(s);
	if(string_length > SZ - 1)
	{
		strncpy(str, s, SZ - 1);	// Copy SZ - 1 characters (78 in this case)
		str[SZ - 1] = '\0';		// Add null character to str[79] position
	}
	else
		strcpy(str, s);			// Otherwise it's easy to copy 
}

void PString2::left( PString2 Text1, int N )
{

	strncpy(str, Text1, N);
	str[N] = '\0';

}

void PString2::mid( PString2 Text1,int S,int N )
{
	int temp;

	for(temp = 0; temp < N; temp++)
	{
		str[temp] = Text1[S + temp];
	}

	str[temp] = '\0';			// Add trailing null character

}

void PString2::right(PString2 Text1,int N )
{

	int string_length,
	    start_point,
	    temp;

	// Get the length of variable Text1
	string_length = strlen(Text1);

	// Get the startpoint to start copying
	start_point = string_length - N;

	for(temp = 0; temp < N; temp++)
	{
		str[temp] = Text1[start_point + temp];
	}

	str[temp] = '\0';

}
