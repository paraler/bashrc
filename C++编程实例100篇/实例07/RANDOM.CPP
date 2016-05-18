//THE PROGRAM HELPS YOU TO GET THE RANDOM NUMBERS.
//FILE RANDOM.CPP

#include <stdlib.h>
#include  <stdio.h>
#include  <conio.h>
#include   <time.h>

int main(void)
{
	int INPUT,NUMBER,CIRCLE;
    printf("\n*-*-*-*-* TO GETTING RANDOM NUMBERS' PROGRAM *-*-*-*-*\n");
	printf("\n***** MESSAGE : I WILL DISPLAY RANDOM NUMBERS\n");
	printf("                    BELOW YOUR INPUT INTEGER !!!\n");
	printf("\n----- NOW , PLEASE INPUT AN INTEGER : ");
	scanf("%d",&INPUT);
	printf("\n-*-*-*-*-*- HOW MANY RANDOW NUMBERS YOU WANT : ");
	scanf("%d",&NUMBER);
	printf("\n***** THE RANDOM NUMBERS ARE THE FOLLOWING *****\n\n");
	for (CIRCLE=0;CIRCLE<NUMBER;CIRCLE++)
	{
		printf("%d ",INPUT);
	}
	getch();
	return 0;
}