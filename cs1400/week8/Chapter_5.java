// Josh Braegger
// CS1440

import java.util.Scanner;

public class Chapter_5 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int rand = (int)(Math.random() * 100) % 100 + 1;
		int guess = -1;
		int guesses = 0;
		
		while (guess != rand) {
			System.out.print("Please enter your guess: ");
			guess = s.nextInt();
			
			guesses++;
			
			if (guess > rand) {
				System.out.println("Incorrect Number.  Too High.");
			}
			else if (guess < rand) {
				System.out.println("Incorrect Guess.  Too Low.");
			}	
		}
		
		System.out.printf("Nice Guess! It only took you %d times\n", guesses);
		
	}

}