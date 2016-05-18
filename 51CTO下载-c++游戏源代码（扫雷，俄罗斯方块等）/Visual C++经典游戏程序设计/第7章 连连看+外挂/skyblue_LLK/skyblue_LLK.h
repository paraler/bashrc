// app

#if !defined(AFX_SKYBLUE_LLK_H__A2AA2546_B9F0_4250_9623_03889A3B311A__INCLUDED_)
#define AFX_SKYBLUE_LLK_H__A2AA2546_B9F0_4250_9623_03889A3B311A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_LLKApp:
// See skyblue_LLK.cpp for the implementation of this class
//

class CSkyblue_LLKApp : public CWinApp
{
public:
	CSkyblue_LLKApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_LLKApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkyblue_LLKApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_LLK_H__A2AA2546_B9F0_4250_9623_03889A3B311A__INCLUDED_)
