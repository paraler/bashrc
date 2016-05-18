/*-------------------------------------------------------------------------*/
/*Program name: Example  1										*/
/*Draw some line												*/
/*-------------------------------------------------------------------------*/

#include<graphics.h>
#include<stdio.h>
#include<conio.h>
void main()
{
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");     /*INITIALIZE THE MODE*/

	/* * * * DRAW SOME NORMAL LINES * * * */
	setcolor(RED);/* CHANGE THE CURRENT COLOR TO red*/
	line(150,101,450,101);  /*DRAW THE TOP LINE*/
	line(151,101,151,201);  /*DRAW THE LEFT LINE*/
	setcolor(BLUE);/* CHANGE THE CURRENT COLOR TO blue */
	line(150,200,450,200);  /*DRAW THE BOTTOM LINE*/
	line(450,200,450,100);  /*DRAW THE RIGHT LINE*/

	/*DRAW SOME LINES USING linerel()*/
	setcolor(YELLOW);
	moveto(150,101);        /*MOVE THE CURSOR TO THE START POSITION*/
	linerel(300,100);
	setcolor(YELLOW);
	moveto(450,101);        /*MOVE THE CURSOR TO THE START POSITION*/
	linerel(-300,100);

	getch();                /*GET A CHAR TO RETURN(EXIT)*/
	closegraph();           /*CLOSE GRAPH :VERY IMPORTANT!!!*/
}
