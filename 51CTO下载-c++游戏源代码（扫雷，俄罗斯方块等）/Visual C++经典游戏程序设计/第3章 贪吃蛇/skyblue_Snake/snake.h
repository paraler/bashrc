/*++

Copyright (c) 2004-2005  AFE(Active-Free-Elegance)

Module Name:

    snake.h

Abstract:

    the class of Snake,including the basic-method 
	such as : move,born,and eat,and so on.

Author:


    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#ifndef _GREED_SNAKE_
#define _GREED_SNAKE_

#define SNAKE_MOVE 1
#define SAFE_DELETE(p) {delete (p);(p)=NULL;}
#define SAFE_DELETE_ARRAY(p) {delete[](p);(p)=NULL;}

#include <stdio.h>

//�ڵ�ͼ����ʾ�˶�״̬(����)
enum BitmapState{M_NONE,M_UP_UP,M_DOWN_DOWN,M_LEFT_LEFT,M_RIGHT_RIGHT,
			M_UP_LEFT,M_UP_RIGHT,M_LEFT_UP,M_LEFT_DOWN,
			M_RIGHT_UP,M_RIGHT_DOWN,M_DOWN_RIGHT,M_DOWN_LEFT};

//�ڵ��˶�״̬(����)
enum MoveState{S_NONE,S_UP,S_DOWN,S_LEFT,S_RIGHT};

//����λ�ýṹ
struct SPoint
{
	int x;
	int y;
};

class CSnake
{
	struct Snake_Struct//��������״̬
	{
		MoveState head;  //ͷ��
		MoveState *body; //����
		MoveState tail; //β��
	};
	
	private:
		int m_length;                 //�ߵĳ���
		Snake_Struct m_newSnake;      //�ߵ���̬�����нڵ��˶�״̬
		Snake_Struct m_oldSnake;      //�ߵ�ԭ̬�����нڵ��˶�״̬
		BitmapState *m_pStateArray;   //�ߵ����нڵ���ʾλͼ��״̬
		SPoint *m_pPos;                //��������
		
	private:
		BitmapState GetRightState(MoveState oldDirect,MoveState newDirect);
		
	public:
		
		void Move(void);          
		void ChangeDirect(MoveState d);
		void AddBody(int n=1);
		void SetHeadPos(int x,int y);
		BitmapState* GetStateArray(void);
		SPoint* GetPos(void);
		bool IsHeadTouchBody(int x,int y);
		int GetLength( void );
		void Initial( void );
		
	public:
		CSnake(int x_pos=0,int y_pos=0,int len=1);
		~CSnake();
};


#endif //_GREED_SNAKE_
