/*----------------------------PICTURE-----------------------------*/
/*					    NAME: A BEAUTIFUL BALL					   */
/*----------------------------PIICTURE-----------------------------*/
#include<graphics.h>
#include<dos.h>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int X1=250,Y1=244,R1=50,
	    X2=260,Y2=233,R2=70,
	    X3=270,Y3=210,R3=100;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	setcolor(DARKGRAY);
	circle(X3,Y3,R3);
	setfillstyle(1,DARKGRAY);
	floodfill(X3,Y3,DARKGRAY);
	delay(30);
	setcolor(LIGHTGRAY);
	circle(X2,Y2,R2);
	setfillstyle(1,LIGHTGRAY);
	floodfill(X2,Y2,LIGHTGRAY);
	delay(30);
	setcolor(WHITE);
	circle(X1,Y1,R1);
	setfillstyle(1,WHITE);
	floodfill(X1,Y1,WHITE);
	delay(30);
	getch();
	setcolor(11);
	outtextxy(10,450,"*-*-*-*-*-*-*-*-*-*-*-*-*"
				  " ISN'T IT A BEAUTIFUL BALL?"
				  " *-*-*-*-*-*-*-*-*-*-*-*-*-*");
	getch();
	closegraph();
}