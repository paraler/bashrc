// skyblue_BoxManView.h : interface of the CSkyblue_BoxManView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBLUE_BOXMANVIEW_H__8CD00672_97C8_4FA3_8F9B_8B770643EC49__INCLUDED_)
#define AFX_SKYBLUE_BOXMANVIEW_H__8CD00672_97C8_4FA3_8F9B_8B770643EC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkyblue_BoxManView : public CView
{
protected: // create from serialization only
	CSkyblue_BoxManView();
	DECLARE_DYNCREATE(CSkyblue_BoxManView)

// Attributes
public:
	CSkyblue_BoxManDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_BoxManView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_BoxManView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkyblue_BoxManView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in skyblue_BoxManView.cpp
inline CSkyblue_BoxManDoc* CSkyblue_BoxManView::GetDocument()
   { return (CSkyblue_BoxManDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_BOXMANVIEW_H__8CD00672_97C8_4FA3_8F9B_8B770643EC49__INCLUDED_)
