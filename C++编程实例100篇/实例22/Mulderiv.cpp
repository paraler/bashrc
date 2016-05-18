//THE PROGRAM IS TO DISPLAY A MULDERIV CLASS
//FILE MULDERIV.CPP

#include <stdio.h>
#include <conio.h>

class CLASS_A
{
	protected:
			int NUM_A;
	public:
			void READ_NUM()
			{
				printf("Input a number please(NUM_A):");
				scanf("%d",&NUM_A);
			}
};
class CLASS_B
{
	protected:
			int NUM_B;
	public:
			void READ_NUM()
			{
				printf("Input a number please(NUM_B):");
				scanf("%d",&NUM_B);
			}
};
class CLASS_SUM:public CLASS_A,public CLASS_B
{
	private:
			int SUM;
	public:
			void MAKE_SUM()
			{
				SUM=NUM_A+NUM_B;
			}
			int GET_SUM()
			{
				return SUM;
			}
};
int main(void)
{
	CLASS_SUM SUM;
	clrscr();
	SUM.CLASS_A::READ_NUM();
	SUM.CLASS_B::READ_NUM();
	SUM.MAKE_SUM();
	printf("- - - The SUM is: %d - - -",SUM.GET_SUM());
	getch();
	return 0;
};

