#include <conio.h>
#include <stdio.h>
int GLOBAL;
void TEST();
int main(void)
{
	TEST();
	printf("\nGLOBAL=%d",GLOBAL);
	//printf("\nLOCAL=%d",LOCAL);
	getch();
	return 0;
}
void TEST()
{
	int LOCAL;
	LOCAL=10;
	printf("\nLOCAL=%d",LOCAL);
	GLOBAL=20;
}