// C++ program to perform Inking/Free hand Draw (using mouse programming) (Dr R.K. Singla)
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
	int click, mousex, mousey, startx, starty;
	const int brushcolor = RED;
	// Initialize graphics
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	initMouse();
	// Show the mouse pointer
	showMouse();
	setbkcolor(LIGHTGRAY);
	
	// kbhit If a key has been pressed then it returns a non zero value
	// otherwise returns zero(false)
	while (!kbhit()) {

		// Get the mouse position
		getMousePosition(&mousex, &mousey, &click);
		if(click==1)
		{
			startx = mousex;
			starty = mousey;
			setcolor(brushcolor);
			hideMouse();
			putpixel(startx, starty, brushcolor); //start free hand drawing
			showMouse();
			// Till the mouse is kept left clicked
			do{
				getMousePosition(&mousex, &mousey, &click);
				if(mousex != startx || mousey != starty)
				{
					hideMouse();
					// Draw line for free hand drawing
					line(startx, starty, mousex, mousey);
					showMouse();
					startx = mousex;
					starty = mousey;
				}

			} while (click == 1);

		} //end of if

	} //end of while

	getch();

	// Close the graphics
	closegraph();

	return 0;
}// end of main