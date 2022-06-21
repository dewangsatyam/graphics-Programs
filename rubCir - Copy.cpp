#include<dos.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<math.h>
union REGS in, out;
#define PI 3.14159

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

void mycircle(int cenx,int ceny,int radius)
	{
	float cx,cy,angle=0;
	while(angle<360)
		{
		float THETA=PI/180.0 * angle;
		cx=cenx+radius*cos(THETA);
		cy=ceny-radius*sin(THETA);
		line(cx,cy,cx,cy);
		angle+=.5;
		}
	}

// Driver Code
int main()
{
	int gd = DETECT, gm;
	int click, mousex, mousey, startx, starty, endx, endy;
	int dx, dy, centrex, centrey, diameter, radius;
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
			startx = mousex;
			starty = mousey;
			setwritemode(XOR_PUT);
			setcolor(WHITE-brushcolor);

			// till the mouse is kept left clicked
			do{
				getMousePosition(&mousex, &mousey, &click);
				endx=mousex; endy=mousey;
				if(startx !=endx || starty !=endy)
				{
				     dx=abs(startx-endx); dy=abs(starty-endy);
				     // (centrex, centrey) is the centre
				     centrex = (startx+endx)/2;
				     centrey = (starty+endy)/2;

				     diameter = (int)(sqrt(dx * dx + dy * dy)); //x^2 + y^2 = r^2
				     radius = diameter/2;
				     hideMouse();
				     mycircle(centrex, centrey, radius); //draw circle
				     mycircle(centrex, centrey, radius); //erase circle
				     showMouse();
				}//end of if
			} while (click == 1);

			//left click released
			setwritemode(COPY_PUT);
			setcolor(brushcolor);

			hideMouse();
			// Draw Final Circle
			circle(centrex, centrey, radius);
			showMouse();
		} //end of if

	} //end of while

	getch();

	// Close the graphics
	closegraph();

	return 0;
}