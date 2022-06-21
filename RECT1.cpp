// C++ program to perform Rubberbanding-Rectangle (using mouse programming) (Dr R.K. Singla)
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

	// Get the coordinates
	int86(0x33, &in, &out);

	// Update the coordinates
	*x = out.x.cx;
	*y = out.x.dx;
	*click = out.x.bx & 1;
}

// Driver Code
int main()
{
	int gd = DETECT, gm;
	int click, mousex, mousey, startx, starty, endx, endy;
	const int brushcolor = RED;

	// Initialize graphics
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	setbkcolor(LIGHTGRAY);

	// Initialize mouse and show the mouse pointer
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
			setwritemode(XOR_PUT);
			setcolor(WHITE-brushcolor);
			rectangle(startx, starty, endx, endy); //start drawing rectangle

			// till the mouse is kept left clicked
			do{
				getMousePosition(&mousex, &mousey, &click);
				if(mousex !=endx || mousey !=endy)
				{
					hideMouse();
					rectangle(startx, starty, endx, endy); //erase previous rectangle
					endx = mousex; //new end points
					endy = mousey;
					rectangle(startx, starty, endx, endy); //draw new rectangle
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
			rectangle(startx, starty, endx, endy);
			showMouse();
		} //end of if

	} //end of while

	getch();

	// Close the graphics
	closegraph();

	return 0;
}