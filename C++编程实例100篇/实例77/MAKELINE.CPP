#include<graphics.h>
#include<conio.h>
#include<stdio.h>

int READ_NUM(void);
int READ_HIGHT(int ID);

void main()
{
	int NUM,I,VALUE[50];
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	NUM=READ_NUM();
	for(I=1;I<=NUM;I++)
		VALUE[I]=READ_HIGHT(I);
	setcolor(WHITE);
	line(0,400,639,400);
	setcolor(YELLOW);
	moveto(2,400);
	for(I=1;I<=NUM;I++)
	{
		setcolor(YELLOW);
		lineto(I*10,400-VALUE[I]);
		setfillstyle(1,RED);
		bar(I*10-1,400-VALUE[I]+1,I*10,400-VALUE[I]);
	}
	getch();
	closegraph();
}
int READ_NUM(void)
{
	int NUM;
	do
	{
		printf("Input the NUM(1-50):");
		scanf("%d",&NUM);
	}while((NUM>50)|(NUM<0));
	return(NUM);
}
int	READ_HIGHT(int ID)
{
	int NUM;
	do
	{
		printf("Input the VALUE[%d](1-400):",ID);
		scanf("%d",&NUM);
	}while((NUM<1)|(NUM>400));
	return(NUM);
}