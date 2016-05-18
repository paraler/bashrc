#include <stdio.h>
#include <math.h>

void EXCHANGE(int &NUM1,int &NUM2);

int main(void)
{
	int NUMBER1,NUMBER2;
    printf("Please input two integers : ");
	scanf("%d %d",&NUMBER1,&NUMBER2);
	printf("Before the exchange :\n");
	printf("NUMBER1 = %d NUMBER2 = %d\n",NUMBER1,NUMBER2);
	EXCHANGE(NUMBER1,NUMBER2);
	printf("After the exchange :\n");
	printf("NUMBER1 = %d NUMBER2 = %d\n",NUMBER1,NUMBER2);
    return 0;
}

void EXCHANGE(int &NUM1,int &NUM2)
{
	int BUFFER;
	BUFFER=NUM1;
	NUM1=NUM2;
	NUM2=BUFFER;
}