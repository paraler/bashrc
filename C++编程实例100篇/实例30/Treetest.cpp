//THE PROGRAM IS TO TEST THE CLASS "TREE" & CLASS "NODE"
//FILE TREETEST.CPP

#include <string.h>
#include  <stdio.h>
#include  <conio.h>
#include   "Tree.h"

int main(void)
{
	TREE BTREE;
	NODE *TREE_ROOT=0;
	int NUM;
	clrscr();
	BTREE.BUILD_TREE(TREE_ROOT,10);
	BTREE.BUILD_TREE(TREE_ROOT,18);
	BTREE.BUILD_TREE(TREE_ROOT,32);
	BTREE.BUILD_TREE(TREE_ROOT,16);
	BTREE.BUILD_TREE(TREE_ROOT,3);
	BTREE.BUILD_TREE(TREE_ROOT,77);
	BTREE.BUILD_TREE(TREE_ROOT,200);
	printf("\nTO DISPLAY THE TREE (INORDER):");
	BTREE.DISPLAY_TREE(TREE_ROOT);
	printf("\n\nNow,you can search a number in the tree!");
	printf("\n\nWhat number do you want to search? Input it:");
	scanf("%d",&NUM);
	printf("\n");
	BTREE.SEARCH_TREE(TREE_ROOT,NUM);
	getch();
	return 0;
}