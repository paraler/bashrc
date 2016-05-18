#include<dos.h>
#include<conio.h>

void INIT_SCREEN(void);
void RESTORE_SCREEN(void);

void DRAWPOINT(int X,int Y,int color);
void DRAWLINE(int X,int Y,int LENGTH,int COLOR);
void CHANGE_COLOR(int COLORNUM,int Red,int Green,int Blue);
void DRAWBAR(int X,int Y);


int main(void)
{
	INIT_SCREEN();
	DRAWBAR(10,50);
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
void DRAWLINE(int X,int Y,int LENGTH,int COLOR)
{
	int NUM;
	for(NUM=0;NUM<LENGTH;NUM++)
		DRAWPOINT(X+NUM,Y,COLOR);
}
void DRAWBAR(int X,int Y)
{
	int NUM;
	int Red=0,Green=0,Blue=0;
	for(NUM=0;NUM<15;NUM++)
	{
		CHANGE_COLOR(NUM,Red,Green,Blue);
		Blue+=4;
		Red+=3;
		Green+=2;
	}
	int TEMP_Y=Y;
	for(NUM=14;NUM>=0;NUM--)
		DRAWLINE(X,TEMP_Y--,200,NUM);
	TEMP_Y=Y;
	for(NUM=14;NUM>=0;NUM--)
		DRAWLINE(X,TEMP_Y++,200,NUM);
}