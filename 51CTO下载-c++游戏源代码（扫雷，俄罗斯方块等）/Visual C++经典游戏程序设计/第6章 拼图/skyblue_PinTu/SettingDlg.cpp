/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    SettingDlg.cpp

Abstract:

	the Dialog class for user's favor configuration

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "skyblue_PinTu.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_bMusic = FALSE;
	m_iCols = 0;
	m_strMusicFileName = _T("");
	m_iRows = 0;
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_Rows, m_Crows);
	DDX_Control(pDX, IDC_Cols, m_Ccols);
	DDX_Control(pDX, IDC_SPINROWS, m_SpinRows);
	DDX_Control(pDX, IDC_SPINCOLS, m_SpinCols);
	DDX_Check(pDX, IDC_CHKMUSIC, m_bMusic);
	DDX_Text(pDX, IDC_Cols, m_iCols);
	DDV_MinMaxInt(pDX, m_iCols, 2, 10);
	DDX_Text(pDX, IDC_MusicFileName, m_strMusicFileName);
	DDX_Text(pDX, IDC_Rows, m_iRows);
	DDV_MinMaxInt(pDX, m_iRows, 2, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iCols=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("hnums"),4);
	m_iRows=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("vnums"),3);
	m_bMusic=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("musiconoff"),FALSE);
	m_strMusicFileName=AfxGetApp()->GetProfileString(_T("游戏参数"),_T("musicfilename"),"");
	m_SpinRows.SetBuddy(&m_Crows);
	m_SpinRows.SetRange(2,10);
	m_SpinRows.SetPos(m_iRows);
	m_SpinCols.SetBuddy(&m_Ccols);
	m_SpinCols.SetRange(2,10);
	m_SpinCols.SetPos(m_iCols);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_bMusic==TRUE)
	{
		if(m_strMusicFileName.IsEmpty())
		{
			MessageBox("你已选择了播放音乐，请指定MP3音乐文件名！","拼图游戏",MB_OK|MB_ICONINFORMATION);
			return;
		}
	}
	if(!m_strMusicFileName.IsEmpty())
	{
		if (m_strMusicFileName.Right(3)!="mp3")
		{
			MessageBox("所选文件不是MP3文件！","拼图游戏",MB_OK|MB_ICONWARNING);
			return;
		}
		FILE *f;
		f=fopen(m_strMusicFileName,"r");
		if(f==NULL)
		{
			MessageBox("所选文件不存在！","拼图游戏",MB_OK|MB_ICONWARNING);
			return;
		}
		fclose(f);
	}
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("hnums"),m_iCols);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("vnums"),m_iRows);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("musiconoff"),m_bMusic);
	AfxGetApp()->WriteProfileString(_T("游戏参数"),_T("musicfilename"),m_strMusicFileName);
	CDialog::OnOK();
}

void CSettingDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CString strFilter="MP3文件(*.mp3)|*.mp3";
	CFileDialog fileopen(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,strFilter);
	if(fileopen.DoModal()==IDOK)
		m_strMusicFileName=fileopen.GetPathName();
	UpdateData(FALSE);
}

