// DlgBJ.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgBJ.h"
#include "AccessConn.h"
#include "Chaxun.h"
//#include "iostream.h"
//#include "CScore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBJ dialog
BOOL m_bAsc1=TRUE;
int m_nCol1=0;

CDlgBJ::CDlgBJ(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBJ)
	//m_strCombo = _T("");
	m_fMax = 0.0f;
	m_fMin = 0.0f;
	//}}AFX_DATA_INIT
	m_strCombo="语文";
	
}


void CDlgBJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBJ)
	DDX_Control(pDX, IDC_COMBO_CHOOSE, m_Combo);
	DDX_Control(pDX, IDC_LIST_SUM, m_ListSum);
	DDX_Control(pDX, IDC_LIST_ALL, m_ListAll);
	DDX_CBString(pDX, IDC_COMBO_CHOOSE, m_strCombo);
	DDX_Text(pDX, IDC_EDIT_MAX, m_fMax);
	DDV_MinMaxFloat(pDX, m_fMax, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT_MIN, m_fMin);
	DDV_MinMaxFloat(pDX, m_fMin, 0.f, 100.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBJ, CDialog)
	//{{AFX_MSG_MAP(CDlgBJ)
	ON_BN_CLICKED(IDC_NIANJI_UPDATE, OnNianjiUpdate)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ALL, OnColumnclickListAll)
	ON_BN_CLICKED(IDC_BUTTON_CHAXUN, OnButtonChaxun)
	ON_BN_CLICKED(IDC_BUTTON_GETFING, OnButtonGetfing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBJ message handlers

//DEL void CDlgBJ::OnOK() 
//DEL {
//DEL 	// TODO: Add extra validation here
//DEL 	
//DEL 	//CDialog::OnOK();
//DEL }

void CDlgBJ::OnOK() 
{
	// TODO: Add extra validation here
	return ;
	//CDialog::OnOK();
}

void CDlgBJ::OnNianjiUpdate() 
{
	// TODO: Add your control notification handler code here
	CScore m_Score;
	CAccessConn m_Conn;
	_bstr_t vSQL="select * from student";
	m_Conn.OnInitAccessConn();
	m_Conn.GetRecordSet(vSQL);
	if(m_ListAll.GetItemCount()>0)
		m_ListAll.DeleteAllItems();
	if(m_ListSum.GetItemCount()>0)
		m_ListSum.DeleteAllItems();
	if(m_Conn.m_pRecordset->adoEOF)
	{
		m_Conn.CutConn();
		return ;
	}
	m_Conn.m_pRecordset->MoveFirst();
	while(!m_Conn.m_pRecordset->adoEOF)
	{
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("学号");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("姓名");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("班级");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("性别");
		m_Score.m_fChinese=m_Conn.m_pRecordset->GetCollect("语文");
		m_Score.m_fMaths=m_Conn.m_pRecordset->GetCollect("数学");
		m_Score.m_fEnglish=m_Conn.m_pRecordset->GetCollect("英语");
		m_Score.m_fPhysics=m_Conn.m_pRecordset->GetCollect("物理");
		m_Score.m_fChemistry=m_Conn.m_pRecordset->GetCollect("化学");
		m_Score.m_fBiology=m_Conn.m_pRecordset->GetCollect("生物");
		m_Score.m_fSports=m_Conn.m_pRecordset->GetCollect("体育");
		Show(m_Score);
		m_Conn.m_pRecordset->MoveNext();
	}
	m_Conn.CutConn();
	Count();	
}

BOOL CDlgBJ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString str[23]={"班级","人数","语文优秀","语文及格","语文平均"
					,"数学优秀","数学及格","数学平均","英语优秀","英语及格"
					,"英语平均","物理优秀","物理及格","物理平均","化学优秀"
					,"化学及格","化学平均","生物优秀","生物及格","生物平均"
					,"体育优秀","体育及格","体育平均"};
	CString strl[13]={"学号","姓名","班级","性别","语文","数学","英语",
					"物理","化学","生物","体育","总分","平均"};
	
	for(int i=0;i<23;i++)
	{
		m_ListSum.InsertColumn(i,str[i],LVCFMT_LEFT,75,-1);	
	}
	for(i=0;i<13;i++)
	{
		m_ListAll.InsertColumn(i,strl[i],LVCFMT_LEFT,60,-1);
	}
	for(i=0;i<2;i++)
	{
		m_ListSum.SetColumnWidth(i,50);
	}
	m_ListAll.SetColumnWidth(0,80);
	m_ListAll.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	m_ListSum.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	OnNianjiUpdate();
	Count();
	//m_Combo.ModifyStyleEx();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBJ::Show(CScore score)
{
	CScore scr=score;
	CString str;
	int n=m_ListAll.GetItemCount();
	int i=0;		
	m_ListAll.InsertItem(n,scr.m_strNO);
	m_ListAll.SetItemText(n,++i,scr.m_strName);
	m_ListAll.SetItemText(n,++i,scr.m_strClass);
	m_ListAll.SetItemText(n,++i,scr.m_strSex);
	str.Format("%4.1f",scr.m_fChinese);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fMaths);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fEnglish);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fPhysics);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fChemistry);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fBiology);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fSports);
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.fScore());
	m_ListAll.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.fAverage());
	m_ListAll.SetItemText(n,++i,str);
	m_ListAll.SetItemData(n,n);
	
}

void CDlgBJ::Count()
{
	float m_fOne[28]={0},m_fTwo[28]={0},m_fThree[28]={0};
	CString str;
	int n,j;
	int nIndex=m_ListAll.GetItemCount();
	if(m_ListSum.GetItemCount()>0)
		m_ListSum.DeleteAllItems();
	for(int i=0;i<nIndex;i++)
	{
		
		if((str=m_ListAll.GetItemText(i,2))=="一班")
		{		
			for(n=4,j=0;n<=10;n++)
			{
				m_fOne[j]+=1;
				str=m_ListAll.GetItemText(i,n);
				m_fOne[j+3]+=(float)atof(str);
				if((float)atof(str)>=60)
					m_fOne[j+2]+=1;
				if((float)atof(str)>=90)
					m_fOne[j+1]+=1;
				j=j+4;
			//	continue ;
			}
		//	MessageBox("hi");
		}
		
		else if(str=m_ListAll.GetItemText(i,2),str=="二班")
		{
			for(n=4,j=0;n<=10;n++)
			{
				m_fTwo[j]+=1;
				str=m_ListAll.GetItemText(i,n);
				m_fTwo[j+3]+=(float)atof(str);
				if((float)atof(str)>=60)
					m_fTwo[j+2]+=1;
				if((float)atof(str)>=90)
					m_fTwo[j+1]+=1;
				j=j+4;
			//	continue ;
			}
		}
		else if(str=m_ListAll.GetItemText(i,2)=="三班")
		{
			for(n=4,j=0;n<=10;n++)
			{
				m_fThree[j]+=1;
				str=m_ListAll.GetItemText(i,n);
				m_fThree[j+3]+=(float)atof(str);
				if((float)atof(str)>=60)
					m_fThree[j+2]+=1;
				if((float)atof(str)>=90)
					m_fThree[j+1]+=1;
				j=j+4;
			}
		//	continue ;
		}
	}
	m_ListSum.InsertItem(0,"一班");
	for(i=0,j=1;i<28;i++)
	{		
		if((i!=0)&&(i%4==0))
			continue;
		if(i%4==3)
		{
			if(m_fOne[0]==0)
			{
				m_ListSum.SetItemText(0,j,"0.0");
				j++;
				continue;
			}
			str.Format("%4.1f",(m_fOne[i]/m_fOne[0]));
		}
		else
			str.Format("%g",m_fOne[i]);
		m_ListSum.SetItemText(0,j,str);
		j++;
	}
	m_ListSum.InsertItem(1,"二班");
	for(i=0,j=1;i<28;i++)
	{	
		if((i!=0)&&(i%4==0))
			continue;
		if(i%4==3)
		{
			if(m_fTwo[0]==0)
			{
				m_ListSum.SetItemText(1,j,"0.0");
				j++;
			//	MessageBox(m_ListSum.GetItemText(1,j));
				continue;
			}
			str.Format("%4.1f",(m_fTwo[i]/m_fTwo[0]));
		}
		else
			str.Format("%g",m_fTwo[i]);
		m_ListSum.SetItemText(1,j,str);
		j++;
	}
	m_ListSum.InsertItem(2,"三班");
	for(i=0,j=1;i<28;i++)
	{		
		if((i!=0)&&(i%4==0))
			continue;
		if(i%4==3)
		{
			if(m_fThree[0]==0)
			{
				m_ListSum.SetItemText(2,j,"0.0");
				j++;
				continue;
			}
			str.Format("%4.1f",(m_fThree[i]/m_fThree[0]));
		}
		else
			str.Format("%g",m_fThree[i]);
		m_ListSum.SetItemText(2,j,str);
		j++;
	}
	
}



void CDlgBJ::OnColumnclickListAll(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	/*	CString str[13]={"学号","姓名","班级","性别","语文","数学","英语",
	"物理","化学","生物","体育","总分","平均"};
	static m_bIs=0;
	CScore m_Score;
	int nIndex= pNMListView->iSubItem;
	_bstr_t vSQL;
	if(m_bIs)
	vSQL="select * from student  order by "+str[nIndex]+" ASC";
	else
	vSQL="select * from student  order by "+str[nIndex]+" DESC";
	CAccessConn m_Conn;
	m_Conn.OnInitAccessConn();
	m_Conn.GetRecordSet(vSQL);
	if(m_Conn.m_pRecordset->adoEOF)
	{	
		m_Conn.CutConn();
		return ;
	}
	_RecordsetPtr m_Set;
	m_Set=m_Conn.GetRecordSet(vSQL);
	m_Set->MoveFirst();
	if(m_ListAll.GetItemCount()>0) 
		m_ListAll.DeleteAllItems();
	while(!m_Set->adoEOF)
	{
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Set->GetCollect("学号");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Set->GetCollect("姓名");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Set->GetCollect("班级");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Set->GetCollect("性别");
		m_Score.m_fChinese=m_Set->GetCollect("语文");
		m_Score.m_fMaths=m_Set->GetCollect("数学");
		m_Score.m_fEnglish=m_Set->GetCollect("英语");
		m_Score.m_fPhysics=m_Set->GetCollect("物理");
		m_Score.m_fChemistry=m_Set->GetCollect("化学");
		m_Score.m_fBiology=m_Set->GetCollect("生物");
		m_Score.m_fSports=m_Set->GetCollect("体育");
		Show(m_Score);
		m_Set->MoveNext();
	}
	m_Conn.CutConn();
	m_bIs=++m_bIs%2;*/
	if(pNMListView->iSubItem==m_nCol1)
	{
		m_bAsc1=!m_bAsc1;
	}
	else
	{
		m_bAsc1=TRUE;
		m_nCol1=pNMListView->iSubItem;
	}
	m_ListAll.SortItems(CompareFunc,(DWORD)&m_ListAll);
	*pResult = 0;
}

void CDlgBJ::OnButtonChaxun() 
{
	// TODO: Add your control notification handler code here
	CChaxun dlg;
	if(IDOK!=dlg.DoModal()) return ;
	CAccessConn m_Conn;
	_bstr_t vSQL;
	CScore m_Score;
	vSQL="select * from student where 学号='"+dlg.m_strNO+"'";
	m_Conn.GetRecordSet(vSQL);
	if(m_Conn.m_pRecordset->adoEOF)
	{
		MessageBox("没有“"+dlg.m_strNO+"”这个数据!");	
		m_Conn.CutConn();
		return ;		
	}
		m_ListAll.DeleteAllItems();
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("学号");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("姓名");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("班级");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("性别");
		m_Score.m_fChinese=m_Conn.m_pRecordset->GetCollect("语文");
		m_Score.m_fMaths=m_Conn.m_pRecordset->GetCollect("数学");
		m_Score.m_fEnglish=m_Conn.m_pRecordset->GetCollect("英语");
		m_Score.m_fPhysics=m_Conn.m_pRecordset->GetCollect("物理");
		m_Score.m_fChemistry=m_Conn.m_pRecordset->GetCollect("化学");
		m_Score.m_fBiology=m_Conn.m_pRecordset->GetCollect("生物");
		m_Score.m_fSports=m_Conn.m_pRecordset->GetCollect("体育");
		Show(m_Score);
		m_Conn.CutConn();
}

void CDlgBJ::OnButtonGetfing() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_fMax<m_fMin)		
	{
		MessageBox("最大值不能少于最少值！");
		return;
	}
//	CString str1,str2;
	CAccessConn m_Conn;
	CScore m_Score;
	m_Conn.OnInitAccessConn();
//	char buf[1024] = "";
	//sprintf_s<1024>(buf, "select * from student where %s between %f and %f", m_strCombo, m_fMax, m_fMin);
	//_bstr_t vSql = buf;
	CString vSQL;
	
//	CString str;
	//str.Format("select * from student where %s<=%4.1f and %s>=%4.1f",m_strCombo,m_fMax,m_strCombo,m_fMin);

//	str1.Format("%4.1f",m_fMax);
//	str2.Format("%4.1f",m_fMin);
	//vSQL="select * from student ";
	vSQL.Format("select * from student where %s BETWEEN %.1f AND %.1f",m_strCombo,m_fMin,m_fMax);
	
		//" select * from student where "+ m_strCombo +" between '" + m_fMax + "' and '" + m_fMin + "' ";
	//vSQL=(_bstr_t)((LPCSTR)str);
	m_Conn.GetRecordSet((_bstr_t)((LPCSTR)vSQL));
	
//	m_Conn.ExecuteSQL(vSQL);
	if(m_Conn.m_pRecordset->adoEOF)
	{
		m_ListAll.DeleteAllItems();
		m_Conn.CutConn();
		return ;		
	}
	if(!m_Conn.m_pRecordset->adoBOF)
		m_Conn.m_pRecordset->MoveFirst();
	m_ListAll.DeleteAllItems();
	while(!m_Conn.m_pRecordset->adoEOF)
	{
		
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("学号");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("姓名");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("班级");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("性别");
		m_Score.m_fChinese=m_Conn.m_pRecordset->GetCollect("语文");
		m_Score.m_fMaths=m_Conn.m_pRecordset->GetCollect("数学");
		m_Score.m_fEnglish=m_Conn.m_pRecordset->GetCollect("英语");
		m_Score.m_fPhysics=m_Conn.m_pRecordset->GetCollect("物理");
		m_Score.m_fChemistry=m_Conn.m_pRecordset->GetCollect("化学");
		m_Score.m_fBiology=m_Conn.m_pRecordset->GetCollect("生物");
		m_Score.m_fSports=m_Conn.m_pRecordset->GetCollect("体育");
		Show(m_Score);
		m_Conn.m_pRecordset->MoveNext();
	}
	m_Conn.CutConn();
}

int CALLBACK CDlgBJ::CompareFunc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CListCtrl *pListCtrl = (CListCtrl*)lParamSort;
	int rValue=0;	
	int nItem1,nItem2;
	LVFINDINFO FindInfo;
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=lParam1;
	nItem1=pListCtrl->FindItem(&FindInfo,-1);
	FindInfo.lParam=lParam2;
	nItem2=pListCtrl->FindItem(&FindInfo,-1);
	if((nItem1 == -1)||(nItem2 == -1)) 
	{
		return 0;
	}
	CString str1,str2;
	str1=pListCtrl->GetItemText(nItem1,m_nCol1);
	str2=pListCtrl->GetItemText(nItem2,m_nCol1);

	if((m_nCol1>=0)&&(m_nCol1<=3))
	{	

		if(m_bAsc1)
		{
			rValue = strcmp(str1,str2);
		}
		else
		{
			rValue = strcmp(str2,str1);
		}
	}
	else 
	{
		float num1,num2;
		num1 = (float)atof(str1);
		num2 = (float)atof(str2);
		if(m_bAsc1)
		{
			if(num1 == num2) rValue = 0;
			else if(num1 > num2) rValue = 1;
			else rValue = -1;
		}
		else
		{
			if(num1 == num2) rValue = 0;
			else if(num1 < num2) rValue = 1;
			else rValue = -1;
		}
	}	
	
	return rValue;
}
