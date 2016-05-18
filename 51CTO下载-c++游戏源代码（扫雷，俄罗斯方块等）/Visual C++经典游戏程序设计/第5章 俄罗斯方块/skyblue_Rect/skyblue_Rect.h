// skyblue_Rect.h : main header file for the SKYBLUE_RECT application
//

#if !defined(AFX_SKYBLUE_RECT_H__2AFA952D_A6AB_427D_9B71_700FF98ED40D__INCLUDED_)
#define AFX_SKYBLUE_RECT_H__2AFA952D_A6AB_427D_9B71_700FF98ED40D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectApp:
// See skyblue_Rect.cpp for the implementation of this class
//

class CSkyblue_RectApp : public CWinApp
{
public:
	CSkyblue_RectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_RectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkyblue_RectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_RECT_H__2AFA952D_A6AB_427D_9B71_700FF98ED40D__INCLUDED_)
