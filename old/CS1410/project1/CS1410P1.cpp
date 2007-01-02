//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #1
//			Mr. Hart
//			Due:  mm/dd/yy
//----------------------------------------------------
// This program that simulates the game of craps, and
// gives an estimate of the results
// ---------------------------------------------------


// Compiler directives
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>	// for manipulators 
using namespace std;

int main()
{
	// Variable declarations
	int games, dice1, dice2, gameOn; 
	float  point, totalRoll, firstLose = 0, firstWin = 0,
	    totalWin = 0, totalLose = 0, afterFirstLoop = 0,
	    firstWinDiff = 0, firstLoseDiff = 0, totalWinDiff = 0, totalLoseDiff = 0; 
	srand(time(0));

	// Loop for the 3 games
	for(games = 1000; games <= 100000; games *= 10) {

		// Set all variable to 0 for each iteration
		totalRoll = 0;
		point = 0;
		totalWin = 0;
		totalLose = 0;
		firstLose = 0;
		firstWin = 0;
		afterFirstLoop = 0;
		firstWinDiff = 0;
		firstLoseDiff = 0;
		totalWinDiff = 0;
		totalLoseDiff = 0;

	// For loop for how many games played
	for(gameOn = 0; gameOn < games; gameOn++)
	{
		// Generate first random number
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
   		totalRoll = dice1 + dice2;
	  
	        // If the roll is 2, 3, or 12, then you lose the game on the first roll	
		if((totalRoll == 2) || (totalRoll == 3) || (totalRoll == 12))
		{
			firstLose++;
			totalLose++;
		}

		// If the roll is 7 or 11, then you lose the game on the first roll
		else if((totalRoll == 7) || (totalRoll == 11))
		{
			firstWin++;
			totalWin++;
		}

		// If anything else, then roll for the second time
		else 
		{
			//Set variable afterFirstLoop, and set the point
			afterFirstLoop = 0;
			point = totalRoll;

			// Loop to keep us rolling until we win or lose
			while(afterFirstLoop != 1)
			{
				// Generate random numbers
				dice1 = rand() % 6 + 1;
				dice2 = rand() % 6 + 1;
   				totalRoll = dice1 + dice2;

				// If we roll a 7, then we lose and quit the loop
				if(totalRoll == 7)
				{
					totalLose++;
					afterFirstLoop = 1;

				}

				// If we roll the same as our point, then we win and quit the loop
				if(totalRoll == point)
				{
					totalWin++;
					afterFirstLoop = 1;
				}

			}
		}
	}

	// Find the probability of the different win/lose
	firstWin = firstWin / games;
	firstLose = firstLose / games;
	totalWin = totalWin / games;
	totalLose = totalLose / games;

	// Calculate the difference between the wins and the losses
	firstWinDiff = (abs (.223 - firstWin) / .223 ) * 100;
	firstLoseDiff = (abs (.112 - firstLose) / .112) * 100;
	totalWinDiff = (abs (.497 - totalWin) / .497) * 100;
	totalLoseDiff = (abs (.503 - totalLose) / .503) * 100;
	cout << setprecision(3) << setiosflags(ios::fixed) << setiosflags(ios::showpoint);

	// Display all the data we've collected
	cout << "                                        Craps Simulation            " << endl;
	cout << "                             Number of games in simulation: " << games << endl;
	cout << "                        Actual             Simulated            % Difference " << endl;
	cout << endl;
	cout << "Win on first roll" << setw(13) << ".223" << setw(22) << firstWin << setw(24) << firstWinDiff << endl;
	cout << "Lose on first roll" << setw(12) << ".112" << setw(22) << firstLose << setw(24) << firstLoseDiff << endl;
	cout << "Total Win" << setw(21) << ".497" << setw(22) << totalWin << setw(24) << totalWinDiff << endl;
	cout << "Total Lose" << setw(20) << ".503" << setw(22) << totalLose << setw(24) << totalLoseDiff << endl;
	cout << endl;
	}	
return 0;
}
