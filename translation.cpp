#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
int main()
{
    //translation of triangle
    int gd=DETECT,gm;
    int x1,y1,x2,y2,x3,y3;
    int dx,dy;
    int a1,b1,a2,b2,a3,b3;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    setcolor(YELLOW);
    printf("Enter x1,y1");
    scanf("%d%d",&x1,&y1);
    printf("Enter x2,y2");
    scanf("%d%d",&x2,&y2);
    printf("Enter x3,y3");
    scanf("%d%d",&x3,&y3);
    cleardevice();
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x1,y1);
    
    printf("Enter dx,dy");
    scanf("%d%d",&dx,&dy);
    a1=x1+dx;
    b1=y1+dy;
    a2=x2+dx;
    b2=y2+dy;
    a3=x3+dx;
    b3=y3+dy;
     line(a1,b1,a2,b2);
    line(a2,b2,a3,b3);
    line(a3,b3,a1,b1);
    getch();
    closegraph();
    return 0;

}