//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #8
//                  Mr. Rague
//                  Due: 11/3/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  Gets an input and counts how many letters are in the word
//  -----------------------------------------------------------------

import java.io.*;

public class BufferSize {

	public static void main(String args[]) {
		String inString = new String();
		
		System.out.print("Please enter a string: ");
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		try {
			inString = br.readLine();
		} catch(Exception e) { 
			System.err.println("An error occured while getting input"); 
			return; // Just quit
		}
			
		System.out.println("The length of the string you entered is: " + inString.length());
		
	
	}

}
