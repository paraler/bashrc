//THE PROGRAM IS TO TEST THE CLASS "STACK"
//FILE STACK.CPP

#include "STACK.H"

class STACK : LIST
{
	public:
			STACK():LIST(){}
			void PUSH(int NUM)
			{
				LIST::FORWARD_ADD(NUM);
			}
			int POP()
			{
				return LIST::GET();
			}

};


int main(void)
{
	int INTNUM;
	STACK TEXT_S;
	clrscr();
	printf("		--- STACK ---");
	printf("\n Push 1");
	INTNUM=1;
	TEXT_S.PUSH(INTNUM);
	printf("\n Push 4");
	INTNUM=4;
	TEXT_S.PUSH(INTNUM);
	printf("\n Push 9");
	INTNUM=9;
	TEXT_S.PUSH(INTNUM);
	INTNUM=TEXT_S.POP();
	printf("\n THE FIRST ITEM POPPED FROM THE STACK  = %d",INTNUM);
	INTNUM=TEXT_S.POP();
	printf("\n THE SECOND ITEM POPPED FROM THE STACK = %d",INTNUM);
	INTNUM=TEXT_S.POP();
	printf("\n THE THIRD ITEM POPPED FROM THE STACK  = %d",INTNUM);
	getch();
	return 0;
}