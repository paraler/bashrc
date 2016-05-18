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
//// ��ʼ������
//
void CTable::InitialTable(int w,int h)
{//��ʼ��Table

	int i,j;
	//�����������ӵĸ߶�����
	m_width=w;
	m_height=h;

	//������Ա������������ʳ�ʼ��
	m_snake.Initial();
	if(m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	}

	//���ݸ߶ȺͿ�ȴ���һ���µ�����
	m_board=new int*[m_height];
	for(i=0;i<h;i++)
	{
		m_board[i]=new int[m_width];
		for(j=0;j<w;j++)
			m_board[i][j]=0;
	}

	//��������������Ϊǽ
	//���������ײ��ı�Ե����Ϊ�ϰ���ǽ��״̬
	for(i=0;i<h;i++)
	{
		m_board[i][0]=TB_STATE_SBLOCK;
		m_board[i][m_width-1]=TB_STATE_SBLOCK;
	}
	//���󲿺��Ҳ��ı�Ե����Ϊ�ϰ���ǽ��״̬
	for(i=0;i<w;i++)
	{
		m_board[0][i]=TB_STATE_SBLOCK;
		m_board[m_height-1][i]=TB_STATE_SBLOCK;
	}
}

//
//// ��ĳ��λ�÷��ö���
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
//// ��ĳ��λ�÷���ˮ��
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
//// ���ĳ��λ�õĹ�ʵ
//
bool CTable::ClearFood(int x,int y)
{
	m_board[y][x]=TB_STATE_OK;
	return true;
}

//
//// ��ȡ�߶���
//
CSnake* CTable::GetSnake(void)
{
	return &m_snake;
}

//
//// ȡ���Ӷ���
//
int** CTable::GetBoard(void)
{
	return m_board;
}

//
//// ȡ����ĳ��λ������
//
int CTable::GetData(int x,int y)
{
	return m_board[y][x];
}

//
//// �ߵ��ƶ�
//
void CTable::SnakeMove(void)
{
	m_snake.Move();
}

//
//// �ı��ߵķ��� 
//
bool CTable::ChangeSnakeDirect(MoveState d)
{
	m_snake.ChangeDirect(d);
	return true;
}
