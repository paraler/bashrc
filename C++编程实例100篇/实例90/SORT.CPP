#include <conio.h>
#include <stdio.h>

int main()
{
	int NUM,CIRCLE,I,J,BUFFER;
	int DATA[200];
	clrscr();
	printf("Input the number of data:");
	scanf("%d",&NUM);
	for(CIRCLE=0;CIRCLE<NUM;CIRCLE++)
	{
		printf("\nDATA[%d]:",CIRCLE+1);
		scanf("%d",&DATA[CIRCLE]);
	}
	for(I=0;I<NUM-1;I++)
		for(J=I+1;J<NUM;J++)
		{
			if(DATA[J]<DATA[I])
			{
				BUFFER=DATA[J];
				DATA[J]=DATA[I];
				DATA[I]=BUFFER;
			}
		}
	printf("\nThe result is: ");
	for(CIRCLE=0;CIRCLE<NUM;CIRCLE++)
	{
		printf("%d  ",DATA[CIRCLE]);
	}
	getch();
	return 0;
}