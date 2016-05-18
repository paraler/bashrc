/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_BoxMan.cpp

Abstract:

	BoxMan Game 's App Class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "skyblue_BoxMan.h"


#include "BoxManWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManApp

BEGIN_MESSAGE_MAP(CSkyblue_BoxManApp, CWinApp)
	//{{AFX_MSG_MAP(CSkyblue_BoxManApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManApp construction

CSkyblue_BoxManApp::CSkyblue_BoxManApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSkyblue_BoxManApp object

CSkyblue_BoxManApp theApp;

const CString className = _T("skyblue_boxman_class");

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManApp initialization

BOOL CSkyblue_BoxManApp::InitInstance()
{
	// �����ע�ᴰ��
	m_pBoxManWnd = new CBoxManWnd();
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.hInstance = AfxGetInstanceHandle();
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(IDC_ARROW);
	wc.hIcon = LoadIcon(IDR_MAINFRAME);
	wc.lpszClassName = className;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);
	// register the minewnd class
	if (!AfxRegisterClass(&wc)) 
	{
		AfxMessageBox("ע�ᴰ����ʧ��");
		return FALSE;
	}

	UINT uWidth = 350;
	UINT uHeight = 350;
	UINT uXPos = GetSystemMetrics(SM_CXSCREEN) / 2 - uWidth / 2;
	UINT uYPos = GetSystemMetrics(SM_CYSCREEN) / 2 - uHeight / 2;
	//��������ʾ����
	if ( !m_pBoxManWnd->CreateEx( NULL, className, _T("������"), 
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
		uXPos, uYPos, uWidth, uHeight,
		NULL, NULL) ) 
	{
		AfxMessageBox("����������ʧ�ܣ�");
		return FALSE;
	}
	
	m_pBoxManWnd->ShowWindow(SW_NORMAL);

	// �󶨴���Ϊ������
	m_pMainWnd = m_pBoxManWnd;

	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
// CSkyblue_BoxManApp message handlers

