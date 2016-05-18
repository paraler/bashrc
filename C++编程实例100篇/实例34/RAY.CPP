/*----------------------------ANIMATION-----------------------------*/
/*				  NAME : COLOR RAYS WITH SOUND    			   */
/*----------------------------ANIMATION-----------------------------*/

#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int X0=300,Y0=200,X=350,Y=200,R=100,NUM;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	for(NUM=1;NUM<=50;NUM++)
	{
		X=X0+R*cos(NUM*2*3.1415926/50); /*CALCULATE THE NEW STATION*/
		Y=Y0+R*sin(NUM*2*3.1415926/50);
		setcolor(NUM%11);               /*CHANGE THE COLOR*/
		line(X0,Y0,X,Y);                /*DRAW THE NEW LINE*/
		sound(523);
		delay(20);
		nosound();
		delay(30);
	}
	setcolor(YELLOW);
	outtextxy(100,450,"*-*-*-*-*-*   COLOR RAYS WITH SOUND   *-*-*-*-*-*-*");
	getch();
	closegraph();
}