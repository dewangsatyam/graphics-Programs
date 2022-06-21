#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
void drawCircle(int x,int y,int xc,int yc)
{
    putpixel(x+xc,y+yc,YELLOW);
    putpixel(-x+xc,y+yc,YELLOW);
    putpixel(x+xc,-y+yc,YELLOW);
    putpixel(-x+xc,-y+yc,YELLOW);
    putpixel(y+xc,x+yc,YELLOW);
    putpixel(-y+xc,x+yc,YELLOW);
    putpixel(y+xc,-x+yc,YELLOW);
    putpixel(-y+xc,-x+yc,YELLOW);
}
void circlemid(int xc,int yc,int r)
{
    int x=0,y=r;
    int d=1-r;
    drawCircle(x,y,xc,yc);
    while(y>=x)
    {
        if(d<0)
        {
            x++;
            d+=2*x+3;
        }
        else
        {
            x++;
            y--;
            d+=(2*(x-y)+5);
        }
        drawCircle(x,y,xc,yc);
        delay(60);
    }
}
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    int xc,yc,r;
    printf("Enter x and y");
    scanf("%d%d",&xc,&yc);
    printf("Enter radius");
    scanf("%d",&r);
    if(r<=0)
    {
        printf("Radius cannot be zero or negative");
        return 0;
    }
    circlemid(xc,yc,r);
    getch();
    closegraph();
    return 0;
}