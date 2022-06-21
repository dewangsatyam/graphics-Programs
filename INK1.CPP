
#include <dos.h>
#include<conio.h>
#include <graphics.h>
#include <stdio.h>
union REGS in, out;

// Function to initialize the mouse pointer
int initMouse()
{
	in.x.ax = 0;//status return
	int86(0X33, &in, &out);  //port of mouse

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

	// Get the coordinates
	int86(0x33, &in, &out);

	// Update the coordinates
	*x = out.x.cx;   //cx-x coordinate
	*y = out.x.dx;   //dx-y coordinate
	*click = out.x.bx & 1; //bx-0 not prssed
	//1-left
	//2-right
}

// Driver Code
int main()
{
	int click, status, i, gd = DETECT, gm,x1,y1,x2,y2;

	// Initialize graphics
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	initMouse();

	// kbhit If a key has been pressed then it returns a non zero value
	// otherwise returns zero(false)
	while (!kbhit()) {

		// Show the mouse pointer
		showMouse();

		// Get the mouse position
		getMousePosition(&x1, &y1, &click);
		//wahi start wahi end
		x2 = x1;
		y2 = y1;

		// When mouse is clicked
		while (click == 1) {
			hideMouse();

			// Draw line
			line(x1, y1, x2, y2);
			//now start from x2 y2
			x1 = x2;
			y1 = y2;

			// Get the mouse position
			getMousePosition(&x2, &y2, &click);
		}
	}

	getch();

	// Close the graphics
	closegraph();

	return 0;
}