#include <stdio.h>
#include <conio.h>
#include <math.h>

int *Data_list;
int NUM=5;
int main(void)
{
	void InitDatalist(int *Data);
	void SORT(int *Data,int LOW,int HIGH);
	void DISPLAY(int *Data);
	Data_list=new int [5];
	clrscr();
	InitDatalist(Data_list);
	DISPLAY(Data_list);
	SORT(Data_list,0,NUM-1);
	printf("\n\n***** THIS IS A SORT PROGRAM *****\n");
	DISPLAY(Data_list);
	getch();
	return 0;
}
void InitDatalist(int *Data)
{
	for (int i=0;i<NUM;i++)
	{
		*(Data+i)=((NUM-i)*1000);
	}
}
void Qkpass(int *Data,int LOW,int HIGH,int &i)
{
	int x,j;
	i=LOW;
	j=HIGH;
	x=Data[LOW];
	while(i<j)
	{
		while((i<j)&&(Data[j]>=x))  j=j-1;
		Data[i]=Data[j];
		while((i<j)&&(Data[j])<=x)  i=i+1;
		Data[j]=Data[i];
	}
	Data[i]=x;
}
void SORT(int *Data,int LOW,int HIGH)
{
	int MIDDLE;
	if (LOW<HIGH)
	{
		Qkpass(Data,LOW,HIGH,MIDDLE);
		SORT(Data,LOW,MIDDLE-1);
		SORT(Data,MIDDLE+1,HIGH);
	}
}

void DISPLAY(int *Data)
{
	int CIRCLE=0;
	for (CIRCLE=0;CIRCLE<NUM;CIRCLE++)
		printf("\n%d",*(Data+CIRCLE));
}
