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
	//����1��2�еķ�����ͼ
	m_wndSplitter.CreateStatic(this,1, 2); 

	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CSkyblue_PinTuView), CSize(300,0), pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(COrgView), CSize(0,0), pContext);
	//����һ����Ϊ��ǰ����״̬����ͼ
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

	//�л�"�ı���ʾ��ʽ"�˵�ѡ��Ϊ"ͼ����ʾ��ʽ"


	HMENU hmenu;
	//��ȡ���˵�����Ȩ
	hmenu=::GetMenu(m_hWnd);
	//��ȡͼƬѡȡ�˵�ѡ�����ڵ��Ӳ˵���Ŀ�Ŀ���Ȩ
	hmenu=::GetSubMenu(hmenu,1);


	char * hbmp;
	UINT ITEM_ID;
	//��ȡʵ���ľ��
	HINSTANCE hinst = AfxGetInstanceHandle();

	//������ص���СԤ���͵�λͼͼƬ�����������ѡ��������޸�

	//ͼƬ������
	hbmp=(char *)LoadBitmap(hinst,MAKEINTRESOURCE(IDB_PIC1));
	//��Ӧ�˵�ѡ���ID��ȡ
	ITEM_ID = ::GetMenuItemID(hmenu,1);
	//�����޸�--�л���ͼ����ʾ��ʽ
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


