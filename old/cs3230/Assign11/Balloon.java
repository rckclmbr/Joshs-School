//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #11
//                  Mr. Rague
//                  Due: 11/28/2006
//                  Version: 1.0
//  -----------------------------------------------------------------

//  -----------------------------------------------------------------
import java.awt.*;

public class Balloon extends java.applet.Applet implements Runnable  {

	// These are for double buffering
	Image offscreen;
	Dimension dim; 
	Graphics bufferGraphics; 

	volatile Thread myThread;
	int x = 0, y = 0, width, height;
	
	public void start()  {
		if (myThread == null)  {
			myThread = new Thread(this);
			myThread.start();
		}
	}
	
	public void stop()  {
		myThread = null; 
	}

	public void init() {
		this.setBackground(Color.blue);

	}

	public void run() {
		// For double buffering
		dim = this.getSize();
		offscreen = createImage(dim.width,dim.height); 
		bufferGraphics = offscreen.getGraphics();
		width = dim.width;
		height = dim.height;
		
		while (true)  {
			while(width > 0) {
				try  { Thread.sleep(1); }
				catch (InterruptedException e)  { }
				width = width - 1;
				height = height - 1;
				x = (dim.width - width) / 2;
				y = (dim.height - height) / 2;
				repaint();
			}
			
			while(width < this.getWidth()) {
				try  { Thread.sleep(1); }
				catch (InterruptedException e)  { }
				width = width + 1;
				height = height + 1;
				x = (dim.width - width) / 2;
				y = (dim.height - height) / 2;
				repaint();
			}
		}
	}

	public void paint(Graphics g)  {
		bufferGraphics.clearRect(0,0,dim.width,dim.width); 
		bufferGraphics.setColor(Color.red);
		bufferGraphics.fillOval(x,y,width,height);

		g.drawImage(offscreen,0,0,this);
	}

	// Overridden to avoid flicker
	public void update(Graphics g)
	{
	  paint(g);
	} 
}