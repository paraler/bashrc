// DlgNJPage.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgNJPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNJPage property page

IMPLEMENT_DYNCREATE(CDlgNJPage, CPropertyPage)

CDlgNJPage::CDlgNJPage() : CPropertyPage(CDlgNJPage::IDD)
{
	//{{AFX_DATA_INIT(CDlgNJPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgNJPage::~CDlgNJPage()
{
}

void CDlgNJPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNJPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNJPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNJPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNJPage message handlers
