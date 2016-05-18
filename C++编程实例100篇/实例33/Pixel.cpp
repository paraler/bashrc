#include<graphics.h>
#include<math.h>
#include<complex.h>
#include<conio.h>

void main()
{
	int NUM;
	int X=300,Y=250,R=1,XX=0,YY=0,ANGLE=0;
	int DRIVER=DETECT,MODE;

	registerbgidriver(EGAVGA_driver);
	initgraph(&DRIVER,&MODE,"");
	for(NUM=0;NUM<300;NUM++)
	{
		XX=X+R*cos(ANGLE);
		YY=Y+R*sin(ANGLE);
		putpixel(XX,YY,WHITE);
		ANGLE+=1;
		R++;
	}
	getch();
	closegraph();
}
