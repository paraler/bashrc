#include<stdio.h>
#include<dos.h>
#include<conio.h>

int main(void)
{
   int HOUR=0,MINUTE=0,SECOND=0;
   struct  time T;

   clrscr();
   textcolor(12);
   gettime(&T);
   gotoxy(10,5);
   cprintf("The current time is: %2d:%02d:%02d\n",
		T.ti_hour, T.ti_min, T.ti_sec);
   textcolor(11);
   gotoxy(10,7);
   cprintf("Input the alarm time please!");
   textcolor(YELLOW);
   gotoxy(10,9);
   cprintf("The hour(0-23):");
   scanf("%d",&HOUR);
   gotoxy(10,11);
   cprintf("The minute(0-59):");
   scanf("%d",&MINUTE);
   gotoxy(10,13);
   cprintf("The second(0-59):");
   scanf("%d",&SECOND);

   while((HOUR*3600+MINUTE*60+SECOND-(T.ti_hour*3600+T.ti_min*60+T.ti_sec))>0)
   {
	gettime(&T);
   }
   while(!kbhit())
	sound(440);
   nosound();
   getch();
   gotoxy(10,15);
   textcolor(WHITE);
   cprintf("Press any key to exit... ...");
   getch();
   return 0;
}