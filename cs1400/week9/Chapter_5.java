// Josh Braegger
// CS1440
// Guessing Game Quiz

import java.util.Scanner;

public class Chapter_5 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int guesses = 0;
		int guess;
		int max_guess = 10;
		int min_guess = 1;
		String correct;
		String higher_lower;
		Boolean liar = false;
		
		System.out.println("This program has, the user, choose a " +
				"number between 1 and 100, then I, the computer,\n will " +
				"try my best to guess it.");
		
		do {
			int offset = min_guess;
			int span = max_guess - min_guess;
			if (span == 0) {
				// This is when we're *pretty* sure it's the right number.
				guess = offset; 
			}
			else {
				// Make a completely random guess, but that's *kind* of right
				guess = (int)(Math.random() * span) % span + offset;
			}
			guesses++;
			
			System.out.printf("Is it %d? (y/n) ", guess);
			correct = s.next();
			
			// Didn't guess the right number
			if (!correct.equals("y")) {
				// Don't trip over yourself -- sometimes the user can lie
				if (min_guess == max_guess) {
					liar = true;
					break;
				}

				System.out.print("Was the number higher or lower? (h/l) ");
				higher_lower = s.next();
				
				if (higher_lower.equals("h")) {
					// User guesses higher
					if (guess + 1 > max_guess) {
						liar = true;
						break;
					}
					min_guess = guess + 1;

				}
				else {
					// User guesses lower
					if (guess - 1 < min_guess) {
						liar = true;
						break;
					}
					max_guess = guess - 1;
				}
			}
		} while (!correct.equals("y"));
		
		// Print friendly ending message to the user
		if (liar.booleanValue()) {
			System.out.println("You're such a liar.");
		}
		else {
			System.out.printf("I got your number of %d correct in %d guesses\n", guess, guesses);
		}
		
	}

}