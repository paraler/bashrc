#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{

   int driver=DETECT,mode;
   int MID_X,MID_Y,NUM;
   char STRING[30];
   int USER_STYLE[3]={0x2020,0xE0E0,0x0001};
   char *STYLE_NAME[] = {"SOLID_LINE","DOTTED_LINE",
					"CENTER_LINE","DASHED_LINE",
					"USERBIT_LINE:0x2020",
					"USERBIT_LINE:0xE0E0",
					"USERBIT_LINE:0x0001"};
   registerbgidriver(EGAVGA_driver);
   initgraph(&driver, &mode, "");
   MID_X=getmaxx()/2;
   MID_Y=getmaxy()/2;

   setcolor(YELLOW);
   /*system style*/
   for (NUM=0; NUM<3; NUM++)
   {
	 setlinestyle(NUM,0, 0);
	 strcpy(STRING,STYLE_NAME[NUM]);
	 line(MID_X-100,MID_Y, MID_X+100, MID_Y);
	 outtextxy(MID_X, MID_Y+50, STRING);
	 getch();
	 cleardevice();
   }
   /*user style*/
   for(NUM=0;NUM<3;NUM++)
   {
	setlinestyle(USERBIT_LINE,USER_STYLE[NUM],1);
	 strcpy(STRING,STYLE_NAME[NUM+4]);
	 line(MID_X-100,MID_Y, MID_X+100, MID_Y);
	 outtextxy(MID_X, MID_Y+50, STRING);
	 getch();
	 cleardevice();
   }
   closegraph();
   return 0;
}