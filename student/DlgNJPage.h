#if !defined(AFX_DLGNJPAGE_H__274922C5_7766_465B_A04D_B2293D957F77__INCLUDED_)
#define AFX_DLGNJPAGE_H__274922C5_7766_465B_A04D_B2293D957F77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNJPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNJPage dialog

class CDlgNJPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNJPage)

// Construction
public:
	CDlgNJPage();
	~CDlgNJPage();

// Dialog Data
	//{{AFX_DATA(CDlgNJPage)
	enum { IDD = IDD_DIALOG_NIANJI };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNJPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNJPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNJPAGE_H__274922C5_7766_465B_A04D_B2293D957F77__INCLUDED_)
