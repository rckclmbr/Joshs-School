//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #11
//                  Mr. Rague
//                  Due: 11/28/2006
//                  Version: 1.0
//  -----------------------------------------------------------------

//  -----------------------------------------------------------------
import java.awt.Graphics;
import java.awt.Font;
import java.util.Date;

public class DigClock extends java.applet.Applet implements Runnable  {

	Font  fnt = new Font("Helvetica",Font.BOLD,20);
	Date theDate;
	volatile Thread myThread;
	
	public void start()  {
		if (myThread == null)  {
			myThread = new Thread(this);
			myThread.start();
		}
	}
	
	public void stop()  {
		myThread = null; 
	}

	public void run() {
		while (true)  {
			theDate = new Date();
			repaint();
			try  { Thread.sleep(1000); }
			catch (InterruptedException e)  { }
		}
	}

	public void paint(Graphics g)  {
		theDate = new Date();
		g.setFont(fnt);
		g.drawString(theDate.toString(),5,20);
		//g.drawString("a string",5,20);
	}
}