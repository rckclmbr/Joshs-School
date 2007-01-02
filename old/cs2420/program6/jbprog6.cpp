// Joshua Braegger
// CS2750 Data Structures

// This is a very simple version of the hangman game.
// I used the set because it automatically organizes 
// guessed letters / numbers.  It was the easiest solution
// to what I needed to do.

#include <iostream>
#include <string>
#include <set>
using namespace std;

int hangman(string, set<char>, string, int);	// Pretty much the entire
												// hangman game (recursive)
char check_guessed(set<char>);	// Get input for guess, and checks to 
								// see if it's been guessed (recursive)

int main()
{
	string fullword;
	string word;

	while(true)
	{
		int guesses;
		cout << "Enter the word you want: ";
		getline(cin, fullword,'\n');
		word = fullword;

		if(word == "done")
		{
			cout << endl << "Ending game" << endl << endl;
			return 0;
		}

		cout << "Enter number of guesses: ";
		cin >> guesses;
		cout << endl << endl;

		// Fill spaces and underscores
		string::iterator i;
		string::iterator j = word.begin();
		for(i = fullword.begin(); i != fullword.end(); i++)
		{
			if(*i == ' ')
				*j  = ' ';
			else
				*j = '_';
			j++;
		}

		// Enter hangman recursion
		set<char> already_guessed;	// Need this for first iteration
		hangman(fullword, already_guessed, word, guesses);
		cin.ignore();
	}
}

int hangman(string fullword, set<char> already_guessed, string word, int guesses)
{
	bool guessed_ok = false;

	cout << "Guesses left: " << guesses << endl;
	cout << "Word: " << word << endl;
	if(guesses == 0)
	{
		cout << "Sorry, you lose" << endl;
		cout << "The word was: " << fullword << endl << endl;
		return 0;
	}
	else if(fullword == word)
	{
		cout << "Congraratulations, you correctly guessed the word: " << word << endl << endl;
		return 0;
	}
	else
	{
		char guess = check_guessed(already_guessed);
		already_guessed.insert(guess);
		for(int i = 0; i < fullword.size(); i++)
		{
			if(guess == fullword[i])
			{
				word[i] = guess;
				guessed_ok = true;
			}
		}
				
	}
   	if(!guessed_ok)
		cout << endl << "Invalid guess, try again" << endl << endl;

	// Here's the recursion!
	return hangman(fullword, already_guessed, word, guessed_ok? guesses : --guesses);
}

char check_guessed(set<char> already_guessed)
{
	char guess;
	set<char>::iterator i;
	
	cout << endl << "Guessed letters: ";
	if(already_guessed.empty())
		cout << "None";
	else
	{
		for(i = already_guessed.begin(); i != already_guessed.end(); i++)
			cout << *i << " ";
	}
	cout << endl << endl;

	cout << "Enter a letter to guess: ";
	cin >> guess;

	for(i = already_guessed.begin(); i != already_guessed.end(); i++)
	{
		if(guess == *i)
		{
			cout << endl << "That was already guessed, try again";
			return check_guessed(already_guessed); // Recusion again
		}
	}
	return guess;
}
