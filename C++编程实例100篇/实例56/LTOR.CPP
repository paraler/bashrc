#include<graphics.h>
#include<conio.h>
#include<dos.h>

void DRAWPICTURE(void);
void CLR_L_R(void);
void CLR_R_L(void);

void main()
{
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	DRAWPICTURE();
	getch();
	CLR_L_R();
	setcolor(YELLOW);
	outtextxy(250,200,"Press any key to CONTINUE!");
	getch();
	DRAWPICTURE();
	getch();
	CLR_R_L();
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
void CLR_R_L(void)
{
	int NUM;
	setcolor(BLACK);
	for(NUM=639;NUM>=0;NUM--)
	{
		line(NUM,0,NUM,479);
		delay(5);
	}
}
void CLR_L_R(void)
{
	int NUM;
	setcolor(BLACK);
	for(NUM=0;NUM<640;NUM++)
	{
		line(NUM,0,NUM,479);
		delay(5);
	}
}