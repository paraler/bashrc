#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy, i;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "D:\\Tools\\Tc3.0\\Bgi");

   /* read result of initialization */
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
	 printf("Graphics error: %s\n", grapherrormsg(errorcode));
	 printf("Press any key to halt:");
	 getch();
	 exit(1);             /* return with error code */
   }

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;
   for (i=EMPTY_FILL; i<USER_FILL; i++)
   {
	 /* set the fill style */
	 setfillstyle(i, getmaxcolor());
	 /* draw the 3-d bar */
	 bar3d(midx-50, midy-50, midx+50,midy+50, 10, 1);
	 getch();
   }
   getch();
   closegraph();
}