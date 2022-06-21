#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
int main()
{
    int gd=DETECT,gm;
    int x1,y1,x2,y2;
    int a1,b1,a2,b2;
    float sx,sy;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    setcolor(GREEN);
    printf("Enter x1,y1");
    scanf("%d%d",&x1,&y1);
    printf("Enter x2,y2");
    scanf("%d%d",&x2,&y2);
    cleardevice();
    rectangle(x1,y1,x2,y2);
     printf("Enter sx,sy");
    scanf("%f%f",&sx,&sy);
    a1=x1*sx;
    b1=y1*sy;
     a2=x2*sx;
    b2=y2*sy;
    rectangle(a1,b1,a2,b2);
    getch();
    closegraph();
    return 0;
    
}