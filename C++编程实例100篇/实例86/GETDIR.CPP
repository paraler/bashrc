#include<stdio.h>
#include<direct.h>
#include<dir.h>
#include<process.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	char PATHNAME[100];
	if(getcwd(PATHNAME,100)==NULL)
	{
		printf("0:get current directory error!\n");
		exit(1);
	}
	printf("The current directory is %s\n",PATHNAME);
	getch();
}