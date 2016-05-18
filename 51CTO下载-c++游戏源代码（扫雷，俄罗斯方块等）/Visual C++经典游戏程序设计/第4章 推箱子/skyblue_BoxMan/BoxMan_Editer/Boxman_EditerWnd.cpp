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

//��ͼ״̬
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

	//����������	
	if (CreateExToolBar() == -1 )
	{
		MessageBox("����������ʧ��");
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
	
	//���ð�ť�Ŀ�Ⱥͳ���
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 100);
	//�ı�����
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | 
								TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
	//���ð�ť��Ϊ6
	m_wndToolBar.SetButtons(NULL,6);	

	// 2. ���ͼ��
	//����"��/hot"״̬�ĵ�λͼ
	img.Create(28, 28, ILC_COLOR8|ILC_MASK,2,2);
	img.SetBkColor(RGB(0, 0, 102));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_WALL));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_PATH));	
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_DISTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_MAN));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BACKGROUND)); 
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	img.Detach();	
	//����"��/cold"״̬��λͼ
	img.Create(26, 26, ILC_COLOR8|ILC_MASK, 2,2);
	img.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//˳����������ͼ��
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_WALL));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_PATH));	
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_DISTINATION));
    img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BOX));
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_MAN)); 
	img.Add(AfxGetApp()->LoadIcon(IDR_ICON_BACKGROUND));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

/*
ID_MENU_MAP_WHITEWALL     Χǽ
ID_MENU_MAP_BLUEWALL      ͨ��
ID_MENU_MAP_BALL          Ŀ�ĵ�
ID_MENU_MAP_YELLOWBOX     ����
ID_MENU_MAP_MAN_WALL_BALL ����
*/
	//3. ��������  
	m_wndToolBar.SetButtonInfo(0, ID_MENU_MAP_WHITEWALL, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonText(0, "Χǽ");	

	m_wndToolBar.SetButtonInfo(1, ID_MENU_MAP_BLUEWALL, TBSTYLE_BUTTON, 1);
	m_wndToolBar.SetButtonText(1, "ͨ��");

	m_wndToolBar.SetButtonInfo(2, ID_MENU_MAP_BALL, TBSTYLE_BUTTON,2);
	m_wndToolBar.SetButtonText(2, "Ŀ�ĵ�");
	
	m_wndToolBar.SetButtonInfo(3, ID_MENU_MAP_YELLOWBOX, TBSTYLE_BUTTON,3);
	m_wndToolBar.SetButtonText(3, "����");	

	m_wndToolBar.SetButtonInfo(4, ID_MENU_MAP_MAN_WALL_BALL, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonText(4, "����");

	m_wndToolBar.SetButtonInfo(5, ID_MENU_MAP_BKGROUND, TBSTYLE_BUTTON, 5);
	m_wndToolBar.SetButtonText(5, "����");
	

	CRect rectToolBar;
	//�õ���ť�Ĵ�С
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	//���ð�ť�Ĵ�С
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(26,26));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//����ͣ��
	EnableDocking(CBRS_ALIGN_ANY);
	//Ư��ͣ��
	CPoint pt(GetSystemMetrics(SM_CXSCREEN)/2+100,GetSystemMetrics(SM_CYSCREEN)/3+100);
	FloatControlBar(&m_wndToolBar,pt);

	return TRUE;
}

//ѡ��Ŀ�ĵ�
void CBoxman_EditerWnd::OnMenuMapBall() 
{
	m_now_Select = MAP_BALL;
}

//ѡ��ͨ��
void CBoxman_EditerWnd::OnMenuMapBluewall() 
{
	m_now_Select = MAP_BLUEWALL;	
}
//ѡ����
void CBoxman_EditerWnd::OnMenuMapManWallBall() 
{
	m_now_Select = MAP_MANWALL;	
}

//ѡ��ǽ
void CBoxman_EditerWnd::OnMenuMapWhitewall() 
{
	m_now_Select = MAP_WHITEWALL;	
}

//ѡ������
void CBoxman_EditerWnd::OnMenuMapYellowbox() 
{
	m_now_Select = MAP_YELLOWBOX;	
}

//ѡ�б���
void CBoxman_EditerWnd::OnMenuMapBkground() 
{
	m_now_Select = MAP_BACKGROUP;
	
}

void CBoxman_EditerWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	//��¼��ǰ�����λ�ã��Ա�������Ч����ʵ��
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
	//��ʶ��걻����
	m_bMouseDown = TRUE;
	//��ȡ����λ�ò�������ڵ�ͼ��Ӧ�ķ���λ��
	m_mousePoint = point;
	x = point.x / MAP_SMALL_SQUARE_SIZE;
	y = point.y / MAP_SMALL_SQUARE_SIZE;
	//�޸ĵ�ͼ��Ӧλ�õ�״̬
	m_boxManEdit.ChangeMap(x,y,m_now_Select);
	//֪ͨ�����ػ�
	Invalidate(FALSE);

	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CBoxman_EditerWnd::OnPaint() 
{
	
	CPaintDC dc(this);    // ������Ļ��ʾ���豸
	CDC dcMemory;  // �ڴ��豸
	
	CBitmap bitmap;
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	if (!dc.IsPrinting()) 
	{
		
		// ��dc�豸����
		if (dcMemory.CreateCompatibleDC(&dc))
		{	
			// ʹ��bitmap��ʵ����ʾ���豸����
			if (bitmap.CreateCompatibleBitmap(&dc, m_rcClient.right, m_rcClient.bottom))
			{
				// �ڴ��豸ѡ�������λͼ
				dcMemory.SelectObject(&bitmap);
				
				//���Ƶ�ͼ		
				m_boxManEdit.DrawMap(&dcMemory);

				//����������ͼ��	
				int x = m_mousePoint.x-MAP_SMALL_SQUARE_SIZE/2;
				int y = m_mousePoint.y-MAP_SMALL_SQUARE_SIZE/2;
				m_boxManEdit.DrawMouseCursor(x,y,m_now_Select,&dcMemory);
				
				
				// ���ڴ��豸�����ݿ�����ʵ����Ļ��ʾ���豸
				dc.BitBlt(m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom, &dcMemory, 0, 0, SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}	
}



void CBoxman_EditerWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//��¼���״̬Ϊ�ͷ�״̬
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

	//��������ȷ���ύ�ɹ���
	if(loadMapDlg.DoModal() == IDOK)
	{
		//��ȡ��༭����������α�����ֵ
		int iMissionNum = loadMapDlg.m_loadMapNum;
		//������ص�ͼ
		m_boxManEdit.LoadMap(iMissionNum);
	}	
}
