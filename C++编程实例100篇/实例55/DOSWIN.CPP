#include<graphics.h>
#include<conio.h>

void DRAW_WIN(int X,int Y,int W,int H,int FORWARD,int BACKWARD);
void main()
{
	int driver=DETECT,mode;
	int XX=50,YY=30,WIDE=500,HIGHT=400;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	DRAW_WIN(XX,YY,WIDE,HIGHT,BLUE,LIGHTGRAY);
	setcolor(YELLOW);
	outtextxy(XX+120,YY+150,"Welcome to this system!");
	setcolor(11);
	outtextxy(XX+120,YY+170,"Press any key to EXIT... ...");
	getch();
	DRAW_WIN(XX+80,YY+80,WIDE-200,HIGHT-300,RED,LIGHTGRAY);
	outtextxy(XX+100,YY+120,"Thank you for using this system!");
	getch();
	closegraph();

}
void DRAW_WIN(int X,int Y,int W,int H,int FORWARD,int BACKWARD)
{
	setfillstyle(1,BACKWARD);
	bar(X+10,Y+10,X+W+10,Y+H+10);
	setfillstyle(1,FORWARD);
	bar(X,Y,X+W,Y+H);
}