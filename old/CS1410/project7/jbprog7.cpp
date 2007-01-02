//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #7
//			Mr. Hart
//			Due:  10/31/05
// -----------------------------------------------------
// This program reads in names and scores from a file
// and sorts them, finds the average, standard
// deviation, median, high, low, and range of scores.
// -----------------------------------------------------


// Compiler directives
#include <iostream>
#include <fstream>
#include <iomanip>	// for manipulators
#include <cmath>
using namespace std;

class StudentStat
{
	private:
		int Size;
		string Names[20];		// List of names
		int Scores[20];			// List of scores
		float Avg,			// Average of scores
		      StDev,			// (score - avg) / (num scores)
		      Median;			// Median of scores
		int High_Score,			// Highest score
		    Low_Score,			// Lowest score
		    range;			// Range of scores (highest - lowest)
		void Sortem();			// Sort by scores
	public:
		void Input();
		void Calc_Avg();
		void Calc_StDev();
		void Calc_Median();
		void Range();
		void Calc_HighLowRange();
		void Output();
};

int main()
{
	StudentStat StudObj;

	StudObj.Input();
	StudObj.Calc_Avg();
	StudObj.Calc_StDev();
	StudObj.Calc_Median();
	StudObj.Range();
	StudObj.Output();

	return 0;
}

void StudentStat::Sortem()
{
	void order (int*, int*, string*, string*);
	int j, k;

	for(j = 0; j < Size-1; j++)
		for(k=j+1; k < Size; k++)
			order(Scores+j, Scores+k, Names+j, Names+k);
}

void order(int *numb1, int *numb2, string *name1, string *name2)
{
	if(*numb1 > *numb2)
	{
		int temp = *numb1;
		*numb1 = *numb2;
		*numb2 = temp;

		string temp2 = *name1;
		*name1 = *name2;
		*name2 = temp2;
	}
}

void StudentStat::Input()
{
	ifstream infile;
	char filename[10];
	int temp = 0;

	cout << "Insert filename to read from: ";
	cin >> filename;
	infile.open(filename);

	while(!infile.eof())
	{
		infile >> *(Names+temp);
		infile >> *(Scores+temp);
		temp++;
	}

	Size = temp - 1;	// Subtract one for last iteration
	infile.close();
}

void StudentStat::Calc_Avg()
{
	float tempAvg = 0;

	for(int n = 0; n < Size; n++)
		tempAvg += *(Scores + n);

	tempAvg /= Size;
	Avg = tempAvg;
}

void StudentStat::Calc_StDev()
{
	float tempDev = 0;

	for(int n = 0; n < Size; n++)
		tempDev += pow(abs((*(Scores + n) - Avg)),2);	// equal to |Scores - Avg|^2

	tempDev /= Size;
	StDev = sqrt(tempDev);

}

void StudentStat::Calc_Median()
{
	float tempMedian = 0;

	Sortem();						// Sorts the names/scores

	if(Size % 2 == 0)					// If the size is even
	{
		tempMedian += *(Scores + ((Size / 2) - 1));	// Need to subtract 1 because array starts at 0
		tempMedian = *(Scores + (Size / 2));		
		Median = tempMedian / 2;			
	}
	else
		Median = *(Scores + (Size / 2));

}

void StudentStat::Range()
{
	Calc_HighLowRange();
}

void StudentStat::Calc_HighLowRange()
{
	Low_Score = *(Scores);
	High_Score = *(Scores + (Size - 1));
	range = High_Score - Low_Score;
}

void StudentStat::Output()
{
	char filename[20];
	ofstream outfile;

	cout << "Enter the filename you want to save the output as: ";
	cin >> filename;

	outfile.open(filename);
	outfile << setprecision(2) << setiosflags(ios::fixed | ios::showpoint | ios::left);

	for(int n = 0; n <= Size-1; n++)
	{
		outfile << setw(25) << *(Names + n) << setw(15) << setiosflags(ios::right) 
			<< *(Scores + n) << endl << resetiosflags(ios::right);
	}
	outfile << endl;

	outfile << setw(25) << "Average: " << setw(15) << setiosflags(ios::right) 
		<< Avg << endl << resetiosflags(ios::right);
	outfile << setw(25) << "Standard deviation: " << setw(15) << setiosflags(ios::right) 
		<< StDev << endl << resetiosflags(ios::right);
	outfile << setw(25) << "Median: " << setw(15) << setiosflags(ios::right) 
		<< Median << endl << resetiosflags(ios::right);
	outfile << setw(25) << "High Score: " << setw(15) << setiosflags(ios::right) 
		<< High_Score << endl << resetiosflags(ios::right);
	outfile << setw(25) << "Low Score: " << setw(15) << setiosflags(ios::right) 
		<< Low_Score << endl << resetiosflags(ios::right);
	outfile << setw(25) << "Range: " << setw(15) << setiosflags(ios::right) 
		<< range << endl << resetiosflags(ios::right);

	outfile.close();
}
