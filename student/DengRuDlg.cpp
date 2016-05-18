// DengRuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DengRuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDengRuDlg dialog


CDengRuDlg::CDengRuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDengRuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDengRuDlg)
	m_strHaoMa = _T("");
	m_strMiMa = _T("");
	m_nChoose = 0;
	//}}AFX_DATA_INIT
}


void CDengRuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDengRuDlg)
	DDX_Text(pDX, IDC_DENGRU_HAOMA, m_strHaoMa);
	DDX_Text(pDX, IDC_DENGRU_MIMA, m_strMiMa);
	DDX_Radio(pDX, IDC_RADIO_LEADER, m_nChoose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDengRuDlg, CDialog)
	//{{AFX_MSG_MAP(CDengRuDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDengRuDlg message handlers

//DEL void CDengRuDlg::OnCancel() 
//DEL {
//DEL 	// TODO: Add extra cleanup here
//DEL 	
//DEL 	CDialog::OnCancel();
//DEL }

BOOL CDengRuDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
