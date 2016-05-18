/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    LoadMapDlg.cpp

Abstract:

		the Dialog class for Loading the 
	very Game Map to be re-edit.

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "BoxMan_Editer.h"
#include "LoadMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadMapDlg dialog
extern int MAX_MISSION_NUM;

CLoadMapDlg::CLoadMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadMapDlg)
	m_loadMapNum = 1;
	//}}AFX_DATA_INIT

}


void CLoadMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadMapDlg)
	DDX_Text(pDX, IDC_EDIT_LOAD_NUM, m_loadMapNum);
	DDV_MinMaxInt(pDX, m_loadMapNum, 1, MAX_MISSION_NUM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadMapDlg, CDialog)
	//{{AFX_MSG_MAP(CLoadMapDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadMapDlg message handlers



void CLoadMapDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
    //显示前设置好文本为最大关数
	SetDlgItemInt(IDC_STATIC_MAX_NUM, MAX_MISSION_NUM);
}
