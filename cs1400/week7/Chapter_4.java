import java.util.Scanner;

public class Chapter_4 {
    public static void main(String[] args) {
        Scanner c = new Scanner(System.in);

        System.out.print("Enter side length one: ");
        double one = c.nextDouble();

        System.out.print("Enter side length two: ");
        double two = c.nextDouble();

        System.out.print("Enter side length three: ");
        double three = c.nextDouble();

        // Get the angles of all three sides
        double angleOne   = getAngle( two, three, one );
        double angleTwo   = getAngle( three, one, two );
        double angleThree = getAngle( one, two, three );

        System.out.printf("Side 1: %5.2f, Side 2: %5.2f, Side 3: %5.2f %n", 
        		angleOne, angleTwo, angleThree);
    }

    public static double getAngle(double a, double b, double c) {
        // Law of cosines
    	// (has issues with numbers close to one (super acute angles),
    	// but works for all others)
    	return Math.toDegrees(
        	Math.acos(
                ( Math.pow(a, 2.0) + Math.pow(b,2.0) - Math.pow(c,2.0) ) 
                	/ ( 2.0 * a * b )
        	)
        );
    }
}
