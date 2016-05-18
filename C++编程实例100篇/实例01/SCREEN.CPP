//THE PROGRAM IS TO TEST THE SCREEN POINTER'S USING
//FILE SCREEN.CPP

#include <string.h>
#include  <stdio.h>
#include  <conio.h>
#include	<dos.h>

#define SCREEN (*SCREENPOINTER)
#define      ROW 25
#define   COLUMN 80

typedef struct TEXT
{
	unsigned char CHAR;
	unsigned char ATTRIBUTE;
}TEST;

typedef TEST SCREENARRAY[ROW][COLUMN];
SCREENARRAY  *SCREENPOINTER=(SCREENARRAY  *)0xb8000000l;

char HELLO[]="I LOVE YOU --->XIANGCHENGYAN !";

int main(void)
{
	int CIRCLE,CIRCLE1;
	circle();
	for(CIRCLE=0;CIRCLE<strlen(HELLO);CIRCLE++)
	{
		SCREEN[10][CIRCLE].CHAR=HELLO[CIRCLE];
	}
	getch();
	for(CIRCLE1=5;CIRCLE1<15;CIRCLE1++)
		for(CIRCLE=0;CIRCLE<strlen(HELLO);CIRCLE++)
		{
			SCREEN[10][CIRCLE].ATTRIBUTE=CIRCLE1;
			delay(10);
		}
	getch();
	return 0;
}