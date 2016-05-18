//THE PROGRAM IS TO TEST THE FIBONACCI ORDER LIST.
//FILE FIBONACI.CPP

#define   CONST 46
#include <stdio.h>
#include <conio.h>

long FIBONACI[CONST];
long FIBFUNCTION(int NUMBER);

int main()
{
	int CIRCLE;
	window(1,1,80,25);
	clrscr();
	for (CIRCLE=0;CIRCLE<CONST;CIRCLE++)
		FIBONACI[CIRCLE]=FIBFUNCTION(CIRCLE);
	printf("\nTHE NUMBER FIBFUNCTION(45) IS : %ld\n",FIBFUNCTION(CONST-1));
	for (CIRCLE=0;CIRCLE<46;CIRCLE++)
		printf("%ld ",FIBONACI[CIRCLE]);
	//The above limit is "45" && The long integer must less than ten bits.
	//The Fibonacci Order List begins at "FIBFUNCTION(0)=1".
	getch();
	return 0;
}

long FIBFUNCTION(int NUMBER)
{
	long FIB1=1,FIB2=1,FIB3;
	int CIRCLE;
	if (NUMBER<=1)	return 1;
	for (FIB3=FIB1+FIB2,CIRCLE=2;CIRCLE<NUMBER;CIRCLE++)
	{
		FIB1=FIB2;
		FIB2=FIB3;
		FIB3=FIB1+FIB2;
	}
	return FIB3;
}