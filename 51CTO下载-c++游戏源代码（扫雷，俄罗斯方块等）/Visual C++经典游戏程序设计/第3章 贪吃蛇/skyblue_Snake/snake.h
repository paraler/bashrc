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

//节点图像显示运动状态(方向)
enum BitmapState{M_NONE,M_UP_UP,M_DOWN_DOWN,M_LEFT_LEFT,M_RIGHT_RIGHT,
			M_UP_LEFT,M_UP_RIGHT,M_LEFT_UP,M_LEFT_DOWN,
			M_RIGHT_UP,M_RIGHT_DOWN,M_DOWN_RIGHT,M_DOWN_LEFT};

//节点运动状态(方向)
enum MoveState{S_NONE,S_UP,S_DOWN,S_LEFT,S_RIGHT};

//坐标位置结构
struct SPoint
{
	int x;
	int y;
};

class CSnake
{
	struct Snake_Struct//定义蛇体状态
	{
		MoveState head;  //头部
		MoveState *body; //身体
		MoveState tail; //尾部
	};
	
	private:
		int m_length;                 //蛇的长度
		Snake_Struct m_newSnake;      //蛇的新态的所有节点运动状态
		Snake_Struct m_oldSnake;      //蛇的原态的所有节点运动状态
		BitmapState *m_pStateArray;   //蛇的所有节点显示位图的状态
		SPoint *m_pPos;                //蛇体坐标
		
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
