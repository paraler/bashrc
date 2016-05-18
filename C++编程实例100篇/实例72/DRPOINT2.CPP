#include<dos.h>
#include<conio.h>

void INIT_SCREEN(void);
void RESTORE_SCREEN(void);

void DRAWPOINT(int X,int Y,int COLOR);
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
	union REGS regs;
	regs.h.ah=0x10;
	regs.h.al=0x10;
	regs.x.bx=COLORNUM;
	regs.h.dh=Red;
	regs.h.ch=Green;
	regs.h.cl=Blue;
	int86(0x10,&regs,&regs);
}
void DRAWPOINT(int X,int Y,int COLOR)
{
	union REGS regs;
	regs.h.ah=0x0c;
	regs.h.al=COLOR;
	regs.x.cx=X;
	regs.x.dx=Y;
	regs.h.bh=0;
	int86(0x10,&regs,&regs);
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
		Blue+=3;
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