//THE PROGRAM IS TO TELL YOU HOW TO USE
//THE MATH.H LIBRARY .
//FILE MATH.CPP

#define HUNDRED 100
#include  <stdio.h>
#include  <conio.h>
#include   <math.h>

int main(void)
{
	double CIRCLE,PI,VALUE;
    printf("\n	   -*-*- THE MATH FUNCTIOIN 'SIN()' & 'COS()'& 'TAN()'-*-*-\n");
	printf("\nTHE DEGREE");
	printf("   THE SIN() VALUE");
	printf("	 THE COS() VALUE ");
	printf("	 THE TAN() VALUE \n");
	PI=3.1415926;
	for (CIRCLE=0;CIRCLE<HUNDRED;CIRCLE+=10)
	{
		VALUE=CIRCLE*PI/180;
		printf("%2d",(int)CIRCLE);
		printf("	     %6.4f",sin(VALUE));
		printf("	 	 %6.4f",cos(VALUE));
		printf("	                 %6.4f",tan(VALUE));
		printf("\n");
	}
	getch();
	return 0;
}