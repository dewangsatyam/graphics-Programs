#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
void main()
{
       int gd=DETECT,gm;
       int d,r,x,y,xc,yc;
       clrscr();
       initgraph(&gd,&gm,"C://TURBOC3//BGI");
       printf("enter the radius");
       scanf("%d",&r);
       printf("enter the centre of circle");
       scanf("%d",&xc);
       scanf("%d",&yc);
       for(int i=0;i<=7;i++)
       {
       d=3-2*r;
       x=0;
       y=r;
       while(x<=y)
       {
  putpixel(xc+x,yc+y,6);
  putpixel(xc-y,yc-x,6);
  putpixel(xc+y,yc-x,6);
  putpixel(xc-y,yc+x,6);
  putpixel(xc+y,yc+x,6);
  putpixel(xc-x,yc-y,6);
  putpixel(xc+x,yc-y,6);
  putpixel(xc-x,yc+y,6);
  if(d<=0)
  {

     d=d+4*x+6;
  }
  else
  {
      d=d+4*x-4*y+10;
      y=y-1;

  }
  x=x+1;
  delay(30);
}
r=r+15;
}
getch();
}
