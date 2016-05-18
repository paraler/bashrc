// DlgDR.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgDR.h"

#include "AccessConn.h"


//#include "C"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDR dialog



CDlgDR::CDlgDR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDR)
	m_HaoMa = _T("");
	m_MiMa = _T("");
	m_leader = -1;
	//}}AFX_DATA_INIT
}


void CDlgDR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDR)
	DDX_Text(pDX, IDC_DENGRU_HAOMA, m_HaoMa);
	DDV_MaxChars(pDX, m_HaoMa, 10);
	DDX_Text(pDX, IDC_DENGRU_MIMA, m_MiMa);
	DDV_MaxChars(pDX, m_MiMa, 16);
	DDX_Radio(pDX, IDC_RADIO_LEADER, m_leader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDR, CDialog)
	//{{AFX_MSG_MAP(CDlgDR)
	ON_BN_CLICKED(IDC_RADIO_LEADER, OnRadioLeader)
	ON_BN_CLICKED(IDC_RADIO_STUDENT, OnRadioStudent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDR message handlers

void CDlgDR::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CString str;
	CAccessConn m_Conn;
	m_Conn.OnInitAccessConn();
	_RecordsetPtr m_Set;
	_bstr_t vSQL;
	if(m_bSelet)
		vSQL="select * from managemessage";
	else
		 vSQL="select * from studentmassage";
	m_Set=m_Conn.GetRecordSet(vSQL);
	while(!m_Set->adoEOF)
	{
		if(str=((LPCTSTR)(_bstr_t)m_Set->GetCollect("IDUers")),str==m_HaoMa)
		{
			str=((LPCTSTR)(_bstr_t)m_Set->GetCollect("ÃÜÂë"));
			if(str==m_MiMa)
			{
				MessageBox("³É¹¦µÇÈë£¡");
				//m_Set->Close();
				//m_Set.Release();
				m_Conn.CutConn();

				CDialog::OnOK();
				return ;
				
			}
		}
		m_Set->MoveNext();
	}
	static n=0;
	n++;
	MessageBox("ÕÊºÅ»òÃÜÂë´íÎó£¡");
	
	if(n>=3)
	{			
		//m_Set->Close();
		//m_Set.Release();
		m_Conn.CutConn();
		SendMessage(WM_CLOSE,0,0);   
	}
	//CDialog::OnOK();
}

BOOL CDlgDR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_leader=0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDR::OnRadioLeader() 
{
	// TODO: Add your control notification handler code here
	m_bSelet=TRUE;
}

void CDlgDR::OnRadioStudent() 
{
	// TODO: Add your control notification handler code here
	m_bSelet=FALSE;
}
