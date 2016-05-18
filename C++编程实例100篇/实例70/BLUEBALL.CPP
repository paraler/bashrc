#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<dos.h>

void DRAWBALL(void);
void CHANGE_COLOR(int NUM,int R,int G,int B);

void main(void)
{
	int driver=DETECT,mode;
	int NUM;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	CHANGE_COLOR(1,0,0,25);
	CHANGE_COLOR(2,0,10,30);
	CHANGE_COLOR(3,0,15,40);
	CHANGE_COLOR(4,10,20,50);
	CHANGE_COLOR(5,22,32,63);
	DRAWBALL();
	getch();
	closegraph();
}
void CHANGE_COLOR(int NUM,int R,int G,int B)
{
	outportb(0x3c8,NUM);
	outportb(0x3c9,R);
	outportb(0x3c9,G);
	outportb(0x3c9,B);
}
void DRAWBALL(void)
{
	int NUM1,NUM2,R=120;

	for(NUM2=1;NUM2<=5;NUM2++)
		{
			setcolor(NUM2);
			setfillstyle(1,NUM2);
			circle(320,240,R);
			floodfill(320,240,NUM2);
			R-=20;
		}
}