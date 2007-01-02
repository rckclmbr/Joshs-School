//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #8
//                  Mr. Rague
//                  Due: 11/3/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This opens a file named "random.txt" and replaces every fifth
//  character with an 'x'.
//  -----------------------------------------------------------------

import java.io.*;

public class RAF {
	public static void main(String args[]) throws Exception {
		RandomAccessFile rf;
		long currLoc;
		
		// open file
		rf = new RandomAccessFile("random.txt","rw");

		// loop and replace
		while( (currLoc = rf.getFilePointer() + 4) < rf.length() ) {
			rf.seek(currLoc);
			rf.write('x');
		}
		
		// Explain success story
		System.out.println("Replaced file with x's");
		rf.close();
	}

}
