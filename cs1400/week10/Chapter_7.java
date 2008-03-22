// Josh Braegger
// CS1440
// Mastermind

import java.util.Scanner;

public class Chapter_7 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		System.out.println("This program generates a random " +
				"4 digit number, and has the user try to guess it.");
		
		int[] randomNumber = new int[4];
		
		// Generate random number
		for (int i = 0; i < 4; i++) {
			int num = (int)(Math.random() * 100 % 10);
			randomNumber[i] = num;
		}
		
		// Keep going until they guess the right number
		while(true) {
			char[] guessedNumberChars = new char[4];
			boolean[] dontCheckRandomAgain = new boolean[4]; // For checking the generated random number
			boolean[] dontCheckGuessedAgain = new boolean[4]; // For checking the guessed number
			int numRightNumbers = 0; // The count of right numbers
			int numRightButWrong = 0; // The count of right numbers, but in the wrong spot.
			
			System.out.print("Please enter your guess: ");
			
			// Get next digits, and store them in a char array
			try {
				s.next().getChars(0, 4, guessedNumberChars, 0);
			}
			catch (Exception e) {
				System.out.println("Come on now, put in 4 numbers");
				continue;
			}
			
			// Find which numbers are right in the right place
			for (int i = 0; i < guessedNumberChars.length; i++) {
				if ( Character.getNumericValue ( guessedNumberChars[i] ) == randomNumber[i]) {
					dontCheckGuessedAgain[i] = true;
					dontCheckRandomAgain[i] = true;
					numRightNumbers++;
				}
			}
			
			// If all 4 are right, quit, because they won
			if (numRightNumbers == 4)
				break;
			
			// Find how many are right but in the wrong place
			for (int i = 0; i < guessedNumberChars.length; i++) {
				// Means they got this one right, don't check it
				if (dontCheckGuessedAgain[i] == true)
					continue;
				
				// See if the current value they guessed is in
				for (int j = 0; j < randomNumber.length; j++) {
					if (dontCheckRandomAgain[j] == true)
						continue;
					else if (randomNumber[j] == 
							Character.getNumericValue( guessedNumberChars[i])) 
					{
						dontCheckRandomAgain[j] = true;
						numRightButWrong++;
						break;
					}
				}
				
			}
			
			System.out.printf("You got %d numbers right and in the right place\n", numRightNumbers);
			System.out.printf("You got %d numbers right but in the wrong place\n", numRightButWrong);
			
		}
		
		System.out.println("Congrats, you win!");
		
	}

}