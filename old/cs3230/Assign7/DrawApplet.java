import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class DrawApplet extends Applet implements MouseListener {
	int startX, startY;
	int		numShapes;
	Shape	shapeList[];
	
	public void init()  {
		shapeList = new Shape[100];
		numShapes = 0;
		this.addMouseListener(this); // This is for the "implemented" part
	}

	public void paint(Graphics g)  {
		for (int i=0;i<numShapes;i++)
			shapeList[i].draw(g);
	}

	public void mousePressed(MouseEvent evt) {
		startX=evt.getX();
 		startY=evt.getY();
	}
	
	public void mouseReleased(MouseEvent evt) {
		int x = evt.getX();
		int y = evt.getY();
	
		if(evt.isMetaDown()) // Right Click
			shapeList[numShapes] = new EclipseShape(startX, startY, x, y);
		else // Left click or Other
			shapeList[numShapes] = new LineShape(startX, startY, x, y);
	
		shapeList[numShapes].setColor(Color.red);
		numShapes++;
		repaint();	
	}
	
	// not used
	public void mouseExited(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	public void mouseClicked(MouseEvent e) {}
}

abstract class Shape {
	int		x,y;

	Color drawColor;
	
	public abstract void draw(Graphics g);
	public void setColor(Color c) {
		drawColor=c;
	}
}

class LineShape extends Shape {
	int  endX,endY;

	public LineShape(int x1,  int y1,  int x2,  int y2)
	{
		x=x1;
		y=y1;
		endX=x2;
		endY=y2;
	}

	public void draw(Graphics g)
	{
		g.setColor(drawColor);
		g.drawLine(x, y, endX, endY);
	}
}


class EclipseShape extends Shape {
	int endX, endY;
	
	public EclipseShape(int x1, int y1, int x2, int y2) 
	{
		x=x1;
		y=y1;
		endX=x2;
		endY=y2;	
	}
	
	public void draw(Graphics g)
	{
		int width = Math.abs(endX - x);
		int height = Math.abs(endY - y);
		int topLeftX = (x < endX ? x : endX);
		int topLeftY = (y < endY ? y : endY);
		
		g.setColor(drawColor);
		g.drawOval(topLeftX, topLeftY, width, height);
	}
}
