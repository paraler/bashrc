/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

     BoxManWnd.cpp

Abstract:

The Main Frame Class of the Game.

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "skyblue_BoxMan.h"
#include "BoxManWnd.h"
#include "HelpDlg.h"
#include "MissionLevelDlg.h"
#include <Mmsystem.h>   //��Ч  Winmm.lib

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxManWnd

IMPLEMENT_DYNCREATE(CBoxManWnd, CWnd)

CBoxManWnd::CBoxManWnd()
{
}

CBoxManWnd::~CBoxManWnd()
{
}


BEGIN_MESSAGE_MAP(CBoxManWnd, CWnd)
	//{{AFX_MSG_MAP(CBoxManWnd)
	ON_COMMAND(ID_MENU_GAME_EXIT, OnMenuGameExit)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENU_GAME_HELP, OnMenuGameHelp)
	ON_COMMAND(ID_MENU_GAME_LEVEL, OnMenuGameLevel)
	ON_COMMAND(ID_MENU_GAME_MUSIC, OnMenuGameMusic)
	ON_WM_INITMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxManWnd message handlers

//
// �˳���Ϸ
//
void CBoxManWnd::OnMenuGameExit() 
{
			PostQuitMessage(0);	
}

//
//  ��ͼ
//
void CBoxManWnd::OnPaint() 
{
	CPaintDC dc(this); // PaintDC�豸����
	CDC memDC;         //�ڴ��豸����
	CRect rt;          //�Ӵ��ھ���
	CBitmap memBmp;    //�ڴ�λͼ

	//���ݹ�����ʾ�豸
	memDC.CreateCompatibleDC(&dc);  
	//��ȡ�������С
	GetClientRect(&rt);  

	//��ʼ��λͼ��ʹ������ʾ�豸����
	memBmp.CreateCompatibleBitmap(&dc,rt.Width(),rt.Height());
	//����λͼ
	memDC.SelectObject(&memBmp);
	//���ڴ��豸��������
	m_boxMan.DrawGameArea(&memDC);
	//���ڴ��豸����һ�ο�����������ͼ����Ļ
	dc.BitBlt(0,0,rt.Width(),rt.Height(),&memDC,0,0,SRCCOPY);
	
	// Do not call CWnd::OnPaint() for painting messages
}

//
// ������Ϣ
//
void CBoxManWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	m_boxMan.KeyDown(nChar, nRepCnt, nFlags);
	Invalidate(FALSE);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
// ����
//
void CBoxManWnd::OnMenuGameHelp() 
{
	CHelpDlg helpDlg;
	helpDlg.DoModal();	
}

//
// ѡ��
//
void CBoxManWnd::OnMenuGameLevel() 
{
	CMissionLevelDlg missionDlg;
	missionDlg.m_iMisslionLev = m_boxMan.GetNowMissionNum();

	if(missionDlg.DoModal() == IDOK)
	{
		int iMissionLev = 1;
		iMissionLev = missionDlg.m_iMisslionLev;
		m_boxMan.ChangeMissionNum(iMissionLev);
		Invalidate(FALSE);
	}	
}

void CBoxManWnd::OnMenuGameMusic() 
{
	//�����Է����ı�
	m_bSound = (!m_bSound);  

	//CBoxMan�����޸���������״̬
	m_boxMan.IsSound(m_bSound); 

	//�˵��޸��Ƿ��Ѿ�ѡ�ñ��Ч��
	if (m_pSubMenu)
	{
		if (m_bSound == TRUE) 
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_CHECKED | MF_BYCOMMAND);
		}
		else 
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_UNCHECKED | MF_BYCOMMAND);
		}
	}
}

void CBoxManWnd::OnInitMenu(CMenu* pMenu) 
{
	CWnd::OnInitMenu(pMenu);

	//������²���
	//�������˵��ľ����m_pSubMenu	
	if ((m_pSubMenu = pMenu->GetSubMenu(0)) == 0) 
	{
		AfxMessageBox("��ʼ���˵�ʧ��");
		PostQuitMessage(0);
	}
}

void CBoxManWnd::SetCheckSound(void)
{
	m_bSound = (!m_bSound);
	m_boxMan.IsSound(m_bSound);
	if (m_pSubMenu)
	{
		if (m_bSound == TRUE) 
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_CHECKED | MF_BYCOMMAND);
		}
		else 
		{
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC, MF_UNCHECKED | MF_BYCOMMAND);
		}
	}
}
