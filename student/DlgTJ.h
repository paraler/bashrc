#if !defined(AFX_DLGTJ_H__3A61F94F_B7BE_4712_9E4A_AED2ABD7BEA0__INCLUDED_)
#define AFX_DLGTJ_H__3A61F94F_B7BE_4712_9E4A_AED2ABD7BEA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTJ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTJ dialog

class CDlgTJ : public CDialog
{
// Construction
public:
	CDlgTJ(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTJ)
	enum { IDD = IDD_DIALOG_TIANJIA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTJ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTJ)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTJ_H__3A61F94F_B7BE_4712_9E4A_AED2ABD7BEA0__INCLUDED_)
