//File Mouse.H

#ifndef_MOUSE_H
#define_MOUSE_H

#include <dos.h>
#include <conio.h>

#define LEFT 1
#define RIGHT 2
#define CENTER 3

//The Mouse Class Declaration.
class Mouse
{
	private :
				int mx,my;
				int got_mouse;
				int num_buttons;
				int button;
				REGS inRegs;
				REGS outRegs;
	public :
			Mouse(void);
			~Mouse(void);
			int GotMouse(void){return got_mouse;}
			void SetLimits(int minXLimit,int maxXLimit,int minYLimit,
						  int maxYLimit);
			void ShowMouse(void);
			void HideMouse(void);
			int Event(void);
			int GetButton(void){return button;}
			void GetXY(int &x,int &y){x=mx;y=my;}
			void ButtonUp(void);
};

extern Mouse mouse;

#endif

Mouse::Mouse(void)
{
	got_mouse=0;
	if (getvect(0x33))
	{
		inRegs.x.ax=0x0000;
		int86(0x33,&inRegs,&outRegs);
		got_mouse=outRegs.x.ax;
		num_buttons=outRegs.x.bx;
	}
}

Mouse::~Mouse(void)
{
	inRegs.x.ax=0x0000;
	int86(0x33,&inRegs,&outRegs);
}

void Mouse::SetLimits(int minXLimit,int maxXLimit,int minYLimit,int maxYLimit)
{
	if (!got_mouse) return;
	inRegs.x.ax=0x0007;
	inRegs.x.cx=minXLimit;
	inRegs.x.dx=maxXLimit;
	int86(0x33,&inRegs,&outRegs);
	inRegs.x.ax=0x0008;
	inRegs.x.cx=minYLimit;
	inRegs.x.dx=maxYLimit;
	int86(0x33,&inRegs,&outRegs);
}

void Mouse::ShowMouse(void)
{
	if (!got_mouse) return;
	inRegs.x.ax=0x0001;
	int86(0x33,&inRegs,&outRegs);
}

void Mouse::HideMouse(void)
{
	if (!got_mouse) return;
	inRegs.x.ax=0x0002;
	int86(0x33,&inRegs,&outRegs);
}

int Mouse::Event(void)
{
	if (!got_mouse) return 0;
	inRegs.x.ax=0x0003;
	int86(0x33,&inRegs,&outRegs);
	button=outRegs.x.bx;
	mx=outRegs.x.cx;
	my=outRegs.x.dx;
	if (button) return 1;
	else return 0;
}

void Mouse::ButtonUp(void)
{
	while (button) Event();
}
