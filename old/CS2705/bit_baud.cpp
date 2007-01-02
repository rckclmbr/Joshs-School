//			Joshua Braegger
//			CS2705
//			Mr Anderson
//			10/03/05
//////////////////////////////////////////////////////////////////
//								//
//	This program converts baud rate to bit rate, and	//
//	vice versa.						//
//								//
//////////////////////////////////////////////////////////////////


#include <iostream>			// ONLY include needed for this program, yay!
using namespace std;

// Declaration of functions used in the program
int menu(void);
void bit_to_baud(void);
void baud_to_bit(void);

int main()
{
	int choice = 0;

	// Loop to keep the program running
	do {
		choice = menu();	
		if(choice == 1)
			bit_to_baud();
		else if(choice == 2)
			baud_to_bit();
		else if(choice == 0)
			cout << "Quitting" << endl;
		else
			cout << "Invalid choice, try again" << endl;
	} while(choice != 0);

	return 0;
}

// Choice of what to calculate
int menu()
{
	// Function variables
	int choice = 0;			// Get the choice to go

	// Display the menu
	cout << endl;
	cout << "Baud rate is LESS THAN or EQUAL TO the bit rate" << endl << endl;
	cout << "Enter what you want to convert:" << endl;
	cout << "1. Bit rate to baud rate" << endl;
	cout << "2. Baud rate to bit rate" << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "Choice: ";

	// Prompt for a choice
	cin >> choice;

	// Return that choice :)
	return choice;
}

// Function to convert bit rate to baud rate
void bit_to_baud()
{
	float bits,			// User enters number of bits
	      signals,			// Number of bits per signal unit
	      baud;			// The exact baud rate

	cout << "Enter the bit rate: ";
	cin >> bits;
	cout << "Enter the number of bits per signal unit: ";
	cin >> signals;

	baud = bits / signals;		// Actual bit_to_baud calculation
	cout << endl;
	cout << "Baud rate is: " << baud << " baud/s" << endl;;

}

// Functino to convert baud rate to bit rate
void baud_to_bit()
{
	float bits,			// User enters number of bits
	      signals,			// Number of bits per signal unit
	      baud;			// The exact baud rate

	cout << "Enter the baud rate: ";
	cin >> baud;
	cout << "Enter the number of bits per signal unit: ";
	cin >> signals;

	bits = signals * baud;		// Actual baud_to_bit calculation
	cout << endl;
	cout << "Bit rate is: " << bits << " bps" << endl;
}
