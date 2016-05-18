//THIS PROGRAM IS THE FIRST STEP TO LEARN THE DERIVED CLASS
//FILE DERIVED.CPP

#include <stdio.h>
#include <conio.h>

class PARENT
{
	private :
			int NUM_1;
	public :
			PARENT(){};
			void ASSIGN_PRI_1(int NUM1)
			{
				NUM_1=NUM1;
			}
			void NUM_1_INC()
			{
				NUM_1+=1;
			}
			void DISPLAY()
			{
				printf("\n NUM_1(PARENT PRIVATE NUMBER)=%d",NUM_1);
			}
			int GET_NUM_1()
			{
				return NUM_1;
			}
};

class PRIVATE_DERIVED : private PARENT	//Private Inherit
{
	private :
			int NUM_2;

	public :
			PRIVATE_DERIVED(int NUM2)
			{
				NUM_2=NUM2;
			}
			void ASSIGN_PRI_1(int NUM1)
			{
				PARENT::ASSIGN_PRI_1(NUM1);
			}
			void NUM_1_INC()
			{
				if (NUM_2>5)
					PARENT::NUM_1_INC();
			}
			void NUM_2_INC()
			{
				NUM_2+=1;
			}
			void DISPLAY()
			{
				PARENT::DISPLAY();
				printf("\n NUM_2(PRIVATE DERIVED PRIVATE NUMBER)=%d\n",NUM_2);
			}
};

class PUBLIC_DERIVED : public PARENT	//Public Inherit
{
	private :
			int NUM_3;

	public :
			PUBLIC_DERIVED(int NUM3)
			{
				NUM_3=NUM3;
			}
			void NUM_1_INC()
			{
				if (PARENT::GET_NUM_1()<20)
					PARENT::NUM_1_INC();
			}
			void NUM_3_INC()
			{
				NUM_3+=1;
			}
			void DISPLAY()
			{
				PARENT::DISPLAY();
				printf("\n NUM_3(PUBLIC DERIVED PRIVATE NUMBER)=%d",NUM_3);
			}
};

int main(void)
{
	clrscr();
	PARENT PRE;
	printf("\n\nBEFORE increasing :");
	PRIVATE_DERIVED PRI_D(2);
	PRI_D.ASSIGN_PRI_1(99);
	PRI_D.DISPLAY();
	printf("\n\nAFTER increasing : ");
	PRI_D.NUM_1_INC();
	PRI_D.NUM_2_INC();
	PRI_D.DISPLAY();
	printf("\n\n----  Because NUM_2 < 5,NUM_1 did not increase!  ----");
	printf("\n\nPRESS ANY KEY TO CONTINUE... ...");
	getch();
	clrscr();

	printf("\n\nBEFORE increasing :");
	PUBLIC_DERIVED PUB_D(2);
	PUB_D.ASSIGN_PRI_1(25);
	PUB_D.DISPLAY();
	printf("\n\nAFTER increasing : ");
	PUB_D.NUM_1_INC();
	PUB_D.NUM_3_INC();
	PUB_D.DISPLAY();
	printf("\n\n----  Because NUM_1 > 20,NUM_1 did not increase!  ----");
	printf("\n\nPRESS ANY KEY TO CONTINUE... ...");
	getch();
	clrscr();

	printf("\n\nBEFORE increasing :");
	PUB_D.ASSIGN_PRI_1(25);
	PUB_D.DISPLAY();
	printf("\n\nAFTER increasing : ");
	PUB_D.PARENT::NUM_1_INC();
	PUB_D.NUM_3_INC();
	PUB_D.DISPLAY();
	printf("\n\n----  Because use the NUM_1_INC() of PARENT CLASS,"
		" the limitation in PUBLIC_DERIVED did not available!"
		"   Though NUM_1 > 20 ,NUM_1 increased !");
	printf("\n\nPRESS ANY KEY TO EXIT... ...");
	getch();
	return 0;
}