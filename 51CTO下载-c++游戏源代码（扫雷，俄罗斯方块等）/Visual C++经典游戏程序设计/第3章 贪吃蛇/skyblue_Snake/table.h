/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    table.h

Abstract:

 the table class:
	1. the table envirement configuration
	2. set and clear the food(good ones and bad ones)
	3. call the snake instance to move

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#ifndef _GAME_TABLE_
#define _GAME_TABLE_

#define TB_STATE_OK                   0   //正常
#define TB_STATE_FOOD                 1   //食物
#define TB_STATE_BLOCK                2   //障碍－毒果
#define TB_STATE_SBLOCK               3   //障碍－墙

#include"snake.h"

class CTable
{
private:
	int m_width;          //桌子的宽度
	int m_height;         //桌子的高度
	int m_foodNumber;     //水果的数目
	int m_blockNumber;    //障碍物(毒果)的数目
	CSnake m_snake;       //桌子上的蛇
	int **m_board;          //桌子面板
	
public:
	CTable();
	~CTable();

	//初始化桌子面板
	void InitialTable(int w,int h);
	
	//食物的操作
	bool AddBlock(int x,int y);
	bool AddFood(int x,int y);
	bool ClearFood(int x,int y);

	//物件获取
	CSnake* GetSnake(void);
	int** GetBoard(void);
	int GetData(int x,int y);

	//蛇的操作
	void SnakeMove(void);
	bool ChangeSnakeDirect(MoveState d);
};

#endif //_GAME_TABLE_