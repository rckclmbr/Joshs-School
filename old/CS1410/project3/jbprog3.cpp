//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #3
//			Mr. Hart
//			Due:  09/26/05
//------------------------------------------------------
// This program gets two inputs for time format hh:mm:ss
// and outputs the two times.
// -----------------------------------------------------


// Compiler directives
#include <iostream>
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
		Rational add_fractions(Rational right);	// Add two fractions together
		Rational sub_fractions(Rational right);	// Subtract two fractions
		Rational mul_fractions(Rational right);	// Multiply two fractions
		Rational div_fractions(Rational right);	// Divide two fractions
		void disp_oneFrac(void);		// Display a fraction in fraction format (ie 4/6)
		void disp_floatFrac(void);		// Display a fraction in float format (ie -.667)

};

int main()
{
	int choice;		// Variable for the choice in menu
	Rational left,		// Rational variable for the first fraction
		 right,		// Rational variable for the second fration
		 result;	// Rational variable for the result

	// Keep us in the program unless we exit
	do
	{
		choice = menu();
		// Input two fractions
		if(choice == 1)
		{
			cout << "First fraction:" << endl;;
			left.inp_single();
			cout << "Second fraction:" << endl;
			right.inp_single();
		}
		// Add and display result
		else if(choice == 2)
		{
			result = left.add_fractions(right);
			left.disp_oneFrac();
			cout << " + ";
			right.disp_oneFrac();
			cout << " = ";
			result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Subtract and display result
		else if(choice == 3)
		{
			result = left.sub_fractions(right);
			left.disp_oneFrac();
			cout << " - ";
			right.disp_oneFrac();
			cout << " = ";
			result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Multiply and display result
		else if(choice == 4)
		{
			result = left.mul_fractions(right);
			left.disp_oneFrac();
			cout << " * ";
			right.disp_oneFrac();
			cout << " = ";
			result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Divide and display result
		else if(choice == 5)
		{
			result = left.div_fractions(right);
			left.disp_oneFrac();
			cout << " / ";
			right.disp_oneFrac();
			cout << " = ";
			result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Quit
		else if(choice == 6)
			cout << "Quitting" << endl;
		else
			cout << "Invalid choice, try again" << endl;
	} while(choice != 6);

	return 0;
}

int menu(void)
{
	int choice;

	cout << "Menu" << endl;
	cout << "1. Input two fractions" << endl;
	cout << "2. Add and display result" << endl;
	cout << "2. Subtract and display result" << endl;
	cout << "4. Multiply and display result" << endl;
	cout << "5. Divide and display result" << endl;
	cout << "6. Quit" << endl << endl;
	cout << "Choice: ";
	cin >> choice;
	cout << endl;

	return choice;
}

void Rational::reduce(void)
{
	int temp,				// temporary variables GCD
	    tempNumerator = numerator,		// temporary numerator for GCD
	    tempDenominator = denominator;	// temporary denominator for GCD

	// Get the GCD
	if(tempNumerator > tempDenominator)
	{
		temp = tempNumerator;
		tempNumerator = tempDenominator;
		tempDenominator = temp;
	}
	while(tempNumerator != 0)
	{
		temp = tempDenominator % tempNumerator;
		tempDenominator = tempNumerator;
		tempNumerator = temp;
	}

	numerator /= tempDenominator;
	denominator /= tempDenominator;

}

void Rational::normalize(void)
{
	if(denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}

}

void Rational::inp_single(void)
{
	cout << "Enter the numerator: ";
	cin >> numerator;
	cout << "Enter the denominator: ";
	cin >> denominator;
}

Rational Rational::add_fractions(Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator) + (denominator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;
}

Rational Rational::sub_fractions(Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator) - (denominator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;

}
Rational Rational::mul_fractions(Rational right)
{
	Rational result;

	result.numerator = (numerator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;
}

Rational Rational::div_fractions(Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator);
	result.denominator = (denominator * right.numerator);

	return result;
}

// Displays a fraction (format: 4/7)
void Rational::disp_oneFrac(void)
{
	reduce();
	normalize();
	cout << numerator << "/" << denominator;
}

// Displays a fraction (format: .667)
void Rational::disp_floatFrac(void)
{
	float answer,
	      longnumerator = numerator,
	      longdenominator = denominator;

	cout << setprecision(3) << setiosflags(ios::fixed) << setiosflags(ios::showpoint);
	answer = longnumerator / longdenominator;
	cout << answer;
}
