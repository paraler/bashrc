//THE PROGRAM IS TO HELP YOU HOW THE 3D FORMED .
//FILE 3DDEMO.CPP

#include   <stdlib.h>
#include    <conio.h>
#include <iostream.h>
#include <graphics.h>

void INIT(void);
void DRAW(void);

int main(void)
{
	INIT();
	DRAW();
	getch();
	return 0;
}

void DRAW()
{
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(100,100,300,240);
	setcolor(WHITE);
	moveto(120,160);
	lineto(120,120);
	lineto(279,120);
	setcolor(BLACK);
	moveto(120,160);
	lineto(279,160);
	lineto(279,120);
	moveto(120,220);
	lineto(120,180);
	lineto(279,180);
	setcolor(WHITE);
	moveto(120,220);
	moveto(279,220);
	lineto(279,180);
}

void INIT()
{
	int GDRIVER=DETECT,GMODE,ERROR;
	initgraph(&GDRIVER,&GMODE,"D:\\TOOLS\\TC3.0\\BGI");
	ERROR=graphresult();
	if (ERROR!=grOk)
	{
		cout<<"INIT GRAPHICS ERROR (CHANGE THE PATH) : "<<ERROR<<"\n";
		getch();
		abort();
	}
}