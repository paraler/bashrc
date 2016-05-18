/* Svga64k.bgi 测试文件 */

#include "graphics.h"
#include "Svga64k.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "malloc.h"
#include "io.h"

int huge Return_SVGA64K(void)
{
 return(0); /* 返回各种分辨率的对应编号 0～6 宏定义参见 Svga64k.h */
}

typedef struct    /*16Mrgb像素类型*/
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

    installuserdriver("Svga64K",Return_SVGA64K);/*对于svga64k必需执行该函数以安装BGI驱动*/
    initgraph(&gd,&gm,"");/* 执行TC默认的BGI初始化函数 */

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
