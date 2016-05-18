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

int TREE::SEARCH_TREE(NODE *Root,int Data)
{
	NODE *TEMP;
	TEMP=Root;
	while((TEMP!=0)&&(TEMP->DATA!=Data))
	{
		if(Data<TEMP->DATA)
		{
			TEMP=TEMP->LEFT;
		}
		else
		{
			TEMP=TEMP->RIGHT;
		}
	}
	if(TEMP->DATA==Data)
	{
		printf("Find it!!!");
		return(0);
	}
	else
	{
		printf("Can not find it!!!.It isn't in this TREE!!!");
		return(1);
	}
}

void TREE::DISPLAY_TREE(NODE *Root)
{
	if(Root!=NULL)
	{
		DISPLAY_TREE(Root->LEFT);
		printf("%d  ",Root->DATA);
		DISPLAY_TREE(Root->RIGHT);
	}
}