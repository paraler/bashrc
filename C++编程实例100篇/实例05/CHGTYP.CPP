#include <stdio.h>
#include <conio.h>


int main(void)
{
	int NUM_INT=65;
	float NUM_FLOAT=11.11;
	char CH_CHAR='A';
    printf("\n 65 (int) ---> %c (char) ",(char)NUM_INT);
	printf("\n 11.11 (float) ---> %d (int)",(int)NUM_FLOAT);
	printf("\n A (char) ---> %d (int)",(int)CH_CHAR);
	getch();
	return 0;
}