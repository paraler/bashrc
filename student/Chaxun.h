#if !defined(AFX_CHAXUN_H__5FFDA7C4_3A7B_41FC_89ED_FC7C2FCAA3BF__INCLUDED_)
#define AFX_CHAXUN_H__5FFDA7C4_3A7B_41FC_89ED_FC7C2FCAA3BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Chaxun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChaxun dialog

class CChaxun : public CDialog
{
// Construction
public:
	CChaxun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChaxun)
	enum { IDD = IDD_DIALOG_CHAXUN };
	CString	m_strNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChaxun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChaxun)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAXUN_H__5FFDA7C4_3A7B_41FC_89ED_FC7C2FCAA3BF__INCLUDED_)
