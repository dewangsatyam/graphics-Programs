#include<iostream.h>
#include<conio.h>
#include<graphics.h>
// Defining region codes
 int x_max , y_max, x_min, y_min;
const int INSIDE = 0;
const int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;
int computeCode(double x, double y)
{
 int code = INSIDE;
 if (x < x_min)
code |= LEFT;
 else if (x > x_max)
code |= RIGHT;
 if (y < y_min)
code |= BOTTOM;
 else if (y > y_max)
code |= TOP;
 return code;
}
void cohenSthAlgo(double x1, double y1,
double x2, double y2)
{
 // region codes
 int code1 = computeCode(x1, y1);
 int code2 = computeCode(x2, y2);
 int accept = 0;
 while (1)
 {
if ((code1 == 0) && (code2 == 0))
{
 accept = 1;
 break;
}
else if ((code1 & code2)!=0)
 break;
else
{
 int code_out;   //temp variable
 double x, y;
 if (code1 != 0)  //point x1 y1 is out

code_out = code1;
 else
code_out = code2;
//--FORMULAS---
 // y = y1 + slope * (x - x1),
 // x = x1 + (1 / slope) * (y - y1)
 if (code_out & TOP)
 {
x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
y = y_max;
 }
 else if (code_out & BOTTOM)
 {
x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
y = y_min;
 }
 else if (code_out & RIGHT)
 {
y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
x = x_max;
 }
 else if (code_out & LEFT)
 {
y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
x = x_min;
 }
 if (code_out == code1)
 {
x1 = x;
y1 = y;
code1 = computeCode(x1, y1);
 }
 else
 {
x2 = x;
y2 = y;
code2 = computeCode(x2, y2);
 }
}
 }
 if (accept)
 {
line(x1, y1, x2, y2);
 }
 else
cout << "Line rejected" << endl;
}

void main()
{
 clrscr();
 double px1, py1, px2, py2;
 int gd = DETECT,gm;
 initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
 cout<<"Enter window minimum coordinates : ";
 cin>>x_min>>y_min;
 cout<<"Enter window maximum coordinates : ";
 cin>>x_max>>y_max;
 cout<<"Enter initial coordinates of line:  ";
 cin>>px1>>py1;
 cout<<"Enter final coordinates of line: ";
 cin>>px2>>py2;
 rectangle(x_min, y_max, x_max, y_min);
 line(px1, py1, px2, py2);
 outtextxy(300, 455,"Press a key to clip line");
 getch();
 setcolor(BLUE);
 cohenSthAlgo(px1, py1, px2, py2);
 getch();
}
