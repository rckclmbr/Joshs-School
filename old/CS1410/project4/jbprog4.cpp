//			Joshua Braegger
//			CS 1410 - 11 am
//			Assignment #4
//			Mr. Hart
//			Due:  10/10/05
//------------------------------------------------------
//  This program reads in values for a magic square, 
//  and tests to see if it is truely a magic square. 
// -----------------------------------------------------


// Compiler directives
#include <iostream>
#include <fstream>
using namespace std;

class Magic_Square
{
	private:
		int Size;		// Number of rows and columns in the Magic Square array
		int MagSq[5][5];	// Magic Square matrix
		int ColSums[5];		// Array of column sums
		int RowSums[5];		// Array of rowsums
		int Diag1;		// Sum of major diagonal
		int Diag2;		// Sum of minor diagonal
		bool Sum_Criteria;	// Was the sum test met?
		bool Sequence_Criteria;	// Was the sequence test met?
		void Calc_RowSums();	// Calculates the row sums
		void Calc_ColSums();	// Calculates the column sums
		void Calc_Diags();	// Calculates the two diagonal sums
	public:
		Magic_Square();		// Constructor to initialize ColSums, RowSums, Diag1, and Diag2
					// to zeros
		void Input_Values();	// Inputs the matrix values
		void Output_Values();	// Displays the matrix values
		void Seq_Test();	// Determines if the sequence test was met
		void Sum_Test();	// Determines if the sum test was met
		void Evaluate();	// Determines and displays whether a magic square or not and if not,
					// which criteria failes.
};

ifstream infile;
ofstream outfile;

int main()
{
	int x;
	infile.open("infile.txt");
	outfile.open("outfile.txt");

	Magic_Square square;

	// While loop to keep us going until EOF
	while(!infile.eof())
	{
		// Read the line we're on
		square.Input_Values();
	
		// Second loop or else it'll process last line twice
		if(!infile.eof())
		{
			square.Seq_Test();
			square.Sum_Test();
			square.Output_Values();
			square.Evaluate();
		}
	}

	outfile.close();
	infile.close();
	return 0;
}

void Magic_Square::Calc_RowSums()
{
	int row,
	    col;

	// Initialize RowSums to 0
	for(row = 0; row < Size; row++)
		RowSums[row] = 0;

	// Get the RowSums
	for(row = 0; row < Size; row++)
		for(col = 0; col < Size; col++)
			RowSums[row] += MagSq[col][row];
}

void Magic_Square::Calc_ColSums()
{
	int row,
	    col;
	
	// Initialize ColSums to 0
	for(col = 0; col < Size; col++)
		ColSums[col] = 0;	

	// Get the ColSums
	for(col = 0; col < Size; col++)
		for(row = 0; row < Size; row ++)
			ColSums[col] += MagSq[col][row];

}

void Magic_Square::Calc_Diags()
{
	int row,
	    col;

	// Reinitialize Diag1 and Diag2 for each iteration
	Diag1 = 0;
	Diag2 = 0;

	// First diagonal
	row = 0;
	for(col = 0; col < Size; col++)
	{
		Diag1 += MagSq[col][row];
		row++;
	}

	// Second diagonal
	row = Size - 1;
	for(col = 0; col < Size; col++)
	{
		Diag2 += MagSq[col][row];
		row--;
	}
}

// Initialize magic square to 0
Magic_Square::Magic_Square()
{
	int temp;

	Size = 0;

	// Set ColSums and RowSums to 0
	for(temp = 0; temp < 5; temp++)
	{
		ColSums[temp] = 0;
		RowSums[temp] = 0;
	}
	// Set Diag1 and Diag2 to 0
	Diag1 = 0;
	Diag2 = 0;

}

void Magic_Square::Input_Values()
{

	int col,
	    row;

	Magic_Square();		// Reset all values of Magic_Square
	infile >> Size;		// Set the Size variable to first number in line
	for(col = 0; col < Size; col++)
		for(row = 0; row <= Size - 1; row++)
		{
			infile >> MagSq[col][row];
		}
}

void Magic_Square::Output_Values()
{

	int col,
	    row;

	for(col = 0; col < Size; col++)
	{
		for(row = 0; row <= Size - 1; row++)
		{
			outfile << MagSq[col][row] << "\t";
		}

		outfile << endl;
	}

	// For Testing (prints values to the console, not the file)
	int temp;

	cout << endl;
	for(temp = 0; temp < Size; temp++)
	{
		cout << "Colsums[" << temp << "] - " << ColSums[temp] << endl;
		cout << "RowSums[" << temp << "] - " << RowSums[temp] << endl;
		cout << endl;
	}

	cout << "Diag1: " << Diag1 << " Diag2: " << Diag2 << endl; 
	cout << "------------" << endl;
	
}

void Magic_Square::Seq_Test()
{
	int row,
	    col,
	    seq,			// What number we're on
	    seq_counter,		// variable for testing 
	    seq_num;			// How many variables there are (3 * 3 = 9 variables)

	seq_num = Size * Size;

	// innocent until proven guilty:)
	Sequence_Criteria = true;

	// Check for the numbers, starting with 1
	for(seq = 1; seq <= seq_num; seq++)
	{
		seq_counter = 0;	// Initialize counter for each iteration
	
		// Nested 'for' loop to run through each number
		for(col = 0; col < Size; col++)
		{
			for(row = 0; row < Size; row++)
			{
				// If the number is equal to the sequence it's on,
				// then increase the counter
				if(MagSq[col][row] == seq)
					seq_counter += 1;
			}
		}

		// Only 1 number can be the same (or if there's none)
		// Exit if it's false (we don't need to try anymore)
		if(seq_counter != 1)
		{
			Sequence_Criteria = false;
			break;
		}
	}
}

void Magic_Square::Sum_Test()
{
	int col = 0,
	    temp;

	// Get all the totals we need
	Calc_Diags();
	Calc_ColSums();
	Calc_RowSums();

	temp = ColSums[0];

	Sum_Criteria = true;

	// Calculate
	for(col = 0; col < Size; col++)
		 if(ColSums[col] != temp || RowSums[col] != temp || Diag1 != temp || Diag2 != temp)
			 Sum_Criteria = false;

}

void Magic_Square::Evaluate()
{
	if(Sum_Criteria == true && Sequence_Criteria == true)
		outfile << "It's a magic square" << endl;
	else 
	{
		outfile << "Not a Magic Square" << endl;

		if(Sum_Criteria != true)
			outfile << "Sum criteria failed." << endl;
		if(Sequence_Criteria != true)
			outfile << "Sequence criteria failed." << endl;
	}

	outfile << endl;
}
