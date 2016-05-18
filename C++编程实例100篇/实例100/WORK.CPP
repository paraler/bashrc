#include<stdio.h>
#include<iostream.h>
#include<bios.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#define READY 0
#define RUNNING 1
typedef struct ProcType ;
struct ProcType{
	int ID;
	int Status;
	struct time ArriTime;
	struct time RunTime;
	int SerTime;
	int StartP;
	int Resource;
};
ProcType Proc[100];
struct ConType{
	int First;
	int ProcNum;
	int Free;
}Control;
struct MemType{
	int ID;
	int Flag;
}Mem[50];
struct xyType{
	int lx;
	int rx;
	int ly;
	int ry;
}xy;
int WaitArr[50];
int wh=0;
int wt=0;
int Tail=0;
int Number=-1;

void Initgraph()
{
	int gdriver = DETECT, gmode;
	registerbgidriver(EGAVGA_driver);
	initgraph(&gdriver, &gmode, "");
}
void Waiting()
{
	setcolor(YELLOW);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(200,170,"Press SOME keys");
	outtextxy(150,250,"to produce processes... ...");
	while(!kbhit()){};
	delay(3000);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}
void Closegraph()
{
	closegraph();
}
int ranres(void)
{
	int i,a,size;
	size=1;
	a=random(4);
	for(i=0;i<a;i++)
	{
		size=size*2;
	}
	printf("\na=%d",a);
	printf("size=%d",size);
	return size;
}

int rantime(void)
{
	int b,time;
	time=1;
	b=random(4);
	time=(b+1)*5;
	return time;
}

struct time biuldtime(void)
{
	struct time t;
	gettime(&t);
	return t;
}

void biuldwait(int id)
{

	Proc[id].ID=id;
	Proc[id].SerTime=rantime();
	Proc[id].Resource=ranres();
	WaitArr[wt]=id;
	wt++;

}
void biuldmem(void)
{
	int a,i,id;
	a=Proc[WaitArr[wh]].Resource;
	while(a<=Control.Free&&(wh!=wt))
	{
		id=WaitArr[wh];

		Proc[id].ArriTime=biuldtime();
		Proc[id].StartP=Tail;	/*Don't forget the initial of the Tail*/
		Proc[id].Status=READY;

		for(i=0;i<Proc[id].Resource;i++)
			Mem[Tail+i].Flag=1;
		Control.ProcNum++;

		Control.Free-=Proc[id].Resource;
		Tail+=Proc[id].Resource;

		wh++;
		a=Proc[WaitArr[wh]].Resource;
	}
}
struct xyType getxy(int id)
{
	int a,b;
	struct xyType xy;
	a=id%10;
	b=int(id/10);
	xy.lx=100+a*40;xy.ly=250+b*30;
	xy.rx=125+a*40;xy.ry=260+b*30;
	return xy;
}
int retcolor(int id)
{
	if (id==1) return 12;
	if (id==2) return 1;
	if (id==4) return 10;
	if (id==8) return 14;
	else return 0;
}
void drawgrid(void)
{
	int i;
	setcolor(12);
	moveto(10,430);
	lineto(620,430);

	setcolor(11);
	outtextxy(40,40,
	"*-*-*-*-*-*-*-*-*-The Memory Distribution Of The Process"
	"-*-*-*-*-*-*-*-*-*");
	setcolor(13);
	outtextxy(160,80,"--**-- Color Declaration --**--");
	for(i=0;i<7;i++)
	{
		moveto(200,100+i*20);
		lineto(400,100+i*20);
	}
	for(i=0;i<3;i++)
	{
		moveto(200+i*100,100);
		lineto(200+i*100,220);
	}
	setcolor(14);
	outtextxy(205,105,"Color");outtextxy(305,105,"Process Size");
	setcolor(12);
	outtextxy(210,125,"RED");outtextxy(330,125,"1 M");
	setcolor(1);
	outtextxy(210,145,"BLUE");outtextxy(330,145,"2 M");
	setcolor(10);
	outtextxy(210,165,"GREEN");outtextxy(330,165,"4 M");
	setcolor(14);
	outtextxy(210,185,"YELLOW");outtextxy(330,185,"8 M");
	setcolor(15);
	outtextxy(210,205,"WHITE");outtextxy(330,205,"FREE");

}
void drawrun(void)
{
	int i,k,size,id,timesub,color,j=0,a;
	char msg[50];
	struct time t,st;

	id=Control.First;
	Proc[id].RunTime=biuldtime();
	st=Proc[id].RunTime;
	size=Proc[Control.First].Resource;

	gettime(&t);
	timesub=(t.ti_hour*60*60*100+t.ti_min*60*100+t.ti_sec*100+t.ti_hund)
		-(st.ti_hour*60*60*100+st.ti_min*60*100+st.ti_sec*100+st.ti_hund);
	a=0;
	while(timesub<=5*Proc[id].SerTime)
	{
		color=5+j%10;
		j++;
		setfillstyle(6,color);
		for(i=0;i<size;i++)
		{
			bar(getxy(i).lx,getxy(i).ly,getxy(i).rx,getxy(i).ry);
		}
		gettime(&t);
		timesub=(t.ti_hour*60*60*100+t.ti_min*60*100+t.ti_sec*100+t.ti_hund)
		-(st.ti_hour*60*60*100+st.ti_min*60*100+st.ti_sec*100+st.ti_hund);

		setcolor(11);
		sprintf(msg,"The process %d is running... ...",(id+1));
		outtextxy(30,450,msg);

		setcolor(YELLOW);
		outtextxy(150,395,"Now you can ALSO press "
					"any key to produce processes... ...");
		setcolor(11);
		outtextxy(5,395,"* Time Show *");
		moveto(10+a,410);
		lineto(10+a,425);
		a++;
	}
	setfillstyle(1,WHITE);
	for(i=0;i<size;i++)
		{
			bar(getxy(i).lx,getxy(i).ly,getxy(i).rx,getxy(i).ry);
		}
}
void drawother(void)
{
	int id,i;
	for(id=Control.First+1;id<(Control.First+Control.ProcNum);id++)
	{
		setfillstyle(1,retcolor(Proc[id].Resource));
		for(i=Proc[id].StartP;i<Proc[id].StartP+Proc[id].Resource;i++)
			bar(getxy(i).lx,getxy(i).ly,getxy(i).rx,getxy(i).ry);
	}
}
void drawfree(void)
{
	int i;
	setfillstyle(1,WHITE);
	for(i=Tail;i<50;i++)
		{
			bar(getxy(i).lx,getxy(i).ly,getxy(i).rx,getxy(i).ry);
		}
}
void run(void)
{
	int id;
	id=Control.First;
	Proc[id].Status=RUNNING;
	drawother();
	drawfree();
	drawrun();
}
void finish(void)
{
	int id;
	int i;
	id=Control.First;
	for(i=0;i<Proc[id].Resource;i++)
		Mem[i].Flag=0;
	Control.ProcNum--;
	Control.Free+=Proc[id].Resource;
}
void compress(void)
{
	int i,j,k;
	i=0;j=0;
	while(Mem[i].Flag==1) i++; /*i point to the first "0" */
	j=i;
	while(Mem[j].Flag==0&&j<(i+8)) j++; /*j point to the first "1" */
	while(Mem[j].Flag==1)
	{
		Mem[i].Flag=1;
		Mem[j].Flag=0;
		for(k=0;k<(Control.ProcNum+1);k++) /*Control.ProcNum+1=The procnum befor*/
		{
			if(Proc[Control.First+k].StartP==j)
				Proc[Control.First+k].StartP=i;
		}
		i++;j++;
	}
	Control.First++;
	Tail=i; /*Tail point to the first "0" after compress */
}
void display(void)
{

	int i;
	int id;
	for(id=Control.First;id<(Control.First+Control.ProcNum);id++)
	{
		setfillstyle(1,retcolor(Proc[id].Resource));
		for(i=Proc[id].StartP;i<Proc[id].StartP+Proc[id].Resource;i++)
			bar(getxy(i).lx,getxy(i).ly,getxy(i).rx,getxy(i).ry);
	}

	drawfree();
}

void runkernel(void)
{
	cleardevice();
	setbkcolor(0);

	int id,l,count=0;
	Control.First=0;
	Control.Free=50;
	id=Number+1;
	while((Control.Free<50)||(Number==-1))
	{
		while(bioskey(1)!=0)
		{
			count++;
			bioskey(0);
			biuldwait(id);
			id++;
			Number++;
		}
		if((wt==wh&&wh==0)||(wt!=wh))	biuldmem();/*Biuld all can*/
		cleardevice();
		setbkcolor(0);
		drawgrid();
		run();
		finish();
		compress();
		display();
		delay(2000);
	}
	setcolor(0);
	for(int a=0;a<629;a++)
	{
		moveto(a,390);
		lineto(a,425);
		moveto(a,445);
		lineto(a,460);
	}
	setcolor(YELLOW);
	outtextxy(180,450,"All the processes have been done!");
	getch();
}
int main(void)
{
	Initgraph();
	Waiting();
	runkernel();
	Closegraph();
	return 0;
}

