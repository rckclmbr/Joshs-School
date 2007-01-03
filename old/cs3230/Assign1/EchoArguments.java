//					Joshua Braegger
//					CS 3230 - T H 7:30PM
//					Assignment #1
//					Mr. Rague
//					Due: 9/5/2006
//					Version: 1.0
//	-----------------------------------------------------------------
//	This program echoes the arguments back to the screen	
//	-----------------------------------------------------------------

class EchoArguments {
	public static void main ( String args[] ) {
		for(int i = 0; i < args.length; i++) {
			System.out.println("Argument " + (i + 1) + ": " + args[i]);
		}
	}
}
