#include "header.h"
#include "canvas.h"

Canvas cvs(640,480,"A turtle! OMG!"); //global canvas object
 
void display(void)
{
    cvs.clearScreen();//clear screen
    cvs.setWindow(-10.0,10.0,-10.0,10.0);
    cvs.setViewport(10,640,10,460);
    
    cvs.forward(10,1);
    cvs.turn(90);
    cvs.forward(10,1);
    cvs.turn(90);
    cvs.forward(10,1);
    cvs.turn(90);
    cvs.forward(10,1);
    /*
    cvs.moveTo(0,-10.0);//draw a line
    cvs.lineTo(0,10.0);
    cvs.moveTo(-10.0, 0);
    cvs.lineTo(10.0, 0);
    RealRect box(-2.0,8.0,-1.0,9.0);//construct a box
    box.draw();//draw the box
    IntRect box2(-8, -3, -9, 12);
    box2.draw();*/
}


int main(int argc, char* argv[])
{
    //the window is opened in the Canvas constructor 
    cvs.setBackgroundColor(1.0,1.0,1.0); //background is white
    cvs.setColor(0.0,0.0,0.0); //set drawing color
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

