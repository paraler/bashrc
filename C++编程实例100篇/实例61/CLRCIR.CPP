#include<graphics.h>
#include<conio.h>

void DRAWPICTURE(void);
void CLR_CIRCLE(void);

void main()
{
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	DRAWPICTURE();
	getch();
	CLR_CIRCLE();
	setcolor(YELLOW);
	outtextxy(250,200,"Press any key to EXIT!");
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

void CLR_CIRCLE(void)
{
	setcolor(0);
	setfillstyle(1,0);
	for(int NUM=0;NUM<400;NUM+=1)
	{
		circle(320,240,NUM);
		floodfill(320,240,0);
		circle(319,239,NUM);
		floodfill(319,239,0);
		circle(319,241,NUM);
		floodfill(319,241,0);
	}
}