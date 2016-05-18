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
			void TREE::LR_PREORDER(NODE *Root);
			void TREE::LR_INORDER(NODE *Root);
			void TREE::LR_POSTORDER(NODE *Root);
			void TREE::RL_PREORDER(NODE *Root);
			void TREE::RL_INORDER(NODE *Root);
			void TREE::RL_POSTORDER(NODE *Root);
			~TREE(){}
};