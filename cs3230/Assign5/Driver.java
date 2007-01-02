//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #5
//                  Mr. Rague
//                  Due: 10/10/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the driver for the person class and all the person's
//  child classes
//  -----------------------------------------------------------------

import java.util.*;

public class Driver {

	public static void main(String args[]) {
	
		SalesPerson sp1 = new SalesPerson("SP Name 1", 22, "District 1");
		SalesPerson sp2 = new SalesPerson("SP Name2", 32, "District 2");
		Manager m1 = new Manager("M Name 1", 55,"Department 1");
		Executive s1 = new Executive("E Name 1",75);

		// Print information
		sp1.show();	
		System.out.println();
		sp2.show();	
		System.out.println();
		m1.show();	
		System.out.println();
		s1.show();	
		System.out.println();

		// Remove sp1
		sp1.destroy(); 
		sp1 = null;

		System.out.println("-------------------------------");
		// Show updated info
		sp2.show();	
		System.out.println();
		m1.show();	
		System.out.println();
		s1.show();	
		System.out.println();
	}
}
