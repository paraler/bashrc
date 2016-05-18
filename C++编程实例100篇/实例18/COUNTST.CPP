//THIS PROGRAM IS TO TEST THE COUNTER CLASS
//FILE COUNTST.CPP

#define     ZERO 0
#define     TEN 10
#include <conio.h>
#include "Count.h"

int main(void)
{
	COUNTER TEST;
	int CIRCLE;
	clrscr();
	for (CIRCLE=ZERO;CIRCLE<TEN;CIRCLE++)
	{
		TEST++;
		TEST.DISPLAY();
	}
	for (CIRCLE=ZERO;CIRCLE<TEN;CIRCLE++)
	{
		TEST--;
		TEST.DISPLAY();
	}
	getch();
	return 0;
}