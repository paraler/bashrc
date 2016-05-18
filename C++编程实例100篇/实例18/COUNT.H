//INTERFACE TO COUNTER CLASS WITH THE OVERLOADED OPERATORS
//FILE COUNT.H

#include <stdio.h>

class COUNTER
{
	private :
			unsigned int NUMBER;
	public :
			COUNTER()
			{
				NUMBER=0;
			}
			void operator++();
			void operator--();
			void DISPLAY();
};