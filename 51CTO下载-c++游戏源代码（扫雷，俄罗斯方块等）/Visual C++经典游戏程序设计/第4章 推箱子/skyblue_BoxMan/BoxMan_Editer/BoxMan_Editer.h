/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_Editer.h

Abstract:

	program's App Class 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_BOXMAN_EDITER_H__D34D028F_4754_4558_85F2_FFDB9FC86D95__INCLUDED_)
#define AFX_BOXMAN_EDITER_H__D34D028F_4754_4558_85F2_FFDB9FC86D95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerApp:
// See BoxMan_Editer.cpp for the implementation of this class
//

class CBoxMan_EditerApp : public CWinApp
{
public:
	CBoxMan_EditerApp();
public :
	CWnd *	m_pBoxManEditerWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxMan_EditerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBoxMan_EditerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMAN_EDITER_H__D34D028F_4754_4558_85F2_FFDB9FC86D95__INCLUDED_)
