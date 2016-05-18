#include<conIO.h>
#include<stdio.h>
#define LEFT	5
#define TOP	2
#define RIGHT 78
#define BOTTOM 25

void DRAW_WIN(int LEFT_X,int LEFT_Y,int RIGHT_X,int RIGHT_Y);
void main()
{
	int NUM;
	void DRAW_WIN(int LEFT_X,int LEFT_Y,int RIGHT_X,int RIGHT_Y);
	clrscr();
	DRAW_WIN(LEFT-1,TOP-1,RIGHT-1,BOTTOM-1);
	window(LEFT,TOP,RIGHT,BOTTOM);
	gotoxy(16,10);
	textcolor(BLINK+11);
	cprintf("**** WELCOME TO THIS SYSTEM ****");
	gotoxy(12,15);
	textcolor(BLUE);
	textbackground(LIGHTGRAY);
	cprintf("-----Thank you for using this system!-----");
	getch();
}

void DRAW_WIN(int LEFT_X,int LEFT_Y,int RIGHT_X,int RIGHT_Y)
{
	int NUM;

	gotoxy(LEFT,TOP);              /*DRAW THE LEFT-TOP CORNER*/
	printf("\xda");
	for(NUM=LEFT+1;NUM<RIGHT;NUM++)      /*DRAW THE TOP LINE*/
		printf("\xc4");
	printf("\xbf");                /*DRAW THE RIGHT-TOP CORNER*/
	gotoxy(RIGHT,TOP+1);
	for(NUM=TOP+1;NUM<BOTTOM;NUM++)      /*DRAW THE RIGHT LINE*/
	{
		printf("\xd8");
		gotoxy(RIGHT,NUM+1);
	}
	gotoxy(RIGHT,BOTTOM);
	printf("\xd9");                /*DRAW THE RIGHT-BOTTOM CORNER*/
	gotoxy(LEFT+1,BOTTOM);
	for(NUM=LEFT+1;NUM<RIGHT;NUM++)      /*DRAW THE BOTTOM LINE*/
		printf("\xc4");
	gotoxy(LEFT,BOTTOM);
	printf("\xc0");                /*DRAW THE LEFT-BOTTOM CORNER*/
	gotoxy(LEFT,TOP+1);
	for(NUM=TOP+1;NUM<BOTTOM;NUM++)      /*DRAW THE LEFT LINE*/
	{
		printf("\xd8");
		gotoxy(LEFT,NUM+1);
	}
}