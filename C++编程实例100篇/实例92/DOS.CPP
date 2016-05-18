//THE PROGRAM IS TO DISPLAY THE DOS VERSION FOR YOU.
//FILE DOS.CPP

#define DOS_INTEGER 0x21
#include        <dos.h>
#include      <stdio.h>
#include      <conio.h>

int main(void)
{
	union REGS REGISTER;
	REGISTER.h.ah=0x30;
	int86(DOS_INTEGER,&REGISTER,&REGISTER);
	clrscr();
	int AL=REGISTER.h.al;
	int AH=REGISTER.h.ah;
	printf("-*-*-*-*-*- DOS VERSION IN YOUR COMPUTER IS  %d.%d"
			,AL,AH);
	getch();
	return 0;
}