//THIS IS A SIMPLE PROGRAM FOR CHANGING SHESHI TO HUASHI .
//FILE HUASHI.CPP

#include <stdio.h>
#include <conio.h>

int main(void)
{
	int LOWLIMIT,HIGHLIMIT;
	int HUASHI,SHESHI;
	LOWLIMIT=30;
	HIGHLIMIT=45;
	clrscr();
	printf("\n		-*-*-*-*-*-*-* A CHANGING SYSTEM *-*-*-*-*-*-*-\n");
	printf("\n***** THE FOLLOWING DATAS ARE THE HUASHI & SHESHI DEGREES\n");
	printf("\n	       -*-*-HUASHI-*-*-	          -*-*-SHESHI-*-*- \n");
	for(SHESHI=LOWLIMIT;SHESHI<HIGHLIMIT;SHESHI++)
	{
		HUASHI=(9.0/5.0)*float(SHESHI)+32;
		printf("		      %d 		         %d\n",HUASHI,SHESHI);
	}
	printf("\n-*-*-*-*-*-* YOU CAN USE IT TO KNOW THE TEMPRATURE OF POEPLE *-*-*-*-*-*-\n");
	getch();
	return 0;
}