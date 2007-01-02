//			Joshua Braegger
//			CS2705
//			Mr Anderson
//			Week 3 Program
//			09/21/05
//////////////////////////////////////////////////////////////////
//								//
//	This program calculates the attenuation, propagation    //
//	time, and wavelength					//
//								//
//////////////////////////////////////////////////////////////////


#include <iostream>					// ONLY include needed for this program, yay!
using namespace std;

// Declaration of functions used in the program
int menu(void);
void attenuation(void);
void prop(void);
void wave(void);

int main()
{
	int choice = 0;

	// Loop to keep the program running
	do {
		choice = menu();	
		if(choice == 1)
			attenuation();
		else if(choice == 2)
			prop();
		else if(choice == 3)
			wave();
		else if(choice == 0)
			cout << "Quitting" << endl;
		else
			cout << "Invalid choice, try again" << endl;
	} while(choice != 0);
}

// Choice of what to calculate
int menu()
{
	// Function variables
	int choice = 0;					// Get the choice to go

	// Display the menu
	cout << endl;
	cout << "Enter what you want to convert:" << endl;
	cout << "1. Attenuation" << endl;
	cout << "2. Propagation Time" << endl;
	cout << "3. Wavelength" << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "Choice: ";

	// Prompt for a choice
	cin >> choice;

	// Return that choice :)
	return choice;
}

// Function to calculate attenuation (sum of dB levels between different measured points)
void attenuation()
{
	int points = 0,					// Number of points we're find the dB level
	    pointOn = 0,				// The point we're on (for the loop)
	    atten = 0,					// Attenuation (the answer)
	    decibels = 0;				// Number of dB between each point (used for the loop)

	cout << "Enter the number of points: ";
	cin >> points;

	// Create loop for the number of points
	for(pointOn = 1; pointOn <= points - 1; pointOn++)
	{
	cout << "Enter the dB level between points " << pointOn << " and " << pointOn + 1 << ": ";
	cin >> decibels;
	atten += decibels;
	}
	if(atten >= 0)
		cout << "There was no attenuation, congratulations!" << endl;
	else
		cout << "Attenuation: " << atten << "dB" << endl;
}

// Functioon to calculate propagation time (prop_time = distance / prop_speed)
void prop()
{
	float distance = 0,				// Distance between points in time
	      prop_speed = 0,				// Propagation speed (assumed)
	      prop_time = 0;				// Propagation time (answer)

	cout << "Enter the distance: ";
	cin >> distance;

	cout << "Enter the propagation speed: ";
	cin >> prop_speed;

	prop_time = distance / prop_speed;

	cout << "Propagation time: " << prop_time << endl;
}

// Function to calculate wavelength (wavelength = prop_speed * period)
void wave()
{
	int prop_speed = 0,				// Propogation speed
	    period = 0,					// The period
	    wavelength = 0;				// The wavelength (answer)
	
	cout << "Enter the propagation speed: ";
	cin >> prop_speed;

	cout << "Enter the period: ";
	cin >> period;

	wavelength = prop_speed * period;

	cout << "Wavelength: " << wavelength << endl;
}
