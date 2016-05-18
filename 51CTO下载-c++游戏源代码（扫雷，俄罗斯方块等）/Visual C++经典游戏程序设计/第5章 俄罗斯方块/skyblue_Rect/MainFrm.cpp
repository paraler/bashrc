// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "skyblue_Rect.h"

#include "MainFrm.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//��������ʵ��

	CImageList img;
	CString str;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		return -1;		
	}
	//���ð�ť�Ŀ�Ⱥͳ���
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	//�ı�����
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | 
								TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
	//���ð�ť��Ϊ6
	m_wndToolBar.SetButtons(NULL,4);
	

	// 2. ���ͼ��
	//����"��/hot"״̬�ĵ�λͼ
	img.Create(28, 28, ILC_COLOR8|ILC_MASK,2,2);
	img.SetBkColor(RGB(0, 0, 102));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDI_ICON_START));
    img.Add(AfxGetApp()->LoadIcon(IDI_ICON_PAUSE));	
	img.Add(AfxGetApp()->LoadIcon(IDI_ICON_END));
    img.Add(AfxGetApp()->LoadIcon(IDI_ICON_SET));
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();	
	//����"��/cold"״̬��λͼ
	img.Create(32, 32, ILC_COLOR8|ILC_MASK, 2,2);
	img.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDI_ICON_START));
    img.Add(AfxGetApp()->LoadIcon(IDI_ICON_PAUSE));	
	img.Add(AfxGetApp()->LoadIcon(IDI_ICON_END));
    img.Add(AfxGetApp()->LoadIcon(IDI_ICON_SET));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();


	//3. ��������  
	m_wndToolBar.SetButtonInfo(0, ID_GAME_START, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, "��ʼ");	

	m_wndToolBar.SetButtonInfo(1, ID_GAME_PAUSH, TBSTYLE_BUTTON, 1);
	m_wndToolBar.SetButtonText(1, "��ͣ");

	m_wndToolBar.SetButtonInfo(2, ID_GAME_END, TBSTYLE_BUTTON,2);
	m_wndToolBar.SetButtonText(2, "����");
	
	m_wndToolBar.SetButtonInfo(3, ID_GAME_OPTION, TBSTYLE_BUTTON,3);
	m_wndToolBar.SetButtonText(3, "����");	

	CRect rectToolBar;
	//�õ���ť�Ĵ�С
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	//���ð�ť�Ĵ�С
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(32,32));

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 500;
	cs.cy = 500;	

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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

