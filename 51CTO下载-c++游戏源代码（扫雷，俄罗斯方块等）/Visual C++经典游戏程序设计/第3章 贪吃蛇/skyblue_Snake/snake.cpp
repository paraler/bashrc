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

	m_length=len;  //�ߵ������峤

	//��ʼ���ߵ�����λ��
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x_pos;m_pPos[0].y=y_pos;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//��ʼ���ߵ��˶�״̬
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

	//��ʼ���ߵ�λͼ��ʾ״̬
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
//�����¾�����������˶�������������ص�ǰӦ����ʾ������״̬
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
//�ı䷽��
//
void CSnake::ChangeDirect(MoveState d)
{
  //  �ı䷽����������Ƕ�������
  //  ֻ��Ϊ����ǰ���ҷ�
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
//���ƶ�
//
void CSnake::Move(void)
{
	int i;
	//1.������״̬�����ڵ��״̬
	//���������������λ����״
	for(i=0;i<m_length;i++)
	{
		m_oldSnake.body[i]=m_newSnake.body[i];
	}	

	//���������״̬����ǰ���״̬�䶯һ��
	m_newSnake.tail=m_newSnake.body[m_length-1];
	for(i=m_length-1;i>0;i--)
	{
		m_newSnake.body[i]=m_newSnake.body[i-1];
	}
	m_newSnake.body[0]=m_newSnake.head;	
	
	//�����¾�״̬����ȡ��ȷ��״̬
	m_pStateArray[0]=GetRightState(m_oldSnake.head,m_newSnake.head);
	for(i=0;i<m_length;i++)
		m_pStateArray[i+1]=GetRightState(m_oldSnake.body[i],m_newSnake.body[i]);
	m_pStateArray[m_length+1]=GetRightState(m_oldSnake.tail,m_newSnake.tail);


	//2.�������ߵ������ƶ�
	//����ͷ�⣬�������ֵ���λ��Ϊ��ǰһ���ֵ�ԭ��λ��
	for(i=m_length+1;i>0;i--)
		m_pPos[i]=m_pPos[i-1];
	//��ͷ����λ�ø����ߵ��˶������ж�����Ӧƫ��
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
//�ߵ���������
//
void CSnake::AddBody(int n)
{

//  ������ʱ��"save����"��������������
//  �ߵĸ�������״̬
	int i;
	Snake_Struct saveOldSnake,saveNewSnake;
	BitmapState *savestateArray;
	SPoint *savePos;

	//�����ߵ�λ����Ϣ 
	// pos
	savePos=new SPoint[m_length+2];
	for(i=0;i<m_length+2;i++)
		savePos[i]=m_pPos[i];

	//�����ߵ�״̬��Ϣ
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
	
	//����������
	m_length+=n;
	
	//�ͷ������ߵ�����洢���ݿռ�
	delete[] m_oldSnake.body;m_oldSnake.body=NULL;
	delete[] m_newSnake.body;m_newSnake.body=NULL;
	delete[] m_pStateArray;m_pStateArray=NULL;
	delete[] m_pPos;m_pPos=NULL;

	//��������ʼ����������ߵĴ洢���ݿռ�

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

	//�ָ�ԭ�����ȵ�����(�µ��ó�ʼ��������)
	//a. newSnake ,oldSnake״̬
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
//������ͷ������
//
void CSnake::SetHeadPos(int x,int y)
{
	m_pPos[0].x=x;m_pPos[0].y=y;
}

//
//ȡ�ߵ�״̬��ʶ����
//
BitmapState* CSnake::GetStateArray(void)
{
	return m_pStateArray;
}

//
//ȡ�ߵ�λ������
//
SPoint* CSnake::GetPos(void)
{
	return m_pPos;
}

//
//ȡ����ĳ���
//
int CSnake::GetLength(void)
{
	return m_length+2;
}

//
//�����ͷ�Ƿ�����������
//
bool CSnake::IsHeadTouchBody(int x,int y)
{
	int i;
	for(i=1;i<m_length+2;i++)
		if(m_pPos[i].x==x&&m_pPos[i].y==y) return true;
	return false;
}

//
//��ʼ�� ������Ϸ���������¿�ʼ
//
void CSnake::Initial(void )
{
	//�ͷ���ǰ�����д洢�ռ�
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);

	//����������Ϊ1���ߣ��������ֳ�ʼ��
	int i;
	int x = 0;
	int y = 0;

	//��ʼ���ߵ�����λ��
	m_length=1;
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x;m_pPos[0].y=y;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//��ʼ���ߵ��˶�״̬
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

	//��ʼ���ߵ�λͼ��ʾ״̬
	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
}