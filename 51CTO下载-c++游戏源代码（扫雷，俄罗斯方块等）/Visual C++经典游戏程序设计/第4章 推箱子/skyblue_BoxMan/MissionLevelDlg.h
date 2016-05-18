/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    MissionLevelDlg.h

Abstract:

	The Dialog class for user to select the 
	Mission Level

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_MISSIONLEVELDLG_H__E108DD76_FC69_4CFC_885C_E610B5D20DB6__INCLUDED_)
#define AFX_MISSIONLEVELDLG_H__E108DD76_FC69_4CFC_885C_E610B5D20DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MissionLevelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMissionLevelDlg dialog

class CMissionLevelDlg : public CDialog
{
// Construction
public:
	CMissionLevelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMissionLevelDlg)
	enum { IDD = IDD_DIALOG_LEVEL_SELECT };
	int		m_iMisslionLev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMissionLevelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMissionLevelDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISSIONLEVELDLG_H__E108DD76_FC69_4CFC_885C_E610B5D20DB6__INCLUDED_)
