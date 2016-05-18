/*----------------------------ANIMATION-----------------------------*/
/*					    NAME:ROLLING					   */
/*----------------------------ANIMATION-----------------------------*/

#include<graphics.h>
#include<dos.h>
#include<alloc.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	int driver=DETECT,mode;
	int  X=10,Y=190-1,R=10,NUM;
	unsigned int SIZE;
	char /*far*/ *BUFFER;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	SIZE=imagesize(0,169,20,189);              /*GET TTHE SIZE OF THE CIRCLE*/
	BUFFER=(char far *)malloc(SIZE);           /*REMEMBER THE LOCATION OF THE CIRCLE DATA*/
	line(0,200,640,200);
	setcolor(11);
	circle(X,Y,R);
	setfillstyle(1,11);
	floodfill(X,Y,11);
	getimage(0,179,20,199,BUFFER);             /*STORE THE DATA OF THE CIRCLE*/
	for(NUM=0;NUM<32;NUM++)
	{
		putimage(X-10,Y-10,BUFFER,XOR_PUT);    /*DELETE THE CIRCLE*/
		X+=20;
		putimage(X-10,Y-10,BUFFER,COPY_PUT);   /*DRAW THE CIRCLE*/
		delay(50);
	}
	getch();      /*PRESS ANY KEY TO RETURN TO TEXT MODE*/
	closegraph();
}