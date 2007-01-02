//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #2
//                  Mr. Rague
//                  Due: 9/12/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This program centers red text in a blue box.  There is a yellow
//	background.
//  -----------------------------------------------------------------
import    java.applet.Applet;
import	  java.awt.*;

public class CenterTextApplet extends Applet {
	Font f;
	int rectx, recty, rectoffx, rectoffy;

	public void init(){
		f = new Font ("Helvetica", Font.BOLD,36);

		rectx = 20;
		recty = 20;
		rectoffx = 500;
		rectoffy = 100;

		// Set background to yellow
		setBackground(Color.yellow); 
	}
	public void paint(Graphics g)  {
		String str = "This is my Big Red Applet.";

		// Create blue box
		g.setColor(Color.blue);
		g.fillRect(rectx, recty, rectoffx, rectoffy);

		// Get x and y coordinates
		g.setFont(f);	// First set font so we get the right size
		FontMetrics metrics = g.getFontMetrics();
		int x = rectx + ((rectoffx - metrics.stringWidth(str)) / 2);
		int y = recty + ((rectoffy + metrics.getHeight() / 2) / 2);

		// Insert text
 		g.setColor(Color.red);
		g.drawString (str, x, y);
	}
}
