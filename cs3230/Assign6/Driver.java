//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #6
//                  Mr. Rague
//                  Due: 10/17/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the main interface used for the checking account and
//  savings account classes
//  -----------------------------------------------------------------
public class Driver {
	
	public static void main(String args[] ) {

		CheckingAccount ca = new CheckingAccount("Checking Account 1",100);
		SavingsAccount sa = new SavingsAccount("Savings Account 1");

		ca.raiseBalance((float)50.0);
		sa.raiseBalance((float)100.0);

		ca.lowerBalance((float)25.0);
		sa.lowerBalance((float)25.0);

		ca.displayInfo();
		System.out.println();
		sa.displayInfo();

	}

}
