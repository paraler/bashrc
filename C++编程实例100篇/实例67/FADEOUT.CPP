#include<graphics.h>
#include<conio.h>
#include<dos.h>

void FADEOUT(void);
void DRAWPICTURE(void);

void main()
{
	int driver=DETECT,mode;
	int NUM1,NUM2;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	DRAWPICTURE();
	FADEOUT();
	getch();
	closegraph();
}
void DRAWPICTURE(void)
{
	void DRAWCIRCLE(int X,int Y,int R,int COLOR);
	void DRAWANGLE(int X1,int Y1,int X2,int Y2,int X3,int Y3,int COLOR);

	bar(0,0,639,479);
	setfillstyle(1,LIGHTGRAY);
	floodfill(1,1,LIGHTGRAY);
	DRAWANGLE(50,20,450,150,550,30,WHITE);
	DRAWANGLE(70,80,200,150,290,90,RED);
	DRAWANGLE(100,170,230,160,300,190,11);
	DRAWANGLE(350,250,450,150,560,200,12);
	DRAWANGLE(50,300,160,260,390,480,RED);
	DRAWCIRCLE(200,350,80,RED);
	DRAWCIRCLE(450,100,80,13);
	DRAWCIRCLE(450,300,150,YELLOW);
	DRAWCIRCLE(100,150,100,BLUE);
}
void DRAWANGLE(int X1,int Y1,int X2,int Y2,int X3,int Y3,int COLOR)
{
		int DATAARRAY[8];
		DATAARRAY[0]=X1;
		DATAARRAY[1]=Y1;
		DATAARRAY[2]=X2;
		DATAARRAY[3]=Y2;
		DATAARRAY[4]=X3;
		DATAARRAY[5]=Y3;
		DATAARRAY[6]=X1;
		DATAARRAY[7]=Y1;
		setcolor(COLOR);
		drawpoly(4,DATAARRAY);

}
void DRAWCIRCLE(int X,int Y,int R,int COLOR)
{
	setcolor(COLOR);
	circle(X,Y,R);
	setfillstyle(1,COLOR);
	floodfill(X,Y,COLOR);
}
void FADEOUT(void)
{
	char R[256],G[256],B[256];
	char RR[256],GG[256],BB[256];
	int NUM,NOTFINISH;

	for(NUM=0;NUM<256;NUM++)
	{
		outportb(0x3c7,NUM);
		R[NUM]=RR[NUM]=inportb(0x3c9);
		G[NUM]=GG[NUM]=inportb(0x3c9);
		B[NUM]=BB[NUM]=inportb(0x3c9);
	}
	for(NUM=0;NUM<256;NUM++)
	{
		R[NUM]=0;
		G[NUM]=0;
		B[NUM]=0;
		outportb(0x3c8,NUM);
		outportb(0x3c9,0);
		outportb(0x3c9,0);
		outportb(0x3c9,0);
	}
	delay(100);
	NOTFINISH=1;
	while(NOTFINISH==1)
	{
		NOTFINISH=0;
		for(NUM=0;NUM<256;NUM++)
		{
			if(R[NUM]!=RR[NUM])
			{
				NOTFINISH=1;
				R[NUM]++;
			}
			if(G[NUM]!=GG[NUM])
			{
				NOTFINISH=1;
				G[NUM]++;
			}
			if(B[NUM]!=BB[NUM])
			{
				NOTFINISH=1;
				B[NUM]++;
			}
			outportb(0x3c8,NUM);
			outportb(0x3c9,R[NUM]);
			outportb(0x3c9,G[NUM]);
			outportb(0x3c9,B[NUM]);
		}
		delay(50);
	}
}
