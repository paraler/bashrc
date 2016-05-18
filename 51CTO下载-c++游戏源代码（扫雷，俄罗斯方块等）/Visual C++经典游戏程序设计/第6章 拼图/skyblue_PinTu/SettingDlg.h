/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    SettingDlg.h

Abstract:

	the Dialog class for user's favor configuration

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_SETTINGDLG_H__8E23A109_7181_443A_987A_5F4EAAFADB3E__INCLUDED_)
#define AFX_SETTINGDLG_H__8E23A109_7181_443A_987A_5F4EAAFADB3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTING };
	CEdit	m_Crows;
	CEdit	m_Ccols;
	CSpinButtonCtrl	m_SpinRows;
	CSpinButtonCtrl	m_SpinCols;
	BOOL	m_bMusic;
	int		m_iCols;
	CString	m_strMusicFileName;
	int		m_iRows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__8E23A109_7181_443A_987A_5F4EAAFADB3E__INCLUDED_)
