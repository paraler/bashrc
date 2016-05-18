#include<graphics.h>
#include<conio.h>

void main(void)
{
	void DRAW6(int X,int Y);
	int driver=DETECT,mode;
	int NUM,NUM1;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	for(NUM=0;NUM<6;NUM++)
		for(NUM1=0;NUM1<3;NUM1++)
			DRAW6(NUM*100+50,NUM1*150);
	getch();
	closegraph();
}
void DRAW6(int X,int Y)
{
	int DATA[]={X,Y,X-50,Y+50,X-50,Y+100,X,Y+150,X+50,Y+100,X+50,Y+50,X,Y};
	setcolor(YELLOW);
	setfillstyle(3,YELLOW);
	fillpoly(6,DATA);
}