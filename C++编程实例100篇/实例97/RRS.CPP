//THE PROGRAM IS TO TEST THE OPERATING SYSTEM'S "ROUND-ROBIN SCHEDULING".
//FILE RRS.CPP

#include    <stdio.h>
#include    <conio.h>
#include   <string.h>
#include   <stdlib.h>
#include <graphics.h>
#include       "Rr.h"

#define Count 5

float TqTs[Count];
int Quantum=0,Finish[Count];
int Ts[Count],ArriveTime[Count],EndTime[Count],Tq[Count];

void Kernel(void);
void Result(void);
void Version(void);
void InitGrid(void);
int IF_Finish(void);
void InitGraph(void);
void InitRecord(void);
void InitProcess(void);

Node Table[50];
Grid Record,Graph;

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

void InitGraph(void)
{
	int Gdriver=DETECT,Gmode,Errorcode;
	initgraph(&Gdriver,&Gmode,"D:\\Tools\\Tc3.0\\Bgi");
	Errorcode=graphresult();
	if (Errorcode!=grOk)
	{
		printf("Graphics Error: %s\n",grapherrormsg(Errorcode));
		printf("Press any key to exit:");
		getch();
		exit(1);
	}
}

void InitProcess(void)
{
	int i;
	window(1,1,80,25);
	textbackground(1);
	textcolor(14);
	clrscr();
	printf("\n		---------- The Round Robin Scheduling ---------\n");
	printf("\n***** Input The Quantum Time Of The Process : ");
	scanf("%d",&Quantum);
	for (i=0;i<Count;i++)
	{
		printf("\n----- Input The Arrive  Time Of The Process %d : ",i+1);
		scanf("%d",&ArriveTime[i]);
		printf("\n***** Input The Service Time Of The Process %d : ",i+1);
		scanf("%d",&Ts[i]);
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
	Record.GetRectangle(1)->Outtextxy("ArriveTime");
	Record.GetRectangle(2)->Outtextxy("    Ts    ");
	Record.GetRectangle(3)->Outtextxy("FinishTime");
	Record.GetRectangle(4)->Outtextxy("    Tq    ");
	Record.GetRectangle(5)->Outtextxy("  Tq/Ts   ");
	Record.GetRectangle(6)->Outtextxy("    P1    ");
	Record.GetRectangle(12)->Outtextxy("    P2    ");
	Record.GetRectangle(18)->Outtextxy("    P3    ");
	Record.GetRectangle(24)->Outtextxy("    P4    ");
	Record.GetRectangle(30)->Outtextxy("    P5    ");
	setcolor(9);
	for (i=7,circle=0;i<=31,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(ArriveTime[circle]);
	for (i=8,circle=0;i<=32,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(Ts[circle]);
}

void InitGrid(void)
{
	int number1=0,circle1,i;
	setcolor(11);
	outtextxy(155,155,"The Process Round Robin Scheduling");
	setlinestyle(CENTER_LINE,1,1);
	line(15,175,610,175);
	setcolor(15);
	setlinestyle(DOTTED_LINE,1,0);
	for (i=0;i<5;i++)
	{
		for (circle1=0;circle1<40;circle1++)
		{
			Graph.NewRectangle(number1,15+circle1*15,200+i*20,
						    circle1*15+30,200+(i+1)*20);
			number1=number1+1;
		}
	}
}

int IF_Finish(void)
{
	if (Finish[0]+Finish[1]+Finish[2]+Finish[3]+Finish[4]==5) return 1;
	else return 0;
}

int LineTest(int a)
{
	return (a*40);
}

void Kernel(void)
{
	int i=0,j=0,IN=0,FillNumber=0,Order=0,StartNumber=0;
	int Clock=0,EndIn=0,Temp=0,Current=0;
	Node TempNode;
	Table[Order].SetID(0);
	Table[Order].SetCurrentLength(Ts[0]);
	while (IF_Finish()==0)
	{
		IN=0;
		TempNode=Table[Current];
		StartNumber=LineTest(TempNode.GetID());
		FillNumber=TempNode.GetCurrentLength()-Quantum;
		Temp=Clock;
		if (FillNumber<=0)
		{
			FillNumber=TempNode.GetCurrentLength();
			Finish[TempNode.GetID()]=1;
			for (i=StartNumber+Temp;i<StartNumber+FillNumber+Temp;i++)
			{
				Graph.GetRectangle(i)->Fill();
				Clock=Clock+1;
				for (j=0;j<Count;j++)
					if (Clock==ArriveTime[j])
					{
						Table[Order+1].SetID(j);
						Table[Order+1].SetCurrentLength(Ts[j]);
						Order=Order+1;
						IN=1;
						if (j==Count-1) EndIn=1;
					}
			}
			EndTime[TempNode.GetID()]=Clock;
			while ((IN==0) && (IF_Finish()==0) && (EndIn==0))
			{
				Clock=Clock+1;
				for (j=0;j<Count;j++)
				{
					if ((Clock==ArriveTime[j]) && (Finish[j]==0))
						{
							Table[Order+1].SetID(j);
							Table[Order+1].SetCurrentLength(Ts[j]);
							Order=Order+1;
							IN=1;
						}
				}
			}
		}
		else
		{
			for (i=StartNumber+Temp;i<StartNumber+Quantum+Temp;i++)
			{
				Graph.GetRectangle(i)->Fill();
				Clock=Clock+1;
				for (j=0;j<5;j++)
					if ((Clock==ArriveTime[j]) && (Finish[j]==0))
					{
						Table[Order+1].SetID(j);
						Table[Order+1].SetCurrentLength(Ts[j]);
						Order=Order+1;
						if (j==Count-1) EndIn=1;
					}
			}
			if (Finish[TempNode.GetID()]==0)
			{
				Table[Order+1].SetID(TempNode.GetID());
				Table[Order+1].SetCurrentLength(FillNumber);
				Order=Order+1;
			}
		}
		Current=Current+1;
	}
}

void Result()
{
	int i=0,circle=0;
	float Sum=0.0,Everage=0.0;
	for (i=0;i<Count;i++)
	{
		Tq[i]=EndTime[i]-ArriveTime[i];
		TqTs[i]=(float (Tq[i]))/(float (Ts[i]));
		Sum=Sum+TqTs[i];
	}
	Everage=Sum/Count;
	for (i=9,circle=0;i<=33,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(EndTime[circle]);
	for (i=10,circle=0;i<=34,circle<Count;i=i+6,circle++)
		Record.GetRectangle(i)->Display(Tq[circle]);
	setcolor(12);
	for (i=11;i<=35;i=i+6)
		Record.GetRectangle(i)->Outtextxy("Thinking...");
	getch();
	outtextxy(100,330,"----- Result -----");
	gotoxy(19,23);
	printf("The Everage Time Of (Tq/Ts) IS : %f",Everage);
	getch();
}

void Version()
{
	setcolor(14);
	outtextxy(150,400,"    DESIGNED BY NEWTRUMP 2001.01.01     ");
	outtextxy(150,420,"            Version 1.0                 ");
}