// BoxMan_EditerDoc.cpp : implementation of the CBoxMan_EditerDoc class
//

#include "stdafx.h"
#include "BoxMan_Editer.h"

#include "BoxMan_EditerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerDoc

IMPLEMENT_DYNCREATE(CBoxMan_EditerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBoxMan_EditerDoc, CDocument)
	//{{AFX_MSG_MAP(CBoxMan_EditerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerDoc construction/destruction

CBoxMan_EditerDoc::CBoxMan_EditerDoc()
{
	// TODO: add one-time construction code here

}

CBoxMan_EditerDoc::~CBoxMan_EditerDoc()
{
}

BOOL CBoxMan_EditerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerDoc serialization

void CBoxMan_EditerDoc::Serialize(CArchive& ar)
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
// CBoxMan_EditerDoc diagnostics

#ifdef _DEBUG
void CBoxMan_EditerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBoxMan_EditerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerDoc commands
