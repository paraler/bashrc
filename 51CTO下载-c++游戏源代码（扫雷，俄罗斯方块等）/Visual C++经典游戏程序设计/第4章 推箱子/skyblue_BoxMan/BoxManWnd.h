/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

     BoxManWnd.h

Abstract:

The Main Frame Class of the Game.

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_BOXMANWND_H__7828B348_6D29_4C3B_977D_7285BA9FE7EC__INCLUDED_)
#define AFX_BOXMANWND_H__7828B348_6D29_4C3B_977D_7285BA9FE7EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoxManWnd.h : header file
//

#include "BoxMan.h"

/////////////////////////////////////////////////////////////////////////////
// CBoxManWnd frame

class CBoxManWnd : public CWnd
{
	DECLARE_DYNCREATE(CBoxManWnd)
public:
	CBoxManWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CBoxMan m_boxMan;           // 
	CMenu*		m_pSubMenu;		// 主菜单记录指针
	BOOL   m_bSound;            //  是否启用声音标记
// Operations
public:
void SetCheckSound(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxManWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBoxManWnd();

	// Generated message map functions
	//{{AFX_MSG(CBoxManWnd)
	afx_msg void OnMenuGameExit();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMenuGameHelp();
	afx_msg void OnMenuGameLevel();
	afx_msg void OnMenuGameMusic();
	afx_msg void OnInitMenu(CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMANWND_H__7828B348_6D29_4C3B_977D_7285BA9FE7EC__INCLUDED_)
