
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <math.h>
#include <graphics.h>

#define PI 3.14159265
#define TRUE 1
union REGS in,out;

//mouse interrupt with functions 0, 1, 2, 3, 7
void initmouse() {
    in.x.ax=0;
    int86(0x33,&in,&out);
    }
void showmouse() {
    in.x.ax=1;
    int86(0x33,&in,&out);
    }
void hidemouse() {
    in.x.ax=2;
    int86(0x33,&in,&out);
    }
void getmousepos(int &button,int &x,int &y) {
    in.x.ax=3;
    int86(0x33,&in,&out);
    button=out.x.bx;
    x=out.x.cx;
    y=out.x.dx;
    }
void restrictmouse(int x1,int y1,int x2,int y2) {
    in.x.ax=7;
    in.x.cx=x1;
    in.x.dx=x2;
    int86(0x33,&in,&out);
    in.x.ax=8;
    in.x.cx=y1;
    in.x.dx=y2;
    int86(0x33,&in,&out);
    }
//(52,30,628,418) is the drawing area with lightgray background

int posx, posy, control_button, colx,coly, col_button; //global variables
void selectcolour(int, int, int); //prototype
int colour, col2; //global variables in selectcolour()

//save image in picture.dat in /bin directory of Turbo-C++
void save_image(){

    //setting impression of all button presses
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    //giving impression of save button press
    setcolor(BLACK);
    line(5,80,5,100); line(5,80,25,80);
    setcolor(WHITE);
    line(25,100,25,80); line(25,100,5,100);
        hidemouse();
        FILE *fp=fopen("picture.dat","wb");
        for(int x=52+1;x<=628-1;x++){
            for(int y=30+1;y<=418-1;y++)
            {
                int cr=getpixel(x,y);
                fwrite(&cr,2,1,fp);
            }
        }

        fclose(fp);
        showmouse();
} //end of save_image()

//load image file image.dat from /bin
void load_image() {
    
    //setting impression of all button press
    for(int k=80;k<212;k+=21) {
    setcolor(BLACK);
    rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
    setcolor(WHITE);
    line(5,k,5,k+20); line(5,k,25,k);
    line(26,k,26,k+20); line(26,k,46,k);
    }
    //giving impression of load button press
    setcolor(BLACK);
    line(26,80,26,100); line(26,80,46,80);
    setcolor(WHITE);
    line(46,100,46,80); line(46,100,26,100);

        FILE *fp=fopen("picture.dat","rb");
        int cr;
        for(int x=52+1;x<=628-1;x++){
            for(int y=30+1;y<=418-1;y++)
            {
                fread(&cr,2,1,fp);
                putpixel(x,y,cr);
            }
        }
        fclose(fp);
}//end of load_image()

//create pencil button for pencil();
void *pb; //global
void createpb() {
    //filled lightgray rectangle for backgroud of buttons
    setcolor(LIGHTGRAY);
    rectangle(3,3,300,300);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(40,40,LIGHTGRAY);

    //pencil from end to before nose
    setcolor(RED);
    line(60,50,50,57); line(63,54,53,61);
    line(50,57,53,61); line(60,50,63,54);
    setfillstyle(SOLID_FILL,RED);
    floodfill(60,52,RED);

    //nose of pencil
    setcolor(BLACK);
    line(50,57,47,62); line(47,62,53,61);
    line(60,50,50,57); line(63,54,53,61);
    line(50,57,53,61); line(60,50,63,54);
    
    int size=imagesize(45,48,65,65);
    pb= new int [size];
    getimage(45,48,65,65,pb);
    cleardevice();
} // end of createpb()

void *eraser; //create eraser button for rub()
void createeraser() {
    setcolor(LIGHTGRAY);
    rectangle(10,10,200,200);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(50,50,LIGHTGRAY);

    setcolor(RED);
    rectangle(30,112,37,115);
    line(30,112,35,105); line(35,105,42,105);
    line(42,105,37,112); line(42,105,42,109);
    line(42,109,37,115);
    setfillstyle(SOLID_FILL,RED);
    floodfill(33,110,RED); floodfill(40,110,RED);

    setcolor(WHITE);
    rectangle(30,112,37,115);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(33,113,WHITE);

    int size = imagesize(28,102,45,118);
    eraser = new int [size];
    getimage(28,102,45,118,eraser);
    cleardevice();
} //end of createeraser()

//create fill button for getcolour()
void *fill;
void createfill() {
    setcolor(LIGHTGRAY);
    rectangle(3,3,300,300);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(40,40,LIGHTGRAY);

    setcolor(BLACK);
    line(50,57,47,62); line(47,62,53,61);
    line(60,50,50,57); line(63,54,53,61);
    line(60,50,63,54);

    int size=imagesize(45,48,65,65);
    fill= new int [size];
    getimage(45,48,65,65,fill);
    cleardevice();
} //end of createfill()

//graphical user interface
void gui() {
    int i,x=getmaxx(),y=getmaxy();

    createpb();
    createfill();
    createeraser();
    putimage(6,102,pb,COPY_PUT); //pencil button
    putimage(6,123,fill,COPY_PUT); //colour filler button
    putimage(27,103,eraser,COPY_PUT); //eraser button

    setcolor(BLUE);
    rectangle(0,0,x,15); //top blue
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(10,10,BLUE);

    //plain yellow square/sheet on top blue
    setcolor(YELLOW);
    rectangle(5,3,12,12);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(9,9,YELLOW);

    settextstyle(12,0,5);
    outtextxy(20,4,"Paint Simulator");

    setcolor(LIGHTGRAY);
    rectangle(0,15,x-1,30); //top
    rectangle(0,30,50,y); // left
    rectangle(50,y-60,x-1,y); // bottom
    rectangle(x-1,30,x-10,y-60); // right
    setfillstyle(SOLID_FILL,LIGHTGRAY); // fill above borders
    floodfill(20,20,LIGHTGRAY);
    floodfill(40,60,LIGHTGRAY);
    floodfill(60,y-20,LIGHTGRAY);
    floodfill(x-5,y-100,LIGHTGRAY);

    setcolor(BLACK);
    line(0,31,50,31);
    line(50,y-61,0,y-61);
    line(x-1,31,x-10,31);
    line(x-1,y-61,x-10,y-61);
    line(0,y-15,x-1,y-15); // filler lines
    line(x-100,y-15,x-100,y);
    line(x-200,y-15,x-200,y);
    rectangle(10,y-50,37,y-23); // Outer box of selected colour

    setcolor(WHITE);
    line(37,y-23,37,y-50);
    line(37,y-23,10,y-23);

    //16 color boxes at the bottom
    setcolor(BLACK);
    int k,c=0;
    for(k=40;k<157;k+=15) {
        setcolor(c);
        rectangle(k,y-50,k+12,y-38);
        setfillstyle(SOLID_FILL,c);
        floodfill(k+5,y-40,c);
        setcolor(BLACK);
        line(k,y-50,k,y-38);//drawing and filling of colour boxes(1-8)
        line(k,y-50,k+12,y-50);
        setcolor(WHITE);
        line(k+12,y-38,k+12,y-50); line(k+12,y-38,k,y-38);
        c++;
        }
    for(k=40;k<157;k+=15) {
        setcolor(c);
        rectangle(k,y-35,k+12,y-23);
        setfillstyle(SOLID_FILL,c);
        floodfill(k+5,y-25,c);
        setcolor(BLACK);
        line(k,y-35,k,y-23); line(k,y-35,k+12,y-35);
        setcolor(WHITE); //drawing and filling of colour boxes(9-16)
        line(k+12,y-23,k+12,y-35); line(k+12,y-23,k,y-23);
        c++;
        }
    setcolor(WHITE);
    rectangle(52,32,x-12,y-62);
    setfillstyle(SOLID_FILL,WHITE); //Drawing area (52,32) to (628,418)
    floodfill(200,200,WHITE);

    setcolor(BLACK);
    for(k=80;k<212;k+=21) {
        rectangle(5,k,25,k+20);
        rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20);
        line(5,k,25,k); // Function Buttons
        line(26,k,26,k+20);
        line(26,k,46,k);
        setcolor(BLACK);
        }
    rectangle(8,k+8,43,k+68); // button option box
    setcolor(WHITE);
    line(43,k+68,8,k+68); line(43,k+68,43,k+8);

    setcolor(BLACK);
    rectangle(13,y-45,25,y-33); // selected foreground colour box
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(15,y-40,BLACK);
    setcolor(WHITE);
    line(26,y-40,32,y-40);
    line(20,y-28,20,y-32);
    line(32,y-40,32,y-28);
    line(32,y-28,20,y-28); //selected background colour box
    line(26,y-40,26,y-33);
    line(26,y-32,20,y-32);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(30,y-37,WHITE);
    line(13,y-45,13,y-33); line(13,y-45,25,y-45);
    setcolor(BLACK);
    line(26,y-40,32,y-40); line(20,y-28,20,y-32);
    setcolor(LIGHTGRAY);
    rectangle(x-16,2,x-5,12); // close icon
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    floodfill(x-10,8,LIGHTGRAY);
    setcolor(BLACK);
    line(x-13,4,x-7,10); line(x-13,10,x-7,4);
    line(x-5,12,x-5,2); line(x-5,12,x-16,12);
    setcolor(WHITE);
    line(x-16,2,x-16,12); line(x-16,2,x-5,2);
    setcolor(BLACK);
    ellipse(15,153,0,360,8,4); //ellipse button
    rectangle(9,168,22,178); // rectangle button
    line(9,190,20,201); //line button

    // For polygon button
    line(33,127,30,136); line(30,136,39,136);
    line(33,127,38,127); line(38,127,36,132);
    line(36,132,40,132); line(40,132,39,136);
    // For Paint Brush button
    line(35,145,35,151); line(38,145,38,151);
    line(35,145,38,145); line(35,151,32,153);
    line(38,151,41,153); line(32,153,32,159);
    line(41,153,41,159); line(32,159,41,159);
    line(41,154,32,154); line(41,155,32,155);
    line(35,159,35,157); line(38,159,38,157);
    // For curved line button
    ellipse(32,173,180,0,4,2);
    ellipse(39,173,0,180,4,2);
    // For bucket button for fill
    line(32,200,40,200); line(32,200,32,193);
    line(40,200,40,193); line(32,193,40,193);
    line(36,193,38,189); line(38,193,40,189);
    line(38,189,40,190); line(37,193,39,189);
    line(32,195,40,195); line(32,196,40,196);
    // For spray can button
    line(7,223,7,215);   line(7,215,12,215);
    line(12,215,12,223); line(12,223,7,223);
    line(8,215,8,213);   line(11,215,11,213);
    line(11,213,8,213);  line(11,213,19,210);
    line(11,213,19,216); line(11,213,19,215);
    line(11,213,19,213); line(11,213,19,211);
    //For text button
    settextstyle(1,0,1);
    outtextxy(30,203,"A");
    //buttons for save and load
    setusercharsize(7,25,7,25);//more than size 1/4 and less than 1/3
    outtextxy(7, 83,"Save");
    outtextxy(28, 83,"Load");
    
    settextstyle(12,0,5);
    outtextxy(8,y-10,"DCSA - Panjab university");
} //end of gui()

//pencil: free hand drawing after left-clicking on pencil icon
void pencil() {
    //setting impression of all button press
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    //giving impression of pencil button press
    setcolor(BLACK);
    line(5,101,5,121); line(5,101,25,101);
    setcolor(WHITE);
    line(25,121,25,101); line(25,121,5,121);

    int button,x,y,prevx,prevy; //local
    while(TRUE) {
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)) {
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        setcolor(colour);
        if(button & 1 ==1 && x>52 && x<628 && y>32 && y<418){
            prevx=x; prevy=y;
            while((button & 1) ==1){
                restrictmouse(52,32,627,417);
                hidemouse();
                line(prevx,prevy,x,y);
                showmouse();
                prevx=x; prevy=y;
                getmousepos(button,x,y);
            }
        restrictmouse(0,0,getmaxx(),getmaxy());
        }
    }
} // end of pencil()

void getcolour(){
    for(int k=80;k<212;k+=21){
    setcolor(BLACK);
    rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
    setcolor(WHITE);
    line(5,k,5,k+20); line(5,k,25,k);
    line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(5,122,25,122); line(5,122,5,142);
    setcolor(WHITE);
    line(25,142,25,122); line(25,142,5,142);

    int button,x,y,prevx,prevy,gcolour,e,f,u; //local
    k=226;
    while(!kbhit()){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x;
            posy=y;
            break;
        }
        if(button & 1==1 && x>52 && x<627 && y>32 && y<417){
            while(button & 1==1){
                restrictmouse(52,32,627,417);
                hidemouse();
                gcolour=getpixel(x,y);
                showmouse();
                setcolor(gcolour);
                for(e=9;e<43;e++)
                    for(f=k+9;f<k+68;f++)
                        putpixel(e,f,gcolour);
                getmousepos(button,x,y);
            }
            for(e=9;e<43;e++)
                for(f=k+9;f<k+68;f++)
                    putpixel(e,f,LIGHTGRAY);
            colour=gcolour;
            restrictmouse(0,0,getmaxx(),getmaxy());
            colour=gcolour;
            u=getmaxy();
            rectangle(13,u-45,25,u-33); // selected foreground colour box
            setfillstyle(SOLID_FILL,colour);
            floodfill(15,u-40,colour);
            setcolor(BLACK);
            line(25,u-33,25,u-45); line(25,u-33,13,u-33);
            setcolor(WHITE);
            line(13,u-45,25,u-45); line(13,u-45,13,u-33);
        } //end of if
    } //end of while
}//end of getcolour()

//int colour, col2; //global vars in selectcolour() already defined above
void selectcolour(int col_button, int colx, int coly) {
    if(colx>40 && colx<52 && coly>430 && coly<442) {
        if(col_button==2) col2=0;
        if(col_button==1) colour=0;
    }
    if(colx>55 && colx<67 && coly>430 && coly<442) {
        if(col_button==2) col2=1;
        if(col_button==1) colour=1;
    }
    if(colx>70 && colx<82 && coly>430 && coly<442) {
        if(col_button==2) col2=2;
        if(col_button==1) colour=2;
    }
    if(colx>85 && colx<97 && coly>430 && coly<442) {
        if(col_button==2) col2=3;
        if(col_button==1) colour=3;
    }
    if(colx>100 && colx<112 && coly>430 && coly<442) {
        if(col_button==2) col2=4;
        if(col_button==1) colour=4;
    }
    if(colx>115 && colx<127 && coly>430 && coly<442) {
        if(col_button==2) col2=5;
        if(col_button==1) colour=5;
    }
    if(colx>130 && colx<142 && coly>430 && coly<442) {
        if(col_button==2) col2=6;
        if(col_button==1) colour=6;
    }
    if(colx>145 && colx<157 && coly>430 && coly<442) {
        if(col_button==2) col2=7;
        if(col_button==1) colour=7;
    }
    if(colx>40 && colx<52 && coly>445 && coly<457) {
        if(col_button==2) col2=8;
        if(col_button==1) colour=8;
    }
    if(colx>55 && colx<67 && coly>445 && coly<457) {
        if(col_button==2) col2=9;
        if(col_button==1) colour=9;
    }
    if(colx>70 && colx<82 && coly>445 && coly<457) {
        if(col_button==2) col2=10;
        if(col_button==1) colour=10;
    }
    if(colx>85 && colx<97 && coly>445 && coly<457) {
        if(col_button==2) col2=11;
        if(col_button==1) colour=11;
    }
    if(colx>100 && colx<112 && coly>445 && coly<457) {
        if(col_button==2) col2=12;
        if(col_button==1) colour=12;
    }
    if(colx>115 && colx<127 && coly>445 && coly<457) {
        if(col_button==2) col2=13;
        if(col_button==1) colour=13;
    }
    if(colx>130 && colx<142 && coly>445 && coly<457) {
        if(col_button==2) col2=14;
        if(col_button==1) colour=14;
    }
    if(colx>145 && colx<157 && coly>445 && coly<457) {
        if(col_button==2) col2=15;
        if(col_button==1) colour=15;
    }
    int y=getmaxy();
    if(col_button==1) {
        setcolor(colour);
        rectangle(13,y-45,25,y-33); // selected foreground colour box
        setfillstyle(SOLID_FILL,colour);
        floodfill(15,y-40,colour);
        setcolor(BLACK);
        line(25,y-33,25,y-45); line(25,y-33,13,y-33);
    } //****************
    //Right Click
    if(col_button==2) {
        setcolor(col2);
        line(26,y-40,32,y-40);
        line(20,y-28,20,y-32);
        line(32,y-40,32,y-28);
        line(32,y-28,20,y-28); //selected background colour box
        line(26,y-40,26,y-32);
        line(26,y-32,20,y-32);
        setfillstyle(SOLID_FILL,col2);
        floodfill(30,y-37,col2);
        setcolor(WHITE);
        line(32,y-40,32,y-28); line(32,y-28,20,y-28);
        setcolor(BLACK);
        line(26,y-40,32,y-40); line(20,y-28,20,y-32);
    }
} // end of selectcolor()

int check_rub=0; //global
struct point {
    int xc;
    int yc;
    };
point p1,p2,p3,p4; //global
void four_pt_bez(point p1,point p2,point p3,point p4) {
    int x0,y0,x1,y1,x2,y2,x3,y3,vx,vy,x01,y01,x12,y12,x23,y23;
    int x012,y012,x123,y123,x0123,y0123,x,y;
    x0=p1.xc; y0=p1.yc;
    x3=p2.xc; y3=p2.yc;
    x1=p3.xc; y1=p3.yc;
    x2=p4.xc; y2=p4.yc;
    x01=x1-x0; y01=y1-y0;
    x12=x2-x1; y12=y2-y1;
    x23=x3-x2; y23=y3-y2;
    x012=x12-x01; y012=y12-y01;
    x123=x23-x12; y123=y23-y12;
    x0123=x123-x012; y0123=y123-y012;
    for(float t=0;t<1;t+=0.0001) {
        x=t*t*t*x0123+3*t*t*x012+3*t*x01+x0;
        y=t*t*t*y0123+3*t*t*y012+3*t*y01+y0;
    if(x>52 && x<628 && y>32 && y<417) line(x,y,x,y);
    }
} //end of four_pt_bez()

void thr_pt_bez(point p1,point p2,point p3) {
    int x0,y0,x1,y1,x2,y2,x3,y3,vx,vy,x01,y01,x12,y12,x23,y23;
    int x012,y012,x123,y123,x0123,y0123,x,y;
    x0=p1.xc; y0=p1.yc;
    x3=p2.xc; y3=p2.yc;
    x1=x2=p3.xc; y1=y2=p3.yc;
    x01=x1-x0; y01=y1-y0;
    x12=x2-x1; y12=y2-y1;
    x23=x3-x2; y23=y3-y2;
    x012=x12-x01; y012=y12-y01;
    x123=x23-x12; y123=y23-y12;
    x0123=x123-x012; y0123=y123-y012;
    for(float t=0;t<1;t+=0.0001) {
        x=t*t*t*x0123+3*t*t*x012+3*t*x01+x0;
        y=t*t*t*y0123+3*t*t*y012+3*t*y01+y0;
        if(x>52 && x<628 && y>32 && y<417) line(x,y,x,y);
    }
} //end tr_pt_bez()
void bez2();
void bez() {
    int button1 ,x1,y1,k=0;
    while(!k) {
        getmousepos(button1,x1,y1);
        if(button1==1) {
            setwritemode(XOR_PUT);
            line(p1.xc,p1.yc,p2.xc,p2.yc);
            while(button1==1) {
                // restrictmouse(0,0,getmaxx(),getmaxy());
                setcolor(15-colour);
                p3.xc=x1;
                p3.yc=y1;
                hidemouse();
                thr_pt_bez(p1,p2,p3);
                thr_pt_bez(p1,p2,p3);
                showmouse();
                getmousepos(button1,x1,y1);
            }
            // restrictmouse(52,32,627,417);
            // setcolor(colour);
            hidemouse();
            thr_pt_bez(p1,p2,p3);
            k=1;
            showmouse();
            bez2();
        }
    }
} //end of bez()
void bez2() {
    int button1,x1,y1,k=0;
    while(!k) {
        showmouse();
        getmousepos(button1,x1,y1);
        if(button1==1) {
            // setcolor(0);
            setwritemode(XOR_PUT);
            thr_pt_bez(p1,p2,p3);
            setwritemode(XOR_PUT);
            while(button1==1) {
                // restrictmouse(0,0,getmaxx(),getmaxy());
                p4.xc=x1;
                p4.yc=y1;
                setcolor(15-colour);
                hidemouse();
                four_pt_bez(p1,p2,p3,p4);
                four_pt_bez(p1,p2,p3,p4);
                showmouse();
                getmousepos(button1,x1,y1);
            }
            // restrictmouse(0,0,getmaxx(),getmaxy());
            setwritemode(COPY_PUT);
            setcolor(colour);
            hidemouse();
            four_pt_bez(p1,p2,p3,p4);
            k=1;
            showmouse();
        }
    }
} //end of bez2()
void curve(){
    int button,x,y,prevx,prevy;
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20);
        rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,164,26,184); line(26,164,46,184);
    setcolor(WHITE);
    line(46,184,46,164); line(46,184,26,184);
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1 == 1 && x>52 && x<628 && y>32 && y<418){
            prevx=x; prevy=y;
            setwritemode(XOR_PUT);
            while((button & 1) == 1 && x>120){
                restrictmouse(52,32,627,417);
                setcolor(15-colour);
                hidemouse();
                line(prevx,prevy,x,y);
                line(prevx,prevy,x,y);
                showmouse();
                getmousepos(button,x,y);
            }
            restrictmouse(0,0,getmaxx(),getmaxy());
            hidemouse();
            // setcolor(colour);
            line(prevx,prevy,x,y);
            showmouse();
            p1.xc=prevx; p1.yc=prevy;
            p2.xc=x; p2.yc=y;
            bez();
        } //end of if
    } //end of while
} //end of curve()
struct coordinate {
    int x,y; //structure
    coordinate *next;
    };
coordinate *control,*last,*temp; //global pointer varables holding coordinate
void insert(int x,int y) { //data type
    coordinate *new_coord;
    new_coord=new coordinate;
    new_coord->x=x;
    new_coord->y=y; //insert link function
    new_coord->next=NULL;
    last->next=new_coord;
    last=new_coord;
}//end of insert()
void bucket(int x,int y,int backcolour,int colour){
    if(backcolour==colour)return;
    last=control=new coordinate; //last & control points to new blocks of memory
    control->x=x; // large enough to store a coordinate variable
    control->y=y;
    control->next=NULL; //Null pointer value
    while(control!=NULL){
        putpixel(x,y,colour);
        if(y-1>=32 && getpixel(x,y-1)==backcolour){
            putpixel(x,y-1,colour);
            insert(x,y-1);
        }
        if(x+1<628 && getpixel(x+1,y)==backcolour){
            putpixel(x+1,y,colour);
            insert(x+1,y);
        }
        if(y+1<418 && getpixel(x,y+1)==backcolour){
            putpixel(x,y+1,colour);
            insert(x,y+1);
        }
        if(x-1>=52 && getpixel(x-1,y)==backcolour){
            putpixel(x-1,y,colour);
            insert(x-1,y);
        }
        temp=control;
        control=temp->next; //change the control to next link
        delete temp;
        x=control->x;
        y=control->y;
    } //end of while
} //end of bucket()
void ffill(){
    int button,x,y,backcolour;
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,185,26,205); line(26,185,46,185);
    setcolor(WHITE);
    line(46,205,46,185); line(46,205,26,205);
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1)col_button=1;
            if(button==2)col_button=2;
            colx=x;
            coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1 ==1 && x>52 && x<628 && y>32 && y<418){
            hidemouse();
            backcolour=getpixel(x,y);
            bucket(x,y,backcolour,colour);
        }
        showmouse();
    } //end of while
} //end of ffill()
void text(){
    int button,x,y,m,n,col[200],v,u,g=0,i,j;
    char ch,a[100];
    void *bk;
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,206,26,226); line(26,206,46,206);
    setcolor(WHITE);
    line(46,226,46,206); line(46,226,26,226);
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1==1 && x>52 && x<627 && y>32 && y<417){
            u=m=x;
            n=y;
            setcolor(colour);
            hidemouse();
            settextstyle(0,0,1);
            for(int i=0;i<100;i++)
            a[i]=' ';
            a[0]='_';
            g=0;
            v=imagesize(m,n,getmaxx()-10,n+9);
            bk=new int[v];
            getimage(m,n,getmaxx()-10,n+9,bk);
            outtextxy(m,n,a);
            while((ch=getch())!=13){
                if(ch==8) { //backspace
                    if(g>0){
                        putimage(m,n,bk,COPY_PUT);
                        a[g]=' ';
                        a[g-1]='_';
                        outtextxy(m,n,a);
                        g--;
                        u-=8;
                    }
                }
                else
                {
                    if(u<(getmaxx()-24)){
                        putimage(m,n,bk,COPY_PUT);
                        a[g]=ch;
                        a[g+1]='_';
                        g++;
                        u+=8;
                        outtextxy(m,n,a);
                    }
                    else
                    {
                    putimage(m,n,bk,COPY_PUT);
                    a[g-1]=ch;
                    a[g]=' '; //if it reaches the end
                    outtextxy(m,n,a);
                    }
                }//else
            }// end of while
            a[g]=' ';
            putimage(m,n,bk,COPY_PUT);
            outtextxy(m,n,a);
            showmouse();
        } //end of if
    } //end of while
}//end of text()

void poly(){
    X: int button,x,y,prevx,prevy,j=0,orix,oriy;
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,122,46,122); line(26,122,26,142);
    setcolor(WHITE);
    line(46,122,26,122); line(46,122,46,142);
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button==1 && x<orix+2 && x>orix-2 && y<oriy+2 && y>oriy-2){
            hidemouse();
            setcolor(colour);
            line(orix,oriy,prevx,prevy);
            showmouse();
            goto X;
        }
        if(button==1 && x>=100 && x<=120 && y>=140 && y<=180)break;
        if(button & 1 ==1 && x>52 && x<627 && y>32 && y<417){
            hidemouse();
            if(j==0){ orix=prevx=x; oriy=prevy=y; }
            setwritemode(XOR_PUT);
            while((button & 1) ==1){
                restrictmouse(52,32,627,417);
                if(j==0) {
                    getmousepos(button,x,y);
                    prevx=x; prevy=y;
                    j=1;
                }
                getmousepos(button,x,y);
                setcolor(15-colour);
                hidemouse();
                line(prevx,prevy,x,y); line(prevx,prevy,x,y);
                showmouse();
            }
            restrictmouse(0,0,640,480);
            setcolor(colour);
            setwritemode(COPY_PUT);
            if(x>52&&x<627&&y>32&&y<417){
                hidemouse();
                line(prevx,prevy,x,y);
                showmouse();
            }
            prevx=x; prevy=y;
        }//end of if
    showmouse();
    } //end of while
} //end of poly()
void spray(){
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(5,206,25,206); line(5,206,5,226);
    setcolor(WHITE);
    line(25,226,25,206); line(25,226,5,226);
    int button,x,y,prevx,prevy;
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1==1 && x>52 && x<627 && y>32 && y<417) {
            hidemouse();
            int i,j;
            while((button & 1) ==1){
                restrictmouse(52,32,627,417);
                setcolor(colour);
                for(i=x,j=y;i<x+5,j<y+5;i+=random(20),j+=random(20)){
                    if(i<x-5)break;
                    if(j<y-5) break;
                    i-=random(20);
                    j-=random(20);
                    if(i>52&&i<627&&j>32&&j<417)putpixel(i,j,colour);
                    getmousepos(button,x,y);
                }
                break;
            } //end of while
        }//end of if
    restrictmouse(0,0,640,480);
    showmouse();
    } //end of while
} //end of spray()
void thickline(int prevx,int prevy,int x,int y){
    int radius =3;
    if(check_rub==1) {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,WHITE);
        }
        else
        {
        setcolor(colour);
        setfillstyle(SOLID_FILL,colour);
        }
    int lefx,upy,rigx,lowy;
    if(prevx>x){ lefx=x; rigx=prevx;}
        else { lefx=prevx; rigx=x;}
    if(prevy>y){ upy=y; lowy=prevy;}
        else { upy=prevy; lowy=y;}
    int s1,s2,q1,q2;
    s1=prevx; s2=prevy;
    q1=x; q2=y;
    if(lefx!=rigx) for(int i=lefx;i<=rigx;i++) fillellipse(i,(((q2-s2)*(i-s1))/(q1-s1))+s2,radius,radius);
    if(upy!=lowy) for(int j=upy;j<=lowy;j++)fillellipse((((j-s2)*(q1-s1))/(q2-s2))+s1,j,radius,radius);
    showmouse();
} //end of thickline()
void brush(){
    check_rub=0;
    int button,x,y,prevx,prevy;
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,143,46,143); line(26,143,26,163);
    setcolor(WHITE);
    line(46,163,46,143); line(46,163,26,163);
    while(TRUE){
        getmousepos(button,x,y);
        if((button &1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        int q=3; //q=radius of thick line -refer thickline function
        if(button & 1 ==1 && x>52+q && x<628-q && y>32+q && y<418-q) {
            setcolor(colour);
            prevx=x; prevy=y;
            while((button==1)) {
                restrictmouse(52+q,32+q,627-q,417-q);
                getmousepos(button,x,y);
                setcolor(colour);
                hidemouse();
                thickline(prevx,prevy,x,y);
                showmouse();
                prevx=x; prevy=y;
            }
            restrictmouse(0,0,getmaxx(),getmaxy());
        } //end of if
    } // end of while
} //end of brush()
void rub(){
    check_rub=1;
    int button,x,y,prevx,prevy;
    for(int k=80;k<212;k+=21){
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(26,101,46,101); line(26,101,26,121);
    setcolor(WHITE);
    line(46,121,46,101); line(46,121,26,121);
    while(TRUE){
        getmousepos(button,x,y);
        if((button &1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)) {
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        int q=3; //q=radius of thick line - refer thickline function
        if(button & 1 ==1 && x>52+q && x<628-q && y>32+q && y<418-q){
            setcolor(WHITE);
            prevx=x; prevy=y;
            while((button==1)) {
                restrictmouse(52+q,32+q,627-q,417-q);
                getmousepos(button,x,y);
                setcolor(WHITE);
                hidemouse();
                thickline(prevx,prevy,x,y);
                showmouse();
                prevx=x; prevy=y;
            }
            restrictmouse(0,0,getmaxx(),getmaxy());
        }//end of if
    } //end of while
} //end of rub()
void line() {
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(5,185,5,205); line(5,185,25,185);
    setcolor(WHITE);
    line(25,205,25,185); line(25,205,5,205);
    int button,x,y,prevx,prevy;
    while(TRUE){
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)) {
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1 ==1 && x>52 && x<628 && y>32 && y<418){
            getmousepos(button,x,y);
            setwritemode(XOR_PUT);
            prevx=x; prevy=y;
            while((button & 1) == 1){
                restrictmouse(52,32,627,417);
                getmousepos(button,x,y);
                setcolor(15-colour);
                hidemouse();
                line(prevx,prevy,x,y);
                line(prevx,prevy,x,y);
                showmouse();
            }
            setwritemode(COPY_PUT);
            setcolor(colour);
            hidemouse();
            line(prevx,prevy,x,y);
            showmouse();
            restrictmouse(0,0,getmaxx(),getmaxy());
        } //end of if
    } //end of while
} // end of line()
void myellipse(int cenx,int ceny,int xrad,int yrad) {
    float cx,cy,angle=0;
    while(angle<360) {
        float THETA=PI/180.0 * angle;
        cx=cenx+xrad*cos(THETA);
        cy=ceny-yrad*sin(THETA);
        line(cx,cy,cx,cy);
        angle+=.5;
    }
}//end of myellipse()
void circle() {
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(5,143,5,163); line(5,143,25,143);
    setcolor(WHITE);
    line(25,163,5,163); line(25,163,25,143);
    
    int button,x,y,prevx,prevy,i,j;
    while(TRUE) {
        getmousepos(button,x,y);
        if((button & 1==1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457){
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x; coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1 ==1 && x>52 && x<628 && y>32 && y<418){
            getmousepos(button,x,y);
            setwritemode(XOR_PUT);
            prevx=x; prevy=y;
            while((button & 1) == 1){
                restrictmouse(52,32,627,417);
                getmousepos(button,x,y);
                setcolor(15-colour);
                hidemouse();
                i=abs(x-prevx); j=abs(y-prevy);
                myellipse((prevx+x)/2,(prevy+y)/2,i/2,j/2);
                myellipse((prevx+x)/2,(prevy+y)/2,i/2,j/2);
                showmouse();
            }
            setwritemode(COPY_PUT);
            setcolor(colour);
            hidemouse();
            ellipse((prevx+x)/2,(prevy+y)/2,0,360,i/2,j/2);
            showmouse();
            restrictmouse(0,0,getmaxx(),getmaxy());
        } //end of if
    showmouse();
    } //end of while
} //end of circle()

void rectangle() {
    for(int k=80;k<212;k+=21) {
        setcolor(BLACK);
        rectangle(5,k,25,k+20); rectangle(26,k,46,k+20);
        setcolor(WHITE);
        line(5,k,5,k+20); line(5,k,25,k);
        line(26,k,26,k+20); line(26,k,46,k);
    }
    setcolor(BLACK);
    line(5,164,5,184); line(5,164,25,164);
    setcolor(WHITE);
    line(25,184,25,164); line(25,184,5,184);
    
    int button,x,y,prevx,prevy;
    while(TRUE) {
        getmousepos(button,x,y);
        if((button & 1 == 1 && x>5 && x<46 && y>80 && y<225)||(button & 1==1 && x>625 && x<635 && y>2 && y<12)){
            control_button=1;
            posx=x; posy=y;
            break;
        }
        if(button && x>=40 && x<=157 && y>=430 && y<=457) {
            if(button==1) col_button=1;
            if(button==2) col_button=2;
            colx=x;
            coly=y;
            selectcolour(col_button,colx,coly);
        }
        if(button & 1 == 1 && x>52 && x<628 && y>32 && y<418) {
            getmousepos(button,x,y);
            setwritemode(XOR_PUT);
            prevx=x; prevy=y;
            while((button & 1) == 1) {
                restrictmouse(52,32,627,417);
                getmousepos(button,x,y);
                setcolor(15-colour);
                hidemouse();
                rectangle(prevx,prevy,x,y);
                rectangle(prevx,prevy,x,y);
                showmouse();
            }
            setwritemode(COPY_PUT);
            setcolor(colour);
            hidemouse();
            rectangle(prevx,prevy,x,y);
            showmouse();
            restrictmouse(0,0,getmaxx(),getmaxy());
        }
    }
} //end of tectangle()
void main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");
    gui();
    //(52,30,628,418) is the drawing area with lightgray background
    initmouse();
    showmouse();
    setcolor(BLACK);
    colour=0;
    pencil(); //to start with by default

    while(TRUE) {
        // Action after left-clicking on first row of icons
        if(control_button==1 && posx>5 && posx<25 && posy>100 && posy<120) pencil();
        if(control_button==1 && posx>5 && posx<25 && posy>121 && posy<141) getcolour();
        if(control_button==1 && posx>5 && posx<25 && posy>142 && posy<162) circle();
        if(control_button==1 && posx>5 && posx<25 && posy>163 && posy<183) rectangle();
        if(control_button==1 && posx>5 && posx<25 && posy>184 && posy<204) line();
        if(control_button==1 && posx>5 && posx<25 && posy>205 && posy<225) spray();

        // Acion after left-clicking second row of icons
        if(control_button==1 && posx>26 && posx<46 && posy>100 && posy<120) rub();
        if(control_button==1 && posx>26 && posx<46 && posy>121 && posy<141) poly();
        if(control_button==1 && posx>26 && posx<46 && posy>142 && posy<162) brush();
        if(control_button==1 && posx>26 && posx<46 && posy>163 && posy<183) curve();
        if(control_button==1 && posx>26 && posx<46 && posy>184 && posy<204) ffill();
        if(control_button==1 && posx>26 && posx<46 && posy>205 && posy<225) text();

        // binary file save and load
        if(control_button==1 && posx>5 && posx<25 && posy>80 && posy<100)
        {
            save_image();
            outtextxy(4,335,"SAVED");
            pencil(); //focus on pencil button
        }
        if(control_button==1 && posx>26 && posx<46 && posy>80 && posy<100)
        {
            load_image();
            pencil(); //focus on pencil button
        }

        // Acion after left-clicking on exit icon
        if(control_button==1 && posx>625 && posx<635 && posy>2 && posy<12) exit(0);
    }
}
