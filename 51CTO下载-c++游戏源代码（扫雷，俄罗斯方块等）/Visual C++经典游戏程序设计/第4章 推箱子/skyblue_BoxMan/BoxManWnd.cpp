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
#include <Mmsystem.h>   //音效  Winmm.lib

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
// 退出游戏
//
void CBoxManWnd::OnMenuGameExit() 
{
			PostQuitMessage(0);	
}

//
//  绘图
//
void CBoxManWnd::OnPaint() 
{
	CPaintDC dc(this); // PaintDC设备环境
	CDC memDC;         //内存设备环境
	CRect rt;          //子窗口矩形
	CBitmap memBmp;    //内存位图

	//兼容关联显示设备
	memDC.CreateCompatibleDC(&dc);  
	//获取子区域大小
	GetClientRect(&rt);  

	//初始化位图，使得与显示设备兼容
	memBmp.CreateCompatibleBitmap(&dc,rt.Width(),rt.Height());
	//关联位图
	memDC.SelectObject(&memBmp);
	//在内存设备环境绘制
	m_boxMan.DrawGameArea(&memDC);
	//从内存设备环境一次拷贝整个绘制图像到屏幕
	dc.BitBlt(0,0,rt.Width(),rt.Height(),&memDC,0,0,SRCCOPY);
	
	// Do not call CWnd::OnPaint() for painting messages
}

//
// 键盘消息
//
void CBoxManWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	m_boxMan.KeyDown(nChar, nRepCnt, nFlags);
	Invalidate(FALSE);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
// 帮助
//
void CBoxManWnd::OnMenuGameHelp() 
{
	CHelpDlg helpDlg;
	helpDlg.DoModal();	
}

//
// 选关
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
	//作“自反”改变
	m_bSound = (!m_bSound);  

	//CBoxMan对象修改启用声音状态
	m_boxMan.IsSound(m_bSound); 

	//菜单修改是否已经选用标记效果
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

	//添加以下部分
	//保存主菜单的句柄到m_pSubMenu	
	if ((m_pSubMenu = pMenu->GetSubMenu(0)) == 0) 
	{
		AfxMessageBox("初始化菜单失败");
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
