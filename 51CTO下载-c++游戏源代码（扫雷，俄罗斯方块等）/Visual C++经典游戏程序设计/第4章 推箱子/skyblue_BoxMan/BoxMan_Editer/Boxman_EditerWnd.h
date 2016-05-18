/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_EditWnd.h

Abstract:

	program's MainFrame 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_BOXMAN_EDITERWND_H__42EEA5E0_CD5E_48FC_AA39_C697B9D960CE__INCLUDED_)
#define AFX_BOXMAN_EDITERWND_H__42EEA5E0_CD5E_48FC_AA39_C697B9D960CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Boxman_EditerWnd.h : header file
//

#include "BoxMan_Edit.h"    //编辑类的引入

/////////////////////////////////////////////////////////////////////////////
// CBoxman_EditerWnd view

class CBoxman_EditerWnd : public CFrameWnd
{
public:
	CBoxman_EditerWnd();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBoxman_EditerWnd)

// Attributes
protected:  
	CToolBar    m_wndToolBar;     // 工具栏
	int m_now_Select;             // 当前选定的地图元素
	CDC *m_pWindowDC;             // windows设备环境
	CPoint m_mousePoint;          // 鼠标的坐标位置
	CBoxMan_Edit m_boxManEdit;    // boxmanEdit实体
	BOOL m_bMouseDown;            // 是否鼠标已被按下
public:

// Operations
public:
BOOL CreateExToolBar( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxman_EditerWnd)
	protected:

	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBoxman_EditerWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBoxman_EditerWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMenuMapBall();
	afx_msg void OnMenuMapBluewall();
	afx_msg void OnMenuMapManWallBall();
	afx_msg void OnMenuMapWhitewall();
	afx_msg void OnMenuMapYellowbox();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMenuMapBkground();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuSaveMap();
	afx_msg void OnMenuNewMap();
	afx_msg void OnMenuLoadMap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMAN_EDITERWND_H__42EEA5E0_CD5E_48FC_AA39_C697B9D960CE__INCLUDED_)
