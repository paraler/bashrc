/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_PinTu.cpp

Abstract:

	App class of the Game

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_PINTU_H__7FDDC196_E3D7_4166_BD61_54F4CC503D24__INCLUDED_)
#define AFX_SKYBLUE_PINTU_H__7FDDC196_E3D7_4166_BD61_54F4CC503D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuApp:
// See skyblue_PinTu.cpp for the implementation of this class
//

class CSkyblue_PinTuApp : public CWinApp
{
public:
	CSkyblue_PinTuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_PinTuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkyblue_PinTuApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_PINTU_H__7FDDC196_E3D7_4166_BD61_54F4CC503D24__INCLUDED_)
