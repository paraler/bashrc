//THE PROGRAM IS TO DISPLAY YOUR HARDDISK'S MESSAGE
//FILE HARDDISK.CPP

#include     <dos.h>
#include   <stdio.h>
#include   <conio.h>
#include   <ctype.h>
#include  <string.h>
#include <process.h>

int main(void)
{
	struct dfree DISKMESSAGE;
	long DISK_SECTOR,DISK_CLUSTER,DISK_TOTAL,DISK_AVAIL;
	int DISKNUM;
	char DISK;

	clrscr();
	printf("\n		********** WELCOME TO USE THIS SYSTEM **********\n");
	printf("\n		  ----- IT HELPS YOU KONW YOUR HARDDISK -----\n\n");
	do
	{
		printf("\nINPUT YOUR DRIVER(A B C D E F... ...):");
		scanf("%c",&DISK);
	}while((DISK<'A')||((DISK>'Z')&&(DISK<'a'))||DISK>'z');
	if((DISK>'A')&&(DISK<'Z'))
		DISKNUM=DISK-'A'+1;
	if((DISK>'a')&&(DISK<'z'))
		DISKNUM=DISK-'a'+1;
	getdfree(DISKNUM,&DISKMESSAGE);

	if (DISKMESSAGE.df_sclus==(unsigned)-1)
	{
		printf("***** ERROR : CAN NOT GET INFORMATION FROM YOUR DISK %c:\n"
				,DISK);
		exit(1);
	}
	DISK_SECTOR=DISKMESSAGE.df_bsec;
	DISK_CLUSTER=DISKMESSAGE.df_sclus*DISK_SECTOR;
	DISK_AVAIL=DISKMESSAGE.df_avail*DISK_CLUSTER;
	DISK_TOTAL=DISKMESSAGE.df_total*DISK_CLUSTER;

	if (DISKNUM!=0)
		printf("***** HARDDISK INFORMATION %c :\n",'A'+DISKNUM-1);
	else
		printf("***** HARDDISK INFORMATION (DEFAULT) : AS FOLLOWING\n");
	printf("\n----- TOTAL HARDDIRSK SPACE = %ld BYTES\n",DISK_TOTAL);
	printf("\n***** AVAILABEL SPACE       = %ld BYTES\n",DISK_AVAIL);
	printf("\n----- BYTES (EVERY SECTOR)  = %ld BYTES\n",DISK_SECTOR);
	printf("\n***** BYTES (EVERY CLUSTER) = %ld BYTES\n",DISK_CLUSTER);
	printf("\n\n\n		  ***********    Thank you! ***********\n");
	printf("\n		-----------  <2001.01.01> -----------\n");
	getch();
	return 0;
}