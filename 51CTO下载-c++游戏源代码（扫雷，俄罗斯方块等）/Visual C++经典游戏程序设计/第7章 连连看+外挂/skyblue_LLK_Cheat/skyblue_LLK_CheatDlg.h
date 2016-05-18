//
/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLK_CheatDlg.h

Abstract:

	the game's cheating-kernal-solving Dialog class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_)
#define AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_LLK_CheatDlg dialog

class CSkyblue_LLK_CheatDlg : public CDialog
{
// Construction
public:
	CSkyblue_LLK_CheatDlg(CWnd* pParent = NULL);	// standard constructor

	//给定的2方块是否可连通消除
	BOOL IsLink(int x1,int y1,int x2,int y2);

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

//  入侵图像分析组
	void Hack(void);
	BOOL HackIn(CString strWinName);
	void GenMap();
	int GetRectData( int x, int y);
	BOOL Find2Rect(int &x1,int &y1, int &x2, int &y2);
	void Local_RemoteHintDraw( int x1, int y1, int x2, int y2);
	void RemoteButtonKick( int x1, int y1, int x2, int y2);


// Dialog Data
	//{{AFX_DATA(CSkyblue_LLK_CheatDlg)
	enum { IDD = IDD_SKYBLUE_LLK_CHEAT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_LLK_CheatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CDC		m_MemDC;      //本端游戏区域内存设备环境
	CBitmap m_memBitmap;  //本端游戏区域内存位图

//  地图位置相关属性组
	int*	m_map;        //动态地图数据头指针(一维数组)
	int		m_nRow;		  //地图的行数(虚拟)
	int		m_nCol;		  //地图的列数(虚拟)

	int		m_nX1;        //鼠标选中的记录方块行数
	int		m_nY1;	      //鼠标选中的记录方块列数

//	目标程序相关属性组
	CRect m_DestClientRect;  //目标程序窗口大小
	HDC m_hHackDC;   //目标程序的设备环境句柄
	HWND m_hwndHack; //目标程序的窗口句柄
	BOOL m_bAutoKick; //是否自动控制目标程序销方块


	// Generated message map functions
	//{{AFX_MSG(CSkyblue_LLK_CheatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonHack();
	afx_msg void OnButtonAutoKick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_)
