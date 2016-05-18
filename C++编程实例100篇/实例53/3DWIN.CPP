#include<conio.h>

void WIN3D(int LEFT,int TOP,int RIGHT,int BOTTOM,int FOR_COLOR,int BAK_COLOR,int TEXT_COLOR);
void main(void)
{
	WIN3D(30,10,60,15,YELLOW,BLUE,WHITE);
	gotoxy(10,3);
	cputs("HELLO!");
	getch();
}
void WIN3D(int LEFT,int TOP,int RIGHT,int BOTTOM,int FOR_COLOR,int BAK_COLOR,int TEXT_COLOR)
{
	textbackground(BAK_COLOR);
	window(LEFT,TOP,RIGHT,BOTTOM);
	clrscr();
	textbackground(FOR_COLOR);
	textcolor(TEXT_COLOR);
	window(LEFT-2,TOP-1,RIGHT-2,BOTTOM-1);
	clrscr();
}