/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_BoxMan.h

Abstract:

	BoxMan Game 's App Class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_BOXMAN_H__C535EB93_B16D_4215_BDBD_E403DDCE4514__INCLUDED_)
#define AFX_SKYBLUE_BOXMAN_H__C535EB93_B16D_4215_BDBD_E403DDCE4514__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManApp:
// See skyblue_BoxMan.cpp for the implementation of this class
//

class CSkyblue_BoxManApp : public CWinApp
{
public:
	CSkyblue_BoxManApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_BoxManApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkyblue_BoxManApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
		CWnd * m_pBoxManWnd;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_BOXMAN_H__C535EB93_B16D_4215_BDBD_E403DDCE4514__INCLUDED_)
