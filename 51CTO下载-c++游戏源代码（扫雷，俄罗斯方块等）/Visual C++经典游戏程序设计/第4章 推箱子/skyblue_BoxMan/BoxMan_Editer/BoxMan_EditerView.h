// BoxMan_EditerView.h : interface of the CBoxMan_EditerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOXMAN_EDITERVIEW_H__214488B8_D808_4A6D_B2C1_3BB01B942587__INCLUDED_)
#define AFX_BOXMAN_EDITERVIEW_H__214488B8_D808_4A6D_B2C1_3BB01B942587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBoxMan_EditerView : public CView
{
protected: // create from serialization only
	CBoxMan_EditerView();
	DECLARE_DYNCREATE(CBoxMan_EditerView)

// Attributes
public:
	CBoxMan_EditerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxMan_EditerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBoxMan_EditerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBoxMan_EditerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BoxMan_EditerView.cpp
inline CBoxMan_EditerDoc* CBoxMan_EditerView::GetDocument()
   { return (CBoxMan_EditerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMAN_EDITERVIEW_H__214488B8_D808_4A6D_B2C1_3BB01B942587__INCLUDED_)
