#include<dos.h>
#include<conio.h>
#include<math.h>
#define PI 3.1415926

void INIT_SCREEN(void);
void RESTORE_SCREEN(void);

void DRAWPOINT(int X,int Y,int color);
void DRAWCIRCLE(int X,int Y,int R,int COLOR);
void CHANGE_COLOR(int COLORNUM,int Red,int Green,int Blue);
void DRAW(int X,int Y);


int main(void)
{
	INIT_SCREEN();
	DRAW(150,100);
	getch();
	RESTORE_SCREEN();
	return(0);
}
void INIT_SCREEN(void)
{
	union REGS regs;
	regs.x.ax=0x13;
	int86(0x10,&regs,&regs);
}
void RESTORE_SCREEN(void)
{
	union REGS regs;
	regs.x.ax=0x03;
	int86(0x10,&regs,&regs);
}
void CHANGE_COLOR(int COLORNUM,int Red,int Green,int Blue)
{
	outportb(0x3c8,COLORNUM);
	outportb(0x3c9,Red);
	outportb(0x3c9,Green);
	outportb(0x3c9,Blue);
}
void DRAWPOINT(int X,int Y,int color)
{
	char far *p;
	p=(char far *)(0x0a0000000L);
	*(X+Y*320+p)=color;
}
void DRAWCIRCLE(int X,int Y,int R,int COLOR)
{
	int XX,YY,ANGLE;
	for(ANGLE=0;ANGLE<360;ANGLE++)
	{
		XX=X+R*cos(2*PI*ANGLE/360);
		YY=Y+R*sin(2*PI*ANGLE/360);
		DRAWPOINT(XX,YY,COLOR);
	}

}
void DRAW(int X,int Y)
{
	int NUM;
	int Red=0,Green=0,Blue=0,R=0;
	for(NUM=0;NUM<=15;NUM++)
	{
		CHANGE_COLOR(NUM,Red,Green,Blue);
		Blue+=2;
		Red+=4;
		Green+=2;
	}
	for(NUM=15;NUM>0;NUM--)
	{
		DRAWCIRCLE(X,Y,R++,NUM);
		DRAWCIRCLE(X,Y,R++,NUM);
	}
}