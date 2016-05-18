#if !defined(AFX_DLGXLS_H__BE8FBD9B_008E_498E_8E65_6364527D8179__INCLUDED_)
#define AFX_DLGXLS_H__BE8FBD9B_008E_498E_8E65_6364527D8179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXLS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXLS dialog

class CDlgXLS : public CDialog
{
// Construction
public:
	CDlgXLS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXLS)
	enum { IDD = IDD_DIALOG_XLS };
	CString	m_strXlsName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXLS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXLS)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXLS_H__BE8FBD9B_008E_498E_8E65_6364527D8179__INCLUDED_)
