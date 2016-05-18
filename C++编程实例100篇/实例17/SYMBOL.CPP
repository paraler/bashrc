#include <iostream.h>
#include <conio.h>
#include <stdio.h>

int NUMBER;
int main(void)
{
	int NUMBER;
	clrscr();
	NUMBER=1;
	printf("\n-*-*-*- Before changing the NUMBER -*-*-*-");
	printf("\nDISPLAY LOCAL NUMBER VALUE =%d",NUMBER);
	NUMBER=100;
	::NUMBER=200;
	printf("\n\n-*-*-*- After changing the NUMBER -*-*-*-");
	printf("\nDISPLAY LOCAL NUMBER VALUE =%d",NUMBER);
	printf("\nDISPLAY GLOBAL NUMBER VALUE =%d",::NUMBER);
	getch();
	return 0;
}