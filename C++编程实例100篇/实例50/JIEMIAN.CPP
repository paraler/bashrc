#include<graphics.h>
#include<dos.h>
#include<ALLOC.H>
#include<STDLIB.H>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int X1=1,Y1=1,X2=10,Y2=300,
	    X3=630,Y3=1,X4=640,Y4=300;
	int NUM;
	unsigned SIZE1,SIZE2;
	char far *BUFFER1;
	char far *BUFFER2;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	setfillstyle(1,WHITE);
	bar(1,1,640,500);

	setfillstyle(1,YELLOW);
	bar(X1,Y1,X2,Y2);
	SIZE1=imagesize(X1,Y1,X2,Y2);

	setfillstyle(1,BLUE);
	bar(X3,Y3,X4,Y4);
	SIZE2=imagesize(X3,Y3,X4,Y4);
	BUFFER1=(char far *)malloc(SIZE1);
	BUFFER2=(char far *)malloc(SIZE2);
	
	getimage(X1,Y1,X2,Y2,BUFFER1);
	
	getimage(X3,Y3,X4-1,Y4,BUFFER2);
	for(NUM=0;NUM<50;NUM++)
	{
		putimage(X1,Y1,BUFFER1,COPY_PUT);
		putimage(X3,Y3,BUFFER2,COPY_PUT);
		delay(50);
		X1+=10;
		X3-=10;
	}
	setcolor(RED);
	outtextxy(200,400,"*** WELL COME TO THIS SYSTEM ! ***");
	
	getch();
	
	closegraph();
}
