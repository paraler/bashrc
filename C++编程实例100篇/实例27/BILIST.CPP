//THE IMPLEMENTATION OF THE CLASS "LIST"
//FILE BILIST.CPP

#include "BILIST.H"

void LIST::Build_HT(int Data)
{
	NODE *BUFFER;

	BUFFER=new NODE;
	BUFFER->DATA=Data;
	if(HEAD==0)
	{
		HEAD=BUFFER;
		HEAD->NEXT=0;
		HEAD->PREVIOUS=0;
		TAIL=HEAD;
	}
	else
	{
		 TAIL->NEXT=BUFFER;
		 BUFFER->PREVIOUS=TAIL;
		 BUFFER->NEXT=0;
		 TAIL=BUFFER;
	}
}
void LIST::Build_TH(int Data)
{
	NODE *NEWNODE;
	NEWNODE=new NODE;
	NEWNODE->DATA=Data;

	if(TAIL==0)
	{
		TAIL=NEWNODE;
		TAIL->NEXT=0;
		TAIL->PREVIOUS=0;
		HEAD=TAIL;
	}
	else
	{
		NEWNODE->PREVIOUS=0;
		NEWNODE->NEXT=HEAD;
		HEAD->PREVIOUS=NEWNODE;
		HEAD=NEWNODE;
	}
}

void LIST::DISPLAY_HT()
{
	NODE *TEMP;
	TEMP=HEAD;
	printf("\nDISPLAY THE LIST FROM HEAD TO TAIL:\n");
	while(TEMP!=0)
	{
		printf("%d  ",TEMP->DATA);
		TEMP=TEMP->NEXT;
	}
}
void LIST::DISPLAY_TH()
{
	NODE *TEMP;
	TEMP=TAIL;
	printf("\nDISPLAY THE LIST FROM TAIL TO HEAD:\n");
	while(TEMP!=0)
	{
		printf("%d  ",TEMP->DATA);
		TEMP=TEMP->PREVIOUS;
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