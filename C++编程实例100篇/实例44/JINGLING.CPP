#include<graphics.h>
#include<conio.h>
void main()
{
	int driver=DETECT,mode;
	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	setcolor(LIGHTGRAY);
	setfillstyle(1,YELLOW);
	for(int NUM=0;NUM<7;NUM++)
		pieslice(200,200+NUM,-45,45,70);
	setcolor(LIGHTGRAY);
	for(NUM=0;NUM<7;NUM++)
	{
		circle(190,170+NUM,15);
		setfillstyle(1,0);
		floodfill(190,170,LIGHTGRAY);
	}
	getch();
	closegraph();
}