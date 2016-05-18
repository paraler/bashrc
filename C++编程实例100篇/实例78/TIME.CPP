#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<dos.h>

void main()
{
	time_t tt;
	char * t;

	clrscr();
	while(!kbhit())
	{
		tt=time(NULL);
		textcolor(11);
		gotoxy(30,15);
		t=ctime(&tt);
		cprintf(t);
	}
}