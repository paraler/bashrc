/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLKDlg.h

Abstract:

	LLK-Game's kernal-solving Dialog

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_)
#define AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// C_LLK_Dlg dialog

class C_LLK_Dlg : public CDialog
{
// Construction
public:
	//游戏区域绘制
	void GameDraw(CDC * pDC);
	//开始一个新游戏
	void StartNewGame();


	//给定的2方块是否可连通消除
	BOOL IsLink(int x1,int y1,int x2,int y2);
	//是否已经获得胜利
	BOOL IsWin(void);

	//直接连通
	//X相等
	BOOL X1_Link_X2(int x,int y1,int y2);
	//Y相等
	BOOL Y1_Link_Y2(int x1,int x2,int y);
	//1直角接口连通
	BOOL OneCornerLink(int x1,int y1,int x2,int y2);
	//2直角接口连通
	BOOL TwoCornerLink(int x1,int y1,int x2,int y2);

	BOOL YThrough(int x,int y,BOOL bAdd);
	BOOL XThrough(int x,int y,BOOL bAdd);

	BOOL LineX(int x,int y1,int y2);
	BOOL LineY(int x1,int x2,int y);

	C_LLK_Dlg(CWnd* pParent = NULL);	// standard constructor
	~C_LLK_Dlg();
// Dialog Data
	//{{AFX_DATA(CTemp2Dlg)
	enum { IDD = IDD_LLK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemp2Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

//内存位图属性组
	CDC		m_mem3DBkDC;      //3D框架的内存设备环境
	CBitmap m_mem3DBkBmp;     //3D框架的内存位图

	CDC		m_memAnimalDC;      //动物图像的内存设备环境
	CBitmap m_memAnimalBmp;     //动物图像的内存位图

	CDC		m_MemDC;      //游戏区域内存设备环境
	CBitmap m_memBitmap;  //游戏区域内存位图

//地图位置相关属性组
	int*	m_map;        //动态地图数据头指针(一维数组)
	int		m_nRow;		  //地图的行数(虚拟)
	int		m_nCol;		  //地图的列数(虚拟)

	int		m_nX1;        //鼠标选中的记录方块列数
	int		m_nY1;	      //鼠标选中的记录方块行数


	// Generated message map functions
	//{{AFX_MSG(CTemp2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_)
