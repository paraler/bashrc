#include <graphics.h>
#include    <conio.h>

int main(void)
{
	int driver=DETECT,mode;
	int NUM;

	initgraph(&driver,&mode,"d:\\tools\\tc3.0\\bgi");
	registerbgidriver(EGAVGA_driver);
	registerbgifont(DEFAULT_FONT);

	for(NUM=1;NUM<5;NUM++)
	{
		setcolor(10+NUM);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,NUM);
		outtextxy(100,100*NUM,"Hello!");
	}
	setcolor(11);

	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	outtextxy(300,300,"Hello!");
	settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
	outtextxy(300,200,"Hello!");
	setcolor(10);
	settextstyle(DEFAULT_FONT,VERT_DIR,2);
	outtextxy(20,10,"* * * Welcome To This System! * * *");
	settextstyle(DEFAULT_FONT,VERT_DIR,2);
	outtextxy(620,10,"* * * Welcome To This System! * * *");
	setcolor(WHITE);
	line(20,0,20,479);
	line(22,0,22,479);
	line(600,0,600,479);
	line(602,0,602,479);
	getch();
	closegraph();
	return 0;
}