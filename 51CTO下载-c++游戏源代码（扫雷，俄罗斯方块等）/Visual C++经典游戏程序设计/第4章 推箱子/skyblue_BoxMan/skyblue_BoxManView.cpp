// skyblue_BoxManView.cpp : implementation of the CSkyblue_BoxManView class
//

#include "stdafx.h"
#include "skyblue_BoxMan.h"

#include "skyblue_BoxManDoc.h"
#include "skyblue_BoxManView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView

IMPLEMENT_DYNCREATE(CSkyblue_BoxManView, CView)

BEGIN_MESSAGE_MAP(CSkyblue_BoxManView, CView)
	//{{AFX_MSG_MAP(CSkyblue_BoxManView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView construction/destruction

CSkyblue_BoxManView::CSkyblue_BoxManView()
{
	// TODO: add construction code here

}

CSkyblue_BoxManView::~CSkyblue_BoxManView()
{
}

BOOL CSkyblue_BoxManView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView drawing

void CSkyblue_BoxManView::OnDraw(CDC* pDC)
{
	CSkyblue_BoxManDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView printing

BOOL CSkyblue_BoxManView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSkyblue_BoxManView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSkyblue_BoxManView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView diagnostics

#ifdef _DEBUG
void CSkyblue_BoxManView::AssertValid() const
{
	CView::AssertValid();
}

void CSkyblue_BoxManView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSkyblue_BoxManDoc* CSkyblue_BoxManView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkyblue_BoxManDoc)));
	return (CSkyblue_BoxManDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManView message handlers
