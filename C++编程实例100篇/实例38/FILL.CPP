/*-------------------------------GRAPH---------------------------------*/
/*					    NAME:ALL FILL TYPES					 */
/*-------------------------------GRAPH---------------------------------*/


#include<graphics.h>
#include<dos.h>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int X1=20,Y1=20,R=10,NUM;
	int X2=20,Y2=450;
	int COLOR1=11,COLOR2=12;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	setcolor(COLOR1);
	for(NUM=0;NUM<30;NUM++)
	{
		circle(X1,Y1,R);
		setfillstyle(NUM%12,COLOR1);
		floodfill(X1,Y1,COLOR1);
		X1+=20;
		delay(100);
	}
	setcolor(COLOR2);
	for(NUM=0;NUM<30;NUM++)
	{
		circle(X2,Y2,R);
		setfillstyle(NUM%12,COLOR2);
		floodfill(X2,Y2,COLOR2);
		X2+=20;
		delay(100);
	}
	setcolor(YELLOW);
	outtextxy(200,250,"Wish you have a good time ! ");
	setcolor(BLUE);
	line(200,260,420,260);
	getch();
	closegraph();
}