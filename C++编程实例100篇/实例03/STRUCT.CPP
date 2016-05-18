#include<conio.h>
#include<stdio.h>
void main()
{int NUM,I;
	struct STUDENT
	{char NAME[30];
		int AGE;
		char ID[10];
	};
	struct STUDENT STD[100];
    cprintf("\nHow many student do you have? Input the number:");
	scanf("%d",&NUM);
    for(I=1;I<=NUM;I++)
	{cprintf("\nInput student %d -- name:",I);
		scanf("%s",&STD[I-1].NAME);
		cprintf("\nInput student %d -- age:",I);
		scanf("%d",&STD[I-1].AGE);
		cprintf("\nInput student %d -- ID:",I);
		scanf("%s",&STD[I-1].ID);
	}
	
	cprintf("\nTo see the RESULT,Press Any Key... ...");
	getch();
	
	for(I=1;I<=NUM;I++)
	{
		printf("\n student %d -- name:%s",I,STD[I-1].NAME);
		printf("\n student %d -- age:%d",I,STD[I-1].AGE);
		printf("\n student %d -- ID:%s",I,STD[I-1].ID);
	}
	
	cprintf("\nPress Any Key To EXIT... ...");
	getch();
}