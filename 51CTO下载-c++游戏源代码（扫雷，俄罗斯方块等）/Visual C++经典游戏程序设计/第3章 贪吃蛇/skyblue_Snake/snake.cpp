/*++

Copyright (c) 2004-2005  AFE(Active-Free-Elegance)

Module Name:

    snake.cpp

Abstract:

    the class of Snake,including the basic-method 
	such as : move,born,and eat,and so on.

Author:


    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "snake.h"

CSnake::CSnake(int x_pos,int y_pos,int len)
{
	if(len<1) len=1;
	int i;

	m_length=len;  //蛇的身体体长

	//初始化蛇的坐标位置
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x_pos;m_pPos[0].y=y_pos;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//初始化蛇的运动状态
	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	//初始化蛇的位图显示状态
	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
}

CSnake::~CSnake()
{
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);
}

//
//根据新旧两个身体的运动趋势情况，返回当前应当显示的身体状态
//
BitmapState CSnake::GetRightState(MoveState oldDirect,MoveState newDirect)
{
	BitmapState res;
	switch(oldDirect)
	{
	case S_NONE:
		switch(newDirect)
		{
		case S_NONE:
			res=M_NONE;
			break;
		case S_UP:
			res=M_UP_UP;
			break;
		case S_DOWN:
			res=M_DOWN_DOWN;
			break;
		case S_LEFT:
			res=M_LEFT_LEFT;
			break;
		case S_RIGHT:
			res=M_RIGHT_RIGHT;
			break;
		}
		break;
	case S_UP:
		switch(newDirect)
		{
		case S_UP:
			res=M_UP_UP;
			break;
		case S_LEFT:
			res=M_UP_LEFT;
			break;
		case S_RIGHT:
			res=M_UP_RIGHT;
			break;
		}
		break;
	case S_DOWN:
		switch(newDirect)
		{
		case S_DOWN:
			res=M_DOWN_DOWN;
			break;
		case S_LEFT:
			res=M_DOWN_LEFT;
			break;
		case S_RIGHT:
			res=M_DOWN_RIGHT;
			break;
		}
		break;
	case S_LEFT:
		switch(newDirect)
		{
		case S_LEFT:
			res=M_LEFT_LEFT;
			break;
		case S_UP:
			res=M_LEFT_UP;
			break;
		case S_DOWN:
			res=M_LEFT_DOWN;
			break;
		}
		break;
	case S_RIGHT:
		switch(newDirect)
		{
		case S_RIGHT:
			res=M_RIGHT_RIGHT;
			break;
		case S_UP:
			res=M_RIGHT_UP;
			break;
		case S_DOWN:
			res=M_RIGHT_DOWN;
			break;
		}
		break;
	}
	return res;
}

//
//改变方向
//
void CSnake::ChangeDirect(MoveState d)
{
  //  改变方向的条件：非对立方向
  //  只能为其左，前，右方
	switch(d)
	{
	case S_NONE:
		m_newSnake.head=d;
		break;
	case S_UP:
		if(m_newSnake.head!=S_DOWN) m_newSnake.head=d;
		break;
	case S_DOWN:
		if(m_newSnake.head!=S_UP) m_newSnake.head=d;
		break;
	case S_LEFT:
		if(m_newSnake.head!=S_RIGHT) m_newSnake.head=d;
		break;
	case S_RIGHT:
		if(m_newSnake.head!=S_LEFT) m_newSnake.head=d;
		break;
	}
}

//
//蛇移动
//
void CSnake::Move(void)
{
	int i;
	//1.计算新状态各个节点的状态
	//保存蛇身体各个部位的形状
	for(i=0;i<m_length;i++)
	{
		m_oldSnake.body[i]=m_newSnake.body[i];
	}	

	//将蛇身体的状态根据前面的状态变动一次
	m_newSnake.tail=m_newSnake.body[m_length-1];
	for(i=m_length-1;i>0;i--)
	{
		m_newSnake.body[i]=m_newSnake.body[i-1];
	}
	m_newSnake.body[0]=m_newSnake.head;	
	
	//根据新旧状态特性取正确的状态
	m_pStateArray[0]=GetRightState(m_oldSnake.head,m_newSnake.head);
	for(i=0;i<m_length;i++)
		m_pStateArray[i+1]=GetRightState(m_oldSnake.body[i],m_newSnake.body[i]);
	m_pStateArray[m_length+1]=GetRightState(m_oldSnake.tail,m_newSnake.tail);


	//2.将整个蛇的坐标移动
	//除蛇头外，其他部分的新位置为其前一部分的原来位置
	for(i=m_length+1;i>0;i--)
		m_pPos[i]=m_pPos[i-1];
	//蛇头的新位置根据蛇的运动方向判断做相应偏移
	switch(m_newSnake.head)
	{
	case S_UP:
		m_pPos[0].y-=SNAKE_MOVE;
		break;
	case S_DOWN:
		m_pPos[0].y+=SNAKE_MOVE;
		break;
	case S_LEFT:
		m_pPos[0].x-=SNAKE_MOVE;
		break;
	case S_RIGHT:
		m_pPos[0].x+=SNAKE_MOVE;
		break;
	}

}

//
//蛇的身体增长
//
void CSnake::AddBody(int n)
{

//  分配临时的"save类型"变量，用作保留
//  蛇的各种数据状态
	int i;
	Snake_Struct saveOldSnake,saveNewSnake;
	BitmapState *savestateArray;
	SPoint *savePos;

	//保存蛇的位置信息 
	// pos
	savePos=new SPoint[m_length+2];
	for(i=0;i<m_length+2;i++)
		savePos[i]=m_pPos[i];

	//保存蛇的状态信息
	//  1.oldSnake
	//  2.newSnake
	//  3.stateArray

	//1
	saveOldSnake.head=m_oldSnake.head;
	saveOldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
		saveOldSnake.body[i]=m_oldSnake.body[i];
	saveOldSnake.tail=m_oldSnake.tail;
	//2
	saveNewSnake.head=m_newSnake.head;
	saveNewSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
		saveNewSnake.body[i]=m_newSnake.body[i];
	saveNewSnake.tail=m_newSnake.tail;
	//3
	savestateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		savestateArray[i]=m_pStateArray[i];
	
	//将长度增长
	m_length+=n;
	
	//释放所有蛇的身体存储数据空间
	delete[] m_oldSnake.body;m_oldSnake.body=NULL;
	delete[] m_newSnake.body;m_newSnake.body=NULL;
	delete[] m_pStateArray;m_pStateArray=NULL;
	delete[] m_pPos;m_pPos=NULL;

	//创建并初始化增长后的蛇的存储数据空间

	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
	m_pPos=new SPoint[m_length+2];
	for(i=0;i<m_length+2;i++)
	{
		m_pPos[i].x=0;
		m_pPos[i].y=0;
	}

	//恢复原来长度的数据(新的用初始化的数据)
	//a. newSnake ,oldSnake状态
	//b. stateArray
	//c. pos

	//a
	m_newSnake.head=saveNewSnake.head;
	m_oldSnake.head=saveOldSnake.head;
	for(i=0;i<m_length-n;i++)
	{
		m_newSnake.body[i]=saveNewSnake.body[i];
		m_oldSnake.body[i]=saveOldSnake.body[i];
	}
	m_newSnake.tail=saveNewSnake.tail;
	m_oldSnake.tail=saveOldSnake.tail;

	//b
	for(i=0;i<m_length-n+2;i++)
		m_pStateArray[i]=savestateArray[i];

	//c
	for(i=0;i<m_length-n+2;i++)
		m_pPos[i]=savePos[i];
}

//
//设置蛇头的坐标
//
void CSnake::SetHeadPos(int x,int y)
{
	m_pPos[0].x=x;m_pPos[0].y=y;
}

//
//取蛇的状态标识数组
//
BitmapState* CSnake::GetStateArray(void)
{
	return m_pStateArray;
}

//
//取蛇的位置数组
//
SPoint* CSnake::GetPos(void)
{
	return m_pPos;
}

//
//取蛇身的长度
//
int CSnake::GetLength(void)
{
	return m_length+2;
}

//
//检测蛇头是否触碰到其身体
//
bool CSnake::IsHeadTouchBody(int x,int y)
{
	int i;
	for(i=1;i<m_length+2;i++)
		if(m_pPos[i].x==x&&m_pPos[i].y==y) return true;
	return false;
}

//
//初始化 用作游戏结束后重新开始
//
void CSnake::Initial(void )
{
	//释放以前的所有存储空间
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);

	//创建蛇身长度为1的蛇，并做各种初始化
	int i;
	int x = 0;
	int y = 0;

	//初始化蛇的坐标位置
	m_length=1;
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x;m_pPos[0].y=y;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//初始化蛇的运动状态
	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	//初始化蛇的位图显示状态
	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
}