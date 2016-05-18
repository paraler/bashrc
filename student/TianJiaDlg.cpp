// TianJiaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "TianJiaDlg.h"
//#include "DlgRealBJ.h"
#include "AccessConn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTianJiaDlg dialog


CTianJiaDlg::CTianJiaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTianJiaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTianJiaDlg)
	m_bRadioSex = -1;
	m_fHuaxue = 0.0f;
	m_fShengwu = 0.0f;
	m_fShuxue = 0.0f;
	m_fTiyu = 0.0f;
	m_fWuli = 0.0f;
	m_strName = _T("");
	m_strNO = _T("");
	m_fYingyu = 0.0f;
	m_fYuwen = 0.0f;
	m_strCombo = _T("");
	m_bWrite = TRUE;
	//}}AFX_DATA_INIT
	m_pbj=(CDlgRealBJ*)pParent;  
}


void CTianJiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTianJiaDlg)
	DDX_Radio(pDX, IDC_RADIO_MAN, m_bRadioSex);
	DDX_Text(pDX, IDC_TIANJIA_HUAXUE, m_fHuaxue);
	DDV_MinMaxFloat(pDX, m_fHuaxue, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_SHENGWU, m_fShengwu);
	DDV_MinMaxFloat(pDX, m_fShengwu, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_SHUXUE, m_fShuxue);
	DDV_MinMaxFloat(pDX, m_fShuxue, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_TIYU, m_fTiyu);
	DDV_MinMaxFloat(pDX, m_fTiyu, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_WULI, m_fWuli);
	DDV_MinMaxFloat(pDX, m_fWuli, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_XINGMING, m_strName);
	DDV_MaxChars(pDX, m_strName, 10);
	DDX_Text(pDX, IDC_TIANJIA_XUEHAO, m_strNO);
	DDV_MaxChars(pDX, m_strNO, 10);
	DDX_Text(pDX, IDC_TIANJIA_YINGYU, m_fYingyu);
	DDV_MinMaxFloat(pDX, m_fYingyu, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIANJIA_YUWEN, m_fYuwen);
	DDV_MinMaxFloat(pDX, m_fYuwen, 0.f, 100.f);
	DDX_CBString(pDX, IDC_TIANJIA_BANJI, m_strCombo);
	DDV_MaxChars(pDX, m_strCombo, 4);
	DDX_Check(pDX, IDC_CHECK, m_bWrite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTianJiaDlg, CDialog)
	//{{AFX_MSG_MAP(CTianJiaDlg)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTianJiaDlg message handlers

BOOL CTianJiaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//CDlgRealBJ dlg;
	CString str;
	if(m_pbj->m_bPanduan)
	{
		m_bRadioSex=0;
		m_strCombo="一班";
		//MessageBox("hi");
		UpdateData(FALSE);
	}
	else
	{
		m_bWrite=FALSE;
		OnitXiuGai();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTianJiaDlg::OnOK() 
{
	// TODO: Add extra validation here
	//CString str;
	
	
	if(IsAnyEmpty())
	{
		return ;
	}
	if(!m_pbj->m_bPanduan)
	{
		if(MessageBox("你确定要修改这消息吗？",NULL,MB_OKCANCEL)==IDOK)
		{
			XiuGai();
			AddDataToList();
			m_pbj->ShowClassData();
		}
	}
	else
	{
		if(MessageBox("你确定要添加这消息吗？",NULL,MB_OKCANCEL)==IDOK)
				AddDataToList();
	}
	//MessageBox("你确定要添加这消息吗？");		
}

void CTianJiaDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	m_bWrite=!m_bWrite;
}

BOOL CTianJiaDlg::IsAnyEmpty()
{
	UpdateData();
	
	if(m_strName.IsEmpty()||m_strNO.IsEmpty())
	{
		MessageBox("有数据空了，请检查！");
		return TRUE;
	}
	return FALSE;
}

BOOL CTianJiaDlg::AddDataToList()
{
	CAccessConn m_Conn;
	_RecordsetPtr m_Set;
	_bstr_t vSQL="select * from student";
//	if(m_Conn.m_pConnection==NULL)
	m_Conn.OnInitAccessConn();
	m_Set=m_Conn.GetRecordSet(vSQL);
	CScore score;
	CString strl;
	CString str[13]={"学号","姓名","班级","性别","语文","数学","英语",
		"物理","化学","生物","体育","总分","平均"};
	int nIndex=m_pbj->m_ListClass.GetItemCount();
	UpdateData();
	m_Set->MoveFirst();
	while(!m_Set->adoEOF)
	{
		strl=(LPCSTR)(_bstr_t)(m_Set->GetCollect("学号"));
		if(strl==m_strNO)
		{
			MessageBox("学号重复");
			m_Conn.CutConn();
			return FALSE;
		}
		m_Set->MoveNext();
	}
	if(m_bRadioSex) 
		score.m_strSex="女";
	else
		score.m_strSex="男";
	score.m_strNO=		m_strNO;
	score.m_strName=	m_strName;
	score.m_strClass=	m_strCombo;
	score.m_fChinese=	m_fYuwen;
	score.m_fMaths=		m_fShuxue;
	score.m_fEnglish=	m_fYingyu;
	score.m_fPhysics=	m_fWuli;
	score.m_fBiology=	m_fShengwu;
	score.m_fChemistry=	m_fHuaxue;
	score.m_fSports=	m_fTiyu;
	m_pbj->ChangeStr(score);
	
	m_Set->AddNew();
	m_Set->PutCollect((_bstr_t)str[0],_variant_t(score.m_strNO));
	m_Set->PutCollect((_bstr_t)str[1],_variant_t(score.m_strName));
	m_Set->PutCollect((_bstr_t)str[2],_variant_t(score.m_strClass));
	m_Set->PutCollect((_bstr_t)str[3],_variant_t(score.m_strSex));
	m_Set->PutCollect((_bstr_t)str[4],_variant_t(score.m_fChinese));
	m_Set->PutCollect((_bstr_t)str[5],_variant_t(score.m_fMaths));
	m_Set->PutCollect((_bstr_t)str[6],_variant_t(score.m_fEnglish));
	m_Set->PutCollect((_bstr_t)str[7],_variant_t(score.m_fPhysics));
	m_Set->PutCollect((_bstr_t)str[8],_variant_t(score.m_fChemistry));
	m_Set->PutCollect((_bstr_t)str[9],_variant_t(score.m_fBiology));
	m_Set->PutCollect((_bstr_t)str[10],_variant_t(score.m_fSports));
	m_Set->PutCollect((_bstr_t)str[11],_variant_t(score.fScore()));
	m_Set->PutCollect((_bstr_t)str[12],_variant_t(score.fAverage()));
	m_Set->Update();
	m_Conn.CutConn();
	if(!m_bWrite)
	{		
		CDialog::OnOK();
	}
		
	return TRUE;
}


void CTianJiaDlg::OnitXiuGai()
{
	CString str;
	GetDlgItem(IDC_CHECK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK)->EnableWindow(FALSE);
	int nIndex=-1;
	nIndex=m_pbj->m_ListClass.GetNextItem(nIndex, LVNI_SELECTED);
	m_strNO=m_pbj->m_ListClass.GetItemText(nIndex,0);
	m_strName=m_pbj->m_ListClass.GetItemText(nIndex,1);
	m_strCombo=m_pbj->m_ListClass.GetItemText(nIndex,2);
	if(m_pbj->m_ListClass.GetItemText(nIndex,3)=="男")
		m_bRadioSex=0;
	else
		m_bRadioSex=1;
	str=m_pbj->m_ListClass.GetItemText(nIndex,4);
	m_fYuwen=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,5);
	m_fShuxue=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,6);
	m_fYingyu=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,7);
	m_fWuli=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,8);
	m_fHuaxue=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,9);
	m_fShengwu=(float)atof(str);
	str=m_pbj->m_ListClass.GetItemText(nIndex,10);
	m_fTiyu=(float)atof(str);
	GetDlgItem(IDOK)->SetWindowText("修  改");
	UpdateData(FALSE);
	
}

void CTianJiaDlg::XiuGai()
{
	CString str;
	CAccessConn m_Conn;
	int nIndex=-1;
	nIndex=m_pbj->m_ListClass.GetNextItem(nIndex, LVNI_SELECTED);
	str=m_pbj->m_ListClass.GetItemText(nIndex,0);
	_bstr_t vSQL="delete from student where 学号='"+str+"'";
	_RecordsetPtr m_Set;
	m_Conn.OnInitAccessConn();
	m_Set=m_Conn.GetRecordSet("select * from student");
	m_Conn.ExecuteSQL(vSQL);
	m_Set->Update();
	m_Conn.CutConn();
}
