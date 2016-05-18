//INTERFACE TO THE BINARY TREE
//FILE TREE.H

#include<conio.h>
#include<stdio.h>
class NODE
{
	friend class TREE;
	private:
			int DATA;
			NODE *LEFT;
			NODE *RIGHT;
};
class TREE
{
	private:
			NODE *ROOT;
	public:
			TREE()
			{
				ROOT=0;
			}
			void BUILD_TREE(NODE *&Root,int Data);
			int SEARCH_TREE(NODE *Root,int Data);
			void TREE::DISPLAY_TREE(NODE *Root);
			~TREE(){}
};