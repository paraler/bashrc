#include<graphics.h>
#include<conio.h>
#include<stdio.h>

void main(void)
{
	int driver=DETECT,mode;
	int NUM1,NUM2,C1,C2;
	int X=10,Y=10,COLOR;
	int COLOR_NUM[]={0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63};
	char MASSAGE[100];

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	for (COLOR=1; COLOR<=16; COLOR++)
	{
		setcolor(COLOR);
		sprintf(MASSAGE,"Color:%d",COLOR);
		outtextxy(X,Y,MASSAGE);
		X+=70;
		if(X>600)
		{
				Y+=20;
				X=10;
		}
	}
	printf("\n\n\n\n\n\n");
	printf("Which color do you want to change? Input it:");
	scanf("%d",&C1);
	printf("Which color do you want to change it into?Input it:");
	scanf("%d",&C2);
	setpalette(C1,COLOR_NUM[C2]);
	outtextxy(100,250,"The RESULT is :");
	setcolor(C1);
	sprintf(MASSAGE,"Color:%d",C1);
	outtextxy(250,250,MASSAGE);
	getch();
	outtextxy(100,400,"Press Any Key to EXIT... ...");
	getch();
	closegraph();
}
