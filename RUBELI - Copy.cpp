#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include<math.h>
#define PI 3.14159

union REGS in,out;
void initmouse(){ in.x.ax=0; int86(0x33,&in,&out);}
void showmouse(){ in.x.ax=1; int86(0x33,&in,&out);}
void hidemouse(){ in.x.ax=2; int86(0x33,&in,&out);}
void getmousepos(int &button,int &x,int &y)
{ 	in.x.ax=3; int86(0x33,&in,&out);
	button=out.x.bx; x=out.x.cx; y=out.x.dx;
}

const int colour = RED;

void myellipse(int cenx,int ceny,int xrad,int yrad)
	{
	float cx,cy,angle=0;
	while(angle<360)
		{
		float THETA=PI/180.0 * angle;
		cx=cenx+xrad*cos(THETA);
		cy=ceny-yrad*sin(THETA);
		line(cx,cy,cx,cy);
		angle+=.5;
		}
	}

void rub_circle()
{
	int button,mousex,mousey,startx,starty,dx,dy;
	while(!kbhit())
	{
	getmousepos(button,mousex,mousey);
	if(button & 1==1)
		{	getmousepos(button,mousex,mousey);
			setwritemode(XOR_PUT);
			setcolor(WHITE-colour);
			startx=mousex;
			starty=mousey;
			while((button & 1)==1)
			{
			getmousepos(button,mousex,mousey);
			hidemouse();
			if(mousex>=startx && mousey>=starty)
				{ dx=mousex-startx; dy=mousey-starty;}
			if(mousex<startx&&mousey<starty)
				{ dx=startx-mousex; dy=starty-mousey;}
			if(mousex<startx&&mousey>starty)
				{ dx=startx-mousex; dy=mousey-starty;}
			if(mousex>startx&&mousey<starty)
				{ dx=mousex-startx; dy=starty-mousey;}

			myellipse((startx+mousex)/2,(starty+mousey)/2,dx/2,dy/2);
			myellipse((startx+mousex)/2,(starty+mousey)/2,dx/2,dy/2);
			showmouse();
			}
			setwritemode(COPY_PUT);
			setcolor(colour);
			hidemouse();
			ellipse((startx+mousex)/2,(starty+mousey)/2,0,360,dx/2,dy/2);
			showmouse();

		} //end of if
		showmouse();
	} //end of while
} //end of rubber band circle

void main()
{
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");

	initmouse(); showmouse();
	setcolor(BLACK);
	rub_circle();
	getch();
	closegraph();
}