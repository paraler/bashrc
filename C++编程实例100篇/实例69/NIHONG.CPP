#include<graphics.h>
#include<conio.h>
#include<dos.h>

void DRAWPICTURE(void);
void CHANGE_PALETTE(void);

void main(void)
{
	int driver=DETECT,mode;
	int NUM1,NUM2;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	DRAWPICTURE();
	getch();
	CHANGE_PALETTE();
	getch();
	closegraph();
}
void DRAWPICTURE(void)
{
	int NUM;
	void DRAWPAN(int X,int Y,int R,int COLOR);

	for(NUM=1;NUM<16;NUM++)
	{
		DRAWPAN(40*NUM,350,50,NUM);
	}
}
void DRAWPAN(int X,int Y,int R,int COLOR)
{
	setcolor(WHITE);
	setfillstyle(1,COLOR);
	pieslice(X,Y,45,135,R);
}

void CHANGE_PALETTE(void)
{
	int NUM1=1,NUM2=1;
	while(1)
		{
		for(NUM1=1;NUM1<16;NUM1++)
		{
			setpalette(NUM1,NUM1+NUM2);
			delay(20);
			if(kbhit()) return;
		}
		NUM2++;
		if(NUM2==16) NUM2=1;
		}
}
