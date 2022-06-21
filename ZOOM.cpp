/* Zooming and Panning Demo in Interactive Computer Graphics  (Dr R.K. Singla)

   This file demonstrates the usage of C++ to plot charts and graphs.
   It plots the curve of the sinusoidal function y=a.sin(bx+c)
   You can change the values of a, b and c from within the code and recompile
   the program. You can "pan" and "zoom in/out" the curve during display
   using these keys:
   =================
   z: pan left
   x: pan right
   q: pan up
   w: pan down

   +: Y-axis zoom in
   -: Y-axis zoom out
   [: X-axis zoom out
   ]: X-axis zoom in

   /: Default (initial) zoom

   Note: to run this program, you need the file EGAVGA.BGI in the same
   directory as the executable file... This file is supplied with Borland and
   Turbo C++ */

#include <graphics.h>
#include <conio.h>
#include <math.h>

/* Change the values below to suit your screen resolution.
   These values will probably suit most users. */
#define MAXX 640
#define MAXY 480

/* Co-ordinate conversion functions, prototypes and declarations */
float screen_y(float, float, float);
float screen_y(float, float, float);
/* The user-defined function to be plotted */
float my_func(float);

/* You can use all the parameters below as coeffecients
   to whatever function you wish to plot. You should assign them
   values in main() and define your function in my_func() */
float a,b,c,d,e,f,g,h,i,j;

float screen_x(float xb, float x, float xe)
{
	return ((x-xb)/(xe-xb)*MAXX);
}

float screen_y(float yb, float y, float ye)
{
	return (MAXY-(y-yb)/(ye-yb)*MAXY);
}

float my_func(float x)
{
	/* Define your function here */
	return a *  sin( ( b * x + c ) * 3.1415 / 180.0) ;
}

void main(void)
{
	/* Change the values of 'drv' and 'mode' if you change MAXX and MAXY */
	int drv=VGA, mode=VGAHI;
	float xb,xe,yb,ye,x,y,potx,poty;
	char key;

	/* You can play with the parameters below */
	a  = 1;
	b  = 1;
	c  = 0;
	xb = -360;
	xe = 360;
	yb = -10;
	ye = 10;
	/* Stop playing !!! */

	initgraph(&drv,&mode,"c:\\turboc3\\bgi");

	/* Draw the X and Y axes */
	setcolor(4);
	line(0,screen_y(yb,0,ye),MAXX,screen_y(yb,0,ye));
	line(screen_x(xb,0,xe),0,screen_x(xb,0,xe),MAXY);

	setcolor(15);
	moveto(0,screen_y(yb,my_func(xb),ye));
	for(x=xb;x<=xe;x+=(xe-xb)/MAXX)
	{
		y = my_func(x);
		lineto(screen_x(xb,x,xe),screen_y(yb,y,ye));
	}

	while((key=getch())!=27) /* Repeat the loop until [ESC] pressed */
	{
		potx = xb;
		poty = yb;
		switch(key)
		{
			case 'z':		/* pan left */
					xb -= (xe-xb)/4.0;
					xe -= (xe-potx)/4.0;
					break;
			case 'x':       /* pan right */
					xb += (xe-xb)/4.0;
					xe += (xe-potx)/4.0;
					break;
			case 'q':       /* pan up */
					yb += (ye-yb)/4.0;
					ye += (ye-poty)/4.0;
					break;
			case 'w':       /* pan down */
					yb -= (ye-yb)/4.0;
					ye -= (ye-poty)/4.0;
					break;
			case '+':	/* Y-axis zoom out */
					yb -= (yb-ye)/4.0;
					ye += (poty-ye)/4.0;
					break;
			case '-':      /* Y-axis zoom in */
					yb += (yb-ye)/4.0;
					ye -= (poty-ye)/4.0;
					break;
			case '[':	/* X-axis zoom out */
					xb += (xb-xe)/4.0;
					xe -= (potx-xe)/4.0;
					break;
			case ']':		/* X-axis zoom in */
					xb -= (xb-xe)/4.0;
					xe += (potx-xe)/4.0;
					break;
			case '/':	/* Home (initial view) */
					xb = -360;
					xe = 360;
					yb = 10;
					ye = -10;
					break;
			default:
					//continue;
					break;
		}

		cleardevice();
		/* Draw the X and Y axes */
		setcolor(4);
		line(0,screen_y(yb,0,ye),MAXX,screen_y(yb,0,ye));
		line(screen_x(xb,0,xe),0,screen_x(xb,0,xe),MAXY);

		setcolor(15);
		moveto(0,screen_y(yb,my_func(xb),ye));
		for(x=xb;x<=xe;x+=(xe-xb)/MAXX)
		{
			y = my_func(x);
			lineto(screen_x(xb,x,xe),screen_y(yb,y,ye));
		}

	}
	closegraph();
	return;
}