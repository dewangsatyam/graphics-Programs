/* This program is to draw Polar Functions */

#include <graphics.h>
#include <conio.h>
#include <math.h>

/** Change the values below to suit your screen resolution.
    These values will probably suit most users.   ***/
#define MAXX 640
#define MAXY 480

/* Co-ordinate conversion functions, prototypes and declarations */
float screen_y(float, float, float);
float screen_y(float, float, float);
float P2Q_x(float, float);
float P2Q_y(float, float);
/**********************************************************/

float screen_x(float xb, float x, float xe)
{
	return ( (x - xb) / (xe - xb) * MAXX );
}

float screen_y(float yb, float y, float ye)
{
	return ( MAXY - (y - yb) / (ye - yb) * MAXY);
}

/***********************************************************/
/****** The 2 functions below convert a polar **************
********point into a quadratic point ***********************/
float P2Q_x(float r, float phi)
{
	return r * cos(phi);
}

float P2Q_y(float r, float phi)
{
	return r * sin(phi);
}

/**********************************************************/
void main(void)
{
	/* Change the values of 'drv' and 'mode' if you change MAXX and MAXY */
	int drv = VGA, mode = VGAHI;
	float phi, r, xb, xe, yb, ye, x, y;

	/* You can play with the parameters below to determine the viewable
	   area of your graph */
	xb = -3;
	xe = 3;
	yb = -3;
	ye = 3;
	/* Stop playing !!! */

	initgraph(&drv, &mode, "C:\\TURBOC3\\BGI");

	/* Draw the X and Y axes */
	setcolor(15);
	line( 0, screen_y(yb, 0, ye), MAXX, screen_y(yb, 0, ye) );
	line( screen_x(xb, 0, xe), 0, screen_x(xb, 0, xe), MAXY );

	moveto( screen_x(xb, 0, xe), screen_y(yb, 0, ye) );
	for(phi = 0; phi < 2 * 3.1415; phi += 0.02)
	{
		r = sin(2 * phi) + 2 * cos(3 * phi);
		x = P2Q_x(r, phi);
		y = P2Q_y(r, phi);
		lineto(screen_x(xb, x, xe), screen_y(yb, y, ye) );
	}
	getch();
	closegraph();
	return;
}