#include  <math.h>
#include "Windw.h"

#define MAX    100
#define SIZE    50

class PCB
{
	private :
			int ID;
			int Size;
			int Ts;
			int Flag;
	public :
			PCB()
			{
				ID=0;
				Size=0;
				Ts=0;
				Flag=0;
			}
			void SetID(int I){ID=I;}
			void SetMFlag(){Flag=1;}
			void SetDFlag(){Flag=0;}
			void SetSizeTs(void)
			{
				int number;
				randomize();
				number=rand()%4;
				Size=ldexp(2,number-1);
				Ts=(number+1)*5;
			}
			int GetFlag(void) {return Flag;}
			int GetID(void){return ID;}
			int GetSize(void){return Size;}
			int GetTs(void){return Ts;}
};

class Rectangle
{
	friend class Grid;
	private :
			int left,top,right,bottom;
			char content[SIZE];
	public :
			void Outtextxy(char text[SIZE])
			{
				strcpy(content,text);
				outtextxy(left+9,top+7,content);
			}
			void Fill(int Number)
			{
				setfillstyle(SOLID_FILL,Number);
				bar3d(left+1,top+1,right-1,bottom-1,0,0);
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
				if ((Temp>=0) && (Temp<=9)) Test(Temp,0);
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
			Rectangle *Array[MAX];
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
			Rectangle *GetRectangle(int number) {return Array[number];}
};

void Exit(void);
void Version(void);
void Running(void);
void InitGrid(void);
void InitGraph(void);
void InitRecord(void);
void Allocation(void);
void Compact(int number);
int  Returncolor(int number);

Grid Record,Graph;
PCB MEMORY[MAX];
PCB HARDDISK[MAX];

int Screen[MAX];
int CurrentMIDM=0,CurrentMIDD=0,CurrentMMp=0,CurrentMDp=0;
int LeftSpace=SIZE,LeftD=SIZE,CurrentEIDM,CurrentEIDD;

int main()
{
	int i;

	InitGraph();
	InitRecord();
	InitGrid();
	EventMsg eventMsg;
	mouse.SetLimits(0,getmaxx(),0,getmaxy());
	mouse.ShowMouse();
	Button wndw1(220,360,"^OK");
	Button wndw2(300,360,"^CANCEL");
	wndw1.DrawWindow();
	wndw2.DrawWindow();
	int button=0;
	while (!button)
	{
		GetEvent(eventMsg);
		if (wndw1.Clicked(eventMsg)) Allocation();
		if (wndw2.Clicked(eventMsg)) button=CANCEL;
		else if (!wndw1.Clicked(eventMsg)&&!wndw2.Clicked(eventMsg))
			Running();
	}
	Exit();

	return 0;
}

void Exit(void)
{
	mouse.HideMouse();
	Version();
	getch();
	closegraph();
	exit(1);
}

void InitGraph(void)
{
	int Gdriver=DETECT,Gmode,Errorcode;
	initgraph(&Gdriver,&Gmode,"D:\\Tools\\Tc3.0\\Bgi");
	Errorcode=graphresult();
	if (Errorcode!=grOk)
	{
		printf("Graphics Error: %s\n",grapherrormsg(Errorcode));
		printf("Press any key to exit & Change the dictory :");
		getch();
		exit(1);
	}
}

void InitRecord(void)
{
	int number=0,circle,i;
	for (i=0;i<5;i++)
	{
		for (circle=0;circle<6;circle++)
		{
			Record.NewRectangle(number,15+circle*100,20+i*20,
						circle*100+115,20+((i+1)*20));
			number=number+1;
		}
	}
	setcolor(14);
	Record.GetRectangle(0)->Outtextxy("   SIZE   ");
	Record.GetRectangle(1)->Outtextxy(" INTERVAL ");
	Record.GetRectangle(2)->Outtextxy("  TOTAL   ");
	Record.GetRectangle(3)->Outtextxy("  READY   ");
	Record.GetRectangle(4)->Outtextxy("  RUNNING ");
	Record.GetRectangle(5)->Outtextxy("  COLOR   ");
	setcolor(12);
	Record.GetRectangle(6)->Outtextxy("    1M    ");
	Record.GetRectangle(12)->Outtextxy("    2M    ");
	Record.GetRectangle(18)->Outtextxy("    4M    ");
	Record.GetRectangle(24)->Outtextxy("    8M    ");
	for (i=7,circle=0;i<=25,circle<4;i=i+6,circle++)
		Record.GetRectangle(i)->Display(i-circle-2);
	setcolor(15);
	for (i=8,circle=0;i<=26,circle<4;i=i+6,circle++)
		Record.GetRectangle(i)->Outtextxy("  Random  ");
	for (i=9,circle=0;i<=27,circle<4;i=i+6,circle++)
		Record.GetRectangle(i)->Outtextxy("  Random  ");
	for (i=10,circle=0;i<=28,circle<4;i=i+6,circle++)
		Record.GetRectangle(i)->Outtextxy("  Random  ");
	setcolor(12);
	Record.GetRectangle(11)->Outtextxy("   RED    ");
	setcolor(9);
	Record.GetRectangle(17)->Outtextxy("   BLUE   ");
	setcolor(10);
	Record.GetRectangle(23)->Outtextxy("  GREEN   ");
	setcolor(14);
	Record.GetRectangle(29)->Outtextxy("  YELLOW  ");
}

void InitGrid(void)
{
	int number=0,circle=0;
	setcolor(11);
	outtextxy(130,150,"***** The FIFO Method of Memory Distribute *****");
	line(15,180,625,180);
	line(15,340,625,340);
	setcolor(13);
	for (circle=0;circle<50;circle++)
	{
		Graph.NewRectangle(number,110+circle*10,230,circle*10+120,240);
		number=number+1;
	}
	for (circle=0;circle<50;circle++)
	{
		Graph.NewRectangle(number,110+circle*10,300,circle*10+120,310);
		number=number+1;
	}
	setcolor(14);
	outtextxy(20,210,"Main Memory");
	outtextxy(20,280,"Hard Disk");
}

int Returncolor(int number)
{
	if (number==1) return 12;
	if (number==2) return 9;
	if (number==4) return 10;
	if (number==8) return 14;
	else return 0;
}

void Allocation(void)
{
	PCB NewNode;
	int color,circle;
	NewNode.SetSizeTs();
	if(HARDDISK[CurrentEIDD].GetSize()==0
		&&CurrentMMp+NewNode.GetSize()<=SIZE)
	{
		NewNode.SetID(CurrentMIDM);
		NewNode.SetMFlag();
		color=Returncolor(NewNode.GetSize());
		for (circle=CurrentMMp;circle<CurrentMMp+NewNode.GetSize();circle++)
		{
			Graph.GetRectangle(circle)->Fill(color);
			Screen[circle]=color;
		}
		MEMORY[CurrentMIDM]=NewNode;
		CurrentMIDM=CurrentMIDM+1;
		CurrentMMp=CurrentMMp+NewNode.GetSize();
		LeftSpace=LeftSpace-NewNode.GetSize();
	}
	else
	{
		NewNode.SetID(CurrentMIDD);
		NewNode.SetDFlag();
		color=Returncolor(NewNode.GetSize());
		for (circle=CurrentMDp;circle<CurrentMDp+NewNode.GetSize();circle++)
		{
			Graph.GetRectangle(circle+SIZE)->Fill(color);
			Screen[circle+SIZE]=color;
		}
		HARDDISK[CurrentMIDD]=NewNode;
		CurrentMIDD=CurrentMIDD+1;
		CurrentMDp=CurrentMDp+NewNode.GetSize();
		LeftD=LeftD-NewNode.GetSize();
	}
}

void Running(void)
{
	int circle=0;
	PCB TempNode;
	TempNode=MEMORY[CurrentEIDM];
	if(LeftSpace<50)
	{
		for (circle=0;circle<TempNode.GetSize();circle++)
		{
			delay(MAX);
			Graph.GetRectangle(circle)->Fill(0);
			Screen[circle]=0;
		}
		if (HARDDISK[CurrentEIDD].GetSize()==0)
		{
			CurrentMMp=CurrentMMp-TempNode.GetSize();
			LeftSpace=LeftSpace+TempNode.GetSize();
			Compact(1);
		}
		else Compact(2);
		CurrentEIDM=CurrentEIDM+1;
	}
}

void Compact(int number)
{
	int i=0,circle=0,TempID,j;
	if (number==1)
	{
		while ((Screen[i]==0) && (i<SIZE)) i=i+1;
		if (i>0)
		{
			for (circle=0;circle<MAX-i;circle++)
				Screen[circle]=Screen[circle+i];
			for (circle=MAX-i;circle<MAX;circle++) Screen[circle]=0;
			for (circle=0;circle<MAX;circle++)
				Graph.GetRectangle(circle)->Fill(Screen[circle]);
		}
	}
	if (number==2)
	{
		while ((Screen[i]==0) && (i<SIZE)) i=i+1;
		if (i>0)
		{
			for (circle=0;circle<SIZE-i;circle++)
				Screen[circle]=Screen[circle+i];
			for (circle=SIZE-i;circle<SIZE;circle++) Screen[circle]=0;
			CurrentMMp=CurrentMMp-i;
			LeftSpace+=i;
			TempID=CurrentEIDD;
			while(HARDDISK[TempID].GetSize()<=LeftSpace&&CurrentMDp!=0)
			{
				for (circle=SIZE;circle<SIZE+HARDDISK[TempID].GetSize();
					circle++)	Screen[circle]=0;
				CurrentMDp=CurrentMDp-HARDDISK[TempID].GetSize();
				for (circle=SIZE-LeftSpace;circle<
				SIZE-LeftSpace+HARDDISK[TempID].GetSize();circle++)
					Screen[circle]=Returncolor(HARDDISK[TempID].GetSize());
				CurrentMMp=CurrentMMp+HARDDISK[TempID].GetSize();
				MEMORY[CurrentMIDM]=HARDDISK[TempID];
				CurrentMIDM++;
				LeftSpace=LeftSpace-HARDDISK[TempID].GetSize();
				for (circle=SIZE;circle<SIZE+CurrentMDp;circle++)
					Screen[circle]=
						Screen[circle+HARDDISK[CurrentEIDD].GetSize()];
				for (circle=SIZE+CurrentMDp;circle<MAX;circle++)
					Screen[circle]=0;
				for (circle=0;circle<MAX;circle++)
					Graph.GetRectangle(circle)->Fill(Screen[circle]);
				LeftD=LeftD+HARDDISK[TempID].GetSize();
				CurrentEIDD++;
				TempID++;
			}
		}
	}
}

void Version()
{
	setcolor(14);
	outtextxy(150,420," DESIGNED  By  NEWTRUMP  2001.01.01     ");
	outtextxy(150,440,"             Version 2.0                ");
}