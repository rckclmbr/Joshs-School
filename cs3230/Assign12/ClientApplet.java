//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #12
//                  Mr. Rague
//                  Due: 12/08/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the applet that interacts with the server.  I now that
//  the applet was essentially already written, but I wondered if I
//  could use the other part of the assignment to write to the server.
//  It turns out I can.  The only difference is that, the way I coded
//  it, it will keep on making connections to server, rather than
//  just connecting once and remaining idle. (but at least this way
//  I can send more than one message, and the code is a lot shorter
//  too.)
//  -----------------------------------------------------------------

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class ClientApplet extends Applet implements ActionListener, Runnable {
	TextField inputfield;
	TextArea outputarea;
	String outString;

	public void init() {
		inputfield = new TextField();
		outputarea = new TextArea(80,30);
		outputarea.setEditable(false);
		this.setLayout(new BorderLayout());
		this.add("North",inputfield);
		this.add("Center",outputarea);
		inputfield.addActionListener(this);
	}
	
	public void run() {
		String thisText = this.outString; // Just in case we have multiple threads at the same time
		ClientTest ct = new ClientTest();
		String ret = ct.process(thisText);
		outputarea.append("Sent: " + thisText + "\n");
		outputarea.append("Received: " + ret + "\n");		
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource() == inputfield) {
			this.outString = inputfield.getText(); // In case we have multiple threads
			inputfield.setText("");
			new Thread(this).start();
		}
	}
}