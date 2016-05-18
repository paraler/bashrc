/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_Edit.h

Abstract:

	the BoxMan-Edit operation-contain Class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)
#define AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>  //GDI 绘图CDC

#define M_TAB_WIDTH  20   //横向方块数目宽度
#define M_TAB_HEIGHT 20   //纵向方块数目宽度

class CBoxMan_Edit  
{
public:
	CBoxMan_Edit();
	virtual ~CBoxMan_Edit();
public:
	BOOL ChangeMissionNum(int iNum);
    void DrawMap(CDC* pDC);
	int  GetNowMissionNum(void);
	void ChangeMap(int x, int y, int iState);
	void DrawMouseCursor(int x, int y, int iState, CDC *pDC);
    void LoadMap(int iMissionNum);
	void ClearMap(void);
	void SaveMap(void);

protected:
    CPoint GetManPosition();
    void DrawBackGroup(int x, int y, CDC* pDC);
    void DrawWhiteWall(int x, int y, CDC* pDC);
    void DrawBlueWall(int x, int y, CDC* pDC);
    void DrawBall(int x, int y, CDC* pDC);
    void DrawYellowBox(int x, int y, CDC* pDC);
    void DrawRedBox(int x, int y, CDC* pDC);
    void DrawManWall(int x, int y, CDC* pDC);
    void DrawManBall(int x, int y, CDC* pDC);
    void UpdateMap(UINT nChar);
    void UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3);
    bool IsFinish(void);

	int LoadMaxMissionNum(void);

protected:
    char m_cMap[M_TAB_WIDTH][M_TAB_HEIGHT];  //方块矩阵
    CPoint m_ptManPosition;                  
    int m_iMissionNum;

};

#endif // !defined(AFX_BOXMAN_EDIT_H__57EE21EE_9DC6_47F0_A3B7_FBACB60F4138__INCLUDED_)
