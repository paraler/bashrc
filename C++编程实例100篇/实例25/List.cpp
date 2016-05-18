//THE IMPLEMENTATION OF THE CLASS "LIST"
//FILE LIST.CPP

#include "List.h"

void LIST::Build_Forward(int Data)
{
	NODE *BUFFER;

	BUFFER=new NODE;
	BUFFER->DATA=Data;
	if (HEAD)
	{
		BUFFER->NEXT=HEAD;
		HEAD=BUFFER;
	}
	else
	{
		BUFFER->NEXT=0;
		HEAD=BUFFER;
	}
}

void LIST::Build_Backward(int Data)
{
	NODE *PREVIOUS,*CURRENT,*NEWNODE;

	if (HEAD)
	{
		PREVIOUS=HEAD;
		CURRENT=HEAD->NEXT;
		while (CURRENT!=0)
			{
				PREVIOUS=CURRENT;
				CURRENT=CURRENT->NEXT;
			}
		NEWNODE=new NODE;
		NEWNODE->DATA=Data;
		NEWNODE->NEXT=0;
		PREVIOUS->NEXT=NEWNODE;
	}
	else
	{
		HEAD=new NODE;
		HEAD->DATA=Data;
		HEAD->NEXT=0;
	}
}

NODE* LIST::GET_HEAD()
{
	return (HEAD);
}

int LIST::GET_NEXT(NODE * &TEMP)
{
	if (HEAD==0)
	{
		printf("----Sorry!!!  It's EMPTY !!! ");
		return(NULL);
	}
	else
	{
		int BUFFER;
		BUFFER=TEMP->DATA;
		TEMP=TEMP->NEXT;
		return BUFFER;
	}
}

int LIST::GET_POSITION(int P)
{
	NODE *CURRENT;
	int BUFFER=0;
	int COUNTER=1;
	if (HEAD)
	{
		CURRENT=HEAD;
		while ((CURRENT!=0)&&(COUNTER!=P)&&(P>=COUNTER))
		{
			CURRENT=CURRENT->NEXT;
			COUNTER++;
		}
		if(P<COUNTER)
		{
			printf("\nSorry,can not find the position you gived.");
			printf("\nThe position you gived is too small!");
			return(NULL);
		}
		else if(CURRENT==0)
		{
			printf("\nSorry,can not find the position you gived.");
			printf("\nThe position number is too BIG! ");
			return(NULL);
		}
		else //CURRENT!=0
		{
			BUFFER=CURRENT->DATA;
			return(BUFFER);
		}
	}
	else
	{
		printf("\nSorry,can not find the position you gived.");
		printf("\nThe list is EMPTY! ");
		return(NULL);
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