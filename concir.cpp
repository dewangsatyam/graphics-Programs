#include<graphics.h>
#include<stdio.h>
#include<conio.h>
int main()
{
int gd=DETECT,gm;
int x,y,i,r=30;;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
x=getmaxx()/2;
y=getmaxy()/2;
outtextxy(240,50,"concenteric circle");
for(i=0;i<6;i++){
setcolor(i);
circle(x,y,r);
r+=10;
}
getch();
closegraph();
return 0;
}