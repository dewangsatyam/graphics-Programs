/********************************************************/
/* PROGRAM TO DRAW SINE & COSINE CURVE  (Dr R.K. Singla)*/
/********************************************************/
// view algorithm
#include<graphics.h>
#include<math.h>
#include<conio.h>
#define pie 3.1412

void transform (float minang, float maxang, int option, int l, int b, int t, int r);

void main(){
int option, l, b, t, r;
float ang2, iang, ang1, maxang, maxy;

int gd = VGA, gm = VGAHI, ec = 0;
clrscr();
gotoxy(20, 4); printf("sin/cosine curve drawing");
gotoxy(20, 6); printf("Press 1->SINE CURVE");
gotoxy(20, 8); printf("Press 2->COSINE CURVE");
gotoxy(20, 10); printf("Enter the option:");
gotoxy(40, 10);scanf("%d", &option);

gotoxy(20, 12);printf ("enter the initial angle in degrees:");
gotoxy(56, 12);scanf("%f", &iang); ang1=(iang * pie) / 180;
gotoxy(20, 14);printf("Enter the maximum value of angle in degrees:");
gotoxy(70, 14);scanf("%f", &maxang); ang2=(maxang * pie)/180;
printf("\n\n\n         Press any key to conitune"); getch();
initgraph(&gd, &gm, "C:\\turboc3\\bgi");
ec=graphresult();
if(ec!=0)printf("Graphics system error\n",grapherrormsg(ec));

//printf("Enter the coordinates for the viewport:\n");
//scanf("%d %d %d %d", &l, &t, &r, &b);
l=0; t=0; r=639; b=479;
setviewport(l, t, r, b, 0);
//printf("\n%d %d", getmaxx(), getmaxy());

cleardevice();
rectangle (l, t, r, b);
line(l, b - ((b - t)/2), r, b-((b - t)/2));
transform (ang1, ang2, option, l, t, r, b);
getch();
}

/************************************************************/
/*Transformation of world coordinates to screen coordinates**/
/*World coordinates: xmin, ymin, xmax, y max               **/
/*screen coordinates: sxmin, symin, sxmax, symax           **/
/************************************************************/

void transform (float minang, float maxang, int option,int l, int t, int r, int b){
float temp, x, y, xmax, ymax, xmin, ymin, sxmax, symax, sxmin, symin;
double sx, sy;

sxmin = l; sxmax = r;
symin = t; symax = b;
xmin = minang; xmax = maxang;
ymin = -1.0; ymax = 1.0;

while (minang <= maxang){
if (option == 1) temp = sin(minang);
else temp = cos(minang);
y = -(temp);
x = minang;

sx = (double)((sxmin)+(((sxmax-sxmin)/(xmax- xmin)) *(x-xmin)));
sy = (double)((symin)+(((symax-symin)/(ymax- ymin)) *(y-ymin)));

putpixel((long)sx, (long)sy,3);
minang += 0.05;
}
}