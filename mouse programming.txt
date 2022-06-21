#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
union REGS in,out;

void status()
{
in.x.ax=0;
int86(0x33,&in,&out);
}

void show()
{
in.x.ax=1;
int86(0x33,&in,&out);
}

void main()
{
clrscr();
status();
show();
   in.x.ax=3;

while(!kbhit())
{
     int86(0x33,&in,&out);
     switch(out.x.bx)
     {
     case 1:
     gotoxy(33,12);
     printf("LEFT BUTTON");
     gotoxy(35,13);
     printf("%d %d",out.x.cx,out.x.dx);
     break;
     case 2:
     gotoxy(33,12);
     printf("RIGHT BUTTON");
     gotoxy(35,13);
     printf("%d %d",out.x.cx,out.x.dx);
     break;
     case 0:
     gotoxy(33,12);
     printf("Number Pressed");
     gotoxy(35,13);
      printf("%d %d",out.x.cx,out.x.dx);
     break;
}
  delay(100);
  clrscr();
}
}
