///////////////////////////////////////////////////////////////////////////
// This Code Ddefines Several Classes For The Round Robin Scheduling Task
// File RR.H
///////////////////////////////////////////////////////////////////////////

//	(1) The Node Class Of Queue Class

class Node
{
	private :
			int ID;
			int CurrentLength;

	public :
			Node(){};
			void SetID(int a)
			{
				ID=a;
			}
			void SetCurrentLength(int L)
			{
				CurrentLength=L;
			}
			int GetID(void)
			{
				return ID;
			}
			int GetCurrentLength(void)
			{
				return CurrentLength;
			}
};

//	(2) The Several Classes For Display

class Rectangle
{
	friend class Grid;
	private :
			int left,top,right,bottom;
			char content[50];

	public :
			void Outtextxy(char text[50])
			{
				strcpy(content,text);
				outtextxy(left+9,top+7,content);
			}
			void Fill()
			{
				setfillstyle(SOLID_FILL,1);
				bar3d(left,top,right,bottom,0,0);
				getch();
			}
			void Test(int Temp,int Interval)
			{
				if (Temp==0) outtextxy(left+45+Interval,top+7,"0");
				if (Temp==1) outtextxy(left+45+Interval,top+7,"1");
				if (Temp==2) outtextxy(left+45+Interval,top+7,"2");
				if (Temp==3) outtextxy(left+45+Interval,top+7,"3");
				if (Temp==4) outtextxy(left+45+Interval,top+7,"4");
				if (Temp==5) outtextxy(left+45+Interval,top+7,"5");
				if (Temp==6) outtextxy(left+45+Interval,top+7,"6");
				if (Temp==7) outtextxy(left+45+Interval,top+7,"7");
				if (Temp==8) outtextxy(left+45+Interval,top+7,"8");
				if (Temp==9) outtextxy(left+45+Interval,top+7,"9");
			}
			void Display(int number)
			{
				int Temp=number;
				if ((Temp>=0) && (Temp<=9))
				{
					Test(Temp,0);
				}
				if ((Temp>=10) && (Temp<=99))
				{
					Temp=int (Temp/10);
					Test(Temp,0);
					Temp=number-Temp*10;
					Test(Temp,5);
				}
			}
};

class Grid
{
	private :
			Rectangle *Array[100];
	public :
			Grid(){};
			void NewRectangle(int number,int a,int b,int c,int d)
			{
				Rectangle *Newrect;
				Newrect=new Rectangle;
				Newrect->left=a;
				Newrect->top=b;
				Newrect->right=c;
				Newrect->bottom=d;
				rectangle(a,b,c,d);
				Array[number]=Newrect;
			}
			Rectangle *GetRectangle(int number)
			{
				return Array[number];
			}
};