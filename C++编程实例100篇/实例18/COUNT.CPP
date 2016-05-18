//IMPLEMENTATION OF COUNTER CLASS
//FILE COUNT.CPP

#define MAX 65535
#include "Count.h"

void COUNTER::operator++()
{
	if (NUMBER<MAX)
		NUMBER+=10;
}

void COUNTER::operator--()
{
	if (NUMBER>0)
		NUMBER-=10;
}
void COUNTER::DISPLAY()
{
	printf("\n THE TEST COUNTER = %d",NUMBER);
}
