// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "skyblue_PinTu.h"

#include "MainFrm.h"

#include "OrgView.h"
#include "skyblue_PinTuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//创建1行2列的分裂视图
	m_wndSplitter.CreateStatic(this,1, 2); 

	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CSkyblue_PinTuView), CSize(300,0), pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(COrgView), CSize(0,0), pContext);
	//讲第一个作为当前激活状态的视图
	m_wndSplitter.SetActivePane(0,0);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 600;
	cs.cy = 250;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU;
	cs.dwExStyle = WS_EX_ACCEPTFILES;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//切换"文本提示形式"菜单选项为"图像提示形式"


	HMENU hmenu;
	//获取主菜单控制权
	hmenu=::GetMenu(m_hWnd);
	//获取图片选取菜单选项所在的子菜单栏目的控制权
	hmenu=::GetSubMenu(hmenu,1);


	char * hbmp;
	UINT ITEM_ID;
	//获取实例的句柄
	HINSTANCE hinst = AfxGetInstanceHandle();

	//载入相关的缩小预览型的位图图片，并进行相关选项的属性修改

	//图片的载入
	hbmp=(char *)LoadBitmap(hinst,MAKEINTRESOURCE(IDB_PIC1));
	//相应菜单选项的ID获取
	ITEM_ID = ::GetMenuItemID(hmenu,1);
	//属性修改--切换成图像显示方式
	::ModifyMenu(hmenu,1,MF_BYPOSITION|MF_BITMAP,ITEM_ID,hbmp);

	hbmp=(char *)LoadBitmap(hinst,MAKEINTRESOURCE(IDB_PIC2));
	ITEM_ID = ::GetMenuItemID(hmenu,4);
	::ModifyMenu(hmenu,2,MF_BYPOSITION|MF_BITMAP,ITEM_ID,hbmp);

	hbmp=(char *)LoadBitmap(hinst,MAKEINTRESOURCE(IDB_PIC3));
	ITEM_ID = ::GetMenuItemID(hmenu,4);
	::ModifyMenu(hmenu,3,MF_BYPOSITION|MF_BITMAP,ITEM_ID,hbmp);

	hbmp=(char *)LoadBitmap(hinst,MAKEINTRESOURCE(IDB_PIC4));
	ITEM_ID = ::GetMenuItemID(hmenu,4);
	::ModifyMenu(hmenu,4,MF_BYPOSITION|MF_BITMAP,ITEM_ID,hbmp);

	return 0;
}


