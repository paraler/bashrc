// DlgTJ.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgTJ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTJ dialog


CDlgTJ::CDlgTJ(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTJ)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTJ)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTJ, CDialog)
	//{{AFX_MSG_MAP(CDlgTJ)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTJ message handlers
