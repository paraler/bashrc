// DlgBJPage.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgBJPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBJPage property page

IMPLEMENT_DYNCREATE(CDlgBJPage, CPropertyPage)

CDlgBJPage::CDlgBJPage() : CPropertyPage(CDlgBJPage::IDD)
{
	//{{AFX_DATA_INIT(CDlgBJPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgBJPage::~CDlgBJPage()
{
}

void CDlgBJPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBJPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBJPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgBJPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBJPage message handlers
