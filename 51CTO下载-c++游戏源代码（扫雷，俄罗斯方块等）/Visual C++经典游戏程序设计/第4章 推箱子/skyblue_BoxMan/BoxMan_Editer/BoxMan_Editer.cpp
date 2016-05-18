/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_Editer.cpp

Abstract:

	program's App Class 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "BoxMan_Editer.h"
#include "Boxman_EditerWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int MAP_WIDTH;               //  20
extern int MAP_HEIGHT;              //  20
extern int MAP_SMALL_SQUARE_SIZE;   //  20


/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerApp

BEGIN_MESSAGE_MAP(CBoxMan_EditerApp, CWinApp)
	//{{AFX_MSG_MAP(CBoxMan_EditerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerApp construction

CBoxMan_EditerApp::CBoxMan_EditerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBoxMan_EditerApp object

CBoxMan_EditerApp theApp;

const CString className = _T("skyblue_boxmanediter_class");
/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerApp initialization

BOOL CBoxMan_EditerApp::InitInstance()
{
	// 定义和注册窗口
	m_pBoxManEditerWnd = new CBoxman_EditerWnd();
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(IDC_ARROW);
	wc.hIcon = LoadIcon(IDR_MAINFRAME);
	wc.lpszClassName = className;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
	// register the minewnd class
	if (!AfxRegisterClass(&wc)) 
	{
		AfxMessageBox("注册窗口类失败");
		return FALSE;
	}

	UINT uWidth = MAP_WIDTH*MAP_SMALL_SQUARE_SIZE+10;//地图区域+左右边框宽度
	UINT uHeight = MAP_HEIGHT*MAP_SMALL_SQUARE_SIZE+56;//地图区域+上下边框宽度

	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;
	//创建，显示窗口
	if ( !m_pBoxManEditerWnd->CreateEx( NULL, className, _T("推箱子_地图编辑器"), 
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL) ) 
	{
		AfxMessageBox("创建主窗口失败！");
		return FALSE;
	}
	
	m_pBoxManEditerWnd->ShowWindow(SW_NORMAL);

	// 绑定窗口为主窗口
	m_pMainWnd = m_pBoxManEditerWnd;

	return TRUE;
}





/////////////////////////////////////////////////////////////////////////////
// CBoxMan_EditerApp message handlers

