//					Joshua Braegger
//					CS 3230 - T H 7:30PM
//					Assignment #1
//					Mr. Rague
//					Due: 9/5/2006
//					Version: 1.0
//	-----------------------------------------------------------------
//	This program prints the total income for the corporation, and the
//	average salary for the corporation	
//	-----------------------------------------------------------------

class AvgSalary {
	public static void main (String args[] ) {
		int salary = 20225000;
		System.out.println("The total income for the corporation is $" + salary);
		salary = salary / 400;
		System.out.println("The average salary for employees at the corporation is $" + salary);	
	}
}
