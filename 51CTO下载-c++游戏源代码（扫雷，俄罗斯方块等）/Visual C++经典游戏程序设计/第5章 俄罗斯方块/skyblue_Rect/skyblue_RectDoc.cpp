// skyblue_RectDoc.cpp : implementation of the CSkyblue_RectDoc class
//

#include "stdafx.h"
#include "skyblue_Rect.h"

#include "skyblue_RectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectDoc

IMPLEMENT_DYNCREATE(CSkyblue_RectDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkyblue_RectDoc, CDocument)
	//{{AFX_MSG_MAP(CSkyblue_RectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectDoc construction/destruction

CSkyblue_RectDoc::CSkyblue_RectDoc()
{
	// TODO: add one-time construction code here

}

CSkyblue_RectDoc::~CSkyblue_RectDoc()
{
}

BOOL CSkyblue_RectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectDoc serialization

void CSkyblue_RectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectDoc diagnostics

#ifdef _DEBUG
void CSkyblue_RectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkyblue_RectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectDoc commands
