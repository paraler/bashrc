#include <stdio.h>
#include <conio.h>
#include <string.h>

char *COPY(char *TARGET,char *SOURCE);
char *REVERSE(char *STRING);
int   GETLEN(char *STRING);

int main(void)
{
	char STRING1[]="TO TEST THE FUNCTIONS OF STRING";
	char STRING2[32];
	char STRING3[]="I LOVE THE COMPUTER";

	

	printf("\nSTRING1[]=%s",STRING1);
	printf("\nTHE LENGTH OF STRING1=%d",GETLEN(STRING1));
	COPY(STRING2,STRING1);
	printf("\n\nAFTER COPYING STRING2[]=%s\n",STRING2);
	printf("\nBEFORE REVERSE STRING3[]=%s\n",STRING3);
	REVERSE(STRING3);
	printf("\nAFTER REVERSING STRING3[]=%s\n",STRING3);
	getch();
	return 0;
}

char *COPY(char *TARGET,char *SOURCE)
{
	char *STR1,*STR2;
	STR1=SOURCE;
	STR2=TARGET;
	while (*STR1!='\0')
	{
		*STR2=*STR1;
		STR1++;
		STR2++;
	}
	*STR2='\0';
	return TARGET;
}

char *REVERSE(char *STRING)
{
	char *STR1,*STR2;
	char YUAN[32];
	COPY(YUAN,STRING);
	STR1=YUAN+strlen(YUAN)-1;
	STR2=STRING;
	while (*STR2!='\0')
	{
		*STR2=*STR1;
		STR1--;
		STR2++;
	}
	return STRING;
}
int GETLEN(char *STRING)
{
	int NUM=0;
	while(*STRING!='\0')
	{
		NUM++;
		STRING++;
	}
	return NUM;
}