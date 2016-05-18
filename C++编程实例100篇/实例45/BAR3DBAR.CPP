#include<graphics.h>
#include<conio.h>

void main(void)
{
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	setfillstyle(6,YELLOW);
	bar(100,100,200,150);
	setcolor(LIGHTCYAN);
	outtextxy(300,100,"* * * BAR * * *");
	setcolor(13);
	outtextxy(300,150,"TO see the 3D Bar,Press Any Key... ...");
	getch();
	setcolor(LIGHTCYAN);
	setfillstyle(3,YELLOW);
	bar3d(100,300,200,400,10,1);
	outtextxy(300,300,"* * * 3D BAR * * *");
	setcolor(13);
	outtextxy(300,350,"TO EXIT,Press Any Key... ...");
	getch();
	closegraph();
}