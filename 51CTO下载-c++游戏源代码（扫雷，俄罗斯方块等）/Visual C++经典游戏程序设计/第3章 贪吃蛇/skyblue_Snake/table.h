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

#define TB_STATE_OK                   0   //����
#define TB_STATE_FOOD                 1   //ʳ��
#define TB_STATE_BLOCK                2   //�ϰ�������
#define TB_STATE_SBLOCK               3   //�ϰ���ǽ

#include"snake.h"

class CTable
{
private:
	int m_width;          //���ӵĿ��
	int m_height;         //���ӵĸ߶�
	int m_foodNumber;     //ˮ������Ŀ
	int m_blockNumber;    //�ϰ���(����)����Ŀ
	CSnake m_snake;       //�����ϵ���
	int **m_board;          //�������
	
public:
	CTable();
	~CTable();

	//��ʼ���������
	void InitialTable(int w,int h);
	
	//ʳ��Ĳ���
	bool AddBlock(int x,int y);
	bool AddFood(int x,int y);
	bool ClearFood(int x,int y);

	//�����ȡ
	CSnake* GetSnake(void);
	int** GetBoard(void);
	int GetData(int x,int y);

	//�ߵĲ���
	void SnakeMove(void);
	bool ChangeSnakeDirect(MoveState d);
};

#endif //_GAME_TABLE_