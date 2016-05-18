// skyblue_BoxManDoc.cpp : implementation of the CSkyblue_BoxManDoc class
//

#include "stdafx.h"
#include "skyblue_BoxMan.h"

#include "skyblue_BoxManDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManDoc

IMPLEMENT_DYNCREATE(CSkyblue_BoxManDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkyblue_BoxManDoc, CDocument)
	//{{AFX_MSG_MAP(CSkyblue_BoxManDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManDoc construction/destruction

CSkyblue_BoxManDoc::CSkyblue_BoxManDoc()
{
	// TODO: add one-time construction code here

}

CSkyblue_BoxManDoc::~CSkyblue_BoxManDoc()
{
}

BOOL CSkyblue_BoxManDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManDoc serialization

void CSkyblue_BoxManDoc::Serialize(CArchive& ar)
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
// CSkyblue_BoxManDoc diagnostics

#ifdef _DEBUG
void CSkyblue_BoxManDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkyblue_BoxManDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManDoc commands
