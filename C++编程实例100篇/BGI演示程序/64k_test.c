/* Svga64k.bgi �����ļ� */

#include "graphics.h"
#include "Svga64k.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "malloc.h"
#include "io.h"

int huge Return_SVGA64K(void)
{
 return(0); /* ���ظ��ֱַ��ʵĶ�Ӧ��� 0��6 �궨��μ� Svga64k.h */
}

typedef struct    /*16Mrgb��������*/
{unsigned char b;
 unsigned char g;
 unsigned char r;
}rgb16M;

void putpoint65536(int x,int y,rgb16M color)
{
 setrgbpalette(1026,color.r>>3,color.g>>2,color.b>>3);
 putpixel(x,y,0);
}

void main()
{
    int width,height,gd=DETECT,gm=0;
    int i,j;
    rgb16M rgb;
    char r,g,b;

    installuserdriver("Svga64K",Return_SVGA64K);/*����svga64k����ִ�иú����԰�װBGI����*/
    initgraph(&gd,&gm,"");/* ִ��TCĬ�ϵ�BGI��ʼ������ */

 width = getmaxx();height = getmaxy();
 for(i=0;i<width;i++)
   for(j=0;j<height;j++)
   {
       rgb.r = random(256);
       rgb.g = random(256);
       rgb.b = random(256);
       putpoint65536(i,j,rgb);
   }

 getch();
 closegraph();
}
