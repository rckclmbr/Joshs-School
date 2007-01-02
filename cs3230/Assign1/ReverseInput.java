//					Joshua Braegger
//					CS 3230 - T H 7:30PM
//					Assignment #1
//					Mr. Rague
//					Due: 9/5/2006
//					Version: 1.0
//	-----------------------------------------------------------------
//	This program gets a string, whether input from the command-line
//	or from a prompt, and reverses that string	
//	-----------------------------------------------------------------

import java.io.*;
import java.util.*;

class ReverseInput {
	public static void main ( String args[] ) {
		String s = new String();	// This is the string that will be 
									// reversed, whether by an argument
									// or by input from the Scanner class

		// This create a single string if a line was entered from the command-line input
		for(int i=0; i<args.length; i++) {
			s = s + " " + args[i];
		}
		// This gets the user input if nothing was entered from the command-line
		if(args.length == 0) {
			System.out.println("No command line args");
			System.out.print("Please enter an input string: ");
			Scanner t = new Scanner(System.in);
			s = t.nextLine();
		}
		
		String sb = new StringBuffer(s).reverse().toString(); // Reverse the string
		System.out.println(sb);
	}
}
