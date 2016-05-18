/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    OrgView.h

Abstract:

	the originally photo's View 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_ORGVIEW_H__DF177E91_5904_43DD_AFDA_1A01ED948952__INCLUDED_)
#define AFX_ORGVIEW_H__DF177E91_5904_43DD_AFDA_1A01ED948952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrgView view

class COrgView : public CView
{
protected:
	COrgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COrgView)

// Attributes
public:
void DrawAll(CDC *pDC);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrgView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COrgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COrgView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORGVIEW_H__DF177E91_5904_43DD_AFDA_1A01ED948952__INCLUDED_)
