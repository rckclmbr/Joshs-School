//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #4
//                  Mr. Rague
//                  Due: 9/26/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This application generates 100 random numbers and calculates the
//  variance and average of the numbers  
//  -----------------------------------------------------------------
 
import java.util.Random;

public class StatCalc {

	static int SIZE = 100; 				// The size of the number array we want
	static int MAX_INT_VALUE = 100;		// The maximum integer value in the array

	public static void main(String args[]) {
		double avg = 0, 
			   variance = 0;
		int trialCount;
		int[] rNumbers;
		double total;


		for( trialCount=1; trialCount<=4; trialCount++ ) {
			rNumbers = getRandomNumbers();			// Generate random numbers
			total = getTotal(rNumbers);				// get total of the numbers
			avg = total / rNumbers.length;			// Calculate average
			variance = getVariance(rNumbers);		// Calculate variance

			// Output the data
			System.out.println("Trial #" + trialCount + ":");
			System.out.printf("Average   %.2f\n", avg);
			System.out.printf("Variance: %.2f\n", variance);
			System.out.println();
		}
	}

	// Function returns an array of random integers
	public static int[] getRandomNumbers() {
		Random r = new Random();
		int[] a = new int[SIZE];

		for(int i=0; i<a.length; i++) {
			a[i] = (r.nextInt(MAX_INT_VALUE) + 1);
		}

		return a;
	}

	// Function returns the total off the array
	public static double getTotal(int[] aNumbers) {
		double total = 0;

		for(int i=0; i<aNumbers.length; i++) {
			total = total + aNumbers[i];	
		}

		return total;
	}

	// Function calculates the variance of the array
	public static double getVariance(int[] aNumbers) {
		double variance = 0;

		double total = getTotal(aNumbers);
		double avg = total / (double)aNumbers.length;

		for(int i=0; i<aNumbers.length; i++) {
			variance = variance + Math.pow(aNumbers[i] - avg,2);
		}

		variance = variance / (aNumbers.length);

		return variance;
	}
};
