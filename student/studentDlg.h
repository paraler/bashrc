// studentDlg.h : header file
//

#if !defined(AFX_STUDENTDLG_H__1803A3BB_C480_46F4_90F7_7857CBE99BEA__INCLUDED_)
#define AFX_STUDENTDLG_H__1803A3BB_C480_46F4_90F7_7857CBE99BEA__INCLUDED_

#include "DlgBJ.h"	// Added by ClassView
#include "DlgRealBJ.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStudentDlg dialog

#include "AccessConn.h"
#include "DlgBJ.h"
#include "DlgRealBJ.h"
#include "DlgDR.h"


class CStudentDlg : public CDialog
{
// Construction
public:
	BOOL InToProgram();
	BOOL InitBeginWindows();
	CDlgRealBJ m_bj;
	CDlgBJ m_nj;
	CStudentDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStudentDlg)
	enum { IDD = IDD_STUDENT_DIALOG };
	CTabCtrl	m_Tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStudentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStudentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_nWidth;
	BOOL m_bJudge;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUDENTDLG_H__1803A3BB_C480_46F4_90F7_7857CBE99BEA__INCLUDED_)
