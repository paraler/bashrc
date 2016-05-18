#include <stdio.h>
#include <conio.h>
#define NUMONE 'A'
#define NUMTWO 10000
#define NUMTHREE 10.0

unsigned int AREA(unsigned char NUMBER);
unsigned long AREA(unsigned int NUMBER);
double AREA(double NUMBER);

int main(void)
{
	unsigned char NUMCHAR;
	unsigned int AREACHAR;
	unsigned int NUMINT;
	unsigned long AREALONG;
	double NUMDOUBLE,AREADOUBLE;

	NUMCHAR=NUMONE;
	NUMINT=NUMTWO;
	NUMDOUBLE=NUMTHREE;

	AREACHAR=AREA(NUMCHAR);
	AREALONG=AREA(NUMINT);
	AREADOUBLE=AREA(NUMDOUBLE);

    printf("%d * %d = %d\n",NUMCHAR,NUMCHAR,AREACHAR);
	printf("%d * %d = %ld\n",NUMINT,NUMINT,AREALONG);
	printf("%lf * %lf = %lf",NUMDOUBLE,NUMDOUBLE,AREADOUBLE);
	getch();
	return 0;
}

unsigned int AREA(unsigned char NUMBER)
{
	unsigned int RESULT;
	RESULT=NUMBER*NUMBER;
	return(RESULT);
}

unsigned long AREA(unsigned int NUMBER)
{
	unsigned long RESULT;
	RESULT=(unsigned long)NUMBER*NUMBER;
	return(RESULT);
}

double AREA(double NUMBER)
{
	double RESULT;
	RESULT=NUMBER*NUMBER;
	return(RESULT);
}