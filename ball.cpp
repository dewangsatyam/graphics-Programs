#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
int main()
{
int gd=DETECT,gm;
int x,y;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
setfillstyle(SOLID_FILL,YELLOW);
for(x=50;x<600;x++)
{
for(y=30;y<455;y+=20)
{
x+=5;
cleardevice();
circle(x,y,30);
floodfill(x,y,WHITE);
delay(60);
}
for(y=435;y>30;y-=20)
{
x+=5;
cleardevice();
circle(x,y,30);
floodfill(x,y,WHITE);
delay(60);
}
}
getch();
closegraph();
return 0;
}