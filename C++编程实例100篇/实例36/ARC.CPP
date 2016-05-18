/*----------------------------PICTURE-----------------------------*/
/*					    NAME: GEOMETRIC FORM				 */
/*----------------------------PICTURE-----------------------------*/

#include<graphics.h>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int X=50,Y=350,R=50,NUM;
	int LEFT_X=4,LEFT_Y=332,RIGHT_X=97,RIGHT_Y=400;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	for(NUM=0;NUM<50;NUM++)
	{
		arc(X,Y,20,160,R);
		X+=10;
		Y-=4;
	}
	for(NUM=0;NUM<50;NUM++)
	{
		rectangle(LEFT_X,LEFT_Y,RIGHT_X,RIGHT_Y);
		LEFT_X+=10;
		LEFT_Y-=4;
		RIGHT_X+=10;
		RIGHT_Y-=4;
	}
	getch();
	setcolor(11);
	outtextxy(5,450,"*-*-*-*-*-* This is only one example..."
				 "You can also make a lot! *-*-*-*-*-*");
	getch();
	closegraph();
}