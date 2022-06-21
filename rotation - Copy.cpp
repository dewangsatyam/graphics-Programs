#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
int main()
{
    int gd=DETECT,gm;
    int x1,y1,x2,y2;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    double s,c,angle;
    setcolor(BLUE);//TO SET THE COLOR OF LINE--to set background setbkcolor()
    printf("Enter x1,y1");
    scanf("%d%d",&x1,&y1);
    printf("Enter x2,y2");
    scanf("%d%d",&x2,&y2);
    cleardevice();
    line(x1,y1,x2,y2);//draw a line
    getch();
    printf("Enter rotation angle");
    scanf("%lf",&angle);
    c=cos((angle*3.14)/180);//degree to radian
    s=sin((angle*3.14)/180);
    //new coordiantes
    //x'=xcosO -ysinO
    //y'=ycosO +xsinO
    x1=floor(x1*c-y1*s);
     y1=floor(y1*c+x1*s);
     x2=floor(x2*c-y2*s);
     y1=floor(y2*c+x2*s);
     //cleardevice();
     line(x1,y1,x2,y2);
     getch();
     closegraph();
     return 0;
}