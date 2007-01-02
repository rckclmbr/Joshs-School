//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #6
//                  Mr. Rague
//                  Due: 10/17/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the savings account class
//  -----------------------------------------------------------------
import java.text.NumberFormat;

public class SavingsAccount implements Account {
	
	String name;
	float balance;
	int numTransactions;

	SavingsAccount() {
		name = "No Name";
	}

	SavingsAccount(String myName) {
		name = myName;
	}

	public void raiseBalance(float f) {
		balance += f;
		numTransactions++;
	}

	public void lowerBalance(float f) {
		balance -= f;
		numTransactions++;
	}

	public void displayInfo() {
		NumberFormat df = NumberFormat.getCurrencyInstance();
		System.out.println("Name: " + name);
		System.out.println("Balance: " + df.format(balance));
		System.out.println("Number of transactions: " + numTransactions);
	}
}
