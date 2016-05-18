//THE PROGRAM IS TO CHANGE THE MODE OF DISPLAY FOR YOU .
//FILE CHGDIS.CPP

#include    <dos.h>
#include  <stdio.h>
#include  <conio.h>

int main()
{
	union REGS REGISTER;
	int MODE;
	do{
		printf("***** PLEASE ENTER THE VIDEO MODE(1-7 13-19) : ");
		scanf("%d",&MODE);
	}while(((MODE<=0xC)&&(MODE>=8))||(MODE<1)||(MODE>20));
	getch();
	REGISTER.h.ah=0;
	REGISTER.h.al=MODE;
	int86(0x10,&REGISTER,&REGISTER);
	printf("Hello!");
	getch();
	return 0;
}