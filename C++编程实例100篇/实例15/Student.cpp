//File STUST.CPP

#include "STUDENT.h"

int main(void)
{

	STUDENT Student;
	char string[80];
	printf("\n PLEASE ENTER YOUR NAME : ");
	gets(string);
	Student.AddName(string);
	printf("\n PLEASE ENTER YOUR AGE : ");
	gets(string);
	Student.AddAge(string);
	printf("\n PLEASE ENTER YOUR IDENTIFER NUMBER :");
	gets(string);
	Student.AddId(string);
	printf("\n PLEASE ENTER YOUR TELEPHONE NUMBER :");
	gets(string);
	Student.AddTel(string);
	printf("\n PLEASE ENTER YOUR ADDRESS :");
	gets(string);
	Student.AddAddress(string);
	printf("\n PRESS ANY KEY TO SEE THE RESULT... ...");
	getch();
	Student.Print();
	getch();
	return 0;
}