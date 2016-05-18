#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>

int main(void)
{
   int LENGTH,I;
   char CHOICE;
   char *STRING = "This is a string";
   printf("\nInput the string:");
   gets(STRING);
   LENGTH = strlen(STRING);
   printf("\nWhat do you want to do with the string?");
   printf("\n1: Capital Letters(A B C ... ...)");
   printf("\n2:Lowercase Letters(a b c ... ...)");
   do
   {
	printf("\nEnter you CHOICE:");
	scanf("%c",&CHOICE);
   }
   while((CHOICE!='1')&&(CHOICE!='2'));
   switch (CHOICE){
	case '1':for (I=0; I<LENGTH; I++)
			{
			STRING[I] = toupper(STRING[I]);
			};
			break;
	case '2':for(I=0; I<LENGTH; I++)
			{
			STRING[I] = tolower(STRING[I]);
			};
			break;
   }
   printf("\nThe string has been changed into : %s",STRING);
   printf("\n\nPress Any Key to EXIT... ...");
   getch();
   return 0;
}