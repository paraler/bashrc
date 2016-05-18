//THE PROGRAM IS TO SETUP A NEW FILE SYSTEM FOR STANDARD FILES OPERATING .
//FILE FILE.CPP

#define    XCONST 22
#define    YCONST 11
#define    CONST 100
#include      <io.h>
#include     <dos.h>
#include   <conio.h>
#include   <stdio.h>
#include  <string.h>
#include <process.h>

void EXIT(void);
void ERROR(void);
void SEARCH(void);
void DELETE(void);
void RENAME(void);
void CHECK_RW(char *FILENAME);
void CHECK_R(char *FILENAME);
void CHECK_W(char *FILENAME);
void CHECK_EXE(char *FILENAME);
void GETPRIVILEGE(void);

void main(void)
{
	char CHOICE;
	while (1)
	{
		clrscr();
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
			  "         THE DEMO DISPLAY FOR THE FILE SYSTEM         \n"
			  "                                                      \n"
			  "            1 : DETECT A FILE EXIST OR NOT            \n"
			  "            2 : GET THE OPRATING PRIVILEGE OF THE FILE\n"
			  "            3 : RENAME A FILE                         \n"
			  "            4 : REMOVE A FILE                         \n"
			  "            5 : QUIT AT ONCE                          \n"
			  "\n");
		do
		{
			printf("\n		PLEASE ENTER YOUR CHOICE :");
			CHOICE=getch();
			putch(CHOICE);
		}while((CHOICE<'1')||(CHOICE>'5'));
		printf("\n\n");
		switch (CHOICE)
		{
			case '1' :	SEARCH();
						break;
			case '2' :     GETPRIVILEGE();
						break;
			case '3' :	RENAME();
						break;
			case '4' :	DELETE();
						break;
			case '5' :	EXIT();
						break;
			default  :	ERROR();
						break;
		}
	}
}

void EXIT(void)
{
	exit(1);
}

void RENAME(void)
{
	char SOURCE[CONST];
	char TARGET[CONST];
	int STATE;
	printf("ENTER THE ORIGINAIL FILE NAME : ");
	gets(SOURCE);
	printf("ENTER THE NEW FILE NAME : ");
	gets(TARGET);
	STATE=rename(SOURCE,TARGET);
	if (STATE!=0)
	{
		printf("ERROR : CAN NOT RENAME %s TO %s !\n",SOURCE,TARGET);
	}
	else
		printf("%s HAS BEEN RENAMED TO BE %s . \n",SOURCE,TARGET);
	getch();
}

void DELETE(void)
{
	char FILENAME[CONST];
	int STATE;
	printf("ENTER THE FILE TO REMOVE PLEASE : ");
	gets(FILENAME);
	STATE=remove(FILENAME);
	if (STATE==-1)
	{
		printf("ERROR : CAN NOT REMOVE YOUR INPUT FILE %s !\n",FILENAME);
	}
	else
		printf("%s HAS BEEN REMOVED SUCCESSFULLY !\n",FILENAME);
	getch();
}

void GETPRIVILEGE(void)
{
	char CHOICE;
	char FILENAME[CONST];
	do
	{
		clrscr();
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
			  "         	    OPRATING PRIVILEGE\n"
			  "\n"
			  "            1 : READ AND WRITE\n"
			  "            2 : READ\n"
			  "            3 : WRITE\n"
			  "            4 : EXECUTE\n"
			  "            5 : EXIT\n"
			  "\n" );
		do
		{
			printf("\n		PLEASE ENTER YOUR CHOICE :");
			CHOICE=getch();
			putch(CHOICE);
		}while((CHOICE<'1')||(CHOICE>'5'));
		if(CHOICE!='5')
		{
			printf("\nPLEASE INPUT A FILE NAME : ");
			gets(FILENAME);
			if (access(FILENAME,0)==-1)
			{
				printf("%s DOES NOT EXIST IN THE HARDDISK !\n",FILENAME);
			}
		}
		if((CHOICE=='5')||(access(FILENAME,0)==0))
		{
			printf("\n\n");
			switch (CHOICE)
			{
			case '1' :	CHECK_RW(FILENAME);
						break;
			case '2' :     CHECK_R(FILENAME);
						break;
			case '3' :	CHECK_W(FILENAME);
						break;
			case '4' :	CHECK_EXE(FILENAME);
						break;
			case '5' :	printf("\nPress any key to"
							"return to main menu... ...");
						break;
			default  :	ERROR();
						break;
			}
		}/*else*/
	}while(CHOICE!='5');
}
void CHECK_RW(char *FILENAME)
{
	if (access(FILENAME,6)==0)
	{
		printf("%s : READ AND WRITE",FILENAME);
	}
	else
	{
		printf("%s DOES NOT HAVE THE PRIVILEGE"
			"FOR WRITING AND READING!",FILENAME);
	}
	getch();
}
void CHECK_R(char *FILENAME)
{
	if (access(FILENAME,4)==0)
	{
		printf("%s : READ",FILENAME);
	}
	else
	{
		printf("%s DOES NOT HAVE THE PRIVILEGE FOR READING!",FILENAME);
	}
	getch();
}
void CHECK_W(char *FILENAME)
{
	if (access(FILENAME,2)==0)
	{
		printf("%s : READ",FILENAME);
	}
	else
	{
		printf("%s DOES NOT HAVE THE PRIVILEGE FOR WRITING!",FILENAME);
	}
	getch();
}
void CHECK_EXE(char *FILENAME)
{
	if (access(FILENAME,1)==0)
	{
		printf("%s : READ",FILENAME);
	}
	else
	{
		printf("%s DOES NOT HAVE THE PRIVILEGE FOR EXECUTING!",FILENAME);
	}
	getch();
}
void SEARCH(void)
{
	char FILENAME[CONST];
	printf("\n PLEASE INPUT A FILE NAME : ");
	gets(FILENAME);
	if (access(FILENAME,0)==-1)
	{
		printf("%s DOES NOT EXIST IN THE HARDDISK !\n",FILENAME);
	}
	else
		printf("%s EXISTS .\n",FILENAME);
	getch();
}

void ERROR(void)
{
	nosound();
	sound(CONST*10);
	delay(CONST*2);
	sound(CONST*20);
	delay(CONST*5);
	nosound();
}