//	Joshua Braegger
//	Project 9
//	11/28/2005
//////////////////////////////////////////
//  This program uses virtual functions //
//  to store publication information    //
//////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

class publication
{
	private:
		string title;		// Title of publication
		float price;		// Price of publication
	public:
		virtual void GetData()
		{
			cin.ignore();			// Ignore first \n
			cout << "Enter the title: ";
			getline(cin, title,'\n');
			cout << "Enter the price: ";
			cin >> price;
		}
		virtual void PutData()
		{
			cout << "Title: " << title << endl;
			cout << "Price: $" << price << endl;
		}
		virtual bool IsOversize() = 0;	// pure IsOversize function
};

class book : public publication
{
	private:
		int page_cnt;		// Page count
	public:
		void GetData()
		{
			publication::GetData();
			cout << "Enter page count: ";
			cin >> page_cnt;
		}
		void PutData()
		{
			publication::PutData();
			cout << "Page count: " << page_cnt << " pages" << endl;
			cout << "Type: " << "Book" << endl;
		}
		bool IsOversize()	// If the book is oversized
		{ return (page_cnt > 800) ? true : false; }
};

class tape: public publication
{
	private:
		float play_time;	// Play time (in minutes)
	public:
		void GetData()
		{
			publication::GetData();
			cout << "Enter play time: ";
			cin >> play_time;
		}
		void PutData()
		{
			publication::PutData();
			cout << "Play time: " << play_time << " minutes" << endl;
			cout << "Type: " << "Tape" << endl;
		}
		bool IsOversize()	// If the tape is oversized
		{ return (play_time > 90) ? true : false; }
};

int main()
{
	publication *Pubptr[SIZE];	// Pointers to publication class
	char choice;
	int n = 0;			// Number of publications in list

	do {
		cout << "Enter book or tape (b/t): ";
		cin >> choice;
		if(choice == 'b')
			Pubptr[n] = new book;
		else
			Pubptr[n] = new tape;
		Pubptr[n++]->GetData();
		cout << "	Enter another (y/n)? ";
		cin >> choice;
	} while(choice == 'y');		// Cycle until not 'y'

	cout << endl;

	for(int j = 0; j < n; j++)
	{
		Pubptr[j]->PutData();
		if( Pubptr[j]->IsOversize() )
			cout << "Oversized" << endl;
		cout << endl;
	}
	return 0;
}
