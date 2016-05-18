#include <conio.h>

void main(void)
{
	textcolor(YELLOW+BLINK);
	textbackground(11);
	gotoxy(35,15);
	cprintf("This is a test");
	getch();
}
