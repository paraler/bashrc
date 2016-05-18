/*----------------------------ANIMATION-----------------------------*/
/*					    NAME:ROLLING					   */
/*----------------------------ANIMATION-----------------------------*/

#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>

void main()
{
	int driver=DETECT,mode;
	int R=10,NUM=0;
	int X=10,Y=190-1;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");        /*INITIAL THE GRAPH*/
	line(0,200,640,200);
	do
	{                                   /*DRAW THE CIRCLE*/
		setcolor(11);
		circle(X,Y,R);
		setfillstyle(1,11);
		floodfill(X,Y,11);
		delay(50);
		setcolor(BLACK);               /*DELETE THE CIRCLE*/
		circle(X,Y,R);
		setfillstyle(1,BLACK);
		floodfill(X,Y,BLACK);
		X+=10;                         /*CHANGE THE POSITION OF THE CIRCLE*/
		Y=190-1;
		NUM++;
	} while(NUM<64);
	getch();		/*PRESS ANY KEY TO RETURN TO TEXT MODE*/
	closegraph();
}