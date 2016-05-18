// BoxMan_EditerView.cpp : implementation of the CBoxMan_EditerView class
//

#include "stdafx.h"
#include "BoxMan_Editer.h"

#include "BoxMan_EditerDoc.h"
#include "BoxMan_EditerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerView

IMPLEMENT_DYNCREATE(CBoxMan_EditerView, CView)

BEGIN_MESSAGE_MAP(CBoxMan_EditerView, CView)
	//{{AFX_MSG_MAP(CBoxMan_EditerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerView construction/destruction

CBoxMan_EditerView::CBoxMan_EditerView()
{
	// TODO: add construction code here

}

CBoxMan_EditerView::~CBoxMan_EditerView()
{
}

BOOL CBoxMan_EditerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerView drawing

void CBoxMan_EditerView::OnDraw(CDC* pDC)
{
	CBoxMan_EditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerView diagnostics

#ifdef _DEBUG
void CBoxMan_EditerView::AssertValid() const
{
	CView::AssertValid();
}

void CBoxMan_EditerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBoxMan_EditerDoc* CBoxMan_EditerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBoxMan_EditerDoc)));
	return (CBoxMan_EditerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerView message handlers
