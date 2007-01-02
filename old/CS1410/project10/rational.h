// Compiler directives
#include <iostream>
#include <string>
#include <iomanip>	// for manipulators
using namespace std;



int menu(void);

class Rational
{
	private:
		int numerator;			// Numerator in a single fraction
		int denominator;		// Denominator in a single fraction
		void reduce(void);		// Reduces the fraction to smallest terms
		void normalize(void);		// Negative sign will only be in numerator

	public:
		Rational(int numerator = 1, int denominator = 1) : 
			numerator(numerator), denominator(denominator) 
			{ reduce(); normalize(); } 	// default constructor
		void inp_single(void);			// Input a single fraction
		Rational operator + (Rational right);	// Add two fractions together
		Rational operator - (Rational right);	// Subtract two fractions
		Rational operator * (Rational right);	// Multiply two fractions
		Rational operator / (Rational right);	// Divide two fractions
		bool operator == (Rational right);	// Overloaded == for Rational objects
		bool operator > (Rational right);	// Overloaded > for Rational objects
		bool operator < (Rational right);	// Overloaded < for Rational objects
		void Set_Numerator(int);		// Sets the numerator
		void Set_Denominator(int);		// Sets the denominator
		int Ret_Numerator(void);		// Returns the numerator
		int Ret_Denominator(void);		// Returns the denominator
		void disp_floatFrac(void);		// Display a fraction in float format (ie -.667)
		float conv_floatFrac(void);		// Converts a fraction to float format, and returns
										// 	that value
};


// Overloaded output variable
ostream& operator << (ostream& os, Rational& Ra)
{
	os << Ra.Ret_Numerator() << "/" << Ra.Ret_Denominator();
	return os;
}

// Overloaded input variable
istream& operator >> (istream& is, Rational& Ra)
{
	string Value;
	string sNumer;
	string sDenom;

	int slashPos;
	int lenValue;
	int iNumer;
	int iDenom;

	//is.ignore(80, '\n');
	getline(is, Value, '$');

	slashPos = Value.find('/');
	lenValue = Value.length();
	sNumer = Value.substr(0, slashPos);
	sDenom = Value.substr((slashPos+1), lenValue);

	iNumer = atoi(sNumer.c_str());
	iDenom = atoi(sDenom.c_str());

	Ra.Set_Numerator(iNumer);
	Ra.Set_Denominator(iDenom);

	return is;
}
