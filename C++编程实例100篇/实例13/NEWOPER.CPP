#include <iostream.h>
#include <math.h>
int main(void)

{   int gotoxy();
    int puttext();	
	char *BUFFER;
	int COLUMN,ROW;
    gotoxy(10,10);
	cout<<"THIS IS JUST AN EXAMPLE!\n";
	gotoxy(10,11);
	cout<<"WIDTH=24\n";
	gotoxy(10,12);
	cout<<"HIGHT=3\n";
	COLUMN=25;
	ROW=3;
	BUFFER=new char[COLUMN*ROW*2];
	gettext(10,10,10+COLUMN,10+ROW,BUFFER);
	puttext(50,20,50+COLUMN,20+ROW,BUFFER);
	delete BUFFER;
	return 0;
}
