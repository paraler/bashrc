//THE PROGRAM IS TO TEST THE CLASS "QUEUE"
//FILE QUEUE.CPP

#include "QUEUE.h"

class QUEUE : LIST
{
	public:
			QUEUE():LIST(){}
			void PUT(int NUM)
			{
				LIST::BACKWARD_ADD(NUM);
			}
			char GET()
			{
				return LIST::GET();
			}

};

int main(void)
{
	int INTNUM;
	clrscr();
	QUEUE TEXT_Q;
	printf("		--- QUEUE ---\n\n");
	printf("\n Put 10");
	INTNUM=10;
	TEXT_Q.PUT(INTNUM);
	printf("\n Put 20");
	INTNUM=20;
	TEXT_Q.PUT(INTNUM);
	printf("\n Put 30");
	INTNUM=30;
	TEXT_Q.PUT(INTNUM);
	INTNUM=TEXT_Q.GET();
	printf("\n THE FIRST ITEM POPPED FROM THE QUEUE  = %d",INTNUM);
	INTNUM=TEXT_Q.GET();
	printf("\n THE SECOND ITEM POPPED FROM THE QUEUE = %d",INTNUM);
	INTNUM=TEXT_Q.GET();
	printf("\n THE THIRD ITEM POPPED FROM THE QUEUE  = %d",INTNUM);
	getch();
	return 0;
}