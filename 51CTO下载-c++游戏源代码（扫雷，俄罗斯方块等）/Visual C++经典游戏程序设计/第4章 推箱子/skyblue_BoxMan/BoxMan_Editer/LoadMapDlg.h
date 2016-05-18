/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    LoadMapDlg.h

Abstract:

		the Dialog class for Loading the 
	very Game Map to be re-edit.

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_LOADMAPDLG_H__CC8EB426_F7F5_4F79_8E3E_258D349DB192__INCLUDED_)
#define AFX_LOADMAPDLG_H__CC8EB426_F7F5_4F79_8E3E_258D349DB192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadMapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadMapDlg dialog

class CLoadMapDlg : public CDialog
{
// Construction
public:
	CLoadMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoadMapDlg)
	enum { IDD = IDD_DIALOAG_LOAD_NMU };
	int		m_loadMapNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadMapDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoadMapDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADMAPDLG_H__CC8EB426_F7F5_4F79_8E3E_258D349DB192__INCLUDED_)
