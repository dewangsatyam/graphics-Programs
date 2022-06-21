#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
//void draw(int x1,int y1,int x2,int y2, int c);
void draw(int x1,int y1,int x2,int y2,int c)
{
float dx,dy,p;
int i,x,y,xend;
dx=x2-x1; dy=y2-y1;
p=2*dy-dx;
if(x1>x2)
{
x=x2;y=y2;
xend=x1;
}
else
{
x=x1; y=y1;
xend=x2;
}
putpixel(x,y,c);
while(x<xend)
{
if(p<0)
{
x=x+1;
putpixel(x,y,c);
p=p+(2*dy);
}
else
{
x=x+1; y=y+1;
putpixel(x,y,c);
p=p+(2*dy)-(2*dx);
}
}
}

void drawline(int x0, int y0, int x1, int y1,int c)
{
    while(y0<y1)
    { if(x0 == x1)
       {
    putpixel(x0,y0,c);
    y0=y0+1;
    }
    }
}
void main()
{
int i,j,a,b, gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

for( a =0; a<=50;a=a+3)
{
draw(50,210-a,150,210-a,6);
drawline(50,160,50,210,6);
drawline(150,160,150,210,6);
delay(50);
}
for( b =0;b<=100;b=b+3)
{
drawline(150-b,310,150-b,410,8);
draw(50,310,150,310,8);
draw(50,410,150,410,8);
delay(50);
}

for( j =0; j<=100; j=j+3)
{
drawline(350+j,50,350+j,410,11);
draw(350,50,450,50,11);
draw(350,410,450,410,11);
delay(50);
}
getch();
}
