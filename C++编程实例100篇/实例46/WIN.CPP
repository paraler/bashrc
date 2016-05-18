/*----------------------------GRAPH----------------------------------*/
/*				    NAME:UNREAL TIME BAR				    	    */
/*----------------------------GRAPH----------------------------------*/

#include<graphics.h>
#include<conio.h>
#include<dos.h>


void DrawWin(int WINX,int WINY,int WINWIDE,int WINHIGHT)			//draw main frame of program
{
	setcolor(WHITE);
	moveto(WINX+WINWIDE,WINY);
	lineto(WINX,WINY);
	lineto(WINX,WINY+WINHIGHT);
	moveto(WINX+WINWIDE-1,WINY+1);
	lineto(WINX+1,WINY+1);
	lineto(WINX+1,WINY+WINHIGHT-1);
	setcolor(DARKGRAY);
	moveto(WINX+1,WINY+WINHIGHT);
	lineto(WINX+WINWIDE,WINY);
	moveto(WINX+2,WINY+WINHIGHT-1);
	lineto(WINX+WINWIDE-1,WINY+WINHIGHT-1);
	lineto(WINX+WINWIDE-1,WINY+1);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(WINX+2,WINY+2,WINX+WINWIDE-2,WINY+WINHIGHT-2);
	setcolor(DARKGRAY);
	moveto(WINX+WINWIDE-10,WINY+60);
	lineto(WINX+10,WINY+60);
	lineto(WINX+10,WINY+WINHIGHT-20);
	setcolor(WHITE);
	lineto(WINX+WINWIDE-10,WINY+WINHIGHT-20);
	lineto(WINX+WINWIDE-10,WINY+60);
}

void main()
{
	  int driver=DETECT,mode;
	  int NUM;

	  registerbgidriver(EGAVGA_driver);
	  initgraph(&driver,&mode,"");
	  DrawWin(200,250,250,100);
	  setcolor(BLUE);
	  outtextxy(210,320," Press any key to EXIT... ... ");
	  getch();
	  closegraph();
}

