#if !defined(AFX_HOTBUTTON_H__7D72255D_976C_4409_87F8_748DE438191B__INCLUDED_)
#define AFX_HOTBUTTON_H__7D72255D_976C_4409_87F8_748DE438191B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHotButton window

class CHotButton : public CButton
{
// Construction
public:
	CHotButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotButton)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHotButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTBUTTON_H__7D72255D_976C_4409_87F8_748DE438191B__INCLUDED_)
