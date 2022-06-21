/*  surf-ori.C  -  By R.K. Singla - Hiden Line Elimination
    Back-Face Removal Algorithm

    This program uses 3D Animation to display a house with hidden lines.
    The direction of rotation can be changed by using cursor control
    keys. The escape key can be used to abort the program.

    - Computes Eye Co-ordinates : xe, ye, ze
    - Applies  Perspective Transformation
    - Applies  3D-Rotation Transformation
*/
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <dos.h>
/* define global variables */
int rho=40,d=250;
/* define the 10 corners of the house */
int v[10][3]=
     {
	{5,7,-5}, {5,7,5}, {5,-7,5}, {5,-7,-5},
	{-5,7,-5}, {-5,-7,-5},  {-5,-7,5}, {-5,7,5},
	{0,7,8}, {0,-7,8}
     };
int sv[10][2],rot=1;
int nps[7]={5,6,5,6,5,5,5};
static int s[7][6] = {
	       {0,1,2,3,0}, {0,4,7,8,1,0}, {4,5,6,7,4},
	       {3,2,9,6,5,3}, {2,1,8,9,2}, {6,9,8,7,6},
	       {0,3,5,4,0}
	     };
int n[7][3], e[12][3];
int originx=320,originy=150, page=0;
char c;
double theta=.7,phi=0.9;
float s1,s2,c1,c2;
main()
{
  int gd=VGA,gm=VGAMED;
  initgraph(&gd,&gm,"c:\\turboc3\\bgi");
  for(;;)
   {
       if(kbhit()) keypressed();
       rotation();
       pageflip();
       generatepoint();
       normvector();
       visibility();
       drawedges();
   }
}/* end of main */
screenxy(int x, int y, int z, int *scx, int *scy)
{
   float xe,ye,ze;
   xe=-x*s1 + y*c1;
   ye=-x*c1*c2 - y*s1*c2 + z*s2;
   ze=-x*s2*c1 - y*s1*s2 - z*c2 + rho;
   *scx = (d*xe)/ze;
   *scy = (d*ye)/ze;
   return 0;
}

rotation()
{
  switch(rot)
   { case 1 : phi   +=.1;break;
     case 2 : theta +=.1;break;
     case 3 : phi   -=.1;break;
     case 4 : theta -=.1;break;
     case 5 : rho   -=800;break;
     case 6 : rho   +=800;break;
     case 7 : d -=800;break;
   }
   s1=sin(theta); s2=sin(phi);
   c1=cos(theta); c2=cos(phi);
   return 0;
}
keypressed()
{
  c=getch();
  if(c==27) { restorecrtmode();exit(0);}
  if(c==0)
  {
    c=getch();
    switch(c)
    {   case 72 : rot=1;break;
	case 77 : rot=2;break;
	case 80 : rot=3;break;
	case 75 : rot=4;break;
	case 59 : rot=5;break;
	case 60 : rot=6;break;
	case 61 : rot=7;break;
    }
  }
  return 0;
}
pageflip()
{  setvisualpage(page);
   page=1-page;
   setactivepage(page);
   clearviewport();delay(200);
   return 0;
}
generatepoint()
{
  int i,x,y,z;
  for(i=0;i<10;i++)
  {   x=v[i][0];
      y=v[i][1];
      z=v[i][2];
      screenxy(x,y,z,&sv[i][0],&sv[i][1]);
      sv[i][0]=originx+sv[i][0];
      sv[i][1]=originy-sv[i][1];
   }
   return 0;
}
normvector()
{
  int i,j1,j2,k,u1,u2,u3,v1,v2,v3;
  for(i=0;i<7;i++)
    { j1=s[i][1]; j2=s[i][2]; k=s[i][0];
      u1=v[j1][0]-v[k][0];
      u2=v[j1][1]-v[k][1];
      u3=v[j1][2]-v[k][2];
      v1=v[j2][0]-v[k][0];
      v2=v[j2][1]-v[k][1];
      v3=v[j2][2]-v[k][2];
      n[i][0]=u2*v3-v2*u3;
      n[i][1]=u3*v1-v3*u1;
      n[i][2]=u1*v2-v1*u2;
    }
    return 0;
}
visibility()
{
 int m,i,e2,e1,j,k,flag;
 float xe,ye,ze,wx,wy,wz,dot;

 xe=rho*s2*c1; ye=rho*s2*s1; ze=rho*c2;
 m=0;
 for(i=0;i<7;i++)
    {
       e2=s[i][0];
       wx=xe-v[e2][0];
       wy=ye-v[e2][1];
       wz=ze-v[e2][2];
       dot=n[i][0]*wx+n[i][1]*wy+n[i][2]*wz;
       if(dot<=0)continue;
       e1=s[i][0];
       for(j=1;j<=nps[i];j++)
       {
	 e2=s[i][j];
	 for(k=0;k<=m;k++)
	    { flag=0;
	      if(e[k][0]==e2 && e[k][1]==e1)
		{
		  e[k][2]=2;
		  flag=1;
		}
	      if(flag==1)break;
	    }/* end of k*/
	 if(flag==0){
		      e[m][0]=e1;
		      e[m][1]=e2;
		      e[m][2]=1;
		      m=m+1;
		    }
	 e1=e2;
       }/* end of j */
    }/* end of i */
    return 0;
}/* end of function */

drawedges()
{
  int i,j,k;
  for(i=0;i<12;i++)
     {
      if(e[i][2]==0)continue;
      j=e[i][0];k=e[i][1];
      setcolor(WHITE);
      line(sv[j][0],sv[j][1],sv[k][0],sv[k][1]);
     }
     return 0;
}
