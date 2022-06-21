 // Circle Drawing      
#include <graphics.h>  
#include <stdlib.h>  
#include<stdio.h>
#define color 11 
void SymmetricPlot(int xc,int yc,int x,int y)  
{  
putpixel(x+xc,y+yc,color);  
putpixel(x+xc,-y+yc,color);  
putpixel(-x+xc,-y+yc,color);  
putpixel(-x+xc,y+yc,color);  
putpixel(y+xc,x+yc,color);  
putpixel(y+xc,-x+yc,color);  
putpixel(-y+xc,-x+yc,color);  
putpixel(-y+xc,x+yc,color);  
}  
void PolarCircle(int xc,int yc,int r)  
{  
int x,y,d;  
x=0;  
y=r;  
d=3-2*r;  
SymmetricPlot(xc,yc,x,y);  
while(x<=y)  
{  
if(d<=0)  
d=d+4*x+6;   
else  
{  
d=d+4*x-4*y+10;  
y=y-1;  
}  
x=x+1;  
SymmetricPlot(xc,yc,x,y);  
}  
}  

int main(void)  
{  
int gdriver = DETECT, gmode, errorcode;  
int Cx,Cy,r;  
initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");  
errorcode = graphresult();  
if (errorcode != grOk)    
{  
printf("Graphics error: %s\n", grapherrormsg(errorcode));  
printf("Press any key to halt:");  
getch();  
exit(1);               
}  
printf("Enter the values of Cx and Cy ,that is center points of circle : ");  
scanf("%d%d",&Cx,&Cy);  
printf("Enter the radius of circle : ");  
scanf("%d",&r);  
PolarCircle(Cx,Cy,r);  
getch();  
closegraph();  
return 0;  
}
