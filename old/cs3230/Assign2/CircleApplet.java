//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #2
//                  Mr. Rague
//                  Due: 9/12/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This program creates two circles, a blue one centered inside
//	a larger red one
//  -----------------------------------------------------------------
import    java.applet.Applet;
import	  java.awt.*;

public class CircleApplet extends Applet {
	
	int o1diam, o2diam, o1off, o2off;

	public void init(){
		o1diam = 90;
		o2diam = 50;

		o1off = 20;
		o2off = o1off + (o1diam - o2diam) / 2;
	}
	public void paint(Graphics g)  {
		// Create big circle
		g.setColor(Color.red);
		g.fillOval(o1off, o1off, o1diam, o1diam);

		// Create small circle
		g.setColor(Color.blue);
		g.fillOval(o2off, o2off, o2diam, o2diam);
	}
}
