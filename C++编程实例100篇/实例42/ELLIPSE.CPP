#include<graphics.h>
#include<conio.h>

void main(void)
{
	int driver=DETECT,mode;
	int X0=200,Y0=250;
	int X=200,Y=60,A=100,B=50;
	int X1=200,Y1=400;
	int NUM;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	setcolor(YELLOW);
	for(NUM=0;NUM<10;NUM++)
	{
	    ellipse(X,Y,0,360,A,B+NUM);
	}
	setcolor(11);
	outtextxy(400,100,"* * * RING OF LIGHT * * *");
	setcolor(13);
	outtextxy(300,160,"To see the ellipse,PRESS ANY KRY... ...");
	getch();
	setcolor(YELLOW);
	ellipse(X0,Y0,0,360,A,B);
	setcolor(11);
	outtextxy(400,250,"* * * NORMAL ELLIPSE * * *");
	setcolor(13);
	outtextxy(300,310,"To see the ellipse FILLED,PRESS ANY KRY... ...");
	getch();
	setcolor(YELLOW);
	setfillstyle(5,11);
	fillellipse(X1,Y1,A,B);
	setcolor(11);
	outtextxy(400,400,"* * * FILLED ELLIPSE * * *");
	setcolor(13);
	outtextxy(300,460,"PRESS ANY KEY to EXIT... ...");
	getch();
	closegraph();
}