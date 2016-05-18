//THIS PROGRAM IS TO TEST THE USES OF CLASS "LIST"
//FILE LISTTEST.CPP

#include <conio.h>
#include "BILIST.H"

int main(void)
{
	LIST TEST;
	int BUFFER;

	BUFFER=4;
	TEST.Build_HT(BUFFER);
	BUFFER=5;
	TEST.Build_HT(BUFFER);
	BUFFER=6;
	TEST.Build_HT(BUFFER);
	BUFFER=3;
	TEST.Build_TH(BUFFER);
	BUFFER=2;
	TEST.Build_TH(BUFFER);
	BUFFER=1;
	TEST.Build_TH(BUFFER);
	clrscr();
	TEST.DISPLAY_HT();
	TEST.DISPLAY_TH();
	printf("\n\nPress any key to EXIT... ...");
	getch();
	return 0;
}