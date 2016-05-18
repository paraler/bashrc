#include <stdio.h>
#include <conio.h>
#include <string.h>

class RELATIONSHIP
{
	private :
			RELATIONSHIP *BABY;
			char * NAME;
	public :
			RELATIONSHIP(char *Name);
			void CreateBaby(char * BABY_NAME);
			void Display_People();
			void Display_Baby();
			void Display_Baby_Baby();
};

RELATIONSHIP::RELATIONSHIP(char *Name)
{
	NAME=new char[strlen(Name)+1];
	strcpy(NAME,Name);
	BABY=0;
}
void RELATIONSHIP::CreateBaby(char *BabyName)
{
	BABY=new RELATIONSHIP(BabyName);
}
void RELATIONSHIP::Display_People()
{
	printf("The first people:%s",this->NAME);
}
void RELATIONSHIP::Display_Baby()
{
	printf("Her baby :%s",this->BABY->NAME);
}
void RELATIONSHIP::Display_Baby_Baby()
{
	printf("Her baby's baby:%s",this->BABY->BABY->NAME);
}
int main(void)
{
	RELATIONSHIP People("L1");
	People.CreateBaby("L2");
	clrscr();
	People.Display_People();
	People.Display_Baby();
	People.Display_Baby_Baby();
	getch();
	return 0;
}