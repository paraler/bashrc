#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void SET_PATTERN(int COLOR);
char PATTERN[8]={0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55};

int main(void)
{
	int NUM,X=20,Y=100;
	int driver=DETECT,mode;

	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");

	for(NUM=1;NUM<16;NUM++)
	{
		SET_PATTERN(NUM);
		bar(X,Y,X+100,Y+50);
		X+=120;
		if(X>520)
		{
			X=20;
			Y+=60;
		}
	}
	getch();
	closegraph();
	return(0);
}
void SET_PATTERN(int COLOR)
{
	setfillpattern(PATTERN,COLOR);
}