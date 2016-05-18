#include <conio.h>
#include <iostream.h>

typedef enum {MALE,FEMALE} SEX_TYPE;

class RECORD
{
	public:
		SEX_TYPE SEX;
		char *NAME;
};

ostream &operator<<(ostream &STREAM,RECORD PERSON)
{
	if (PERSON.SEX == MALE) (STREAM<<"MALE");
	else (STREAM<<"FEMALE");
	return STREAM;
}

RECORD PEOPLE[10];

int main(void)
{
	PEOPLE[0].NAME="Mary";
	PEOPLE[0].SEX=FEMALE;
	PEOPLE[1].NAME="JOE";
	PEOPLE[1].SEX=MALE;
	clrscr();
	cout<<"\n"<<PEOPLE[0].NAME<<"--->"<<PEOPLE[0];
	cout<<"\n"<<PEOPLE[1].NAME<<"--->"<<PEOPLE[1];
	getch();
	return 0;
}