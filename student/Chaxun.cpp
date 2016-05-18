// Chaxun.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "Chaxun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChaxun dialog


CChaxun::CChaxun(CWnd* pParent /*=NULL*/)
	: CDialog(CChaxun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChaxun)
	m_strNO = _T("");
	//}}AFX_DATA_INIT
}


void CChaxun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChaxun)
	DDX_Text(pDX, IDC_EDIT_NO, m_strNO);
	DDV_MaxChars(pDX, m_strNO, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChaxun, CDialog)
	//{{AFX_MSG_MAP(CChaxun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChaxun message handlers

void CChaxun::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
