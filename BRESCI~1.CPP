 #include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
void drawCircle(int x,int y,int xc,int yc)
{
    putpixel(x+xc,y+yc,RED);
    putpixel(-x+xc,y+yc,RED);
    putpixel(x+xc,-y+yc,RED);
    putpixel(-x+xc,-y+yc,RED);
    putpixel(y+xc,x+yc,RED);
    putpixel(-y+xc,x+yc,RED);
    putpixel(y+xc,-x+yc,RED);
    putpixel(-y+xc,-x+yc,RED);
}
void circleBres(int xc,int yc,int r)
{
    //take initial point x=0 and y=r
    int x=0,y=r;
    int d=3-2*r;
    //draw circle with this point
    drawCircle(x,y,xc,yc);
    while(y>=x)// y will decrease and x will increase
    {
	if(d<0)
	{
	    x++;
	    d+=4*x+6;
	}
	else
	{
	    x++;
	    y--;
	    d+=(4*(x-y)+10);
	}
	drawCircle(x,y,xc,yc);
	delay(30);
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
    circleBres(xc,yc,r);
    getch();
    closegraph();
    return 0;


}
