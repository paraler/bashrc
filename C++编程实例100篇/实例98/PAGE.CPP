//THE PROGRAM IS TO DISPLAY THE OPREATING SYSTEM'S
//PROCESS PAGE DISTRIBUTE.
//FILE PAGE.CPP

#include    <stdio.h>
#include    <conio.h>
#include   <string.h>
#include   <stdlib.h>
#include <graphics.h>

#define MAX 100
#define Count 5

int TableLength,Virtual[MAX];
int Length[Count],Privilege[Count];
int Normal[Count],IOTime[Count],Finish[Count];

void Kernel(void);
void Result(void);
void Version(void);
int IF_Finish(void);
void InitGrid(void);
void InitGraph(void);
void InitRecord(void);
void InitProcess(void);

class Node
{
	private :
			int ID;
			int Length;
			int Privilege;
			int Temp[MAX];

	public :
			Node()
			{
				for (int i=0;i<MAX;i++) Temp[i]=-1;
			}
			void SetID(int I)
			{
				ID=I;
			}
			void SetLength(int L)
			{
				Length=L;
			}
			void SetPrivilege(int P)
			{
				Privilege=P;
			}
			void SetPosition(int Order)
			{
				Virtual[Order]=ID;
				Temp[Order]=ID;
			}
			void Release(void)
			{
				for (int i=0;i<TableLength;i++)
					if (Virtual[i]==ID)
					{
						Virtual[i]=-1;
						Graph.GetRectangle(i)->Fill(0);
					}
			}
			int GetID(void){return ID;}
			int GetLength(void){return Length;}
			int GetPrivilege(void){return Privilege;}
			int GetPosition(void)
			{
				for (int i=0;i<TableLength;i++)
				{
					if (Temp[i]==ID) break;
				}
				if (Temp[i]==-1) return MAX;
				else
				{
					Temp[i]=-1;
					return i;
				}
			}
};

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
			void Fill(int Number)
			{
				setfillstyle(SOLID_FILL,Number);
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

Grid Record,Graph;
Node Table[50];

int main(void)
{
	InitProcess();
	getch();
	InitGraph();
	InitRecord();
	InitGrid();
	Kernel();
	Result();
	Version();
	getch();
	closegraph();
	return 0;
}

void InitProcess(void)
{
	int i;
	window(1,1,80,25);
	textbackground(1);
	textcolor(14);
	clrscr();
	for (i=0;i<MAX;i++) Virtual[i]=-1;
	printf("\n       ------  The Process Of Page Distribute  ------\n");
	printf("\n***** Input The Page Table Length Of The Process : ");
	scanf("%d",&TableLength);
	for (i=0;i<Count;i++)
	{
		printf("\n----- Input The Length Of The Process %d : ",i+1);
		scanf("%d",&Length[i]);
		printf("\n***** Input The Prilvilege Of The Process %d : ",i+1);
		scanf("%d",&Privilege[i]);
	}
}

void InitGraph(void)
{
	int Gdriver=DETECT,Gmode,Errorcode;
	initgraph(&Gdriver,&Gmode,"d:\\TOOLS\\TC3.0\\BGI");
	Errorcode=graphresult();
	if (Errorcode!=grOk)
	{
		printf("Graphics Error: %s\n",grapherrormsg(Errorcode));
		printf("Press any key to exit:");
		getch();
		exit(1);
	}
}

void InitRecord(void)
{
	int number=0,circle,i;
	for (i=0;i<Count+1;i++)
	{
		for (circle=0;circle<Count+1;circle++)
		{
			Record.NewRectangle(number,15+circle*100,20+i*20,
						circle*100+115,20+((i+1)*20));
			number=number+1;
		}
	}
	setcolor(14);
	Record.GetRectangle(1)->Outtextxy("  Length  ");
	Record.GetRectangle(2)->Outtextxy("Privilege ");
	Record.GetRectangle(3)->Outtextxy("  Normal  ");
	Record.GetRectangle(4)->Outtextxy("  Colour  ");
	Record.GetRectangle(5)->Outtextxy("I/O  Times");
	Record.GetRectangle(6)->Outtextxy("    P1    ");
	Record.GetRectangle(12)->Outtextxy("    P2    ");
	Record.GetRectangle(18)->Outtextxy("    P3    ");
	Record.GetRectangle(24)->Outtextxy("    P4    ");
	Record.GetRectangle(30)->Outtextxy("    P5    ");
	setcolor(9);
	for (i=7,circle=0;i<=31,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(Length[circle]);
	for (i=8,circle=0;i<=32,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(Privilege[circle]);
	for (i=9,circle=0;i<=33,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(Normal[circle]);
	for (i=11,circle=0;i<=35,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(IOTime[circle]);
	setcolor(9);
	Record.GetRectangle(10)->Outtextxy("   BLUE   ");
	setcolor(10);
	Record.GetRectangle(16)->Outtextxy("  GREEN   ");
	setcolor(11);
	Record.GetRectangle(22)->Outtextxy("   CYAN   ");
	setcolor(12);
	Record.GetRectangle(28)->Outtextxy("   RED    ");
	setcolor(13);
	Record.GetRectangle(34)->Outtextxy("  MAGENTA ");
}

void InitGrid(void)
{
	int number=0,circle=0;
	setcolor(11);
	outtextxy(155,180,"The Process Of Memory Page Distribute");
	setlinestyle(CENTER_LINE,1,1);
	line(15,200,610,200);
	setcolor(15);
	setlinestyle(DOTTED_LINE,1,0);
	for (circle=0;circle<TableLength;circle++)
	{
		Graph.NewRectangle(number,30+circle*20,250,circle*20+50,270);
		number=number+1;
	}
}

int IF_Finish(void)
{
	if (Finish[0]+Finish[1]+Finish[2]+Finish[3]+Finish[4]==5)
		return 1;
	else return 0;
}

void Kernel(void)
{
	int i=0,j=0,Free=0,Current=0,EndIn=0;
	int MinPrivilege=0,MinID=Count;
	Node TempNode;
	Free=TableLength;
	Table[0].SetID(0);
	Table[0].SetLength(Length[0]);
	Table[0].SetPrivilege(Privilege[0]);
	for (i=0;i<Table[0].GetLength();i++) Table[0].SetPosition(i);
	Current=0;
	while (IF_Finish()==0)
	{
		TempNode=Table[Current];
		if ((TempNode.GetLength()<Free) || (TempNode.GetLength()==Free))
		{
			Finish[TempNode.GetID()]=1;
			j=0;
			while (j!=MAX)
			{
				j=TempNode.GetPosition();
				if (j!=MAX)
					Graph.GetRectangle(j)->Fill(TempNode.GetID()+9);
			}
			if (TempNode.GetPrivilege()>MinPrivilege)
			{
				MinPrivilege=TempNode.GetPrivilege();
				MinID=TempNode.GetID();
			}
			Free=Free-TempNode.GetLength();
			if (Current==Count-1) EndIn=1;
			if (EndIn==0)
			{
				Table[Current+1].SetID(Current+1);
				Table[Current+1].SetLength(Length[Current+1]);
				Table[Current+1].SetPrivilege(Privilege[Current+1]);
				i=0;
				j=0;
				while ((j<Length[Current+1]) && (Length[Current+1]<=Free))
				{
					if (Virtual[i]==-1)
					{
						Table[Current+1].SetPosition(i);
						j=j+1;
					}
					i=i+1;
				}
			}
		}
		else
		{
			Table[MinID].Release();
			Free=Free+Table[MinID].GetLength();
			i=0;
			j=0;
			while ((j<Length[Current]) && (Length[Current]<=Free))
			{
				if (Virtual[i]==-1)
				{
					Table[Current].SetPosition(i);
					j=j+1;
				}
				i=i+1;
			}
			MinID=MinID-1;
			Current=Current-1;
		}
		Current=Current+1;
	}
}

void Result()
{
	getch();
	setcolor(14);
	outtextxy(200,300,"Default : When there is no page for new process ,");
	outtextxy(250,320,"Clear the lowest privilege process in table !");
	setcolor(12);
	outtextxy(100,340,"***** Result *****");
	setcolor(11);
	outtextxy(120,360,"----- The Above Is The Page Distribute Graph -----");
	getch();
}

void Version()
{
	setcolor(14);
	outtextxy(150,400,"    DESIGNED BY NEWTRUMP 2001.01.01  ");
	outtextxy(150,420,"             Version 1.0                ");
}