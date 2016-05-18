/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    MissionLevelDlg.cpp

Abstract:

	The Dialog class for user to select the 
	Mission Level

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "skyblue_BoxMan.h"
#include "MissionLevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMissionLevelDlg dialog

extern int MAX_MISSION_NUM;     //最大的游戏关数

CMissionLevelDlg::CMissionLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMissionLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMissionLevelDlg)
	m_iMisslionLev = 0;
	//}}AFX_DATA_INIT
}


void CMissionLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMissionLevelDlg)
	DDX_Text(pDX, IDC_EDIT_MISSION_LEVEL, m_iMisslionLev);
	DDV_MinMaxInt(pDX, m_iMisslionLev, 0, MAX_MISSION_NUM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMissionLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CMissionLevelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMissionLevelDlg message handlers

void CMissionLevelDlg::OnOK() 
{
	UpdateData(TRUE);	

	CDialog::OnOK();
}
