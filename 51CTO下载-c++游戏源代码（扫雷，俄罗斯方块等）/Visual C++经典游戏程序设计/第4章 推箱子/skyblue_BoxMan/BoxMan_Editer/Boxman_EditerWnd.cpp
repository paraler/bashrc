/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_EditWnd.cpp

Abstract:

	program's MainFrame 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "BoxMan_Editer.h"
#include "Boxman_EditerWnd.h"
#include "LoadMapDlg.h"
#include <Wingdi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int MAP_WIDTH; //=                16;
extern int MAP_HEIGHT;  // =             14;
extern int MAP_SMALL_SQUARE_SIZE; // =   20;

//地图状态
#define MAP_BACKGROUP  48  //'0'  
#define MAP_WHITEWALL  49  //'1'
#define MAP_BLUEWALL   50  //'2'
#define MAP_BALL       51  //'3'
#define MAP_YELLOWBOX  52  //'4'
#define MAP_REDBOX     53  //'5'
#define MAP_MANWALL    54  //'6'
#define MAP_MANBALL    55  //'7'

/////////////////////////////////////////////////////////////////////////////
// CBoxman_EditerWnd

IMPLEMENT_DYNCREATE(CBoxman_EditerWnd, CFrameWnd)

CBoxman_EditerWnd::CBoxman_EditerWnd()
{
	m_bMouseDown = FALSE;
}

CBoxman_EditerWnd::~CBoxman_EditerWnd()
{
}


BEGIN_MESSAGE_MAP(CBoxman_EditerWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CBoxman_EditerWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_MAP_BALL, OnMenuMapBall)
	ON_COMMAND(ID_MENU_MAP_BLUEWALL, OnMenuMapBluewall)
	ON_COMMAND(ID_MENU_MAP_MAN_WALL_BALL, OnMenuMapManWallBall)
	ON_COMMAND(ID_MENU_MAP_WHITEWALL, OnMenuMapWhitewall)
	ON_COMMAND(ID_MENU_MAP_YELLOWBOX, OnMenuMapYellowbox)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_COMMAND(ID_MENU_MAP_BKGROUND, OnMenuMapBkground)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_SAVE_MAP, OnMenuSaveMap)
	ON_COMMAND(ID_MENU_NEW_MAP, OnMenuNewMap)
	ON_COMMAND(ID_MENU_LOAD_MAP, OnMenuLoadMap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxman_EditerWnd drawing


/////////////////////////////////////////////////////////////////////////////
// CBoxman_EditerWnd diagnostics



/////////////////////////////////////////////////////////////////////////////
// CBoxman_EditerWnd message handlers

int CBoxman_EditerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//创建工具栏	
	if (CreateExToolBar() == -1 )
	{
		MessageBox("创建工具栏失败");
	}

	return 0;
}

BOOL CBoxman_EditerWnd::CreateExToolBar( void )
{
	CImageList img;
	CString str;
	
	if (!m_wndToolBar.CreateEx(this))
	{
		return -1;		
	}
	
	//设置按钮的宽度和长度
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	//改变属性
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | 
								TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
	//设置按钮数为6
	m_wndToolBar.SetButtons(NULL,6);	

	// 2. 添加图像
	//设置"热/hot"状态的的位图
	img.Create(28, 28, ILC_COLOR8|ILC_MASK,2,2);
	img.SetBkColor(RGB(0, 0, 102));
	//顺序增添按键的图标
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_WALL));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_PATH));	
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_DISTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BACKGROUND)); 
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();	
	//设置"冷/cold"状态的位图
	img.Create(26, 26, ILC_COLOR8|ILC_MASK, 2,2);
	img.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//顺序增添按键的图标
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_WALL));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_PATH));	
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_DISTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_MAN)); 
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BACKGROUND));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

/*
ID_MENU_MAP_WHITEWALL     围墙
ID_MENU_MAP_BLUEWALL      通道
ID_MENU_MAP_BALL          目的点
ID_MENU_MAP_YELLOWBOX     箱子
ID_MENU_MAP_MAN_WALL_BALL 工人
*/
	//3. 设置文字  
	m_wndToolBar.SetButtonInfo(0, ID_MENU_MAP_WHITEWALL, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, "围墙");	

	m_wndToolBar.SetButtonInfo(1, ID_MENU_MAP_BLUEWALL, TBSTYLE_BUTTON, 1);
	m_wndToolBar.SetButtonText(1, "通道");

	m_wndToolBar.SetButtonInfo(2, ID_MENU_MAP_BALL, TBSTYLE_BUTTON,2);
	m_wndToolBar.SetButtonText(2, "目的点");
	
	m_wndToolBar.SetButtonInfo(3, ID_MENU_MAP_YELLOWBOX, TBSTYLE_BUTTON,3);
	m_wndToolBar.SetButtonText(3, "箱子");	

	m_wndToolBar.SetButtonInfo(4, ID_MENU_MAP_MAN_WALL_BALL, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonText(4, "工人");

	m_wndToolBar.SetButtonInfo(5, ID_MENU_MAP_BKGROUND, TBSTYLE_BUTTON, 5);
	m_wndToolBar.SetButtonText(5, "背景");
	

	CRect rectToolBar;
	//得到按钮的大小
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	//设置按钮的大小
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(26,26));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//允许停靠
	EnableDocking(CBRS_ALIGN_ANY);
	//漂浮停靠
	CPoint pt(GetSystemMetrics(SM_CXSCREEN)/2+100,GetSystemMetrics(SM_CYSCREEN)/3+100);
	FloatControlBar(&m_wndToolBar,pt);

	return TRUE;
}

//选中目的地
void CBoxman_EditerWnd::OnMenuMapBall() 
{
	m_now_Select = MAP_BALL;
}

//选中通道
void CBoxman_EditerWnd::OnMenuMapBluewall() 
{
	m_now_Select = MAP_BLUEWALL;	
}
//选中人
void CBoxman_EditerWnd::OnMenuMapManWallBall() 
{
	m_now_Select = MAP_MANWALL;	
}

//选中墙
void CBoxman_EditerWnd::OnMenuMapWhitewall() 
{
	m_now_Select = MAP_WHITEWALL;	
}

//选中箱子
void CBoxman_EditerWnd::OnMenuMapYellowbox() 
{
	m_now_Select = MAP_YELLOWBOX;	
}

//选中背景
void CBoxman_EditerWnd::OnMenuMapBkground() 
{
	m_now_Select = MAP_BACKGROUP;
	
}

void CBoxman_EditerWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	//记录当前的鼠标位置，以便鼠标跟随效果的实现
	m_mousePoint = point;
	
	if( m_bMouseDown )
	{
		int x, y;
		
		x = point.x / MAP_SMALL_SQUARE_SIZE;
		y = point.y / MAP_SMALL_SQUARE_SIZE;
		m_boxManEdit.ChangeMap(x,y,m_now_Select);
	}
	Invalidate(FALSE);
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CBoxman_EditerWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x,y;
	//标识鼠标被按下
	m_bMouseDown = TRUE;
	//获取鼠标的位置并计算出在地图相应的方块位置
	m_mousePoint = point;
	x = point.x / MAP_SMALL_SQUARE_SIZE;
	y = point.y / MAP_SMALL_SQUARE_SIZE;
	//修改地图相应位置的状态
	m_boxManEdit.ChangeMap(x,y,m_now_Select);
	//通知窗口重绘
	Invalidate(FALSE);

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CBoxman_EditerWnd::OnPaint() 
{
	
	CPaintDC dc(this);    // 用以屏幕显示的设备
	CDC dcMemory;  // 内存设备
	
	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	if (!dc.IsPrinting()) 
	{
		
		// 与dc设备兼容
		if (dcMemory.CreateCompatibleDC(&dc))
		{	
			// 使得bitmap与实际显示的设备兼容
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right, m_rcClient.bottom))
			{
				// 内存设备选择物件－位图
				dcMemory.SelectObject(&bitmap);
				
				//绘制地图		
				m_boxManEdit.DrawMap(&dcMemory);

				//绘制鼠标跟随图标	
				int x = m_mousePoint.x-MAP_SMALL_SQUARE_SIZE/2;
				int y = m_mousePoint.y-MAP_SMALL_SQUARE_SIZE/2;
				m_boxManEdit.DrawMouseCursor(x,y,m_now_Select,&dcMemory);
				
				
				// 将内存设备的内容拷贝到实际屏幕显示的设备
				dc.BitBlt(m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom, &dcMemory, 0, 0, SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}	
}



void CBoxman_EditerWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//记录鼠标状态为释放状态
	m_bMouseDown = FALSE;	

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CBoxman_EditerWnd::OnMenuSaveMap() 
{
	m_boxManEdit.SaveMap();	
}

void CBoxman_EditerWnd::OnMenuNewMap() 
{
	m_boxManEdit.ClearMap();
}

void CBoxman_EditerWnd::OnMenuLoadMap() 
{
	CLoadMapDlg loadMapDlg;

	//假若按了确认提交成功后
	if(loadMapDlg.DoModal() == IDOK)
	{
		//提取与编辑框关联的整形变量数值
		int iMissionNum = loadMapDlg.m_loadMapNum;
		//载入相关地图
		m_boxManEdit.LoadMap(iMissionNum);
	}	
}
