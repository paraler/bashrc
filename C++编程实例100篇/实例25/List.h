//THIS HEAD FILE ONLY DEFINES A "SINGLE DIRECTION LIST" CLASS
//FILE LIST.H

#include <stdio.h>

class NODE
{
	//FRIEND CLASS "LIST" CAN HAVE ACCESS TO THE CLASS "NODE" 'S PRIVATE PART
	friend class LIST;
	private :
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
	public :
			//CONSTRUCTOR FUNCTION
			LIST()
			{
				//INITIAL
				HEAD=0;
			}
			//ADD TO THE FRONT OF THE LIST
			void Build_Forward(int Data);
			//ADD TO THE BACK OF THE LIST
			void Build_Backward(int Data);
			//GET THE HEAD OF THE LIST
			NODE* GET_HEAD();
			//GET THE DATA OF THE LIST
			int LIST::GET_NEXT(NODE * &TEMP);
			//GET THE DATA IN THE GIVED POSITION
			int LIST::GET_POSITION(int P);
			//REMOVE ALL THE NODES IN THE LIST
			void CLEAR();
			~LIST()
			{
				CLEAR();
			}
};