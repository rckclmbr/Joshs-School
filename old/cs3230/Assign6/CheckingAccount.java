//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #6
//                  Mr. Rague
//                  Due: 10/17/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the checking account class
//  -----------------------------------------------------------------
import java.text.NumberFormat;

public class CheckingAccount implements Account {
	
	String name;
	float balance;
	int numChecks;

	CheckingAccount() {
		name = "No Name";
		numChecks = 0;
	}

	CheckingAccount(String myName, int begCheckNum) {
		name = myName;
		numChecks = begCheckNum;
	}

	public void raiseBalance(float f) {
		balance += f;
	}

	public void lowerBalance(float f) {
		balance -= f;
		numChecks++;
	}

	public void displayInfo() {
		NumberFormat df = NumberFormat.getCurrencyInstance();
		System.out.println("Name: " + name);
		System.out.println("Balance: " + df.format(balance));
		System.out.println("Check Number: " + numChecks);
	}
}
