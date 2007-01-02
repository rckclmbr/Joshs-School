import	java.applet.Applet;
import 	java.awt.*;
import	java.util.Random;

//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #4
//                  Mr. Rague
//                  Due: 9/26/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This application create an applet that displays a different color
//  every time the application starts 
//  -----------------------------------------------------------------

public class ColorChanger extends Applet {
	
	Random r;
	Color[] colors;
	Color currentColor;
	
	public void init() {
		Color[] tempcolor = {Color.red, Color.blue, Color.yellow, Color.green};
		colors = tempcolor;

		r = new Random();
	}

	public void start() {
		Color oldColor = currentColor;
		while(currentColor == oldColor) {
			currentColor = colors[r.nextInt(4)];
		}
	}
		
	public void paint(Graphics g) {
		g.setColor(currentColor);
		g.fillRect(0,0,400,200);
	}

}
