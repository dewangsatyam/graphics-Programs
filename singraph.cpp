#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
void main() 
{
int gd=DETECT,gm;
int angle;
int amplitude;
double x,y;
printf("enter the angle:");
scanf("%d",&angle);
printf("enter the amplitude");
scanf("%d",&amplitude);
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
line(0,getmaxy()/2,getmaxx(),getmaxy()/2);//line in the middle
for(x=0;x<500;x=x+3){
y=amplitude*sin(angle*3.141/180);
y=getmaxy()/2-y;
putpixel(x,y,15);
delay(100);
angle=angle+5;
}
getch();
closegraph();
}