// skyblue_RectView.cpp : implementation of the CSkyblue_RectView class
//

#include "stdafx.h"
#include "skyblue_Rect.h"

#include "skyblue_RectDoc.h"
#include "skyblue_RectView.h"
#include "OptionDlg.h"

//音乐播放
#include "mmsystem.h"
#pragma comment(lib,"Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectView

IMPLEMENT_DYNCREATE(CSkyblue_RectView, CView)

BEGIN_MESSAGE_MAP(CSkyblue_RectView, CView)
	//{{AFX_MSG_MAP(CSkyblue_RectView)
	ON_COMMAND(ID_GAME_EXIT, OnGameExit)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
	// Standard printing commands

	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_START, OnGameStart)
	ON_COMMAND(ID_GAME_END, OnGameEnd)
	ON_COMMAND(ID_GAME_OPTION, OnGameOption)
	ON_UPDATE_COMMAND_UI(ID_GAME_START, OnUpdateGameStart)
	ON_UPDATE_COMMAND_UI(ID_GAME_OPTION, OnUpdateGameOption)
	ON_UPDATE_COMMAND_UI(ID_GAME_END, OnUpdateGameEnd)
	ON_UPDATE_COMMAND_UI(ID_GAME_EXIT, OnUpdateGameExit)
	ON_UPDATE_COMMAND_UI(ID_HELP_ABOUT, OnUpdateHelpAbout)
	ON_UPDATE_COMMAND_UI(ID_HELP_HELP, OnUpdateHelpHelp)
	ON_WM_CREATE()
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_UPDATE_COMMAND_UI(ID_OPTION_AREA1, OnUpdateOptionArea1)
	ON_UPDATE_COMMAND_UI(ID_OPTION_AREA2, OnUpdateOptionArea2)
	ON_UPDATE_COMMAND_UI(ID_OPTION_AREA3, OnUpdateOptionArea3)
	ON_UPDATE_COMMAND_UI(ID_OPTION_AREA4, OnUpdateOptionArea4)
	ON_COMMAND(ID_OPTION_AREA1, OnOptionArea1)
	ON_COMMAND(ID_OPTION_AREA2, OnOptionArea2)
	ON_COMMAND(ID_OPTION_AREA3, OnOptionArea3)
	ON_COMMAND(ID_OPTION_AREA4, OnOptionArea4)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL1, OnUpdateOptionLevel1)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL2, OnUpdateOptionLevel2)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL3, OnUpdateOptionLevel3)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL4, OnUpdateOptionLevel4)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL5, OnUpdateOptionLevel5)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LEVEL6, OnUpdateOptionLevel6)
	ON_COMMAND(ID_OPTION_LEVEL1, OnOptionLevel1)
	ON_COMMAND(ID_OPTION_LEVEL2, OnOptionLevel2)
	ON_COMMAND(ID_OPTION_LEVEL3, OnOptionLevel3)
	ON_COMMAND(ID_OPTION_LEVEL4, OnOptionLevel4)
	ON_COMMAND(ID_OPTION_LEVEL5, OnOptionLevel5)
	ON_COMMAND(ID_OPTION_LEVEL6, OnOptionLevel6)
	ON_UPDATE_COMMAND_UI(ID_OPTION_GRID, OnUpdateOptionGrid)
	ON_COMMAND(ID_OPTION_GRID, OnOptionGrid)
	ON_UPDATE_COMMAND_UI(ID_OPTION_MUSIC, OnUpdateOptionMusic)
	ON_COMMAND(ID_OPTION_MUSIC, OnOptionMusic)
	ON_UPDATE_COMMAND_UI(ID_GAME_PAUSH, OnUpdateGamePaush)
	ON_COMMAND(ID_GAME_PAUSH, OnGamePaush)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectView construction/destruction

CSkyblue_RectView::CSkyblue_RectView()
{
	//第一次开始游戏
	m_bFistPlay = TRUE;

	//缺省为不是游戏暂停状态
	m_bGamePaush = FALSE;

	//缺省为不插放背景音乐
	m_bMusic = FALSE;
	
	//缺省为画网格线
	m_bDrawGrid = TRUE;

	//总分值清零
	m_iPerformance = 0;

	//测试值：为12行，10列
	m_iRow = 12;
	m_iCol = 10;

	//左上角X，Y坐标
	m_iStartX = 10;
	m_iStartY = 10;

	//缺省级别为3级
	m_iLevel = 2;
	//第一种样式
	m_iBlockSytle = 0;

	//缺省方块大小为m_iLarge个象素
	m_iLarge = 30;

	//缺省游戏是结束的
	m_bGameEnd = TRUE;

	int i,j;

	//赋初值
	for (i=0;i<100;i++)
		for (j=0;j<100;j++)
			GameStatus[i][j]=0;

	//各种形状方块的接触面数据，参见设计书的接触面表格, 
	//如果某种形状的方块没有4个接触面，则后面的数据填-1
	for (i=0;i<74;i++)
		for (j=0;j<4;j++)
			InterFace[i][j] = -1;

/*
1  ----
*/
	InterFace[1][0] = 3;
	
	InterFace[11][0] = 0;	InterFace[11][1] = 1;	InterFace[11][2] = 2;	InterFace[11][3] = 3;
/*
2	--
	--
*/  
	InterFace[2][0] = 1;	InterFace[2][1] = 3;
/*
3   -
   ---

*/	
	InterFace[3][0] = 0;	InterFace[3][1] = 2;	InterFace[3][2] = 3;
	
	InterFace[31][0] = 2;	InterFace[31][1] = 3;
	
	InterFace[32][0] = 0;	InterFace[32][1] = 2;	InterFace[32][2] = 3;
	
	InterFace[33][0] = 0;	InterFace[33][1] = 3;
/*
4  --
  --
*/	
	InterFace[4][0] = 1;	InterFace[4][1] = 3;
	
	InterFace[41][0] = 0;	InterFace[41][1] = 2;	InterFace[41][2] = 3;
/*
5  --
    --
*/	
	InterFace[5][0] = 1;	InterFace[5][1] = 3;

	InterFace[51][0] = 0;	InterFace[51][1] = 2;	InterFace[51][2] = 3;
/*
6  --
    -
	-
*/	
	InterFace[6][0] = 0;	InterFace[6][1] = 3;
	
	InterFace[61][0] = 1;	InterFace[61][1] = 2;	InterFace[61][2] = 3;

	InterFace[62][0] = 2;	InterFace[62][1] = 3;

	InterFace[63][0] = 0;	InterFace[63][1] = 1;	InterFace[63][2] = 3;
/*
7  --
   -
   -
*/
	InterFace[7][0] = 2;	InterFace[7][1] = 3;	
	InterFace[71][0] = 1;	InterFace[71][1] = 2;	InterFace[71][2] = 3;

	InterFace[72][0] = 0;	InterFace[72][1] = 3;

	InterFace[73][0] = 0;	InterFace[73][1] = 1;	InterFace[73][2] = 3;

}

CSkyblue_RectView::~CSkyblue_RectView()
{
}

BOOL CSkyblue_RectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_RectView drawing






//创建一些设备
int CSkyblue_RectView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	


	//决定第一次掉下来的方块的样式
	m_inextStatus = Random(7);
	
	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
*
*  名称：OnDraw
*
*  功能：承担所有绘制屏幕工作
*
*  最后修改时间：2005.8.6
*
* * * * * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnDraw(CDC* pDC)
{
	DcEnvInitial();
	DrawGame(&m_memDC);  //在内存位图的游戏区域绘制

	pDC->BitBlt(0,0,m_nWidth,m_nHeight,&m_memDC,0,0,SRCCOPY);
}
//
//绘图设备环境的初始化
//
void CSkyblue_RectView::DcEnvInitial(void)
{
	if(m_bFistPlay)
	{
		m_bFistPlay = FALSE;
		//用默认的参数，获取当前屏幕设备环境
		CDC *pWindowDC = GetDC();

		//1.用于映射屏幕的内存设备环境
		//获取游戏窗口的大小用于下面设置内存位图的尺寸
		CRect windowRect;
		GetClientRect(&windowRect);
		m_nWidth = windowRect.Width();
		m_nHeight = windowRect.Height();

		//内存设备环境与屏幕设备环境关联（兼容）
		m_memDC.CreateCompatibleDC(pWindowDC);
		//内存位图与与屏幕关联(兼容),大小为游戏窗口的尺寸
		m_memBmp.CreateCompatibleBitmap(pWindowDC,m_nWidth,m_nHeight);
		//内存设备环境与内存位图关联，以便通过m_memDC在内存位图上作画
		m_memDC.SelectObject(&m_memBmp);

		//2.存储方块位图的内存资源
		//内存设备环境与屏幕设备环境关联（兼容）
		m_memRectDC.CreateCompatibleDC(pWindowDC);
		//相当于将外部位图rect.bmp动态载入m_hMemRectBmp中
		m_hMemRectBmp=(HBITMAP)LoadImage(NULL,"rect.bmp",IMAGE_BITMAP,150,30,LR_LOADFROMFILE);
		//内存设备环境与内存位图关联，以便通过m_memDC在内存位图上作画
		SelectObject(m_memRectDC.m_hDC, m_hMemRectBmp);	


	
	//黑色的黑笔
	m_pBlackPen  = new CPen(PS_SOLID,1,BLACK);

	//画刷
	m_pGrayBrush  = new CBrush(RGB(66,66,66));
	m_pBlackBrush  = new CBrush(BLACK);
	}
}

void CSkyblue_RectView::DCEnvClear(void)
{
	//设备环境
	m_memDC.DeleteDC();
	m_memRectDC.DeleteDC();
	//位图资源
	DeleteObject(m_memBmp);
	DeleteObject(m_hMemRectBmp);


	delete(m_pBlackPen);
	delete(m_pGrayBrush);
	delete(m_pBlackBrush);

}


void CSkyblue_RectView::DrawGame(CDC *pDC)
{
		int i,j;
	//选用黑色画刷，绘制整个游戏所在窗口的背景
	pDC -> SelectObject(m_pBlackBrush);
	CRect rect;
	GetClientRect(&rect);
	pDC -> Rectangle(rect);

	//选用灰色画刷，绘制游戏区域的背景
	pDC -> SelectObject(m_pGrayBrush);
	pDC -> Rectangle(m_iStartY ,m_iStartX, m_iStartY + 301, m_iStartX + 360);	

	pDC->SelectObject(m_pBlackPen);	
	//画网格线
	if (m_bDrawGrid)
	{
		//画横线
		for (i=0;i<m_iRow;i++)
		{
			pDC->MoveTo(m_iStartY, m_iStartX + i*m_iLarge);
			pDC->LineTo(m_iStartY+300, m_iStartX +i*m_iLarge);
		}	
		
		//画竖线
		for (i=0;i<m_iCol;i++)
		{
			pDC->MoveTo(m_iStartY+i*m_iLarge, m_iStartX);
			pDC->LineTo(m_iStartY+i*m_iLarge, m_iStartX+360);
		}
	}

	int x,y,nW,nH;

	//小方块的绘制
	for (i=0;i<m_iRow;i++)
		for (j=0;j<m_iCol;j++)
		{
			if (GameStatus[i][j]==MAP_STATE_NOT_EMPTY)
			{
				//在游戏区域中状态为被占用状态的区域绘制小方块
				x = m_iStartY+j*m_iLarge +2;
				y = m_iStartX+i*m_iLarge +2;
				nW = m_iLarge-4;
				nH = m_iLarge-4;
			pDC->BitBlt(x,y,nW,nH,&m_memRectDC,m_iBlockSytle*30,0,SRCCOPY);
			}
		}

	//显示游戏区域及游戏级别的汉字描述
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX+220, "游戏区域大小：");
		pDC -> TextOut(m_iStartY+320, m_iStartX+240,m_strArea);

		pDC -> TextOut(m_iStartY+320, m_iStartX+280, "游戏级别：");
		pDC -> TextOut(m_iStartY+320, m_iStartX+300,m_strLevel);
	}
				
	//显示总分
	if (!m_bGameEnd)
	{
		CString lsStr;	
		lsStr.Format("总分为：%d 分",m_iPerformance);
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX+180,lsStr);
	}

	//画下一次将要出现的方块，用于提示用户
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX,"下一个方块：");

		int x,y,nW,nH;		
		for (UINT k=0;k<4;k++)
		{
			i = NextStatus[k][0];
		    j = NextStatus[k][1];

				x = m_iStartY+j*30 +2+320;
				y = m_iStartX+i*30 +2+30;
				nW = m_iLarge-4;
				nH = m_iLarge-4;
		pDC->BitBlt(x,y,nW,nH,&m_memRectDC,m_iBlockSytle*30,0,SRCCOPY);
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
*
*  名称：OnTimer
*
*  功能：承担所有驱动工作
*
*  最后修改时间：2005.8.6
*
* * * * * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnTimer(UINT nIDEvent) 
{
	//如果原来的方块已到底或游戏刚开始，则掉下一个新的方块
	int i,j,k;
	if (m_isBottom)
	{
		//1.产生下一个随机下坠物
		m_icurrentStatus = m_inextStatus;
		m_inextStatus = Random(7);  //得到下一次的方块样式
	//	if (m_inextStatus==0) m_inextStatus++;

		//2.修改新的“下一下坠物”
		RectStatusToNextStatus( m_inextStatus );
	//	CRect rect(m_iStartY+320, m_iStartX, m_iStartY+440, m_iStartX+160);
	//	InvalidateRect(&rect);
	//	Invalidate(FALSE);
		
		//3.将旧的“下一下坠物”用作当前使用
		m_currentRect = m_icurrentStatus;   
		//根据当前下坠物的形状去初始化激活状态下的下坠物坐标
		RectStatusToActiveStatus( m_icurrentStatus );
		//将当前动态数组中的数据反映到大数组中
		ActiveStatusToGameStatus();
		m_isBottom = FALSE;

		//4.判断当前方块是否已到底
		IsBottom();

    	//5.判断游戏是否已结束: 碰了底，且第1行有小方块
		if (m_isBottom)
			for (i=0;i<m_iCol;i++)
				if (GameStatus[0][i])
				{
					KillTimer(1);
					AfxMessageBox("游戏已结束！");
					for (j=0;j<m_iRow;j++)
						for (k=0;k<m_iCol;k++)
							GameStatus[j][k]=0;
					Invalidate(FALSE);
					m_bGameEnd = TRUE;
					break;
				}

	}
	else  //当前方块下降
	{
		RectDown();
	}
	
	CView::OnTimer(nIDEvent);
}


/* * * * * * * * * * * * * * * * * * * * * *
* 函数：产生一个最大值不大于指定值的随机正整数(Random)
*
* 参数：MaxNumber : 随机数的上限
* 
* 返回值: 产生的随机数
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
int CSkyblue_RectView::Random(int MaxNumber)
{
	//部下随机种子
	srand( (unsigned)time( NULL ) );
	//产生随机数
	int random = rand() % MaxNumber;
	//保证非0
	if(random == 0 ) random++;

	return random;
}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：将当前下坠物的位置映射到游戏区域地图数组中去
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::ActiveStatusToGameStatus()
{
	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];
	GameStatus[x1][y1]=MAP_STATE_NOT_EMPTY;
	GameStatus[x2][y2]=MAP_STATE_NOT_EMPTY;
	GameStatus[x3][y3]=MAP_STATE_NOT_EMPTY;
	GameStatus[x4][y4]=MAP_STATE_NOT_EMPTY;
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：初始掉落时，将根据方块的样式决定当前动态数组的值
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectStatusToActiveStatus(int m_which)
{

	switch(m_which)
	{
	case 1:   
		ActiveStatus[0][0] = 0;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 1;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 2;	ActiveStatus[2][1] = 5;	ActiveStatus[3][0] = 3;	ActiveStatus[3][1] = 5;
		break;
	case 2:    
		ActiveStatus[0][0] = 0;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 1;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 0;	ActiveStatus[2][1] = 6;	ActiveStatus[3][0] = 1;	ActiveStatus[3][1] = 6;
		break;
	case 3:
		ActiveStatus[0][0] = 1;	ActiveStatus[0][1] = 4;	ActiveStatus[1][0] = 0;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 1;	ActiveStatus[2][1] = 5;	ActiveStatus[3][0] = 1;	ActiveStatus[3][1] = 6;
		break;
	case 4:
		ActiveStatus[0][0] = 0;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 1;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 1;	ActiveStatus[2][1] = 6;	ActiveStatus[3][0] = 2;	ActiveStatus[3][1] = 6;
		break;
	case 5:
		ActiveStatus[0][0] = 1;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 2;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 0;	ActiveStatus[2][1] = 6;	ActiveStatus[3][0] = 1;	ActiveStatus[3][1] = 6;
		break;
	case 6:
		ActiveStatus[0][0] = 0;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 0;	ActiveStatus[1][1] = 6;
		ActiveStatus[2][0] = 1;	ActiveStatus[2][1] = 6;	ActiveStatus[3][0] = 2;	ActiveStatus[3][1] = 6;
		break;
	case 7:
		ActiveStatus[0][0] = 0;	ActiveStatus[0][1] = 5;	ActiveStatus[1][0] = 1;	ActiveStatus[1][1] = 5;
		ActiveStatus[2][0] = 2;	ActiveStatus[2][1] = 5;	ActiveStatus[3][0] = 0;	ActiveStatus[3][1] = 6;
		break;
	}
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：初始掉落时，将根据方块的样式决定下一次将要掉下来的动态数组的值
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectStatusToNextStatus(int m_which)
{
	switch(m_which)
	{
	case 1:
		NextStatus[0][0] = 0;	NextStatus[0][1] = 1;	NextStatus[1][0] = 1;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 2;	NextStatus[2][1] = 1;	NextStatus[3][0] = 3;	NextStatus[3][1] = 1;
		break;
	case 2:
		NextStatus[0][0] = 0;	NextStatus[0][1] = 1;	NextStatus[1][0] = 1;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 0;	NextStatus[2][1] = 2;	NextStatus[3][0] = 1;	NextStatus[3][1] = 2;
		break;
	case 3:
		NextStatus[0][0] = 1;	NextStatus[0][1] = 0;	NextStatus[1][0] = 0;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 1;	NextStatus[2][1] = 1;	NextStatus[3][0] = 1;	NextStatus[3][1] = 2;
		break;
	case 4:
		NextStatus[0][0] = 0;	NextStatus[0][1] = 1;	NextStatus[1][0] = 1;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 1;	NextStatus[2][1] = 2;	NextStatus[3][0] = 2;	NextStatus[3][1] = 2;
		break;
	case 5:
		NextStatus[0][0] = 1;	NextStatus[0][1] = 1;	NextStatus[1][0] = 2;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 0;	NextStatus[2][1] = 2;	NextStatus[3][0] = 1;	NextStatus[3][1] = 2;
		break;
	case 6:
		NextStatus[0][0] = 0;	NextStatus[0][1] = 1;	NextStatus[1][0] = 0;	NextStatus[1][1] = 2;
		NextStatus[2][0] = 1;	NextStatus[2][1] = 2;	NextStatus[3][0] = 2;	NextStatus[3][1] = 2;
		break;
	case 7:
		NextStatus[0][0] = 0;	NextStatus[0][1] = 1;	NextStatus[1][0] = 1;	NextStatus[1][1] = 1;
		NextStatus[2][0] = 2;	NextStatus[2][1] = 1;	NextStatus[3][0] = 0;	NextStatus[3][1] = 2;
		break;
	}
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：当前方块下降
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectDown()
{
	IsBottom();
	if (!m_isBottom)
	{
		//清除以前的方块
		int x1,x2,x3,x4,y1,y2,y3,y4;
		x1 = ActiveStatus[0][0];
		x2 = ActiveStatus[1][0];
		x3 = ActiveStatus[2][0];
		x4 = ActiveStatus[3][0];
		y1 = ActiveStatus[0][1];
		y2 = ActiveStatus[1][1];
		y3 = ActiveStatus[2][1];
		y4 = ActiveStatus[3][1];
		GameStatus[x1][y1]=MAP_STATE_EMPTY;
		GameStatus[x2][y2]=MAP_STATE_EMPTY;
		GameStatus[x3][y3]=MAP_STATE_EMPTY;
		GameStatus[x4][y4]=MAP_STATE_EMPTY;
		InvalidateCurrent();

		//方块下落
		ActiveStatus[0][0] += 1;
		ActiveStatus[1][0] += 1;
		ActiveStatus[2][0] += 1;
		ActiveStatus[3][0] += 1;
		GameStatus[x1+1][y1]=MAP_STATE_NOT_EMPTY;
		GameStatus[x2+1][y2]=MAP_STATE_NOT_EMPTY;
		GameStatus[x3+1][y3]=MAP_STATE_NOT_EMPTY;
		GameStatus[x4+1][y4]=MAP_STATE_NOT_EMPTY;

		InvalidateCurrent();
	}
}

	
/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：当前方块下降加速，左移，右移
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectArrow(int m_Type)
{
	//获取当前下坠物4个小方块的位置坐标
	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];

	//对不同的移动命令指示进行分类实现
	switch(m_Type)
	{
	case LEFT:
		//对每种不同的移动命令指示特性作相应的可移动分析
		if ( (ActiveStatus[0][1]>0) && IsLeftLimit() && !m_isBottom)
		{
			//清原来的方块
			GameStatus[x1][y1]=MAP_STATE_EMPTY;
			GameStatus[x2][y2]=MAP_STATE_EMPTY;
			GameStatus[x3][y3]=MAP_STATE_EMPTY;
			GameStatus[x4][y4]=MAP_STATE_EMPTY;

		//	InvalidateCurrent();
			//添加新的移动后数据状态
			ActiveStatus[0][1] -= 1;
			ActiveStatus[1][1] -= 1;
			ActiveStatus[2][1] -= 1;
			ActiveStatus[3][1] -= 1;
			GameStatus[x1][y1-1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x2][y2-1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x3][y3-1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x4][y4-1]=MAP_STATE_NOT_EMPTY;

			InvalidateCurrent();
		}
		break;

	case RIGHT:
		if ( (ActiveStatus[3][1]< m_iCol-1) && IsRightLitmit() && !m_isBottom)
		{
			//清原来的方块
			GameStatus[x1][y1]=MAP_STATE_EMPTY;
			GameStatus[x2][y2]=MAP_STATE_EMPTY;
			GameStatus[x3][y3]=MAP_STATE_EMPTY;
			GameStatus[x4][y4]=MAP_STATE_EMPTY;

		//	InvalidateCurrent();
			//添加新的移动后数据状态
			ActiveStatus[0][1] += 1;
			ActiveStatus[1][1] += 1;
			ActiveStatus[2][1] += 1;
			ActiveStatus[3][1] += 1;
			GameStatus[x1][y1+1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x2][y2+1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x3][y3+1]=MAP_STATE_NOT_EMPTY;
			GameStatus[x4][y4+1]=MAP_STATE_NOT_EMPTY;
			
			InvalidateCurrent();
		}
		break;

	case DOWN:
		RectDown();
		break;
	}
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：判断当前方块是否已到底，并且销行等相关的工作
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::IsBottom()
{
	//到底有两种概念：1是已到底部，2是下面碰到了另外的方块
	int x1,x2,x3,x4;
	int x,xx,yy,i;

	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];


	//是否为底部的判断
	//1。到达游戏区域的底部
	//2。与接触面正下方的小方块区域为被占用状态
	if (x1>=m_iRow-1 || x2>=m_iRow-1 || x3>=m_iRow-1 || x4>=m_iRow-1)
		m_isBottom = TRUE;
	else
	{
		for (i=0;i<4;i++)
		{
			if (InterFace[m_currentRect][i] > -1)
			{//取当前下坠物有接触面的方块

				//获取有接触面的小方块的编号
				x=InterFace[m_currentRect][i];
				//根据编号获取ActiveStatus中该小方块的整下方的坐标
				xx=ActiveStatus[x][0]+1;
				yy=ActiveStatus[x][1];
				//判断该接触面整下方的小方块区域是否为被占用状态
				if (GameStatus[xx][yy]==MAP_STATE_NOT_EMPTY)
					m_isBottom = TRUE;
			}
		}
	}

	BOOL m_bIsSucced;
	int k,j;
	int m_iMuch=0; //本次销掉的行数

	//计分规则：一次销掉一行，加100分，一次销掉两行，加400分，三行，900分
	//例如销掉x行，则分数为：x*(x*100)

	if (m_isBottom)
	{
		//判断是否已得分
		for (i=0;i<m_iRow;i++)
		{
			m_bIsSucced = TRUE;
			for (j=0;j<m_iCol;j++)
				if (GameStatus[i][j]==MAP_STATE_EMPTY)
					m_bIsSucced = FALSE;
			
			//如果得分，则销掉此行
			if (m_bIsSucced)
			{
				for (k=i;k>0;k--)
					for (j=0;j<m_iCol;j++)
						GameStatus[k][j] = GameStatus[k-1][j];
				//第1行清零
				for (j=0;j<m_iCol;j++)
					GameStatus[0][j]=MAP_STATE_EMPTY;

				m_iMuch += 1;
			}
		}
		
		if (m_iMuch>0)
		{
			m_iPerformance += m_iMuch * m_iMuch * 100;
			//刷新游戏区域
			CRect rect1(m_iStartY, m_iStartX, m_iStartY+300, m_iStartX+360);
			//InvalidateRect(&rect1);
			
			//刷新分数区域
			CRect rect2(m_iStartY+320, m_iStartX+180, m_iStartY+440, m_iStartX+200);
			//InvalidateRect(&rect2);
			Invalidate(FALSE);
		}

	}

}

/* * * * * * * * * * * * * * * * * * * * * * * * *
*
*  名称：OnKeyDown
*
*  功能：处理用户的输入，方块的左，右移，加速及变形
*
*  最后修改时间：2005.8.6
*
* * * * * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
	case VK_LEFT:
		RectArrow(LEFT);
		break;
	case VK_RIGHT:
		RectArrow(RIGHT);
		break;
	case VK_UP:
		RectChange();
		break;
	case VK_DOWN:
		RectArrow(DOWN);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：方块是否还可以左移
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
BOOL CSkyblue_RectView::IsLeftLimit()
{

	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];

	//根据当前下坠物的具体形态，分析判断其是否有向左移动的空间
	switch(m_currentRect)
	{
		/*
		|
		   |
	       |   "1"字形形态类型，判断其四个方块的正左边都没有任何物件（空间没有被占据)
		   |

		 */
	case 1:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1] || GameStatus[x4][y4-1])
			return FALSE;
		break;
	case 11:
		if (GameStatus[x1][y1-1])
			return FALSE;
		break;
	case 2:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1])
			return FALSE;
		break;
	case 3:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1])
			return FALSE;
		break;
	case 31:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 32:
		if (GameStatus[x1][y1-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 33:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x4][y4-1])
			return FALSE;
		break;
	case 4:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x4][y4-1])
			return FALSE;
		break;
	case 41:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1])
			return FALSE;
		break;
	case 5:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 51:
		if (GameStatus[x1][y1-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 6:
		if (GameStatus[x1][y1-1] || GameStatus[x3][y3-1] || GameStatus[x4][y4-1])
			return FALSE;
		break;
	case 61:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1])
			return FALSE;
		break;
	case 62:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 63:
		if (GameStatus[x1][y1-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 7:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 71:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1])
			return FALSE;
		break;
	case 72:
		if (GameStatus[x1][y1-1] || GameStatus[x2][y2-1] || GameStatus[x3][y3-1])
			return FALSE;
		break;
	case 73:
		if (GameStatus[x1][y1-1] || GameStatus[x4][y4-1])
			return FALSE;
		break;
	}

	return TRUE;			
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：方块是否还可以右移
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
BOOL CSkyblue_RectView::IsRightLitmit()
{

	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];
	
	switch(m_currentRect)
	{
	case 1:
		if (GameStatus[x1][y1+1] || GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 11:
		if (GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 2:
		if (GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 3:
		if (GameStatus[x2][y2+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 31:
		if (GameStatus[x1][y1+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 32:
		if (GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 33:
		if (GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 4:
		if (GameStatus[x1][y1+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 41:
		if (GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 5:
		if (GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 51:
		if (GameStatus[x2][y2+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 6:
		if (GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 61:
		if (GameStatus[x2][y2+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 62:
		if (GameStatus[x1][y1+1] || GameStatus[x2][y2+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 63:
		if (GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 7:
		if (GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 71:
		if (GameStatus[x1][y1+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 72:
		if (GameStatus[x2][y2+1] || GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	case 73:
		if (GameStatus[x3][y3+1] || GameStatus[x4][y4+1])
			return FALSE;
		break;
	}

	return TRUE;
			

}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：方块的变形
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectChange()
{
	//先预先变形，然后判断变形后的方块是否有空间，如有足够空间，则进行实际变形，否则不变
	int xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4;
	int m_lscurrentRect;
	
	CString lsStr;
	
	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];

	//变形后位置在数组中的存放顺序仍需遵循先左后右，在同一列中先上后下
	xx1=x1; xx2=x2; xx3=x3; xx4=x4; yy1=y1; yy2=y2; yy3=y3; yy4=y4;
	switch(m_currentRect)
	{
	case 1:
		xx1=x1+1; yy1=y1-1; xx3=x3-1; yy3=y3+1; xx4=x4-2; yy4=y4+2;
		m_lscurrentRect = 11;
		break;
	case 11:
		xx1=x1-1; yy1=y1+1; xx3=x3+1; yy3=y3-1; xx4=x4+2; yy4=y4-2;
		m_lscurrentRect = 1;
		break;
	case 2:
		m_lscurrentRect=2; 
		break;
	case 3:
		xx1=x1-2; yy1=y1+1; xx4=x4-1; yy4=y4;
		m_lscurrentRect = 31;
		break;
	case 31:
		xx1=x1+1; yy1=y1-1; 
		m_lscurrentRect = 32;
		break;
	case 32:
		xx1=x1+1; yy1=y1; xx4=x4+2; yy4=y4-1;
		m_lscurrentRect=33;
		break;
	case 33:
		xx4=x4-1; yy4=y4+1;
		m_lscurrentRect=3;
		break;
	case 4:
		xx1=x1+2; yy1=y1-1; xx3=x3+1; yy3=y3-1; xx4=x4-1;
		m_lscurrentRect = 41;
		break;
	case 41:
		xx1=x1-2; yy1=y1+1; xx3=x3-1; yy3=y3+1; xx4=x4+1;
		m_lscurrentRect = 4;
		break;
	case 5:
		xx1=x1-1; xx2=x2-2; yy2=y2+1; xx3=x3+1; yy4=y4+1;
		m_lscurrentRect = 51;
		break;
	case 51:
		xx1=x1+1; xx2=x2+2; yy2=y2-1; xx3=x3-1; yy4=y4-1;
		m_lscurrentRect = 5;
		break;
	case 6:
		xx2=x1+1; yy2=y2-1; xx3=x3-1; xx4=x4-2; yy4 = yy4+1;
		m_lscurrentRect = 61;
		break;
	case 61:
		xx3=x3+2; yy3=y3-1; xx4=x4+2; yy4=y4-1;
		m_lscurrentRect = 62;
		break;
	case 62:
		xx1=x1+1; yy1=y1-1; xx3=x3-2; yy3=y3+1; xx4=x4-1;
		m_lscurrentRect = 63;
		break;
	case 63:
		xx1=x1-2; yy1=y1+1; xx2=x2-2; yy2=y2+1;
		m_lscurrentRect = 6;
		break;
	case 7:
		xx3=x3-1; yy3=y3+1; xx4=x4+1; yy4=y4+1;
		m_lscurrentRect = 71;
		break;
	case 71:
		xx1=x1+2; xx2=x2-1; yy2=y2+1; xx4=x4+1; yy4=y4-1;
		m_lscurrentRect = 72;
		break;
	case 72:
		xx1=x1-2; xx3=x3-1; yy3=y3+1; xx4=x4-1; yy4=y4+1;
		m_lscurrentRect = 73;
		break;
	case 73:
		xx2=x2+1; yy2=y2-1; xx3=x3+2; yy3=y3-2; xx4=x4-1; yy4=y4-1;
		m_lscurrentRect = 7;
		break;
	}

	//如果变形后所在的区域内无其他方块，则表示有足够空间，可以变形
	//且不能超越边界
	GameStatus[x1][y1] = MAP_STATE_EMPTY;
	GameStatus[x2][y2] = MAP_STATE_EMPTY;
	GameStatus[x3][y3] = MAP_STATE_EMPTY;
	GameStatus[x4][y4] = MAP_STATE_EMPTY;
	if (GameStatus[xx1][yy1]==MAP_STATE_EMPTY &&
		GameStatus[xx2][yy2]==MAP_STATE_EMPTY &&
		GameStatus[xx3][yy3]==MAP_STATE_EMPTY && 
		GameStatus[xx4][yy4]==MAP_STATE_EMPTY 
		&& yy1>=0 && yy4<=m_iCol-1 
		&& !(xx1<0 || xx2<0 || xx3<0 || xx4<0) 
		&& !(xx1>m_iRow-1 || xx2>m_iRow-1 || xx3>m_iRow-1 || xx4>m_iRow-1) )
	{
		InvalidateCurrent();

		ActiveStatus[0][0]=xx1;
		ActiveStatus[1][0]=xx2;
		ActiveStatus[2][0]=xx3;
		ActiveStatus[3][0]=xx4;
		ActiveStatus[0][1]=yy1;
		ActiveStatus[1][1]=yy2;
		ActiveStatus[2][1]=yy3;
		ActiveStatus[3][1]=yy4;

		GameStatus[xx1][yy1] = MAP_STATE_NOT_EMPTY;
		GameStatus[xx2][yy2] = MAP_STATE_NOT_EMPTY;
		GameStatus[xx3][yy3] = MAP_STATE_NOT_EMPTY;
		GameStatus[xx4][yy4] = MAP_STATE_NOT_EMPTY;

		InvalidateCurrent();

		//改变形状代码
		m_currentRect = m_lscurrentRect;
	}
	else
	{//恢复原来状态
		GameStatus[x1][y1] = MAP_STATE_NOT_EMPTY;
		GameStatus[x2][y2] = MAP_STATE_NOT_EMPTY;
		GameStatus[x3][y3] = MAP_STATE_NOT_EMPTY;
		GameStatus[x4][y4] = MAP_STATE_NOT_EMPTY;
	}

	//判断是否已到底
	IsBottom();
}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：游戏开始
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnGameStart() 
{
	if (!m_bGamePaush)  //如果不是游戏暂停状态，则必须作些初始工作
	{
		m_bGameEnd = FALSE;
		//总分值清零, 并显示总分记分牌
		m_iPerformance = 0;
	
		//显示当前的区域及游戏级别的汉字描述
		CurrentAreaAndLevel();
		
		CRect rect(m_iStartY, m_iStartX, m_iStartY+440, m_iStartX+370);
		InvalidateRect(&rect);
	}

	m_bGamePaush = FALSE;
	SetTimer(1,1500-250*m_iLevel,NULL);
}


//游戏暂停
void CSkyblue_RectView::OnGamePaush() 
{
	m_bGamePaush = TRUE;

	KillTimer(1);
}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：游戏结束
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnGameEnd() 
{
	m_bGameEnd = TRUE;

	int i,j;
	for (i=0;i<m_iRow;i++)
		for (j=0;j<m_iCol;j++)
			GameStatus[i][j]=0;

	CRect rect(m_iStartY, m_iStartX, m_iStartY+440, m_iStartX+370);
	InvalidateRect(&rect);

	m_bGamePaush = FALSE;  //清除游戏暂停状态

	KillTimer(1);	

}

/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：刷新当前的区域
*
* 只刷新需要刷新的四个小方块区域，防止屏幕抖动情况发生
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::InvalidateCurrent()
{
	int i;
	
	for (i=0;i<4;i++)
	{
	CRect rect(m_iStartX+ActiveStatus[i][1]*m_iLarge, 
				m_iStartY+ActiveStatus[i][0]*m_iLarge,
				m_iStartX+(ActiveStatus[i][1]+1)*m_iLarge+5,
				m_iStartY+(ActiveStatus[i][0]+1)*m_iLarge);
			//InvalidateRect(&rect);
			Invalidate(FALSE);
	}
}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：游戏设置
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnGameOption() 
{
	//参数顺序： 区域大小代码：0-3，分别为：12X10，18X15，24X20，m_iLargeX25
	//级别：0-5，分别为：1500，1200，1000，800，600，400
	//背景音乐：TRUE 或者 FALSE
	int m_lsArea;
	switch(m_iRow)
	{
	case 12:
		m_lsArea = 0;
		break;
	case 18:
		m_lsArea = 1;
		break;
	case 24:
		m_lsArea = 2;
		break;
	case 30:
		m_lsArea = 3;
		break;
	}

	COptionDlg dlg(m_lsArea,m_iLevel,m_iBlockSytle,m_bMusic,m_bDrawGrid);
	
	if (dlg.DoModal()==IDOK)
	{
		//确定区域的大小
		switch(dlg.m_iArea)
		{
		case 0:
			m_iRow = 12;
			m_iCol = 10;
			m_iLarge = 30;
			break;
		case 1:
			m_iRow = 18;
			m_iCol = 15;
			m_iLarge = 20;
			break;
		case 2:
			m_iRow = 24;
			m_iCol = 20;
			m_iLarge = 15;
			break;
		case 3:
			m_iRow = 30;
			m_iCol = 25;
			m_iLarge = 12;
			break;
		}

		//确定级别
		m_iLevel = dlg.m_iLevel;
		//选择的样式
		m_iBlockSytle = dlg.m_iBlockStyle;

		//确定是否绘网格背景
		m_bDrawGrid = dlg.m_bDrawGrid;

        //检查是否插放音乐								  
		m_bMusic = dlg.m_bMusic;
		if (m_bMusic)
			PlayMid();
		else
			StopMid();

		Invalidate();
	}	
}


//用于生成当前区域大小与级别所对应的汉字描述
void CSkyblue_RectView::CurrentAreaAndLevel()
{
	switch(m_iRow)
	{
	case 12:
		m_strArea = "12行10列"; break;
	case 18:
		m_strArea = "18行15列"; break;
	case 24:
		m_strArea = "24行20列"; break;
	case 30:
		m_strArea = "30行25列"; break;
	}

	switch(m_iLevel)
	{
	case 0:
		m_strLevel = "第一级: 入门级"; break;
	case 1:
		m_strLevel = "第二级: 初级级"; break;
	case 2:
		m_strLevel = "第三级: 中级"; break;
	case 3:
		m_strLevel = "第四级: 中高级"; break;
	case 4:
		m_strLevel = "第五级: 高级"; break;
	case 5:
		m_strLevel = "第六级: 顶级"; break;
	}
}


/* * * * * * * * * * * * * * * * * * * * * *
* 内部函数：以下为菜单屏蔽与开启控制
*
* 最后修改日期：2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
//如果游戏开始，则此[开始游戏]按钮被屏蔽
void CSkyblue_RectView::OnUpdateGameStart(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd || m_bGamePaush)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//如果游戏开始，则此[游戏设置]按钮被屏蔽
void CSkyblue_RectView::OnUpdateGameOption(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//如游戏开始，则[游戏暂停]按钮开启
void CSkyblue_RectView::OnUpdateGamePaush(CCmdUI* pCmdUI) 
{
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//如果游戏开始，则此[游戏结束]按钮被开启
void CSkyblue_RectView::OnUpdateGameEnd(CCmdUI* pCmdUI) 
{
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
	
}

//如果游戏开始，则此[退出系统]按钮被屏蔽
void CSkyblue_RectView::OnUpdateGameExit(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//如果游戏开始，则此[关于]按钮被屏蔽
void CSkyblue_RectView::OnUpdateHelpAbout(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//如果游戏开始，则此[帮助]按钮被屏蔽
void CSkyblue_RectView::OnUpdateHelpHelp(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(FALSE);	
}


void CSkyblue_RectView::OnHelpHelp() 
{

}


//用菜单设置区域大小
void CSkyblue_RectView::OnUpdateOptionArea1(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iRow==12)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}
void CSkyblue_RectView::OnUpdateOptionArea2(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iRow==18)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}
void CSkyblue_RectView::OnUpdateOptionArea3(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iRow==24)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}

void CSkyblue_RectView::OnUpdateOptionArea4(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iRow==30)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);	
}


//用菜单设置区域大小
void CSkyblue_RectView::OnOptionArea1() 
{
	m_iRow = 12;
	m_iCol = 10;
	m_iLarge = 30;
	Invalidate();
}

void CSkyblue_RectView::OnOptionArea2() 
{
	m_iRow = 18;
	m_iCol = 15;
	m_iLarge = 20;
	Invalidate();
}

void CSkyblue_RectView::OnOptionArea3() 
{
	m_iRow = 24;
	m_iCol = 20;
	m_iLarge = 15;
	Invalidate();
}

void CSkyblue_RectView::OnOptionArea4() 
{
	m_iRow = 30;
	m_iCol = 25;
	m_iLarge = 12;
	Invalidate();
}

// 用菜单设置游戏级别 
void CSkyblue_RectView::OnUpdateOptionLevel1(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 0)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnUpdateOptionLevel2(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 1)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnUpdateOptionLevel3(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 2)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnUpdateOptionLevel4(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 3)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnUpdateOptionLevel5(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 4)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnUpdateOptionLevel6(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd) 
		pCmdUI -> Enable(TRUE);
	else 
		pCmdUI -> Enable(FALSE);

	if (m_iLevel == 5)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}


//用菜单设置游戏级别
void CSkyblue_RectView::OnOptionLevel1() 
{
	m_iLevel = 0;
}

void CSkyblue_RectView::OnOptionLevel2() 
{
	m_iLevel = 1;
}

void CSkyblue_RectView::OnOptionLevel3() 
{
	m_iLevel = 2;
}

void CSkyblue_RectView::OnOptionLevel4() 
{
	m_iLevel = 3;
}

void CSkyblue_RectView::OnOptionLevel5() 
{
	m_iLevel = 4;
}

void CSkyblue_RectView::OnOptionLevel6() 
{
	m_iLevel = 5;
}


//用菜单设置是否有网格
void CSkyblue_RectView::OnUpdateOptionGrid(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI -> Enable(TRUE);
	else
		pCmdUI -> Enable(FALSE);

	if (m_bDrawGrid)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnOptionGrid() 
{
	if (m_bDrawGrid)
		m_bDrawGrid = FALSE;
	else
		m_bDrawGrid = TRUE;

	Invalidate();
}

//
//插放背景音乐, 所有错误忽略
//
void CSkyblue_RectView::PlayMid()
{
	HWND hWnd;
	hWnd = GetSafeHwnd();
	//分配命令字符串缓冲，错误信息储存缓冲，播放的文件名
	char szCmdBuf[300],errBuf[60],szfileName[255];
	//错误码
	MCIERROR mciError;

	//初始化设备元素
	strcpy(szfileName,"skyblue_rect.mid"); 
	//初始化命令字符串
	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
	//打开设备
	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
	if (mciError == 0)
	{//如果打开成功则播放
		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
		//根据播放操作是否成功决定是否关闭设备
		if (mciError != 0)
			mciSendString("close bkMusic",NULL,0,NULL);
	}
}

//
//终止插放背景音乐
//
void CSkyblue_RectView::StopMid()
{
	//关闭设备
	mciSendString("close bkMusic",NULL,0,NULL);
}

//用菜单设置是否插放音乐
void CSkyblue_RectView::OnUpdateOptionMusic(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI -> Enable(TRUE);
	else
		pCmdUI -> Enable(FALSE);

	if (m_bMusic)
		pCmdUI -> SetCheck(TRUE);
	else
		pCmdUI -> SetCheck(FALSE);
}

void CSkyblue_RectView::OnOptionMusic() 
{
	if (m_bMusic)
	{
		m_bMusic = FALSE;
		StopMid();
	}
	else
	{
		m_bMusic = TRUE;
		PlayMid();
	}
	
}

void CSkyblue_RectView::OnGameExit() 
{
	//清理内存设备环境，释放资源
	DCEnvClear();	
}

void CSkyblue_RectView::OnHelpAbout() 
{
	HWND hwnd = ::AfxGetMainWnd()->GetSafeHwnd();

	ShellAbout(hwnd,"俄罗斯方块  作者:skyblue 风中解码","E-mail:skyblue@yahoo.com.cn",NULL);	
}

