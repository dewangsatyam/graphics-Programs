
#include <dos.h>
#include<conio.h>
#include <graphics.h>
#include <stdio.h>
union REGS in, out;

// Function to initialize the mouse pointer
int initMouse()
{
	in.x.ax = 0;
	int86(0X33, &in, &out);

	return out.x.ax;
}

// Function to display the mouse pointer
void showMouse()
{
	in.x.ax = 1;
	int86(0X33, &in, &out);
}

// Function to hide the mouse pointer
void hideMouse()
{
	in.x.ax = 2;
	int86(0X33, &in, &out);
}

// Function to get the exact mouse position
void getMousePosition(int* x, int* y, int* click)
{
	in.x.ax = 3;
	int86(0x33, &in, &out);

	// Update the coordinates
	*x = out.x.cx;//x coordinate
	*y = out.x.dx;//y coordinate
	*click = out.x.bx & 1;  //left or right
}

// Driver Code
int main()
{
	int gd = DETECT, gm;
	int click, mousex, mousey, startx, starty, endx, endy;
	const int brushcolor = YELLOW;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	setbkcolor(BLACK);

	// Initialize  and show the mouse pointer
	initMouse();
	showMouse();

	// kbhit If a key has been pressed then it returns a non zero value
	// otherwise returns zero(false)
	while (!kbhit()) {

		// Get the mouse position
		getMousePosition(&mousex, &mousey, &click);
		if(click==1)
		{
			startx = endx = mousex;
			starty = endy = mousey;
			// setwritemode() sets the current writing mode for line drawing.  Mode can be COPY_PUT or XOR_PUT.

			//COPY_PUT - overwrites with the line on screen
			//	XOR_PUT - uses XOR command to mix line with the screen

			setwritemode(XOR_PUT);
			setcolor(WHITE-brushcolor);
			line(startx, starty, endx, endy); //start drawing line

			// till the mouse is kept left clicked
			do{
				getMousePosition(&mousex, &mousey, &click);
				if(mousex !=endx || mousey !=endy)
				{
					hideMouse();
					line(startx, starty, endx, endy); //erase previous line
					endx = mousex; //new end point of line
					endy = mousey;
					line(startx, starty, endx, endy); //draw new line
					showMouse();
				}
			} while (click == 1);

			//left click released
			setwritemode(COPY_PUT);
			setcolor(brushcolor);
			endx = mousex;
			endy = mousey;
			hideMouse();
			// Draw Final line
			line(startx, starty, endx, endy);
			showMouse();
		}

	}

	getch();

	// Close the graphics
	closegraph();

	return 0;
}