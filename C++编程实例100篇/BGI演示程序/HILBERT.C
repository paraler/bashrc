#include "dos.h"
#define n 6
#define h0 256
int h,x,y;

main()
{
 int x0,y0,i;

     init();
   h=h0;x0=h/2;y0=x0;
   for(i=1;i<=n;i++)
    {h/=2;
     x0+=h/2;
     y0+=h/2;
     x=x0+150;y=y0+100;
     if(i==3) a(i,i+2);
     else a(i,i);
    }
    getch();
    grclose();
}

int init()
{union REGS r;

 r.x.ax=0x0012;
 int86(0x10,&r,&r);

  r.h.ah=0x0b;
  r.h.bh=0x00;
  r.h.bl=7;
  int86(0x10,&r,&r);
  r.h.ah=0x0b;
  r.h.bh=0x01;
  r.h.bl=0x0;
  int86(0x10,&r,&r);

  return 0;
}
int a(int i,int color)
{
 int j;
 if(i>0)
 {
   d(i-1,color);for(j=1;j<=h;j++) {dot(color,x-j,y);delay(5);}x-=h;
   a(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y-j);delay(5);}y-=h;
   a(i-1,color);for(j=1;j<=h;j++) {dot(color,x+j,y);delay(5);}x+=h;
   b(i-1,color);
 }
   return x;
}

int b(int i,int color)
{int j;
  if(i>0)
  {
   c(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y+j);delay(5);}y+=h;
   b(i-1,color);for(j=1;j<=h;j++) {dot(color,x+j,y);delay(5);}x+=h;
   b(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y-j);delay(5);}y-=h;
   a(i-1,color);
  }
  return x;
}

int c(int i,int color)
{int j;
    if(i>0)
      {b(i-1,color);for(j=1;j<=h;j++) {dot(color,x+j,y);delay(5);}x+=h;
       c(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y+j);delay(5);}y+=h;
       c(i-1,color);for(j=1;j<=h;j++) {dot(color,x-j,y);delay(5);}x-=h;
       d(i-1,color);
      }
     return x;
}
int d(int i,int color)
{int j;
  if(i>0)
  {
     a(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y-j);delay(5);}y-=h;
     d(i-1,color);for(j=1;j<=h;j++) {dot(color,x-j,y);delay(5);}x-=h;
     d(i-1,color);for(j=1;j<=h;j++) {dot(color,x,y+j);delay(5);}y+=h;
     c(i-1,color);
  }
  return x;
}

int dot(int color,int x,int y)
{union REGS r;
      r.h.ah=0x0c;
      r.h.bh=0;
      r.h.al=color;
      r.x.cx=x;
      r.x.dx=y;
      int86(0x10,&r,&r);
      return 0;
}

int grclose()
{union REGS r;
 r.x.ax=0x0003;
 int86(0x10,&r,&r);
}
