/*----------------------------GRAPH----------------------------------*/
/*				    NAME:UNREAL TIME BAR				    	    */
/*----------------------------GRAPH----------------------------------*/

#include<graphics.h>
#include<conio.h>
#include<dos.h>


void DrawWin(int wx,int wy,int ww,int wh)			//draw main frame of program
{
	setcolor(WHITE);
	moveto(wx+ww,wy);
	lineto(wx,wy);
	lineto(wx,wy+wh);
	moveto(wx+ww-1,wy+1);
	lineto(wx+1,wy+1);
	lineto(wx+1,wy+wh-1);
	setcolor(DARKGRAY);
	moveto(wx+1,wy+wh);
	lineto(wx+ww,wy);
	moveto(wx+2,wy+wh-1);
	lineto(wx+ww-1,wy+wh-1);
	lineto(wx+ww-1,wy+1);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(wx+2,wy+2,wx+ww-2,wy+wh-2);
	setcolor(DARKGRAY);
	moveto(wx+ww-10,wy+60);
	lineto(wx+10,wy+60);
	lineto(wx+10,wy+wh-20);
	setcolor(WHITE);
	lineto(wx+ww-10,wy+wh-20);
	lineto(wx+ww-10,wy+60);
}

void main()
{
	  int driver=DETECT,mode;
	  int NUM,X1=110,Y1=160,X2=120,Y2=180;
	  int X3=110,Y3=360,X4=123,Y4=380;

	  registerbgidriver(EGAVGA_driver);
	  initgraph(&driver,&mode,"");
	  DrawWin(100,100,300,100);
	  DrawWin(100,300,300,100);
	  setcolor(YELLOW);
	  outtextxy(120,120,"This is a suppositional time bar");
	  outtextxy(120,320,"This is a suppositional time bar");
	  setfillstyle(1,BLUE);
	  for(NUM=0;NUM<22;NUM++)
	  {
		bar(X1,Y1,X2,Y2);
		bar(X3,Y3,X4,Y4);
		delay(100);
		X1+=13;
		X2+=13;
		X3+=13;
		X4+=13;
	  }
	  getch();
	  closegraph();
}

