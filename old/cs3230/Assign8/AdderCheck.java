//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #8
//                  Mr. Rague
//                  Due: 11/3/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This program gets two integer input from the user, and adds them
//  together.  Also catches exceptions if they enter a value other
//  than an integer
//  -----------------------------------------------------------------
import java.util.*;

public class AdderCheck {

	public static void main(String args[]) {
		int firstInt = 0, secondInt = 0;
		String tempString;
		
		// Initialize scanner
		Scanner sc = new Scanner(System.in);
		
		// Insert first integer
		while(true) {
			try {
				System.out.print("Enter first integer: ");
				firstInt = Integer.parseInt(sc.nextLine());
				break;
			} catch(NumberFormatException e) {
				System.out.println("Please enter an integer!");
				System.out.println();
			}
		}
		
		// Insert second integer
		while(true) {
			try {
				System.out.print("Enter second integer: ");
				secondInt = Integer.parseInt(sc.nextLine());
				break;
			} catch(NumberFormatException e) {
				System.out.println("Please enter an integer!");
				System.out.println();
			}
		}
		System.out.println("Sum: " + (firstInt + secondInt));

		sc.close();
	}

}
