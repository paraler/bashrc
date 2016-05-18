#include <stdio.h>
#include <math.h>

int GETMIN(int NUM1=100,int NUM2=200,int NUM3=300)
{
	int MIN;
	if (NUM1>NUM2) MIN=NUM2;
	else MIN=NUM1;
	if (MIN>NUM3) MIN=NUM3;
	return MIN;
}

int main(void)
{
	int NUMBER1,NUMBER2,NUMBER3,MINIUM;
	printf("Please input three integers : ");
	printf("\nThe first:");
	scanf("%d",&NUMBER1);
	printf("The second:");
	scanf("%d",&NUMBER2);
	printf("The third:");
	scanf("%d",&NUMBER3);
	MINIUM=GETMIN(NUMBER1,NUMBER2,NUMBER3);
	printf("\nThe min integer is %d .",MINIUM);
	MINIUM=GETMIN();
	printf("\n\n*** The defaul numbers:100 200 300.***");
	printf("\n\n***The min integer is %d ***.",MINIUM);

	return 0;
}