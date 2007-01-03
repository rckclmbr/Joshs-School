//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #2
//                  Mr. Rague
//                  Due: 9/12/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This program prints "This is my red applet." inside a java
//	applet
//  -----------------------------------------------------------------
import    java.applet.Applet;
import    java.awt.Graphics;
import    java.awt.Font;
import    java.awt.Color;

public class MyApplet extends Applet {
	Font f;

	public void init(){
		f = new Font ("TimesRoman", Font.BOLD,36);
	}
	public void paint(Graphics g)  {
		g.setFont(f);
 		g.setColor(Color.red);
		g.drawString ("This is my applet.", 5, 50);
	}
}
