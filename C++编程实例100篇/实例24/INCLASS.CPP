//THE PROGRAM IS TO INSERT ONE CLASS INTO ANOTHER
//FILE INCLASS.CPP

#define  CONST1 78
#define  CONST2 12
#define  CONST3 23
#include <stdio.h>
#include <conio.h>

class INCLASS_1
{
	private :
			int DATA;

	public :
			INCLASS_1(int NUM)
			{
				DATA=NUM;
			};
			void OUTPUT()
			{
				printf("\n %d",DATA);
			}
};
class INCLASS_2
{
	private :
			int DATA;

	public :
			INCLASS_2(int NUM)
			{
				DATA=NUM;
			};
			void OUTPUT()
			{
				printf("\n %d",DATA);
			}
};
class OUTCLASS
{
	private :
			int DATA;
			INCLASS_1 OB1;
			INCLASS_2 OB2;
	public :
			OUTCLASS(int NUM);
			void OUTPUT()
			{
				printf("\n %d",DATA);
			}
			void OUTPUTOB1()
			{
				OB1.INCLASS_1::OUTPUT();
			}
			void OUTPUTOB2()
			{
				OB2.INCLASS_2::OUTPUT();
			}
};

OUTCLASS::OUTCLASS(int NUM):OB1(CONST1),OB2(CONST2)
{
	DATA=NUM;
}

int main(void)
{
	OUTCLASS TEST(CONST3);
	clrscr();
	TEST.OUTPUT();
	TEST.OUTPUTOB1();
	TEST.OUTPUTOB2();
	getch();
	return 0;
}