//THIS PROGRAM IS TO TEST THE USES OF CLASS "LIST"
//FILE LISTTEST.CPP

#include <conio.h>
#include "List.h"

int main(void)
{
	LIST TEST;
	NODE *Head;
	int BUFFER;

	BUFFER=10;
	TEST.INSERT(BUFFER);
	BUFFER=20;
	TEST.INSERT(BUFFER);
	BUFFER=30;
	TEST.INSERT(BUFFER);
	clrscr();
	Head=TEST.GET_HEAD();
	printf("\nThe data in the list is(from HEAD to END):");
	TEST.DISPLAY(Head);
	printf("\nInput a number to insert in the list:");
	scanf("%d",&BUFFER);
	TEST.INSERT(BUFFER);
	Head=TEST.GET_HEAD();/*SOMETIMES HEAD MAY BE CHANGED*/
	TEST.DISPLAY(Head);
	getch();
	return 0;
}