#if !defined(AFX_DLGDR_H__F994EAD4_6D82_407C_9D3F_6B24CD55DE5F__INCLUDED_)
#define AFX_DLGDR_H__F994EAD4_6D82_407C_9D3F_6B24CD55DE5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDR dialog

class CDlgDR : public CDialog
{
// Construction
public:
	CDlgDR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDR)
	enum { IDD = IDD_DIALOG_GENGRU };
	CString	m_HaoMa;
	CString	m_MiMa;
	int		m_leader;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDR)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioLeader();
	afx_msg void OnRadioStudent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bSelet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDR_H__F994EAD4_6D82_407C_9D3F_6B24CD55DE5F__INCLUDED_)
