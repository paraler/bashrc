//THIS PROGRAM IS TO TEST THE USES OF CLASS "LIST"
//FILE LISTTEST.CPP

#include <conio.h>
#include "List.h"

int main(void)
{
	LIST TEST;
	NODE *Head;
	int BUFFER;
	int CIRCLE=0;
	int PLACE;

	BUFFER=1;
	TEST.Build_Forward(BUFFER);
	BUFFER=2;
	TEST.Build_Forward(BUFFER);
	BUFFER=3;
	TEST.Build_Forward(BUFFER);
	BUFFER=1;
	TEST.Build_Backward(BUFFER);
	BUFFER=2;
	TEST.Build_Backward(BUFFER);
	BUFFER=3;
	TEST.Build_Backward(BUFFER);
	clrscr();
	Head=TEST.GET_HEAD();
	printf("\nThe data in the list is(from HEAD to END):");
	for (CIRCLE=0;CIRCLE<6;CIRCLE++)
	{
		BUFFER=TEST.GET_NEXT(Head);
		printf("\n %d",BUFFER);
	}
	printf("\n\nWe can find the data for you,Plese input a position(1--):");
	scanf("%d",&PLACE);
	printf("The data is:%d",TEST.GET_POSITION(PLACE));
	getch();
	return 0;
}