#include "Tree.h"

void TREE::BUILD_TREE(NODE *&Root,int Data)
{
	NODE *TEMP;
	NODE *BACKTEMP;
	if(Root == 0)
	{
		Root=new NODE;
		Root->LEFT=Root->RIGHT=0;
		Root->DATA=Data;
	}
	else
	{
			TEMP=Root;
			while(TEMP!=0)
			{
					BACKTEMP=TEMP;
					if(Data<(TEMP->DATA)) TEMP=TEMP->LEFT;
					else TEMP=TEMP->RIGHT;
			}
			if(Data<(BACKTEMP->DATA))
			{
				NODE *NEWNODE=new NODE;
				NEWNODE->LEFT=NEWNODE->RIGHT=0;
				NEWNODE->DATA=Data;
				BACKTEMP->LEFT=NEWNODE;

			}
			else
			{
				NODE *NEWNODE=new NODE;
				NEWNODE->LEFT=NEWNODE->RIGHT=0;
				NEWNODE->DATA=Data;
				BACKTEMP->RIGHT=NEWNODE;
			}
	}
}

void TREE::LR_PREORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		printf("%d  ",Root->DATA);
		LR_PREORDER(Root->LEFT);
		LR_PREORDER(Root->RIGHT);
	}
}

void TREE::LR_INORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		LR_INORDER(Root->LEFT);
		printf("%d  ",Root->DATA);
		LR_INORDER(Root->RIGHT);
	}
}

void TREE::LR_POSTORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		LR_POSTORDER(Root->LEFT);
		LR_POSTORDER(Root->RIGHT);
		printf("%d  ",Root->DATA);
	}
}

void TREE::RL_PREORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		printf("%d  ",Root->DATA);
		RL_PREORDER(Root->RIGHT);
		RL_PREORDER(Root->LEFT);
	}
}

void TREE::RL_INORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		RL_INORDER(Root->RIGHT);
		printf("%d  ",Root->DATA);
		RL_INORDER(Root->LEFT);
	}
}

void TREE::RL_POSTORDER(NODE *Root)
{
	if(Root!=NULL)
	{
		RL_POSTORDER(Root->RIGHT);
		RL_POSTORDER(Root->LEFT);
		printf("%d  ",Root->DATA);
	}
}