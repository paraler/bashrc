//THE PROGRAM IS TO REALITY THE USE OF THE VIRTUAL METHOD
//FILE VIRFUNC.CPP


#include <stdio.h>
#include <conio.h>

class PARENT
{
	protected:
			int DATA;
	public:
		virtual void READ_NUM()
		{
			printf("\nNow,this is function in PARENT");
			printf("\nInput a number please:");
			scanf("%d",&DATA);
		}
		virtual int GET_NUM()
		{
			printf("Now,this is function in PARENT");
			return DATA;
		}

};
class DERIVED:public PARENT
{
	protected:
			int DATA;
	public:
		void READ_NUM()
		{
			printf("\nNow,this is function in DERIVED");
			printf("\nInput a number please:");
			scanf("%d",&DATA);
		}
		int GET_NUM()
		{
			printf("Now,this is function in DERIVED");
			return DATA;
		}
};
int main(void)
{
	int NUM;
	PARENT *P,X;
	DERIVED Y;
	clrscr();
	P=&X;
	P->READ_NUM();
	NUM=P->GET_NUM();
	printf("\nNUM (PARENT) =%d\n",NUM);
	P=&Y;
	P->READ_NUM();
	NUM=P->GET_NUM();
	printf("\nNUM (DERIVED) =%d\n",NUM);
	getch();
	return 0;
}