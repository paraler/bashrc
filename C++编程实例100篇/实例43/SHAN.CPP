#include<graphics.h>
#include<conio.h>

void main(void)
{
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	setcolor(YELLOW);
	circle(100,100,50);
	setcolor(LIGHTCYAN);
	outtextxy(300,100,"* * * CIRCLE * * *");
	setcolor(13);
	outtextxy(300,150,"TO see the FAN SHAPED,Press Any Key... ...");
	getch();
	setcolor(LIGHTCYAN);
	setfillstyle(3,YELLOW);
	pieslice(100,350,45,135,100);
	outtextxy(300,300,"* * * SECTOR (FAN SHAPED) * * *");
	setcolor(13);
	outtextxy(300,350,"TO EXIT,Press Any Key... ...");
	getch();
	closegraph();
}