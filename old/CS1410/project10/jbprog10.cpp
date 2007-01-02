//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #10
//			Mr. Hart
//			Due:  12/06/05
//------------------------------------------------------
// This program performs fraction math using overloaded
// operators, including istream and overstream
// -----------------------------------------------------
#include "rational.h"


int main(int argc, char* argv[])
{
	int choice;		// Variable for the choice in menu
	Rational left,		// Rational variable for the first fraction
		 right,		// Rational variable for the second fration
		 result;	// Rational variable for the result

	if(argc != 2)
	{
		cout << "You MUST enter a name via the prompt (IE \"jbprog1 Josh\")";
		exit(0);
	}

	// Keep us in the program unless we exit
	do
	{
		cout << "Hello " << argv[1] << endl;
		choice = menu();
		// Input two fractions
		if(choice == 1)
		{
			cout << "First fraction:" << endl;;
			left.inp_single();
			cout << "Second fraction:" << endl;
			right.inp_single();

			if(left == right)
				cout << "\nThe two fractions entered are equal" << endl << endl;
			else if(left > right)
				cout << "The first fraction is greater than the second" << endl << endl;
			else if(left < right)
				cout << "The first fraction is less than the second" << endl << endl;
		}
		// Add and display result
		else if(choice == 2)
		{
			result = left + right;
			cout << left << " + " << right << " = " << result;
			//left.disp_oneFrac();
			//cout << " + ";
			//right.disp_oneFrac();
			//cout << " = ";
			//result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Subtract and display result
		else if(choice == 3)
		{
			// result = left.sub_fractions(right);
			result = left - right;
			cout << left << " - " << right << " = " << result;
			//left.disp_oneFrac();
			//cout << " - ";
			//right.disp_oneFrac();
			//cout << " = ";
			//result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Multiply and display result
		else if(choice == 4)
		{
			//result = left.mul_fractions(right);
			result = left * right;
			cout << left << " * " << right << " = " << result;
			//left.disp_oneFrac();
			//cout << " * ";
			//right.disp_oneFrac();
			//cout << " = ";
			//result.disp_oneFrac();
			cout << " or ";
			result.disp_floatFrac();
			cout << endl << endl;
		}
		// Divide and display result
		else if(choice == 5)
		{
			//result = left.div_fractions(right);
			result = left / right;
			cout << left << " / " << right << " = " << result;
			//left.disp_oneFrac();
			//cout << " / ";
			//right.disp_oneFrac();
			//cout << " = ";
			//result.disp_oneFrac();
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
	cout << "3. Subtract and display result" << endl;
	cout << "4. Multiply and display result" << endl;
	cout << "5. Divide and display result" << endl;
	cout << "6. Quit" << endl << endl;
	cout << "Choice: ";
	cin >> choice;
	cout << endl;

	return choice;
}

// Reduces the fraction
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

// Normalizes the variable (ie 2/-3 = -2/3)
void Rational::normalize(void)
{
	if(denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}

}

// Input a single fraction
void Rational::inp_single(void)
{
	Rational Ra;
	
	while(true)
	{
		cout << "Enter the fraction format '17/25$' ($ at end): ";
		cin >> Ra;
		if(cin.good())
		{
			cin.ignore(10, '\n');
			break;
		}
		cout << "Invalid, try again" << endl;
        cin.clear();
	}


	numerator = Ra.numerator;
	denominator = Ra.denominator;

	reduce();
}

// Overloaded + operator for Rational objects
Rational Rational::operator + (Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator) + (denominator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;
}

// Overloaded - operator for Rational objects
Rational Rational::operator - (Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator) - (denominator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;
}

// Overloaded * operator for Rational objects
Rational Rational::operator * (Rational right)
{
	Rational result;

	result.numerator = (numerator * right.numerator);
	result.denominator = (denominator * right.denominator);

	return result;
}

// Overloaded / operator for Rational objects
Rational Rational::operator / (Rational right)
{
	Rational result;

	result.numerator = (numerator * right.denominator);
	result.denominator = (denominator * right.numerator);

	return result;
}

// Overloaded == operator for Rational objects
bool Rational::operator == (Rational right)
{
	float float1,
	      float2;

	float1 = conv_floatFrac();
	float2 = right.conv_floatFrac();

	return(float1 == float2) ? true : false;
}

// Overloaded > operator for Rational objects
bool Rational::operator > (Rational right)
{
	float float1,
	      float2;

	float1 = conv_floatFrac();
	float2 = right.conv_floatFrac();

	return(float1 > float2) ? true : false;
}

// Overloaded < operator for Rational objects
bool Rational::operator < (Rational right)
{
	float float1,
	      float2;

	float1 = conv_floatFrac();
	float2 = right.conv_floatFrac();

	return(float1 < float2) ? true : false;
}

void Rational::Set_Numerator(int num)
{
	numerator = num;
}

void Rational::Set_Denominator(int denom)
{
	denominator = denom;
}

// Returns the numerator for use
int Rational::Ret_Numerator(void)
{
	reduce();
	normalize();
	return numerator;
}

// Returns the denominator for use
int Rational::Ret_Denominator(void)
{
	reduce();
	normalize();
	return denominator;
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

// Converts a fraction to float, then returns it (for overloaded operators)
float Rational::conv_floatFrac(void)
{
	float answer,
	      longnumerator = numerator,
	      longdenominator = denominator;

	answer = longnumerator / longdenominator;
	return answer;
}
