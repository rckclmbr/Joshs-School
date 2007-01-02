//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #3
//                  Mr. Rague
//                  Due: 9/19/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This java application calculates where a balloon is at certain
//  points of time, and also its velocity. 
//  -----------------------------------------------------------------
 
//  -----------------------------------------------------------------
//  Balloon returns to ground at hour 51 
//  -----------------------------------------------------------------
import java.text.NumberFormat;

public class Balloon {

	public static void main(String args[]) {
		double v,a;

		System.out.printf("%12s %15s %15s \n", "Time(hours)","Altitude(m)","Velocity(m/h)");
		for(int t=1; t<=5; t++) {
			v = getVelocity(t);
			a = getAltitude(t);
			System.out.printf("%12d %15.2f %15.2f \n", t, a, v);
		}
		
	}

	// Method to return the velocity at the given time in hours.
	public static double getVelocity(int t) {
		return -.48 * Math.pow(t,3) + 36.0 * Math.pow(t,2) - 760.0 * (t) + 4100.0;
	}

	// Method to return the altitute at the given time in hours.
	public static double getAltitude(int t) {
		return -.12 * Math.pow(t,4) + 12.0 * Math.pow(t,3) - 380 * Math.pow(t,2) + (4100.0 * t) + 220.0;

	}
}
