
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include<math.h>
#define PI 3.14159265

double cm[4][3]; //globally declared coordinate-matrix

void plot()
{
	int x=getmaxx()/2; //getting x axis midpoint
	int y=getmaxy()/2; //getting y axis midpoint
	line(x,0,x,y*2); //drawing x axis
	line(0,y,x*2,y); //drawing y axis
	int a[10]={x+cm[0][0],y-cm[0][1],x+cm[1][0],y-cm[1][1],x+cm[2][0],y-cm[2][1],x+cm[3][0],y-cm[3][1],x+cm[0][0],y-cm[0][1]};
	drawpoly(5,a);
}//draw the shape(rectangle in this case)

//new=coordi matrix * homo matrix
void mul(double mat[3][3]) //matrix multiplicaion function, passing homogenous coordinate matrix
{
	double temp_cm[4][3];//temporary storage
	for(int i=0;i<4;i++)//4= no of rows in coordinate matrix
	{
		for(int j=0;j<3;j++)//3=no of columns in homo matrix
		{
			temp_cm[i][j]=0; //initializing all values to zero
			for(int k=0;k<3;k++)//3=no. of rows in homo mat
			{
				temp_cm[i][j]+=cm[i][k]*mat[k][j];
			}
		//cout<<"i="<<i<<"j="<<j<<"\t\t"<<temp_cm[i][j]<<"\n";
		}
	}
	for(int m=0;m<4;m++)
	{
		for(int j=0;j<3;j++)
		{
			cm[m][j]=temp_cm[m][j];
		}
	}
}//mat function closed


void translate(double tx,double ty)
{
	double t[3][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{tx,ty,1.0}};
	mul(t);   //passing this mat for multiplication with coordinate matrix
}

void rotate(double angle)
{
	double s=sin(angle*PI/180);
	double c=cos(angle*PI/180);
	double rot[3][3]={{c,s,0.0},{-1.0*s,c,0.0},{0.0,0.0,1.0}};
	double xb=cm[0][0];//saving the values for backup since cm gets updated after every fn call
	double yb=cm[0][1];
	translate(-xb,-yb);//bringing one vertex to the origin
	mul(rot);          //then rotating
	translate(xb,yb);  //translating back to org position
}

void scale(double x,double y)
{
	double sca[3][3]={{x,0.0,0.0},{0.0,y,0.0},{0.0,0.0,1.0}};
	double midx=(cm[0][0]+cm[1][0])/2;
	double midy=(cm[0][1]+cm[3][1])/2;
	translate(-midx,-midy); //moving center to origin
	mul(sca);               //then scaling
	translate(midx,midy);   //translating center back to org pos
}


void shear(double sx,double sy)
{
	double she[3][3]={{1.0,sy,0.0},{sx,1.0,0.0},{0.0,0.0,1.0}};
	double xb=cm[0][0];
	double yb=cm[0][1];
	translate(-xb,-yb); //moving one vertex to origin
	mul(she);
	translate(xb,yb);
}

void reflect_origin()
{
	double ref_mat[3][3]={{-1.0,0.0,0.0},{0.0,-1.0,0.0},{0.0,0.0,1.0}};
	mul(ref_mat);
}

void reflect_x()
{
	double ref_mat[3][3]={{1.0,0.0,0.0},{0.0,-1.0,0.0},{0.0,0.0,1.0}};
	mul(ref_mat);
}

void reflect_y()
{
	double ref_mat[3][3]={{-1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};
	mul(ref_mat);
}

void reflect_y_equalto_x()
{
	double ref_mat[3][3]={{0.0,1.0,0.0},{1.0,0.0,0.0},{0.0,0.0,1.0}};
	mul(ref_mat);
}

void reflect_y_equalto_minus_x()
{
	double ref_mat[3][3]={{0.0,-1.0,0.0},{-1.0,0.0,0.0},{0.0,0.0,1.0}};
	mul(ref_mat);
}

void main()
{
	clrscr();
	int gd=DETECT,gm,choice;
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	double tx,ty,angle,x,y,sx,sy;
	//initializing the coordinate matrix for a rectangle
	cm[0][0]=25; cm[0][1]=50; cm[0][2]=1;
	cm[1][0]=100; cm[1][1]=50; cm[1][2]=1;
	cm[2][0]=100; cm[2][1]=100; cm[2][2]=1;
	cm[3][0]=25; cm[3][1]=100; cm[3][2]=1;
	outtextxy(1, 5,"1.Translate");
	outtextxy(1, 15,"2.Rotate");
	outtextxy(1, 25,"3.Scale");
	outtextxy(1, 35,"4.Shear");
	outtextxy(1, 45,"5.Reflect-O");
	outtextxy(1, 55,"6.Reflect_X");
	outtextxy(1, 65,"7.Reflect_Y");
	outtextxy(1, 75,"8.Reflect Y=X");
	outtextxy(1, 85,"9.Reflect Y=-X");
	outtextxy(1, 95,"10.Exit");

	plot();//displaying the rectangle in initial position
	delay(500);
	//outtextxy(1, 10,"Select:");

	while(1)
	{
		//cout<<"Enter the operation:"<<endl;
		//cout<<"1.Translate 2.Rotate 3.Scale"<<endl;
		//cout<<"4.Shear 5.Reflect About Origin"<<endl;
		//cout<<"6.Reflect_X 7.Reflect_Y"<<endl;
		//cout<<"8.Reflect Y=X 9.Reflect Y=-X"<<endl;
		//cout<<"10.Exit"<<endl;
		outtextxy(1, 115,"Choice:");
		gotoxy(9, 8);cin>>choice;
		if(choice==10)
		{
			break;
		}
		switch(choice)
		{
			case 1:
			{
				tx=20;
				ty=20;
				setcolor(RED);
				translate(tx,ty);
				plot();
				break;
			}
			case 2:
			{
				angle=30;
				rotate(angle);
				setcolor(RED);
				plot();
				break;
			}
			case 3:
			{
				x=1.5;
				y=1.5;
				scale(x,y);
				setcolor(RED);
				plot();
				break;
			}
			case 4:
			{
				setcolor(RED);
				sx=1;
				sy=0;
				shear(sx,sy);
				plot();
				break;
			}
			case 5:
			{
				setcolor(RED);
				reflect_origin();
				plot();
				break;
			}
			case 6:
			{
				setcolor(RED);
				reflect_x();
				plot();
				break;
			}
			case 7:
			{
				setcolor(RED);
				reflect_y();
				plot();
				break;
			}
			case 8:
			{
				setcolor(RED);
				reflect_y_equalto_x();
				plot();
				break;
			}
			case 9:
			{
				setcolor(RED);
				reflect_y_equalto_minus_x();
				plot();
				break;
			}
			case 10:
			{
			break;
			}
			default:
			{
			cout<<"Invalid choice";
			}
		}//end of switch
	} //end of while
	getch();
	closegraph();
}