/* This program demonstrates the usage of C++ to plot charts and graphs.
   It plots the curve of the quadratic function y=ax^2+bx+c
   You can change the values of a, b and c from within the code and recompile
   the program. You can "pan" and "zoom in/out" the curve by changing the
   values of xb, xe, yb and ye. (Dr R.K. Singla)
*/

#include <graphics.h>
#include <conio.h>

/** Change the values below to suit your screen resolution.
    These values will probably suit most users.   ***/

#define MAXX 640
#define MAXY 480

/* Co-ordinate conversion functions, prototypes and declarations */
float screen_y(float, float, float);
float screen_y(float, float, float);

float screen_x(float xb, float x, float xe)
{
	return ((x-xb)/(xe-xb)*MAXX);
}

float screen_y(float yb, float y, float ye)
{
	return (MAXY-(y-yb)/(ye-yb)*MAXY);
}

void main(void)
{
	/* Change the values of 'drv' and 'mode' if you change MAXX and MAXY */
	int drv=VGA, mode=VGAHI;
	float a,b,c,xb,xe,yb,ye,x,y;

	/* You can play with the parameters below */
	a=1;
	b=0;
	c=0;
	xb=-10;
	xe=10;
	yb=-10;
	ye=150;
	/* Stop playing !!! */

	initgraph(&drv,&mode,"C:\\turboc3\\bgi");

	/* Draw the X and Y axes */
	setcolor(4);
	line(0,screen_y(yb,0,ye),MAXX,screen_y(yb,0,ye));
	line(screen_x(xb,0,xe),0,screen_x(xb,0,xe),MAXY);

	setcolor(15);
	moveto(0,screen_y(yb,a*xb*xb+b*xb+c,ye));
	for(x=xb;x<=xe;x+=(xe-xb)/MAXX)
	{
		y=a*x*x+b*x+c;
		lineto(screen_x(xb,x,xe),screen_y(yb,y,ye));
	}
	getch();
	closegraph();
	return;
}