#if !defined(AFX_MYBUTTON_H__B943B7C5_0ED7_4D7F_9FFB_284C95D7D48B__INCLUDED_)
#define AFX_MYBUTTON_H__B943B7C5_0ED7_4D7F_9FFB_284C95D7D48B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MYBUTTON.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMYBUTTON window

class CMYBUTTON : public CButton
{
// Construction
public:
	CMYBUTTON();
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMYBUTTON)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMYBUTTON();
	CFont fUnderline;
	HCURSOR hHand;
	BOOL bLBtnDown;
	BOOL bHighlight;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMYBUTTON)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__B943B7C5_0ED7_4D7F_9FFB_284C95D7D48B__INCLUDED_)
