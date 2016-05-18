// DlgXLS.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgXLS.h"
//#include "Shlwapi.h"
#include  "Shlwapi.h"   



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgXLS dialog


CDlgXLS::CDlgXLS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXLS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgXLS)
	//m_strXlsName = _T("");
	//}}AFX_DATA_INIT
	m_strXlsName="";
}


void CDlgXLS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXLS)
	DDX_Text(pDX, IDC_EDIT, m_strXlsName);
	DDV_MaxChars(pDX, m_strXlsName, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXLS, CDialog)
	//{{AFX_MSG_MAP(CDlgXLS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXLS message handlers

void CDlgXLS::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
//	CString str;
	if(m_strXlsName.IsEmpty())
	{
		MessageBox("文件名不能为空！");
		return ;
	}
//	GetCurrentDirectory(255,(LPSTR)(LPCSTR)str);
	//str+='092';
//	str+=m_strXlsName;
//	str+=".xls";
	
	/*if(PathFileExists(str))
	{
		MessageBox("EXCEL文件已经存在！\n请重新输入名！！");
		return ;
	}*/
//	CFile f;
//	f.Open(str,CFile::modeCreate );
	//CreateFile(str,GENERIC_READ | GENERIC_WRITE ,FILE_SHARE_READ |FILE_SHARE_WRITE ,0,CREATE_NEW  ,	FILE_ATTRIBUTE_NORMAL ,0);
		
	
	
	CDialog::OnOK();
}

BOOL CDlgXLS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
