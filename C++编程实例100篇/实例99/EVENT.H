//File Event.h

#include <bios.h>
#include "Mouse.h"

#define MBUTTON 1
#define KEYBD   2
#define CR     13
#define ESC    27
#define BACKSP  8

struct EventMsg
{
	int type,mx,my,button;
	unsigned key;
};

int KeyEvent(void)
{
	int key=bioskey(1);
	if (key)key=bioskey(0);
	return key;
}

void GetEvent(EventMsg&eventMsg)
{
	/*while ((!mouse.Event())&&(!(eventMsg.key=KeyEvent()))){}*/
	//******************************************Corresponding The Above Line
	if((!mouse.Event())&&(!(eventMsg.key=KeyEvent()))){}
	//******************************************Corresponding The Above Line
	eventMsg.button=mouse.GetButton();
	if (eventMsg.button)
	{
		eventMsg.type=MBUTTON;
		mouse.GetXY(eventMsg.mx,eventMsg.my);
	}
	else
	{
		eventMsg.type=KEYBD;
		eventMsg.mx=-1;
		eventMsg.my=-1;
	}
}