//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #3
//                  Mr. Rague
//                  Due: 9/19/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This applet accepts user input from an html param, and displays
//  the name and age in an applet window 
//  -----------------------------------------------------------------

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Font;
import java.awt.Color;

public class MyNewApplet extends Applet {
	Font f;
	String name;
	int age;

	public void init() {
		f= new Font("TimesRoman", Font.BOLD,36);
		this.name = this.getParameter("name");
		if(this.name == null)
			this.name = "One with no name.";
		String s = this.getParameter("age");
		if(s == null)
			this.age = 0;
		else
			this.age = Integer.parseInt(s);
	}

	public void paint(Graphics g) {
		g.setFont(f);
		g.setColor(Color.red);
		String s = "Hello, " + this.name + ".  Your age is " + this.age;
		g.drawString(s,5, 50);
	}
}

