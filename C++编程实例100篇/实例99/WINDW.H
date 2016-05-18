//File Windw.h

#include <string.h>
#include <graphics.h>
#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Event.H"

#define TRUE      1
#define FALSE     0
#define OK        1
#define YES       2
#define NO        3
#define CANCEL    4
#define OKALT     0x1c0d
#define CANCELALT 0x011b

Mouse mouse;

class Windw
{
	private :
			int *buffer;
	protected :
				int wx,wy,ww,wh;
				int border,buffered;
				EventMsg eventMsg;
	public :
			Windw(int x,int y,int w,int h,int bdr,int buf);
			virtual ~Windw(void);
			virtual void DrawWindow(void);
			virtual void RunWindow(void);
	private :
			void WindwError(char *s);
};

class CapWindw : public Windw
{
	protected :
				char label[61];
	public :
			CapWindw(int x,int y,int w,int h,int bdr,int buf,char *s);
			virtual void DrawWindow(void);
			void SetCaption(char *s);
	private :
			void DrawCapBar(void);
};

class CapTWindw : public CapWindw
{
	protected :
				char *line1,*line2;
				int button;
	public :
			CapTWindw(char *s1,char *s2,char *s3);
			virtual void DrawWindow(void);
			int GetButton(void) {return button;}
};

class Button : public Windw
{
	private :
			char label[20];
			unsigned hotkey;
			int altkey;
	public :
			Button(int x,int y,char *s);
			void DrawWindow(void);
			int Clicked(EventMsg eventMsg);
			void ClickButton(void);
};

class OKWindw : public CapTWindw
{
	private :
			Button *butn;
	public :
			OKWindw(char *s1,char *s2,char *s3);
			virtual ~OKWindw(void);
			virtual void DrawWindow(void);
			virtual void RunWindow(void);
};

class YesNoWindw : public CapTWindw
{
	protected :
				Button *butn1,*butn2;
	public :
			YesNoWindw(char *s1,char *s2,char *s3);
			virtual ~YesNoWindw(void);
			virtual void DrawWindow(void);
			virtual void RunWindow(void);
};

class YesNoCanWindw : public CapTWindw
{
	private :
			Button *butn1,*butn2,*butn3;
	public :
			YesNoCanWindw(char *s1,char *s2,char *s3);
			virtual ~YesNoCanWindw(void);
			virtual void DrawWindow(void);
			virtual void RunWindow(void);
};

class InputWindw : public CapTWindw
{
	private :
			char input[81];
			Button *butn1,*butn2;
	public :
			InputWindw(char *s1,char *s2,char *s3);
			virtual ~InputWindw(void);
			void GetInput(char *s) {strcpy(s,input);}
			virtual void DrawWindow(void);
			virtual void RunWindow(void);
	private :
			void HandleInput(char k);
};

//All Implementations

unsigned ctrlkeys[]={
					0x1e01,0x3002,0x2e03,0x2004,0x1205,0x2106,
					0x2207,0x2308,0x1709,0x240a,0x250b,0x260c,
					0x320d,0x310e,0x180f,0x1910,0x1011,0x1312,
					0x1f13,0x1414,0x1615,0x2f16,0x1117,0x2d18,
					0x1519,0x2c1a
				};

//Class Windw Implementation
Windw::Windw(int x,int y,int w,int h,int bdr,int buf)
{
	wx=x;wy=y;ww=w;wh=h;
	border=bdr;
	buffered=buf;
	buffer=NULL;
}

Windw::~Windw(void)
{
	if(buffer!=NULL)
	{
		mouse.HideMouse();
		putimage(wx,wy,buffer,COPY_PUT);
		free(buffer);
		mouse.ShowMouse();
	}
}

void Windw::DrawWindow(void)
{
	int size;
	mouse.HideMouse();
	if(buffered)
		if ((size=imagesize(wx,wy,wx+ww,wy+wh))<0)
			WindwError("Image too largeto store.");
		else
		{
			if((buffer=(int *)malloc(size))==NULL)
				WindwError("Not enough memory.");
			else getimage(wx,wy,wx+ww,wy+wh,buffer);
		 }
	setcolor(WHITE);
	moveto(wx+ww,wy);
	lineto(wx,wy);
	lineto(wx,wy+wh);
	moveto(wx+ww-1,wy+1);
	lineto(wx+1,wy+1);
	lineto(wx+1,wy+wh-1);
	setcolor(DARKGRAY);
	moveto(wx+1,wy+wh);
	lineto(wx+ww,wy);
	moveto(wx+2,wy+wh-1);
	lineto(wx+ww-1,wy+wh-1);
	lineto(wx+ww-1,wy+1);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(wx+2,wy+2,wx+ww-2,wy+wh-2);
	if(border)
	{
		setcolor(DARKGRAY);
		moveto(wx+ww-10,wy+10);
		lineto(wx+10,wy+10);
		lineto(wx+10,wy+wh-10);
		setcolor(WHITE);
		lineto(wx+ww-10,wy+wh-10);
		lineto(wx+ww-10,wy+10);
	}
	mouse.ShowMouse();
}

void Windw::RunWindow(void)
{
	GetEvent(eventMsg);
}

void Windw::WindwError(char *s)
{
	printf("Error:\n");
	printf("Press any key ...");
	printf("%s",*s);
	getch();
	abort();
}

//Class CapWindw Implementation
CapWindw::CapWindw(int x,int y,int w,int h,int bdr,
			    int buf,char *s) : Windw(x,y,w,h,bdr,buf)
{
	strcpy(label,s);
}

void CapWindw::DrawWindow(void)
{
	Windw::DrawWindow();
	DrawCapBar();
}

void CapWindw::SetCaption(char *s)
{
	strcpy(label,s);
	DrawCapBar();
}

void CapWindw::DrawCapBar(void)
{
	mouse.HideMouse();
	setcolor(WHITE);
	moveto(wx+20,wy+40);
	lineto(wx+20,wy+20);
	lineto(wx+ww-20,wy+20);
	setcolor(BLACK);
	lineto(wx+ww-20,wy+40);
	lineto(wx+20,wy+40);
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(wx+21,wy+21,wx+ww-21,wy+39);
	setcolor(WHITE);
	int x=(wx+ww/2)-(strlen(label)*4);
	outtextxy(x,wy+27,label);
	mouse.ShowMouse();
}

//Class CapTWindw Implementation
CapTWindw::CapTWindw(char *s1,char *s2,char *s3) :
				CapWindw(0,0,0,150,FALSE,TRUE,s1)
{
	int w=strlen(s1)*8+60;
	if(strlen(s2)>strlen(s3))
		ww=strlen(s2)*8+60;
	else ww=strlen(s3)*8+60;
	if(w>ww) ww=w;
	if(ww<230) ww=230;
	wx=320-ww/2;
	wy=164;
	line1=s2;
	line2=s3;
}

void CapTWindw::DrawWindow(void)
{
	CapWindw::DrawWindow();
	mouse.HideMouse();
	int x=(wx+ww/2)-(strlen(line1)*8)/2;
	setcolor(BLACK);
	if(strlen(line2)==0)
		outtextxy(x,wy+68,line1);
	else
	{
		outtextxy(x,wy+56,line1);
		x=(wx+ww/2)-(strlen(line2)*8)/2;
		outtextxy(x,wy+71,line2);
	}
	mouse.ShowMouse();
}

//Class OKWindw Implementation
OKWindw::OKWindw(char *s1,char *s2,char *s3):CapTWindw(s1,s2,s3)
{
	butn=NULL;
}

OKWindw::~OKWindw(void)
{
	if(butn!=NULL) delete butn;
}

void OKWindw::DrawWindow(void)
{
	CapTWindw::DrawWindow();
	butn=new Button(wx+ww/2-32,wy+wh-42,"^OK");
	butn->DrawWindow();
}

void OKWindw::RunWindow(void)
{
	button=0;
	while(!button)
	{
		GetEvent(eventMsg);
		if(butn->Clicked(eventMsg))
			button=OK;
		else if(eventMsg.type==KEYBD)
		{
			char k=eventMsg.key&0x00ff;
			if(k==ESC) button=CANCEL;
		}
	}
}


//Class YesNoWindw Implementation
YesNoWindw::YesNoWindw(char *s1,char *s2,char *s3) : CapTWindw(s1,s2,s3)
{
	butn1=butn2=NULL;
}

YesNoWindw::~YesNoWindw(void)
{
	if (butn1!=NULL) delete butn1;
	if (butn2!=NULL) delete butn2;
}

void YesNoWindw::DrawWindow(void)
{
	CapTWindw::DrawWindow();
	butn1=new Button(wx+ww/2-70,wy+108,"^YES");
	butn1->DrawWindow();
	butn2=new Button(wx+ww/2+6,wy+108,"^NO");
	butn2->DrawWindow();
}

void YesNoWindw::RunWindow(void)
{
	button=0;
	while (!button)
	{
		GetEvent(eventMsg);
		if (butn1->Clicked(eventMsg))
			button=YES;
		else if (butn2->Clicked(eventMsg))
			button=NO;
		else if (eventMsg.type==KEYBD)
		{
			char k=eventMsg.key&0x00ff;
			if (k==ESC) button=CANCEL;
		}
	}
}

//Class YesNoCanWindw Implementation
YesNoCanWindw::YesNoCanWindw(char *s1,char *s2,char *s3) : CapTWindw(s1,s2,s3)
{
	butn1=butn2=butn3=NULL;
}

YesNoCanWindw::~YesNoCanWindw(void)
{
	if (butn1!=NULL) delete butn1;
	if (butn2!=NULL) delete butn2;
	if (butn3!=NULL) delete butn3;
}

void YesNoCanWindw::DrawWindow(void)
{
	CapTWindw::DrawWindow();
	butn1=new Button(wx+ww/2-105,wy+wh-42,"^YES");
	butn1->DrawWindow();
	butn2=new Button(wx+ww/2-32,wy+wh-42,"^NO");
	butn2->DrawWindow();
	butn3=new Button(wx+ww/2+41,wy+wh-42,"^CANCEL");
	butn3->DrawWindow();
}

void YesNoCanWindw::RunWindow(void)
{
	button=0;
	while (!button)
	{
		GetEvent(eventMsg);
		if (butn1->Clicked(eventMsg))
			button=YES;
		else if (butn2->Clicked(eventMsg))
			button=NO;
		else if (butn3->Clicked(eventMsg))
			button=CANCEL;
	}
}

//Class InputWindw Implementation
InputWindw::InputWindw(char *s1,char *s2,char *s3):CapTWindw(s1,s2,s3)
{
	input[0]=0;
	butn1=butn2=NULL;
}

InputWindw::~InputWindw(void)
{
	if(butn1==NULL) delete butn1;
	if(butn2==NULL) delete butn2;
}

void InputWindw::DrawWindow(void)
{
	CapTWindw::DrawWindow();
	butn1=new Button(wx+ww/2-70,wy+108,"^OK");
	butn1->DrawWindow();
	butn2=new Button(wx+ww/2+6,wy+108,"^CANCEL");
	butn2->DrawWindow();
	mouse.HideMouse();
	setfillstyle(SOLID_FILL,BLACK);
	bar(wx+15,wy+85,wx+ww-15,wy+99);
	mouse.ShowMouse();
}

void InputWindw::RunWindow(void)
{
	button=0;
	while(!button)
	{
		GetEvent(eventMsg);
		if(butn1->Clicked(eventMsg))
			button=OK;
		else if(butn2->Clicked(eventMsg))
			button=CANCEL;
		else if(eventMsg.type==KEYBD)
		{
			char k=eventMsg.key&0x00ff;
			HandleInput(k);
		}
	}
}

void InputWindw::HandleInput(char k)
{
	int l=strlen(input);
	int w=(ww-30)/8;
	settextjustify(LEFT_TEXT,TOP_TEXT);
	if((k>31)&&(k<127)&&(l<80))
	{
		input[l+1]=0;
		input[l]=k;
		setcolor(WHITE);
		if(l<w)
			outtextxy(wx+15,wy+88,input);
		else
		{
			int i=l-w+1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(wx+15,wy+85,wx+ww-15,wy+99);
			outtextxy(wx+15,wy+88,&input[i]);
		}
	}
	else if((k==BACKSP)&&(l>0))
	{
		l-=1;
		input[l]=0;
		setfillstyle(SOLID_FILL,BLACK);
		bar(wx+15,wy+85,wx+ww-15,wy+99);
		setcolor(WHITE);
		if (l<w+1)
			outtextxy(wx+15,wy+88,input);
		else
		{
			int i=l-w;
			outtextxy(wx+15,wy+88,&input[i]);
		}
	}
}

Button::Button(int x,int y,char *s) : Windw(x,y,64,32,FALSE,FALSE)
{
	strcpy(label,s);
	altkey=0;
	hotkey=0;
}

void Button::DrawWindow(void)
{
	int pos=-1;
	char tlabel[20];
	Windw::DrawWindow();
	mouse.HideMouse();
	strcpy(tlabel,label);
	for(int i=0;i<strlen(tlabel);i++)
	{
		if(tlabel[i]=='^')
		{
			pos=i;
			hotkey=ctrlkeys[tlabel[i+1]-65];
			for(int j=i;j<strlen(tlabel);++j) tlabel[j]=tlabel[j+1];
		}
	}
	if(strcmp(tlabel,"OK")==0) altkey=OKALT;
	else if (strcmp(tlabel,"CANCEL")==0) altkey=CANCELALT;
	int x=(wx+ww/2)-(strlen(tlabel)*4);
	setcolor(BLACK);
	outtextxy(x,wy+12,tlabel);
	if (pos>=0) line(x+pos*8,wy+20,x+pos*8+6,wy+20);
	mouse.ShowMouse();
}

int Button::Clicked(EventMsg eventMsg)
{
	int click=0;
	if((eventMsg.type==MBUTTON)&&(eventMsg.mx>wx)&&(eventMsg.mx<wx+ww)&&
		(eventMsg.my>wy)&&(eventMsg.my<wy+wh))
	{
		ClickButton();
		click=TRUE;
	}
	else if(eventMsg.type==KEYBD)
	{
		if((eventMsg.key==hotkey)||(eventMsg.key==altkey))
		{
			ClickButton();
			click=TRUE;
		}
	}
	return click;
}

void Button::ClickButton(void)
{
	int *buff;
	mouse.HideMouse();
	int size=imagesize(wx+2,wy+2,wx+ww-2,wy+wh-2);
	buff=(int *)malloc(size);
	if (buff)
	{
		getimage(wx+2,wy+2,wx+ww-2,wy+wh-2,buff);
		putimage(wx+3,wy+3,buff,COPY_PUT);
		free(buff);
	}
	setcolor(DARKGRAY);
	moveto(wx+ww,wy);
	lineto(wx,wy);
	lineto(wx,wy+wh);
	moveto(wx+ww-1,wy+1);
	lineto(wx+1,wy+1);
	lineto(wx+1,wy+wh-1);
	setcolor(WHITE);
	moveto(wx+1,wy+wh);
	lineto(wx+ww,wy+wh);
	lineto(wx+ww,wy);
	moveto(wx+2,wy+wh-1);
	lineto(wx+ww-1,wy+wh-1);
	lineto(wx+ww-1,wy+1);
	sound(2000);
	delay(100);
	nosound();
	DrawWindow();
	mouse.ShowMouse();
}