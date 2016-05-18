//THE FILE INCLUDES THE CLASS "NODE" "LIST" "STACK" "QUEUE"
//FILE STACK.H

#include    <stdio.h>
#include    <conio.h>
#include <iostream.h>

class NODE
{
	friend class LIST;
	private:
			NODE *NEXT;
			int  DATA;
};

class LIST
{
	private:
			NODE *HEAD;				//Head of list
	public:
			LIST()
			{
				HEAD=0;
			}
			void FORWARD_ADD(int Data);
			void BACKWARD_ADD(int Data);      //Add to the tail of the list
			int  GET();			  //Remove the head of the list
			~LIST(){};
};

void LIST::FORWARD_ADD(int Data)
{
	NODE *BUFFER;
	BUFFER=new NODE;
	BUFFER->DATA=Data;
	if (HEAD==0)      /*Add an head node*/
	{
		BUFFER->NEXT=0;    /**/
		HEAD=BUFFER;
	}
	else              /*Add one node in the head*/
	{
		BUFFER->NEXT=HEAD;
		HEAD=BUFFER;
	}
}
void LIST::BACKWARD_ADD(int Data)
{
	NODE *NEWNODE;
	NODE *TEMP;
	NODE *PREVIOUS;

	if (HEAD==0)
	{
		HEAD=new NODE;
		HEAD->DATA=Data;
		HEAD->NEXT=0;
	}
	else /*HEAD != 0*/
	{
		/*search for the last node*/
		TEMP=HEAD->NEXT;
		PREVIOUS=HEAD;
		while (TEMP!=0)
		{
			PREVIOUS=TEMP;
			TEMP=TEMP->NEXT;
		}
		/*Go to the end.And add a new one.*/
		NEWNODE=new NODE;
		NEWNODE->DATA=Data;
		NEWNODE->NEXT=0;
		PREVIOUS->NEXT=NEWNODE;
	}
}

int LIST::GET()
{
	int Data;
	NODE *PREVIOUS;
	if (HEAD==0)
	{
		printf("\n\n The stack is EMPTY!");
		return 0;
	}
	else
	{
		PREVIOUS=HEAD;
		Data=HEAD->DATA;
		HEAD=HEAD->NEXT;
		delete PREVIOUS;
		return Data;
	}
}