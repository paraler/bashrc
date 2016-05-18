#include<stdio.h>
#include<direct.h>
#include<dir.h>
#include<process.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	char PATHNAME[100];
	char NEWPATHNAME[100];
	clrscr();
	if(getcwd(PATHNAME,100)==NULL)
	{
		printf("0:get current directory error!\n");
		exit(1);
	}
	printf("The current directory is %s\n",PATHNAME);
	printf("\nInput the new pathname please:");
	gets(NEWPATHNAME);
	if(chdir(NEWPATHNAME)!=0)
		printf("change current directory error!\n");
	printf("\nChanging directory SUCCEED!");
	printf("\nThe new current directory is %s\n",NEWPATHNAME);
	printf("\nPress Any Key To EXIT!");
	getch();
}