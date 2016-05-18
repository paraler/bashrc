#include <stdio.h>
#include <conio.h>

inline int GETSUM(int NUM1,int NUM2)
{
	int SUM;
	SUM=NUM1+NUM2;
	return SUM;
}

int main(void)
{
	int NUMBER1,NUMBER2,SUM;

	printf("\nPlease input three integer  : ");
	scanf("%d",&NUMBER1);
	printf("\nPlease input another integer:");
	scanf("%d",&NUMBER2);
	SUM=GETSUM(NUMBER1,NUMBER2);
	printf("\nThe SUM integer is %d .",SUM);
	getch();
	return 0;
}