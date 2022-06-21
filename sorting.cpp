#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
//#include"mouseanimate.h"
#include<graphics.h>
void sort(int *,int);
void move(int ,int,int *);
#include<graphics.h>
#define startx 300
#define starty 50
void drawrect(int a[],int n)
{
int i = 0;
char *str = "\0";
int s = 0;
setfillstyle(1,1);
for(i = 0;i < n; i++)
{
s= starty+(i*30);
itoa(a[i],str,10);
bar(startx,s,startx+20,s+20);
outtextxy(startx+5,s+5,str);

}
}
void move(int i,int j,int a[])
{
int y1,y2,flag,x;
char *str1,*str2;
flag=0;
x=startx;
y1=starty+i*30;
y2=starty+j*30;
while(flag!=3)
{
bar(x,y1,x+20,y1+20);
bar(x,y2,x+20,y2+20);
itoa(a[i],str1,10);
outtextxy(x+5,y1+5,str1);
itoa(a[j],str2,10);

outtextxy(x+5,y2+5,str2);
delay(10);
// bar(x,y1,x+20,y1+20);
// bar(x,y2,x+20,y2+20);

if(flag==0)
{
x++;
}
else if(flag==1)
{ y1++;
y2--;
}
else if(flag==2)
{
x--;
}
if(x>=startx+100)
{
flag=1;
}
if(y1>=starty+j*30)
{
flag=2;
}
if(x<=startx)
{
flag=3;
}
}
bar(x,y1,x+20,y1+20);
bar(x,y2,x+20,y2+20);
itoa(a[i],str1,10);
itoa(a[j],str2,10);
outtextxy(x+5,y1+5,str1);
outtextxy(x+5,y2+5,str2);

}
int main()
{
int gd=DETECT,gm,n,a[10],i;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
printf("\n Enter the no of element");
scanf("%d",&n);
printf("\n Enter element please");
for(i=0;i<n;i++)
{
scanf("%d",&a[i]);
}
drawrect(a,n);
sort(a,n);
getch();
closegraph();
return(0);
}
void sort(int a[],int n)
{
int i,j,temp;
for(i=0;i<n-1;i++)
{
for(j=0;j<n-i-1;j++)
{
if(a[j]>a[j+1])
{
move(j,j+1,a);
temp=a[j];
a[j]=a[j+1];
a[j+1]=temp;
}
}
}
}
