/*++

Copyright (c) 2004-2005  AFE(Active-Free-Elegance)

Module Name:

    table.cpp

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


#include "table.h"


CTable::CTable()
{
	m_width=m_height=0;
	m_foodNumber=m_blockNumber=0;
	m_board=NULL;
}

CTable::~CTable()
{
	if(m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	}
}

//
//// 初始化桌子
//
void CTable::InitialTable(int w,int h)
{//初始化Table

	int i,j;
	//重新设置桌子的高度与宽度
	m_width=w;
	m_height=h;

	//其他成员变量的清空性质初始化
	m_snake.Initial();
	if(m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	}

	//根据高度和宽度创建一个新的桌子
	m_board=new int*[m_height];
	for(i=0;i<h;i++)
	{
		m_board[i]=new int[m_width];
		for(j=0;j<w;j++)
			m_board[i][j]=0;
	}

	//将桌子四周设置为墙
	//将顶部跟底部的边缘设置为障碍物墙的状态
	for(i=0;i<h;i++)
	{
		m_board[i][0]=TB_STATE_SBLOCK;
		m_board[i][m_width-1]=TB_STATE_SBLOCK;
	}
	//将左部和右部的边缘设置为障碍物墙的状态
	for(i=0;i<w;i++)
	{
		m_board[0][i]=TB_STATE_SBLOCK;
		m_board[m_height-1][i]=TB_STATE_SBLOCK;
	}
}

//
//// 在某个位置放置毒果
//
bool CTable::AddBlock(int x,int y)
{

	if( (x>=0)&&(x<m_width)&&
		(y>=0)&&(y<m_height)&&
		(m_board[y][x]==TB_STATE_OK) ) 
	{
		m_board[y][x]=TB_STATE_BLOCK;
		++m_blockNumber;
		return true;
	}
	else
	{
		return false;
	}
}

//
//// 在某个位置放置水果
//
bool CTable::AddFood(int x,int y)
{
	if( (x>=0)&&(x<m_width)&&
		(y>=0)&&(y<m_height)&&
		(m_board[y][x]==TB_STATE_OK) ) 
	{
		m_board[y][x]=TB_STATE_FOOD;
		++m_foodNumber;
		return true;
	}
	else
	{
		return false;
	}
}

//
//// 清楚某个位置的果实
//
bool CTable::ClearFood(int x,int y)
{
	m_board[y][x]=TB_STATE_OK;
	return true;
}

//
//// 获取蛇对象
//
CSnake* CTable::GetSnake(void)
{
	return &m_snake;
}

//
//// 取桌子对象
//
int** CTable::GetBoard(void)
{
	return m_board;
}

//
//// 取桌子某个位置数据
//
int CTable::GetData(int x,int y)
{
	return m_board[y][x];
}

//
//// 蛇的移动
//
void CTable::SnakeMove(void)
{
	m_snake.Move();
}

//
//// 改变蛇的方向 
//
bool CTable::ChangeSnakeDirect(MoveState d)
{
	m_snake.ChangeDirect(d);
	return true;
}
