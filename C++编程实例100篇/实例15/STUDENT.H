//File STUDENT.H

#include  <stdio.h>
#include  <conio.h>
#include <string.h>

class STUDENT
{
	private :
			char *NAME;
			char *AGE;
			char *ID;
			char *TEL_NUM;
			char *ADDRESS;
	public :
			STUDENT()                      //Automatic Initial
			{
				NAME=NULL;
				AGE=NULL;
				ID=NULL;
				TEL_NUM=NULL;
				ADDRESS=NULL;
				printf("\nYou are in the constructor(gouzao function)!");
				printf("\nInitial the data to null\n");
				printf("\nPress any key to continue... ...");
				getch();
			}
			void AddName(char *ST)
			{
				NAME=new char[strlen(ST)+1];
				strcpy(NAME,ST);
			}
			void AddAge(char *ST)
			{
				AGE=new char[strlen(ST)+1];
				strcpy(AGE,ST);
			}
			void AddId(char *ST)
			{
				ID=new char[strlen(ST)+1];
				strcpy(ID,ST);
			}
			void AddTel(char *ST)
			{
				TEL_NUM=new char[strlen(ST)+1];
				strcpy(TEL_NUM,ST);
			}
			void AddAddress(char *ST)
			{
				ADDRESS=new char[strlen(ST)+1];
				strcpy(ADDRESS,ST);
			}
			void Print()
			{
				printf("\n%s   %s    %s",NAME,AGE,ID);
				printf("\n%s",TEL_NUM);
				printf("\n%s",ADDRESS);
			}
};