#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	int i;
	float x,y,x1,y1,x2,y2,step,dx,dy;
	printf("Enter x1 and y1");
	scanf("%f%f",&x1,&y1);
	printf("Enter x2 and y2");
	scanf("%f%f",&x2,&y2);
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>=dy)
	{
	step=dx;
	}
	else
	{
	step=dy;
	}
	dx=dx/step;
	dy=dy/step;
	if(x1<=x2)
	{
	x=x1,y=y1;
	}
	else
	{
	x=x2,y=y2;
	}
	i=1;
	while(i<=step)
	{
	putpixel(x,y,5);
	x=x+dx;
	y=y+dy;
	i=i+1;
	}
	getch();
	closegraph();
}