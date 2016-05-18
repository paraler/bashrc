// DlgRealBJ.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "DlgRealBJ.h"
//#include "CScore.h"
#include "AccessConn.h"
#include "TianJiaDlg.h"

#include "excel.h"
#include "comdef.h"
#include "DlgXLS.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRealBJ dialog
BOOL m_bAsc=TRUE;
int  m_nCol=0;
CDlgRealBJ::CDlgRealBJ(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRealBJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRealBJ)
	m_strCombo = _T("");
	//}}AFX_DATA_INIT
	m_bPanduan=TRUE;
	//m_bAsc=TRUE;
	//m_nCol=0;

}


void CDlgRealBJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRealBJ)
	DDX_Control(pDX, IDC_BUTTON_XIUGAI, m_BtnXiugai);
	DDX_Control(pDX, IDC_BUTTON_TIANJIA, m_BtnTianjia);
	DDX_Control(pDX, IDC_BUTTON_MANAGE, m_BtnManage);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_BtnOut);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_BtnDelete);
	DDX_Control(pDX, IDC_LIST_CLASS, m_ListClass);
	DDX_Control(pDX, IDC_COMBO_CLASS, m_ComBoClass);
	DDX_CBString(pDX, IDC_COMBO_CLASS, m_strCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRealBJ, CDialog)
	//{{AFX_MSG_MAP(CDlgRealBJ)
	ON_CBN_SELCHANGE(IDC_COMBO_CLASS, OnSelchangeComboClass)
	ON_BN_CLICKED(IDC_BUTTON_TIANJIA, OnButtonTianjia)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_XIUGAI, OnButtonXiugai)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CLASS, OnColumnclickListClass)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLASS, OnRclickListClass)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRealBJ message handlers

void CDlgRealBJ::OnOK() 
{
	// TODO: Add extra validation here
	return ;
	//CDialog::OnOK();
}

BOOL CDlgRealBJ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	



	// TODO: Add extra initialization here
	CreatDlgList();
	m_strCombo="һ��";
	UpdateData(FALSE);
	//UpdateData();

	ShowClassData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





void CDlgRealBJ::ShowClassData()
{
	CScore m_Score;
	CAccessConn m_Conn;
	_RecordsetPtr m_Set;
	_bstr_t vSQL;
	//if(!m_Conn.m_pConnection->State)
	//MessageBox("hi");
	m_Conn.OnInitAccessConn();
	switch(m_ComBoClass.GetCurSel())
	{
	case 0:
			vSQL="select * from student where �༶='һ��'";
			m_strCombo="һ��";
		break;
	case 1:
			vSQL="select * from student where �༶='����'";
			m_strCombo="����";
		break;
	case 2:
			vSQL="select * from student where �༶='����'";
			m_strCombo="����";
		break;
	}
	if(m_ListClass.GetItemCount()>0) 
		m_ListClass.DeleteAllItems();
	m_Conn.GetRecordSet(vSQL);
	if(m_Conn.m_pRecordset->adoEOF)
	{	
		m_Conn.CutConn();
		return ;
	}
	m_Set=m_Conn.GetRecordSet(vSQL);	
	m_Set->MoveFirst();
	while(!m_Set->adoEOF)
	{
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Set->GetCollect("ѧ��");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Set->GetCollect("����");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Set->GetCollect("�༶");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Set->GetCollect("�Ա�");
		m_Score.m_fChinese=m_Set->GetCollect("����");
		m_Score.m_fMaths=m_Set->GetCollect("��ѧ");
		m_Score.m_fEnglish=m_Set->GetCollect("Ӣ��");
		m_Score.m_fPhysics=m_Set->GetCollect("����");
		m_Score.m_fChemistry=m_Set->GetCollect("��ѧ");
		m_Score.m_fBiology=m_Set->GetCollect("����");
		m_Score.m_fSports=m_Set->GetCollect("����");
		ChangeStr(m_Score);
		m_Set->MoveNext();
		//m_Score.m_strName=(_bstr_t)m_Set->GetCollect("ѧ��");
		//m_Score.m_strName=(_bstr_t)m_Set->GetCollect("ѧ��");	
	}
	

	m_Conn.CutConn();
			
}

void CDlgRealBJ::CreatDlgList()
{
	CString str[13]={"ѧ��","����","�༶","�Ա�","����","��ѧ","Ӣ��",
		"����","��ѧ","����","����","�ܷ�","ƽ����"};
	
	int nIndex=0;
	m_ListClass.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	for(;nIndex<13;nIndex++)
	{	
		m_ListClass.InsertColumn(nIndex,str[nIndex],LVCFMT_LEFT,70);		
	}
	m_ListClass.SetColumnWidth(0,90);
	/*CHeaderCtrl   *pHeader=m_ListClass.GetHeaderCtrl();
	pHeader->ModifyStyle(0,CCS_NORESIZE,0);*/
		
	/*m_ListClass.InsertItem(0,"���");
	m_ListClass.SetItemText(0,1,"����");*/

}

//DEL void CDlgRealBJ::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	if(nIDCtl==IDC_LIST_CLASS)
//DEL 		lpMeasureItemStruct->itemHeight=1000;
//DEL 	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
//DEL }

//DEL void CDlgRealBJ::ChangeStr()
//DEL {
//DEL 	CScore scr;
//DEL 	CString str;
//DEL 	//m_ListClass.GetItemCount();
//DEL 	str.Format("",scr.m_strNO);
//DEL 	
//DEL }

void CDlgRealBJ::ChangeStr(CScore m_scr)
{	
	CScore scr=m_scr;
	CString str;
	int n=m_ListClass.GetItemCount();
	int i=0;
	if(scr.m_strClass!=m_strCombo) return ;
	
	m_ListClass.InsertItem(n,scr.m_strNO);
	
	m_ListClass.SetItemText(n,++i,scr.m_strName);
	m_ListClass.SetItemText(n,++i,scr.m_strClass);
	m_ListClass.SetItemText(n,++i,scr.m_strSex);
	str.Format("%4.1f",scr.m_fChinese);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fMaths);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fEnglish);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fPhysics);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fChemistry);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fBiology);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.m_fSports);
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.fScore());
	m_ListClass.SetItemText(n,++i,str);
	str.Format("%4.1f",scr.fAverage());
	m_ListClass.SetItemText(n,++i,str);
	m_ListClass.SetItemData(n,n);
	
}

void CDlgRealBJ::OnSelchangeComboClass() 
{
	// TODO: Add your control notification handler code here
	ShowClassData();
	//UpdateData();
}

void CDlgRealBJ::OnButtonTianjia() 
{
	// TODO: Add your control notification handler code here
	m_bPanduan=TRUE;
	CTianJiaDlg dlg(this);
	dlg.DoModal();
	//CScore score;
	/*if(IDOK==dlg.DoModal())
	if(dlg.m_bWrite)
	{	
		//MessageBox("hello");
		dlg.DestroyWindow();
		OnButtonTianjia();
	}
	else
	MessageBox("hi");*/
	//score.m_strNO=dlg.m_strNO;


	
}

//DEL CScore CDlgRealBJ::ReScore()
//DEL {
//DEL 	CTianJiaDlg dlg;
//DEL 	CScore score;
//DEL 	if(dlg.DoModal()!=IDOK) return score;
//DEL 
//DEL }

void CDlgRealBJ::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CAccessConn m_Conn;
	
	//int nIndex=-1;
	//nIndex=m_ListClass.GetNextItem(nIndex, LVNI_SELECTED);
	POSITION pos=m_ListClass.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox("��ѡ����Ҫɾ����һ��");
		return ;
	}
	int nIndex=m_ListClass.GetNextSelectedItem(pos);
	str=m_ListClass.GetItemText(nIndex,0);
	if(MessageBox("��ȷ��Ҫɾ����"+str+"������������","ɾ������",MB_OKCANCEL)!=IDOK)
		return ;
	_bstr_t vSQL="delete from student where ѧ��='"+str+"'";
	_RecordsetPtr m_Set;
	m_Conn.OnInitAccessConn();
	
//	m_Set=m_Conn.GetRecordSet();
	try
	{
		m_Set=m_Conn.GetRecordSet("select * from student");
		m_Conn.ExecuteSQL(vSQL);
		m_Set->Update();

		
	}
	catch(_com_error e)
	{
		MessageBox("ʧ��");
		return ;
	}
	MessageBox("�ɹ�ɾ����"+str+"��");
	m_Conn.CutConn();
	ShowClassData();

}

void CDlgRealBJ::OnButtonXiugai() 
{
	// TODO: Add your control notification handler code here
	m_bPanduan=FALSE;
	int nIndex=-1;
	nIndex=m_ListClass.GetNextItem(nIndex, LVNI_SELECTED);
	if(nIndex==-1)
	{
		MessageBox("��ѡ����Ҫ�޸ĵ�һ��");
		return ;
	}
	CTianJiaDlg dlg(this);
	dlg.DoModal();
}

void CDlgRealBJ::OnColumnclickListClass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
/*	CString str[13]={"ѧ��","����","�༶","�Ա�","����","��ѧ","Ӣ��",
	"����","��ѧ","����","����","�ܷ�","ƽ��"};
	static bIs=0;
	CScore m_Score;
	int nIndex= pNMListView->iSubItem;
	_bstr_t vSQL;
	if(bIs)
	vSQL="select * from student where �༶='"+m_strCombo+"' order by "+str[nIndex]+" ASC";
	else
	vSQL="select * from student where �༶='"+m_strCombo+"' order by "+str[nIndex]+" DESC";
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
	if(m_ListClass.GetItemCount()>0) 
		m_ListClass.DeleteAllItems();
	while(!m_Set->adoEOF)
	{
		m_Score.m_strNO=(LPCSTR)(_bstr_t)m_Set->GetCollect("ѧ��");
		m_Score.m_strName=(LPCSTR)(_bstr_t)m_Set->GetCollect("����");
		m_Score.m_strClass=(LPCSTR)(_bstr_t)m_Set->GetCollect("�༶");
		m_Score.m_strSex=(LPCSTR)(_bstr_t)m_Set->GetCollect("�Ա�");
		m_Score.m_fChinese=m_Set->GetCollect("����");
		m_Score.m_fMaths=m_Set->GetCollect("��ѧ");
		m_Score.m_fEnglish=m_Set->GetCollect("Ӣ��");
		m_Score.m_fPhysics=m_Set->GetCollect("����");
		m_Score.m_fChemistry=m_Set->GetCollect("��ѧ");
		m_Score.m_fBiology=m_Set->GetCollect("����");
		m_Score.m_fSports=m_Set->GetCollect("����");
		ChangeStr(m_Score);
		m_Set->MoveNext();
	}
	m_Conn.CutConn();
	bIs=++bIs%2;*/
	if(pNMListView->iSubItem==m_nCol)
	{
		m_bAsc=!m_bAsc;
	}
	else
	{
		m_bAsc=TRUE;
		m_nCol=pNMListView->iSubItem;
	}
	m_ListClass.SortItems(CompareFun,(DWORD)&m_ListClass);


	*pResult = 0;
}

void CDlgRealBJ::OnRclickListClass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu menu,*pSubmenu;
	menu.LoadMenu(IDR_MENU);
	pSubmenu=menu.GetSubMenu(0);
	CPoint point;
	GetCursorPos(&point);
	int nIndex=-1;
	nIndex=m_ListClass.GetNextItem(nIndex, LVNI_SELECTED);
	if(nIndex==-1)	
		return ;
	/*if(m_ListClass.GetItemCount()<=0||
		m_ListClass.GetSelectionMark()-1>m_ListClass.GetItemCount()) return ;*/

	pSubmenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
//	MessageBox("hello");
	*pResult = 0;
}


int CALLBACK CDlgRealBJ::CompareFun(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
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
	str1=pListCtrl->GetItemText(nItem1,m_nCol);
	str2=pListCtrl->GetItemText(nItem2,m_nCol);

	if((m_nCol>=0)&&(m_nCol<=3))
	{	

		if(m_bAsc)
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
		if(m_bAsc)
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











void CDlgRealBJ::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox("��ȷ��Ҫ������EXCEL��","��ʾ",MB_OKCANCEL)!=IDOK)
	{
		return ;
	}
	if (CoInitialize(NULL)!=0) 
	{ 
	AfxMessageBox("��ʼ��COM֧�ֿ�ʧ��!"); 
	exit(1); 
	} 
	
	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		exit(1); 
	} 
	ExcelApp.SetVisible(false); 

	
	
	//str+="student.xls";
	
	//str.Format("%s\\%s.xls",str,dlg.m_strXlsName);
	//MessageBox(str);
//	CFile f;
	//f.Open(str,CFile::modeCreate   );
	//HANDLE handle;
	//handle=CreateFile(str, GENERIC_WRITE  |GENERIC_READ,FILE_SHARE_WRITE |FILE_SHARE_READ ,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL ,0);
//	LPDISPATCH lp;
	//CString str1="0";
	//wssMysheets.GetItem((_variant_t)dlg.m_strXlsName);
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 
	wbMyBook.AttachDispatch(wbsMyBooks.Add(vtMissing));
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true);
//	MessageBox(str);
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true);
//	MessageBox(lp);
//	MessageBox(wsMysheet.GetName());
	//wsMysheet.SetName();	
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true);
	CString string;
	CAccessConn m_Conn;
	_bstr_t vSQL="select * from student";
	m_Conn.OnInitAccessConn();
	m_Conn.GetRecordSet(vSQL);
	if(m_Conn.m_pRecordset->adoEOF)
	{
		ExcelApp.Quit();
		rgMyRge.ReleaseDispatch(); 
		wsMysheet.ReleaseDispatch(); 
		wssMysheets.ReleaseDispatch(); 
		wbMyBook.ReleaseDispatch(); 
		wbsMyBooks.ReleaseDispatch(); 
		ExcelApp.ReleaseDispatch(); 
		m_Conn.CutConn();
		return ;
	}	
	m_Conn.m_pRecordset->MoveFirst();
	
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)1),_variant_t("ѧ��"));
/*	rgMyRge.GetItem(_variant_t((long)1),vtMissing);
	rgMyRge.SetColumnWidth(_variant_t((long)12));*/
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t("����"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)3),_variant_t("�༶"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)4),_variant_t("�Ա�"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)5),_variant_t("����"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)6),_variant_t("��ѧ"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)7),_variant_t("Ӣ��"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)8),_variant_t("����"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)9),_variant_t("��ѧ"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)10),_variant_t("����"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)11),_variant_t("����"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)12),_variant_t("�ܷ�"));
	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)13),_variant_t("ƽ��"));
	
	for(int i=2,j=0;!m_Conn.m_pRecordset->adoEOF;i++,j=0)
	{
		string=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("ѧ��");
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("����");
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("�༶");
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string=(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("�Ա�");
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("����"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("��ѧ"));
	//	MessageBox(m_Conn.m_pRecordset->GetCollect("��ѧ"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("Ӣ��"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("����"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("��ѧ"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("����"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("����"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("�ܷ�"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		string.Format("%s",(LPCSTR)(_bstr_t)m_Conn.m_pRecordset->GetCollect("ƽ��"));
		rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)++j),_variant_t(string)); 
		m_Conn.m_pRecordset->MoveNext();
	}
	m_Conn.CutConn();
	ExcelApp.SetUserControl(true);
	CDlgXLS dlg;
	CString str1;
	CString str="";
	int nOK;
	
	if(MessageBox("������һ���ļ���","��ʾ",MB_OKCANCEL)==IDOK) 
	{
		if(nOK=dlg.DoModal(),nOK==IDOK)
		{
			str=dlg.m_strXlsName;
		}
	}	
	GetCurrentDirectory(218,(LPSTR)(LPCSTR)str1);
	if(nOK==IDOK)
		str1.Format("%s\\%s",str1,str);
	else
		str1.Format("%s\\ѧ���ɼ�",str1);
	//CloseHandle(handle);
	try
	{
		wsMysheet.SaveAs(str1,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing
						,vtMissing,vtMissing,vtMissing
						);
	}
	catch(...)
	{
		if(ExcelApp.m_lpDispatch) ExcelApp.Quit();
		CoUninitialize();
		return ;
	}
	 
	wbMyBook.Close(vtMissing,COleVariant(str),vtMissing);
	wbsMyBooks.Close();
	ExcelApp.Quit();
	CoUninitialize();
	MessageBox("�ɹ�");
}
