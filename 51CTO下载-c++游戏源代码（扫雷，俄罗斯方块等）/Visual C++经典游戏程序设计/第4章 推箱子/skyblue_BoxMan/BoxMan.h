/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

     BoxMan.h

Abstract:

	BoxMan Game Class ,solve all the important movment of the man and box,
	and some thing refer to them

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_BOXMAN_H__6BDB997E_47A5_471A_9589_4BB3B6AFF679__INCLUDED_)
#define AFX_BOXMAN_H__6BDB997E_47A5_471A_9589_4BB3B6AFF679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>  //GDI 绘图CDC


#define M_TAB_WIDTH  20   //横向方块数目宽度
#define M_TAB_HEIGHT 20   //纵向方块数目宽度

class CBoxMan  
{
public:
	CBoxMan();
	virtual ~CBoxMan();

public:
	BOOL ChangeMissionNum(int iNum);
	void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    void DrawGameArea(CDC* pDC);
	int  GetNowMissionNum(void);
	void IsSound(BOOL bUse);


protected:
	//绘图操作
    void DrawBackGroup(int x, int y, CDC* pDC);
    void DrawWhiteWall(int x, int y, CDC* pDC);
    void DrawBlueWall(int x, int y, CDC* pDC);
    void DrawBall(int x, int y, CDC* pDC);
    void DrawYellowBox(int x, int y, CDC* pDC);
    void DrawRedBox(int x, int y, CDC* pDC);
    void DrawManWall(int x, int y, CDC* pDC);
    void DrawManBall(int x, int y, CDC* pDC);

    void LoadMap(int iMissionNum);
    CPoint GetManPosition();
    void DispatchMsg(UINT nChar);
    void UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3);

    bool IsFinish(void);

	void BoxManPlaySound(void);
	int LoadMaxMissionNum(void);

protected:
    char m_cMap[M_TAB_WIDTH][M_TAB_HEIGHT];  //方块矩阵
    CPoint m_ptManPosition;
    int m_iMissionNum;

	int m_soundState;                     //当前播音状态
	int m_bSound;                         //是否启用声音
};

#endif // !defined(AFX_BOXMAN_H__6BDB997E_47A5_471A_9589_4BB3B6AFF679__INCLUDED_)
