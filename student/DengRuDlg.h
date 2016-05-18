#if !defined(AFX_DENGRUDLG_H__E1B6366C_7345_466C_8E98_51B0B1EA1515__INCLUDED_)
#define AFX_DENGRUDLG_H__E1B6366C_7345_466C_8E98_51B0B1EA1515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DengRuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDengRuDlg dialog

class CDengRuDlg : public CDialog
{
// Construction
public:
	CDengRuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDengRuDlg)
	enum { IDD = IDD_DIALOG_GENGRU };
	CString	m_strHaoMa;
	CString	m_strMiMa;
	int		m_nChoose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDengRuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDengRuDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENGRUDLG_H__E1B6366C_7345_466C_8E98_51B0B1EA1515__INCLUDED_)
