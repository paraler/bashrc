#if !defined(AFX_DLGBJPAGE_H__409F97A9_1F1C_45D3_8975_CFD07E49F99F__INCLUDED_)
#define AFX_DLGBJPAGE_H__409F97A9_1F1C_45D3_8975_CFD07E49F99F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBJPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBJPage dialog

class CDlgBJPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgBJPage)

// Construction
public:
	CDlgBJPage();
	~CDlgBJPage();

// Dialog Data
	//{{AFX_DATA(CDlgBJPage)
	enum { IDD = IDD_DIALOG_BANJI };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgBJPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgBJPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBJPAGE_H__409F97A9_1F1C_45D3_8975_CFD07E49F99F__INCLUDED_)
