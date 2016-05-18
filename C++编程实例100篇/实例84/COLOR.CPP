//THE PROGRAM IS TO CHANGE THREE KINDS OF NUMBERS FROM RANDOM TO ORDER.
//FILE COLOR.CPP

#include      <dos.h>
#include    <stdio.h>
#include    <conio.h>
#include   <stdlib.h>

int SHIFTCOUNTS,COMPARECOUNTS,ARRAY[1000];
void INITIAL();
void GETTIME();
void PRINT(const LIMIT);
void PROCEDURE(const LIMIT);
void GETRANDOM(const LIMIT);
int ADJUST(const LIMIT,const DIVIDE,int POSITION);

int main(void)
{
	PROCEDURE(10);
	PROCEDURE(100);
	PROCEDURE(1000);
	return 0;
}

void INITIAL()
{
	window(1,1,80,25);
	clrscr();
	SHIFTCOUNTS=0;
	COMPARECOUNTS=0;
}

void GETRANDOM(const LIMIT)
{
	int CIRCLE;
	randomize();
	for (CIRCLE=0;CIRCLE<LIMIT;CIRCLE++)
		ARRAY[CIRCLE]=random(3);
	printf("\n***** The Original Array *****\n");
	for (CIRCLE=0;CIRCLE<LIMIT;CIRCLE++)
		printf("%d ",ARRAY[CIRCLE]);
}

int ADJUST(const LIMIT,const DIVIDE,int POSITION)
{
	int LOWLIMIT,HIGHLIMIT,TEMP;
	if (POSITION==0) LOWLIMIT=0;
	else LOWLIMIT=POSITION;
	HIGHLIMIT=LIMIT-1;
	TEMP=ARRAY[LOWLIMIT];
	while (LOWLIMIT<HIGHLIMIT)
	{
		while ((LOWLIMIT<HIGHLIMIT) && (ARRAY[HIGHLIMIT]>=DIVIDE))
		{
			COMPARECOUNTS=COMPARECOUNTS+1;
			HIGHLIMIT=HIGHLIMIT-1;
		}
		COMPARECOUNTS=COMPARECOUNTS+1;
		ARRAY[LOWLIMIT]=ARRAY[HIGHLIMIT];
		SHIFTCOUNTS=SHIFTCOUNTS+1;
		while ((LOWLIMIT<HIGHLIMIT) && (ARRAY[LOWLIMIT]<DIVIDE))
		{
			COMPARECOUNTS=COMPARECOUNTS+1;
			LOWLIMIT=LOWLIMIT+1;
		}
		COMPARECOUNTS=COMPARECOUNTS+1;
		ARRAY[HIGHLIMIT]=ARRAY[LOWLIMIT];
		SHIFTCOUNTS=SHIFTCOUNTS+1;
	}
	ARRAY[LOWLIMIT]=TEMP;
	SHIFTCOUNTS=SHIFTCOUNTS+1;
	if (ARRAY[LOWLIMIT]==0) return(LOWLIMIT+1);
	else
		return(LOWLIMIT);
}

void GETTIME()
{
	delay(50);
	struct time TIME;
	gettime(&TIME);
	printf("The Current Time is: %2d:%02d:%02d.%02d\n",
		 TIME.ti_hour, TIME.ti_min, TIME.ti_sec, TIME.ti_hund);
}

void PRINT(const LIMIT)
{
	int CIRCLE;
	printf("\n\n***** The Three Colors In Order *****\n");
	for (CIRCLE=0;CIRCLE<LIMIT;CIRCLE++)
		printf("%d ",ARRAY[CIRCLE]);
	printf("\n\nThe  Shift  Times : %d \n",SHIFTCOUNTS);
	printf("The Compare Times : %d \n\n",COMPARECOUNTS);
}

void PROCEDURE(const LIMIT)                      //Three const PROCEDUREs
{
	int POSITION=0;
	INITIAL();
	//Initial Environment
	GETTIME();
	//To get beginnig time
	GETRANDOM(LIMIT);
	//To get the random array
	POSITION=ADJUST(LIMIT,1,POSITION);
	//First Division by "1"
	ADJUST(LIMIT,2,POSITION);
	//Second Division by "2"
	PRINT(LIMIT);
	//To print the colors
	GETTIME();
	//To get the ending time
	getch();
	//To dispaly by page
}