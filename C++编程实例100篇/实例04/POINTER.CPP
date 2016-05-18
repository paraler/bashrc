#include <conio.h>
#include <stdio.h>

void TEST1(void);
void TEST2(void);
void TEST3(void);

int main(void)
{

	TEST1();
	TEST2();
	TEST3();
	return 0;
}
void TEST1(void)
{
	int X;
	int *Y;
	printf("\nINPUT A NUMBER:");
	scanf("%d",&X);
	printf("\nINPUT A NUMBER:");
	scanf("%d",Y);
	printf("\nX= %d",X);
	printf("\nY= %d",*Y);
	getch();
}
void TEST2(void)
{
	void FUNCTION1(int *X,int *Y);
	int XX,YY;
	XX=1;
	YY=2;
	printf("\n\n");
	printf("\nX=%d  Y=%d",XX,YY);
	FUNCTION1(&XX,&YY);
	printf("\nX=%d  Y=%d",XX,YY);
	getch();
}
void FUNCTION1(int *X,int *Y)
{
	*X=*Y=0;
}
void TEST3(void)
{
	int XX,YY;
	XX=3;
	YY=4;
	printf("\n\n");
	printf("\nX=%d  Y=%d",XX,YY);
	int &RX=XX,&RY=YY;
	RX=RY=0;
	printf("\nX=%d  Y=%d",XX,YY);
	getch();
}
