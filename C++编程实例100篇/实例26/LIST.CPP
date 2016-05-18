//THE IMPLEMENTATION OF THE CLASS "LIST"
//FILE LIST.CPP

#include "List.h"


NODE* LIST::GET_HEAD()
{
	return (HEAD);
}

void LIST::DISPLAY(NODE *TEMP)
{
	if (HEAD==0)
	{
		printf("----Sorry!!!  It's EMPTY !!! ");
	}
	else
	{
		while(TEMP!=0)
		{
			printf("%d ",TEMP->DATA);
			TEMP=TEMP->NEXT;
		}
	}
}
void LIST::INSERT(int Data)
{
	NODE *TEMP=HEAD;
	NODE *PREVIOUS;
	NODE *NEWNODE;

	NEWNODE=new NODE;
	NEWNODE->DATA=Data;
	NEWNODE->NEXT=0;

	if(HEAD==0)
	{
		HEAD=NEWNODE;
	}
	else
	{
		while(((TEMP->DATA)<=Data)&&(TEMP!=0))
		{

		   PREVIOUS=TEMP;
		   TEMP=TEMP->NEXT;
		}
		if(TEMP==HEAD)
		{
			NEWNODE->NEXT=HEAD;
			HEAD=NEWNODE;
		}
		else
		{
			NEWNODE->NEXT=TEMP;
			PREVIOUS->NEXT=NEWNODE;
		}
	}
}
void LIST::CLEAR()
{
	NODE *TEMP_HEAD=HEAD;

	if (TEMP_HEAD==0) return;
	do
	{
		NODE *TEMP_NODE=TEMP_HEAD;
		TEMP_HEAD=TEMP_HEAD->NEXT;
		delete TEMP_NODE;
	}
	while (TEMP_HEAD!=0);
}