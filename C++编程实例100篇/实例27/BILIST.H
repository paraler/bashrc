//THIS HEAD FILE DEFINES A "DOUBLE DIRECTION LIST" CLASS
//FILE BILIST.H

#include <stdio.h>

class NODE
{
	//FRIEND CLASS "LIST" CAN HAVE ACCESS TO THE CLASS "NODE" 'S PRIVATE PART
	friend class LIST;
	private :
			//PREVIOUS NODE LINK
			NODE *PREVIOUS;
			//NEXT NODE LINK
			NODE *NEXT;
			//THE CURRENT NODE DATA
			int DATA;
};

class LIST
{
	private :
			//THE HEAD OF THE LIST
			NODE *HEAD;
			//THE TAIL OF THE LIST
			NODE *TAIL;
	public :
			//CONSTRUCTOR FUNCTION
			LIST()
			{
				//INITIAL
				HEAD=0;
				TAIL=0;
			}
			//ADD TO THE BACK OF THE LIST
			void Build_HT(int Data);
			//ADD TO THE FRONT OF THE LIST
			void Build_TH(int Data);
			//DISPLAY THE DATA OF THE LIST FROM HEAD TO TAIL
			void LIST::DISPLAY_HT();
			//DISPLAY THE DATA OF THE LIST FROM TAIL TO HEAD
			void LIST::DISPLAY_TH();
			//REMOVE ALL THE NODES IN THE LIST
			void CLEAR();
			~LIST()
			{
				CLEAR();
			}
};