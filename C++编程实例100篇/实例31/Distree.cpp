//THE PROGRAM IS TO TEST THE CLASS "TREE" & CLASS "NODE"
//FILE TREETEST.CPP

#include  <string.h>
#include  <stdio.h>
#include  <conio.h>
#include  <process.h>
#include  <stdlib.h>
#include   "Tree.h"

void EXIT(void);

void main(void)
{
	TREE BTREE;
	NODE *TREE_ROOT=0;
	int CHOICE;
	int NUM;
	BTREE.BUILD_TREE(TREE_ROOT,10);
	BTREE.BUILD_TREE(TREE_ROOT,18);
	BTREE.BUILD_TREE(TREE_ROOT,32);
	BTREE.BUILD_TREE(TREE_ROOT,16);
	BTREE.BUILD_TREE(TREE_ROOT,3);
	BTREE.BUILD_TREE(TREE_ROOT,77);
	BTREE.BUILD_TREE(TREE_ROOT,200);
	while(1)
	{
	clrscr();
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n"
			  "         	THE  DISPLAY FOR THE TREE\n"
			  "\n"
			  "            1 : PREORDER  	(LEFT TO RIGHT)\n"
			  "            2 : INORDER 	(LEFT TO RIGHT)\n"
			  "            3 : POSTORDER	(LEFT TO RIGHT)\n"
			  "            4 : PREORDER  	(RIGHT TO LEFT)\n"
			  "            5 : INORDER 	(RIGHT TO LEFT)\n"
			  "            6 : POSTORDER	(RIGHT TO LEFT)\n"
			  "            7 : EXIT\n"
			  "\n");
	do
	{
		printf("\n		PLEASE ENTER YOUR CHOICE :");
		CHOICE=getch();
		putch(CHOICE);
	}while((CHOICE<'1')||(CHOICE>'7'));
	printf("\n\n");
	switch (CHOICE)
		{
			case '1' :	BTREE.LR_PREORDER(TREE_ROOT);
						break;
			case '2' :     BTREE.LR_INORDER(TREE_ROOT);
						break;
			case '3' :	BTREE.LR_POSTORDER(TREE_ROOT);
						break;
			case '4' :	BTREE.RL_PREORDER(TREE_ROOT);
						break;
			case '5' :	BTREE.RL_INORDER(TREE_ROOT);
						break;
			case '6' :	BTREE.RL_POSTORDER(TREE_ROOT);
						break;
			case '7' :     printf("Press any key to EXIT... ...");
						getch();
						EXIT();
						break;
		}
	printf("\n\n\n Press any key to return to the main menu... ...");
	getch();
	}
}

void EXIT(void)
{
	exit(0);
}