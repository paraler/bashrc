//THE CLASSES AND SUBCLASSES OF A COLLEGE
//FILE COLLEGE.H

#include <iostream.h>
#include   <string.h>
#include    <conio.h>

const char EMPTY='\0';

class RECORD
{
	private :
			char *NAME;
			char *SEX;
			char *IDENTIFIER;
			char *BIRTHDAY;
			char *ADDRESS;
			int 	AGE;
	public :
			RECORD()
			{
				NAME=EMPTY;
				SEX="MALE";
				IDENTIFIER=EMPTY;
				BIRTHDAY=EMPTY;
				ADDRESS=EMPTY;
				AGE=0;
			}
			void INSERT_NAME(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				NAME=BUFFER;
			}
			void INSERT_SEX(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				SEX=BUFFER;
			}
			void INSERT_IDENTIFIER(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				IDENTIFIER=BUFFER;
			}
			void INSERT_BIRTHDAY(char *S)
			{

				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				BIRTHDAY=BUFFER;
			}
			void INSERT_ADDRESS(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				ADDRESS=BUFFER;
			}
			void INSERT_AGE(int A)
			{
				AGE=A;
			}
			void PRINT()
			{
				cout<<"\n"<<NAME<<"\n"
				<<SEX<<"   "<<IDENTIFIER<<"   "<<BIRTHDAY<<"   "<<AGE<<"\n"<<ADDRESS;
			}
};

class STUDENT : public RECORD
//This class is derived from RECORD and inherits all the public members of
//the parent class
{
	private :
			char *STUDENT_ID;
			char *DORMITORY_NUM;
			char *MAJOR;
			int LEVEL;
	public :
			STUDENT()
			{
				RECORD:RECORD(); //Use the same constructor as
							  //the parent class.
				DORMITORY_NUM=EMPTY;
				MAJOR=EMPTY;
				LEVEL=0;
			}
			void INSERT_STUDENT_ID(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				STUDENT_ID=BUFFER;
			}
			void INSERT_DORMITORY_NUM(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				DORMITORY_NUM=BUFFER;
			}
			void INSERT_MAJOR(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				MAJOR=BUFFER;
			}
			void INSERT_LEVEL(int A)
			{
				LEVEL=A;
			}
			void PRINT()
			{
				RECORD::PRINT();
				cout<<"\nSTUDENT_ID - - >"<<STUDENT_ID;
				cout<<"\nDORMITORY_NUM"<<DORMITORY_NUM;
				cout<<"\nMAJOR - - >"<<MAJOR;
				cout<<"\nLEVEL - - >"<<LEVEL;
			}
};

class STAFF : public RECORD
//This class is derived from RECORD and inherits all the public members
//of the parent class.
{
	private :
			char *DEPARTMENT;
			int   WORKTIME;
			float SALARY;

	public :

			STAFF()
			{
				RECORD:RECORD(); //Use the same constructor as
							  //the parent class.
				DEPARTMENT=EMPTY;
				WORKTIME=0;
				SALARY=300;
			}
			void INSERT_DEPARTMENT(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				DEPARTMENT=BUFFER;
			}
			void INSERT_SALARY(float A)
			{
				SALARY=A;
			}
			void INSERT_WORKTIME(int A)
			{
				WORKTIME=A;
			}
			void PRINT()
			{
				RECORD::PRINT();
				cout<<"\nDEPARTMENT - - >"<<DEPARTMENT
				<<"\nWORK TIME (PER DAY) - - >"<<WORKTIME
				<<"\nSALARY - - > $"<<SALARY;
			}
};

class PROFESSOR : public STAFF
//This class is derived from the derived class STAFF.
{
	private:
			char *TEACH_MAJOR;
			char *SEARCH_NAME;
			int   GRADUATE_STUDENT_NUM;

	public :
			PROFESSOR()
			{
				STAFF:STAFF();
				TEACH_MAJOR=EMPTY;
				SEARCH_NAME=EMPTY;
				GRADUATE_STUDENT_NUM=0;
			}
			void INSERT_TEACH_MAJOR(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				TEACH_MAJOR=BUFFER;
			}
			void INSERT_SEARCH_NAME(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				SEARCH_NAME=BUFFER;
			}
			void INSERT_GRA_NUM(int A)
			{
				GRADUATE_STUDENT_NUM=A;
			}
			void PRINT()
			{
				STAFF::PRINT();
				cout<<"\nTEACH MAJOR - - >"<<TEACH_MAJOR;
				cout<<"\nTHE PROFESSOR'S SEARCH'S NAME - - >"<<SEARCH_NAME;
				cout<<"\nTHE NUMBER OF PROFESSOR'S GRADUATE STUDENT"<<GRADUATE_STUDENT_NUM;
			}
};
class WORKER:public STAFF
//This class is derived from the derived class STAFF.
{
	private:
			char *WORK_TYPE;
	public:
			WORKER()
			{
				STAFF:STAFF();
				WORK_TYPE="WORKER";
			}
			void INSERT_WORK_TYPE(char *S)
			{
				char *BUFFER;
				BUFFER=new char[strlen(S)+1];
				strcpy(BUFFER,S);
				WORK_TYPE=BUFFER;
			}
			void PRINT()
			{
				STAFF::PRINT();
				cout<<"\nTHE WORKER IS A - - >"<<WORK_TYPE;
			}
};