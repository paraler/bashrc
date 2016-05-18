/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLKDlg.cpp

Abstract:

	LLK-Game's kernal-solving Dialog

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "skyblue_LLK.h"
#include "skyblue_LLKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C_LLK_Dlg dialog

#define BKCOLOR         RGB(128,128,128)	//背景颜色
#define FRONTWIDTH	    (39+2)			    //前面方块的宽度
#define FRONTHEIGHT	    (39+12)			    //前面方块的高度
#define BKWIDTH	        46					//背景方块的宽度
#define BKHEIGHT        56					//背景方块的高度
#define ROWCOUNT        7					//行数
#define COLCOUNT        12					//列数

#define BLANK_STATE     -1                  //空方块(没有任何动物)

/////////////////////////////////////////////////////////////////////////////
// C_LLK_Dlg dialog

C_LLK_Dlg::C_LLK_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C_LLK_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C_LLK_Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//记录方块置为无效状态
	m_nY1= BLANK_STATE;
	m_nX1= BLANK_STATE;

	//初始化行列数
	m_nRow=ROWCOUNT;
	m_nCol=COLCOUNT;

	//根据行列数动态分配内核数据数组空间
	m_map=new int[m_nRow*m_nCol];
}

C_LLK_Dlg::~C_LLK_Dlg()
{
	//释放动态数组空间
	delete[] m_map;
}

void C_LLK_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C_LLK_Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C_LLK_Dlg, CDialog)
	//{{AFX_MSG_MAP(C_LLK_Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_LLK_Dlg message handlers

BOOL C_LLK_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//获取程序框架的设备环境
	CDC *pWinDC = GetDC();	

	//内存设备环境以及内存位图的创建，初始化,关联

	//3D方块边框图样内存位图
	m_mem3DBkDC.CreateCompatibleDC(pWinDC);
	m_mem3DBkBmp.LoadBitmap(IDB_BITMAP_3D_FRAMES);
	m_mem3DBkDC.SelectObject(&m_mem3DBkBmp);
	//动物图样内存位图
	m_memAnimalDC.CreateCompatibleDC(pWinDC);
	m_memAnimalBmp.LoadBitmap(IDB_BMP_ANIMAL);
	m_memAnimalDC.SelectObject(&m_memAnimalBmp);
	//整个游戏区域内存位图	
	m_MemDC.CreateCompatibleDC(pWinDC);
	m_memBitmap.CreateCompatibleBitmap(pWinDC,
		m_nCol*FRONTWIDTH+5,
		m_nRow*FRONTHEIGHT+5);
	m_MemDC.SelectObject(&m_memBitmap);
	
	//开始一个新的游戏
	StartNewGame();

	//放在最桌面的前面显示
	HWND hWnd = ::AfxGetMainWnd()->m_hWnd;
	::SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C_LLK_Dlg::StartNewGame()
{
	//初始化地图,将地图中所有方块区域位置置为空方块状态
	for(int iNum=0;iNum<(m_nCol*m_nRow);iNum++)
	{
		m_map[iNum] = BLANK_STATE;
	}

	//部下随机种子
	srand(time(NULL));

	//生成随机地图
	//将所有匹配成对的动物物种放进一个临时的地图中
	CDWordArray tmpMap;	
	for(int i=0;i<(m_nCol*m_nRow)/4;i++)
		for(int j=0;j<4;j++)
			tmpMap.Add(i);

	//每次从上面的临时地图中取走(获取后并在临时地图删除)
	//一个动物放到地图的空方块上
	for(i=0;i<m_nRow*m_nCol;i++)
	{	
		//随机挑选一个位置
		int nIndex=(int(rand()*0.1+rand()*0.01+rand()))%tmpMap.GetSize();
		//获取该选定物件放到地图的空方块
		m_map[i]=tmpMap.GetAt(nIndex);

		//在临时地图除去该动物
		tmpMap.RemoveAt(nIndex);		
	}
	

	//更新显示
	Invalidate(TRUE);
}

//
//  游戏区域的绘制
//
void C_LLK_Dlg::GameDraw(CDC * pDC)
{
	//绘制背景颜色
	pDC->FillSolidRect(0,0,m_nCol*FRONTWIDTH+5,m_nRow*FRONTHEIGHT+5,BKCOLOR);

	for(int i=0;i<m_nRow;i++)
	{
		for(int j=0;j<m_nCol;j++)
		{			
			if(m_map[i*m_nCol+j]==BLANK_STATE)
			{
			continue;
			}
			//绘制方块边框
			pDC->BitBlt(j*FRONTWIDTH,i*FRONTHEIGHT,
				BKWIDTH,BKHEIGHT,
				&m_mem3DBkDC,
				0,BKHEIGHT,
				SRCCOPY);
			//绘制方块
			//因为要使得效果透明，所以由图样的底色以及表面两部分构成
			pDC->BitBlt(j*FRONTWIDTH,i*FRONTHEIGHT,
				FRONTWIDTH-2,FRONTHEIGHT-12,
				&m_memAnimalDC,
				FRONTWIDTH-2,m_map[i*m_nCol+j]*(FRONTHEIGHT-12),
				SRCAND);
			pDC->BitBlt(j*FRONTWIDTH,i*FRONTHEIGHT,
				FRONTWIDTH-2,FRONTHEIGHT-12,
				&m_memAnimalDC,
				0,m_map[i*m_nCol+j]*(FRONTHEIGHT-12),
				SRCPAINT);
		}
	}
}



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR C_LLK_Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void C_LLK_Dlg::OnPaint() 
{
		CPaintDC dc(this); // device context for painting
		
		//先将整个游戏区域的图像绘制到内存位图
		GameDraw(&m_MemDC);
		//将内存位图中绘制好的图像一次性拷贝到屏幕
		dc.BitBlt(0,0,m_nCol*FRONTWIDTH,m_nCol*FRONTHEIGHT,&m_MemDC,0,0,SRCCOPY);
}

//
// 鼠标左键消息处理
//
void C_LLK_Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//1.计算鼠标点击方块的的位置
	int x=point.x/FRONTWIDTH+(point.x%FRONTWIDTH?1:0)-1;
	int y=point.y/FRONTHEIGHT+(point.y%FRONTHEIGHT?1:0)-1;
	
	//2.在游戏区域内并且该区域还有该区域不是空的区域
	if(x<m_nCol&&y<m_nRow&&m_map[y*m_nCol+x]!= BLANK_STATE)
	{
		
		
		//3.假设尚未记录第一个方块
		if(m_nX1==BLANK_STATE)
		{
			//4.记录第一个方块的位置
			m_nX1=x;
			m_nY1=y;
			
			//获取程序框架的设备环境
			CDC *pWinDC = GetDC();
			
			//临时绘制点中的方块外框
			//只绘屏幕不载入内存位图
			CPen myPen;
			CPen *pOldPen;
			myPen.CreatePen(PS_SOLID, 4, RGB(255,0,0));
			pOldPen = 	pWinDC->SelectObject(&myPen);
			//方块外框绘制，线条环绕绘制框架
			pWinDC->MoveTo(x*FRONTWIDTH,y*FRONTHEIGHT);
			pWinDC->LineTo(x*FRONTWIDTH,(y+1)*FRONTHEIGHT);
			pWinDC->LineTo((x+1)*FRONTWIDTH,(y+1)*FRONTHEIGHT);
			pWinDC->LineTo((x+1)*FRONTWIDTH,y*FRONTHEIGHT);
			pWinDC->LineTo(x*FRONTWIDTH,y*FRONTHEIGHT);
			//现场恢复
			pWinDC->SelectObject(pOldPen);
		}
		else
		{ 
			//5.判断是否点击的方块非本身, 是否点击同一种动物
			if((m_nX1!=x||m_nY1!=y)&& 
			  m_map[m_nY1*m_nCol+m_nX1]==m_map[y*m_nCol+x]
				)
			{
				//6.检测是否可以消除
				if(IsLink(m_nX1,m_nY1,x,y))
				{
					//7.数据清理
					m_map[m_nY1*m_nCol+m_nX1]=BLANK_STATE;
					m_map[y*m_nCol+x]=BLANK_STATE;
				}				
			}
			//8.清空记录方块的值
			m_nX1=BLANK_STATE;  
			m_nY1=BLANK_STATE;	
						
			//通知重绘
			Invalidate(FALSE);
		}
	}
	
	//察看是否已经胜利
	if(IsWin())
	{
		MessageBox("恭喜您胜利闯关,即将开始新局");
		StartNewGame();
	}
}


//
//X直接连通
//
BOOL C_LLK_Dlg::X1_Link_X2(int x, int y1,int y2)
{
	//保证y1的值小于y2
	if(y1>y2)
	{
		//数据交换
		int n=y1;
		y1=y2;
		y2=n;
	}

	//直通 	
	for(int i=y1+1;i<=y2;i++)
	{
		if(i==y2)
			return TRUE;
		if(m_map[i*m_nCol+x]!=BLANK_STATE)
			break;
	}
	//左通
	if(XThrough(x-1,y1,FALSE)&&XThrough(x-1,y2,FALSE))
		return TRUE;
	//右通
	if(XThrough(x+1,y1,TRUE)&&XThrough(x+1,y2,TRUE))
		return TRUE;
	return FALSE;
}

//
//Y直接连通
//
BOOL C_LLK_Dlg::Y1_Link_Y2(int x1,int x2,int y)
{
	if(x1>x2)
	{
		int x=x1;
		x1=x2;
		x2=x;
	}
	//直通
	for(int i=x1+1;i<=x2;i++)
	{
		if(i==x2)
			return TRUE;
		if(m_map[y*m_nCol+i]!=BLANK_STATE)
			break;
	}
	//上通
	if(YThrough(x1,y-1,FALSE)&&YThrough(x2,y-1,FALSE))
		return TRUE;
	//下通
	if(YThrough(x1,y+1,TRUE)&&YThrough(x2,y+1,TRUE))
		return TRUE;
	return FALSE;
}

//
// 是否同一直线通
//
BOOL C_LLK_Dlg::LineX(int x,int y1,int y2)
{
	if(y1>y2)
	{
		int y=y1;
		y1=y2;
		y2=y;
	}
	for(int y=y1;y<=y2;y++)
	{
		if(m_map[y*m_nCol+x]!=BLANK_STATE)
			return FALSE;
		if(y==y2)
			return TRUE;
	}
	return FALSE;
}

//
// 是否同一直线通
//
BOOL C_LLK_Dlg::LineY(int x1,int x2,int y)
{
	if(x1>x2)
	{
		int x=x1;
		x1=x2;
		x2=x;
	}
	for(int x=x1;x<=x2;x++)
	{
		if(m_map[y*m_nCol+x]!=BLANK_STATE)
			return FALSE;
		if(x==x2)
			return TRUE;
	}
	return FALSE;
}

//
//  1直角接口连通
//
BOOL C_LLK_Dlg::OneCornerLink(int x1, int y1,int x2, int y2)
{
	if(x1>x2)
	{
		int n=x1;
		x1=x2;
		x2=n;
		n=y1;
		y1=y2;
		y2=n;
	}
	if(y2<y1)
	{
		if(LineY(x1+1,x2,y1)&&LineX(x2,y1,y2+1))
			return TRUE;
		if(LineY(x2-1,x1,y2)&&LineX(x1,y2,y1-1))
			return TRUE;
		return FALSE;
	}	
	else
	{
		if(LineY(x1+1,x2,y1)&&LineX(x2,y1,y2-1))
			return TRUE;
		if(LineY(x2-1,x1,y2)&&LineX(x1,y2,y1+1))
			return TRUE;		
		return FALSE;
	}
	return FALSE;
}

//
//  2直角接口连通
//
BOOL C_LLK_Dlg::TwoCornerLink(int x1, int y1, int x2, int y2)
{
	if(x1>x2)
	{
		int n=x1;
		x1=x2;
		x2=n;
		n=y1;
		y1=y2;
		y2=n;
	}
	//右通
	if(XThrough(x1+1,y1,TRUE)&&XThrough(x2+1,y2,TRUE))
		return TRUE;
	//左通
	if(XThrough(x1-1,y1,FALSE)&&XThrough(x2-1,y2,FALSE))
		return TRUE;
	//上通
	if(YThrough(x1,y1-1,FALSE)&&YThrough(x2,y2-1,FALSE))
		return TRUE;
	//下通
	if(YThrough(x1,y1+1,TRUE)&&YThrough(x2,y2+1,TRUE))
		return TRUE;
	//右
	for(int x=x1+1;x<m_nCol;x++)
	{
		if(m_map[y1*m_nCol+x]>-1)
			break;
		if(OneCornerLink(x,y1,x2,y2))
			return TRUE;
	}
	//左
	for(x=x1-1;x>-1;x--)
	{
		if(m_map[y1*m_nCol+x]!=BLANK_STATE)
			break;
		if(OneCornerLink(x,y1,x2,y2))
			return TRUE;
	}
	//上
	for(int y=y1-1;y>-1;y--)
	{
		if(m_map[y*m_nCol+x1]!=BLANK_STATE)
			break;
		if(OneCornerLink(x1,y,x2,y2))
			return TRUE;
	}
	//下
	for(y=y1+1;y<m_nRow;y++)
	{
		if(m_map[y*m_nCol+x1]!=BLANK_STATE)
			break;
		if(OneCornerLink(x1,y,x2,y2))
			return TRUE;
	}
	
	return FALSE;
}

BOOL C_LLK_Dlg::XThrough(int x, int y, BOOL bAdd)
{
	if(bAdd)
	{
		for(int i=x;i<m_nCol;i++)
			if(m_map[y*m_nCol+i]!=BLANK_STATE)
				return FALSE;
	}
	else
	{
		for(int i=0;i<=x;i++)
			if(m_map[y*m_nCol+i]!=BLANK_STATE)
				return FALSE;
	}
	return TRUE;
}

BOOL C_LLK_Dlg::YThrough(int x, int y,BOOL bAdd)
{
	if(bAdd)
	{
		for(int i=y;i<m_nRow;i++)
			if(m_map[i*m_nCol+x]!=BLANK_STATE)
				return FALSE;
	}
	else
	{
		for(int i=0;i<=y;i++)
			if(m_map[i*m_nCol+x]!=BLANK_STATE)
				return FALSE;
	}
	return TRUE;
}

//
//  判断选中的两个方块是否可以消除
//
BOOL C_LLK_Dlg::IsLink(int x1, int y1, int x2, int y2)
{
	//X直连方式
	if(x1==x2)
	{
		if(X1_Link_X2(x1,y1,y2))
			return TRUE;
	}
	//Y直连方式
	else if(y1==y2)
	{
		if(Y1_Link_Y2(x1,x2,y1))
			return TRUE;
	}

	//一个转弯直角的联通方式
	if(OneCornerLink(x1,y1,x2,y2))
	{
		return TRUE;
	}
	//两个转弯直角的联通方式
	else if(TwoCornerLink(x1,y1,x2,y2))
	{
		return TRUE;
	}
	return FALSE;
}

//
//  截获键盘消息 F2 (用于新游戏开始)
//
BOOL C_LLK_Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_F2)
		{
			StartNewGame();

		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//
//   检测是否已经赢得了游戏
//
BOOL C_LLK_Dlg::IsWin(void)
{
	//检测所有是否尚有非未被消除的方块
	// (非BLANK_STATE状态)
	for(int i=0;i<m_nRow*m_nCol;i++)
	{
		if(m_map[i] != BLANK_STATE)
		{
			return FALSE;
		}
	}

	return TRUE;
}



