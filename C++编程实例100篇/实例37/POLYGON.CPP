/*----------------------------PICTURE-----------------------------*/
/*					NAME: GEOMETRIC PERSON			 	 */
/*					   TOOL: POLYGON					 */
/*----------------------------PICTURE-----------------------------*/

#include<graphics.h>
#include<conio.h>
#include<dos.h>

void main()
{
	int driver=DETECT,mode;
	int DATAARRAY[]={250,200,150,300,450,300,350,200,250,200};
	int NUM;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	for(NUM=0;NUM<15;NUM++)
	{
		setcolor(NUM);                              /*SET THE COLOR OF LINES*/
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);     /*SET THE LINE STYLE*/
		circle(300,150,50);          /*DRAW THE HEAD*/
		circle(285,140,7);           /*DRAW THE LEFT EYE*/
		circle(315,140,7);           /*DRAW THE RIGHT EYE*/
		arc(300,150,225,315,25);     /*DRAW THE MOUTH*/
		drawpoly(5,DATAARRAY);       /*DRAW THE BODY*/
		delay(150);
	}
	getch();	/*PRESS ANY KEY TO RETURN */
	closegraph();
}