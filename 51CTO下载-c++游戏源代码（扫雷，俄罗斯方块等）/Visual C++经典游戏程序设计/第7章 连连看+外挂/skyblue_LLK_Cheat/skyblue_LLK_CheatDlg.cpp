//
/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLK_CheatDlg.cpp

Abstract:

	the game's cheating-kernal-solving Dialog class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "skyblue_LLK_Cheat.h"
#include "skyblue_LLK_CheatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





#define BKCOLOR         RGB(128,128,128)	//背景颜色
#define FRONTWIDTH	    (39+2)			    //前面方块的宽度
#define FRONTHEIGHT	    (39+12)			    //前面方块的高度
#define BKWIDTH	        46					//背景方块的宽度
#define BKHEIGHT        56					//背景方块的高度
#define ROWCOUNT        7					//行数
#define COLCOUNT        12					//列数

#define BLANK_STATE     -1                  //空方块(没有任何动物)
#define INVALID_POS     -1                  //无效坐标位置

#define BLOCK_WIDTH_SIZE	        (39+2)					//背景方块的宽度
#define BLOCK_HEIGHT_SIZE        (39+12)					//背景方块的高度

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_LLK_CheatDlg dialog

CSkyblue_LLK_CheatDlg::CSkyblue_LLK_CheatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkyblue_LLK_CheatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkyblue_LLK_CheatDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//记录方块置为无效状态
	m_nY1= INVALID_POS;
	m_nX1= INVALID_POS;

	//初始化行列数
	m_nRow=ROWCOUNT;
	m_nCol=COLCOUNT;

	m_hHackDC = NULL; 
	m_hwndHack = NULL;

	//不是自动作弊(控制目标程序销方块
	m_bAutoKick = FALSE;

	//根据行列数动态分配内核数据数组空间
	m_map=new int[m_nRow*m_nCol];

}

void CSkyblue_LLK_CheatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkyblue_LLK_CheatDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSkyblue_LLK_CheatDlg, CDialog)
	//{{AFX_MSG_MAP(CSkyblue_LLK_CheatDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_HACK, OnButtonHack)
	ON_BN_CLICKED(IDC_BT_AUTO_KICK, OnButtonAutoKick)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_LLK_CheatDlg message handlers

BOOL CSkyblue_LLK_CheatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//获取程序框架的设备环境
	CDC *pWinDC = GetDC();		
	//整个游戏区域内存位图	
	m_MemDC.CreateCompatibleDC(pWinDC);
	m_memBitmap.CreateCompatibleBitmap(pWinDC,m_nCol*FRONTWIDTH+5,m_nRow*FRONTHEIGHT+5);
	m_MemDC.SelectObject(&m_memBitmap);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSkyblue_LLK_CheatDlg::OnPaint() 
{
		CPaintDC dc(this); 

		dc.BitBlt(30,70,               //在对话框的偏移位置
			m_DestClientRect.Width(),  //图像宽度
			m_DestClientRect.Height(), //图像高度
			&m_MemDC                   //来源于与内存设备环境关联的内存位图
			,0,0,SRCCOPY               //0偏移拷贝
			);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkyblue_LLK_CheatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//
//X直接连通
//
BOOL CSkyblue_LLK_CheatDlg::X1_Link_X2(int x, int y1,int y2)
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
BOOL CSkyblue_LLK_CheatDlg::Y1_Link_Y2(int x1,int x2,int y)
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
BOOL CSkyblue_LLK_CheatDlg::LineX(int x,int y1,int y2)
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
BOOL CSkyblue_LLK_CheatDlg::LineY(int x1,int x2,int y)
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
BOOL CSkyblue_LLK_CheatDlg::OneCornerLink(int x1, int y1,int x2, int y2)
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
BOOL CSkyblue_LLK_CheatDlg::TwoCornerLink(int x1, int y1, int x2, int y2)
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
		if(m_map[y1*m_nCol+x]!=BLANK_STATE)
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

BOOL CSkyblue_LLK_CheatDlg::XThrough(int x, int y, BOOL bAdd)
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

BOOL CSkyblue_LLK_CheatDlg::YThrough(int x, int y,BOOL bAdd)
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
BOOL CSkyblue_LLK_CheatDlg::IsLink(int x1, int y1, int x2, int y2)
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
// 自动找出两个可以连通的方块
//
BOOL CSkyblue_LLK_CheatDlg::Find2Rect(int &x1,int &y1, int &x2, int &y2)
{
	BOOL bFound=FALSE;
	int* pMap=m_map;
	
	//第一个方块从地图的0位置开始
	for(int i=0;i<m_nRow*m_nCol;i++)
	{
		//找到则跳出循环
		if(bFound)
			break;
		//无动物的空格跳过
		if(pMap[i]==BLANK_STATE)
			continue;
		
		//第二个方块从前一个方块的后面开始
		for(int j=i+1;j<m_nRow*m_nCol;j++)
		{
			
			//第二个方块不为空 且与第一个方块的动物相同
			if(pMap[j]!=BLANK_STATE&&pMap[i]==pMap[j])
			{
				//算出对应的虚拟行列位置
				x1=i%m_nCol;
				y1=i/m_nCol;/*+(x1?1:0)*/
				x2=j%m_nCol;
				y2=j/m_nCol;/*+(x2?1:0)*/
				
				//判断是否可以连通
				if(IsLink(x1,y1,x2,y2))
				{
					bFound=TRUE;
					break;
				}
			}
		}			
	}
	
	return bFound;
}

//
//  尝试侵入目标程序
//
BOOL CSkyblue_LLK_CheatDlg::HackIn(CString strWinName)
{
	//进入目标窗口，获取其控制权
	CWnd * m_pWndHack = FindWindow(NULL,strWinName);
	m_hwndHack = m_pWndHack->GetSafeHwnd();
	
	if(m_hwndHack != NULL)
	{
		m_hHackDC = ::GetDC(m_hwndHack);
		
		::GetClientRect(m_hwndHack,&m_DestClientRect);
		//	TextOut(m_hHackDC,100,100,"hi, my name is 007, you have been hacke!!",20);
		
		//拷贝目标程序的画面到本端内存位图
		::BitBlt(m_MemDC,0,0,
			m_DestClientRect.Width(),
			m_DestClientRect.Height(),
			m_hHackDC,0,0,SRCCOPY);
		
		//分析图像并生成本端地图数据
		GenMap();
		
		::ReleaseDC(m_hwndHack, m_hHackDC);

		return TRUE;
	}
	else
	{
		return FALSE;	
	}
	
}



//
// 根据图像分析生成游戏地图
//
void CSkyblue_LLK_CheatDlg::GenMap()
{
	int colorDate;
	int i = 0;

	for(i=0;i<m_nRow*m_nCol;i++)
	{
		//算出对应的虚拟行列位置
		int x=i%m_nCol;
		int y=i/m_nCol;

		colorDate = GetRectData(x,y);
		m_map[i] = colorDate;
	}
}

//
// 分析出位置(x,y)方块的图像类别
//
int CSkyblue_LLK_CheatDlg::GetRectData( int x, int y)
{
	COLORREF colorArray[5];
	int colorDate;


	int basicX,basicY; //该方块的左上角基本位置;
	basicX = x * BLOCK_WIDTH_SIZE;
	basicY =  y* BLOCK_HEIGHT_SIZE;	
	
	//取该方块的5个点判断
/*
	   *
	 * * * 
	   *
*/
	CPoint aPos[5];
	
	aPos[0].x = basicX+BLOCK_WIDTH_SIZE/2;
	aPos[0].y = basicY+BLOCK_HEIGHT_SIZE/2+3;
	aPos[1].x = basicX+BLOCK_WIDTH_SIZE/2;
	aPos[1].y = basicY+BLOCK_HEIGHT_SIZE/2-3;
	
	aPos[2].x = basicX+BLOCK_WIDTH_SIZE/2;
	aPos[2].y = basicY+BLOCK_HEIGHT_SIZE/2;
	
	aPos[3].x = basicX+BLOCK_WIDTH_SIZE/2+3;
	aPos[3].y = basicY+BLOCK_HEIGHT_SIZE/2;
	aPos[4].x = basicX+BLOCK_WIDTH_SIZE/2-3;
	aPos[4].y = basicY+BLOCK_HEIGHT_SIZE/2;
	
	
	int xPos, yPos;//坐标位置	
	for( int i=0; i< 5; i++)
	{
		xPos = aPos[i].x;
		yPos= aPos[i].y;
		//记录5个象素值
		colorArray[i]= GetPixel(m_MemDC,xPos,yPos);
	}
	

	int nSameCount = 0;
	for(i=0; i<4; i++)
	{	
		//将方块中采样的5个点的象素值累加
		colorDate += colorArray[i];	

		if(colorArray[i] == colorArray[i+1] &&
			colorArray[i] == RGB(128,128,128))
		{
			nSameCount++;
		}	
	}

	//判断是不是空白方块	
	//如果超过3点相同，则是背景
	if(nSameCount>=3)
	{
		return BLANK_STATE;
	}	
	
	return colorDate;
}


//
//  作弊按钮消息处理
//
void CSkyblue_LLK_CheatDlg::OnButtonHack() 
{
	Hack();	
}

//
//  一次完整的入侵攻击操作
//
void CSkyblue_LLK_CheatDlg::Hack(void)
{
	//操作成功判断记录值
	BOOL bOk; 

	//入侵获取目标程序控制权
	//目标程序名称
	CString strWinName = "skyblue 连连看";
	bOk = HackIn(strWinName);	
	if(!bOk)
	{
		MessageBox("获取失败,目标游戏可能没有运行");
		return;
	}
	
	//分析寻找一组可销的方块
	int x1,y1,x2,y2;
	bOk = Find2Rect(x1, y1, x2, y2);	
	if(!bOk)
	{
		MessageBox("找不到一组可销方块，可能游戏已经胜利");	
		return;
	}

	//根据标记选择作弊的功能	
	if(m_bAutoKick)
	{
		//远端销除找到的两个可连通方块			
		RemoteButtonKick(x1,y1,x2,y2);
	}
	else
	{
		//在本端以及目标程序端绘制提示图像		
		Local_RemoteHintDraw(x1,y1,x2,y2);
	}
}

//
// 在本端以及目标程序端绘制提示图像
//
void CSkyblue_LLK_CheatDlg::Local_RemoteHintDraw( int x1, int y1, int x2, int y2)
{
		//本端显示找到的两个可连通方块		
		CBrush brush(RGB(255,0,0));
		m_MemDC.SelectObject(&brush);
		//标记方块1
		m_MemDC.Ellipse(x1*FRONTWIDTH,y1*FRONTHEIGHT,
			x1*FRONTWIDTH+20,y1*FRONTHEIGHT+20);
		//标记方块2			
		m_MemDC.Ellipse(x2*FRONTWIDTH,y2*FRONTHEIGHT,
			x2*FRONTWIDTH+20,y2*FRONTHEIGHT+20);	
		Invalidate(FALSE);

		//目标程序的绘图实现
		m_hHackDC = ::GetDC(m_hwndHack);
		SelectObject(m_hHackDC,brush.m_hObject);
		Ellipse(m_hHackDC,x1*FRONTWIDTH,y1*FRONTHEIGHT,
			x1*FRONTWIDTH+20,y1*FRONTHEIGHT+20);
		Ellipse(m_hHackDC,x2*FRONTWIDTH,y2*FRONTHEIGHT,
			x2*FRONTWIDTH+20,y2*FRONTHEIGHT+20);
}

//
//  模拟远端程序的鼠标点击
//
void CSkyblue_LLK_CheatDlg::RemoteButtonKick( int x1, int y1, int x2, int y2)
{
		int DestX,DestY;				
		//发送鼠标DOWN的消息
		DestX =  x1*FRONTWIDTH +FRONTWIDTH/2;
		DestY = y1*FRONTHEIGHT + FRONTHEIGHT/2;
		//鼠标点击的坐标
		LPARAM lParam = MAKELPARAM(DestX,DestY);
		::SendMessage(m_hwndHack,WM_LBUTTONDOWN,MK_LBUTTON,lParam);
		::SendMessage(m_hwndHack,WM_LBUTTONUP,MK_LBUTTON,lParam);
		
		DestX =  x2*FRONTWIDTH +FRONTWIDTH/2;
		DestY = y2*FRONTHEIGHT + FRONTHEIGHT/2;
		//鼠标点击的坐标
		lParam = MAKELPARAM(DestX,DestY);
		::SendMessage(m_hwndHack,WM_LBUTTONDOWN,MK_LBUTTON,lParam);
		::SendMessage(m_hwndHack,WM_LBUTTONUP,MK_LBUTTON,lParam);
		
		Invalidate(FALSE);
}

//
//  配置修改按钮 "远端自动销行"or"本端显示"
//
void CSkyblue_LLK_CheatDlg::OnButtonAutoKick() 
{
	//取反，修改原来配置
	m_bAutoKick = !m_bAutoKick;	

	CString btHackSelectInfo;
	CString btHackInfo;
	if(m_bAutoKick)
	{
		btHackSelectInfo = "(&S)屏蔽自动销块功能";
		btHackInfo = "(&H)销除一组可销方块";
	}
	else
	{
		btHackSelectInfo = "(&S)启动自动销块功能";
		btHackInfo = "(&H)获取一组可销方块";
	}

	//根据修改后的值设置按钮的提示
	SetDlgItemText(IDC_BT_AUTO_KICK,btHackSelectInfo);
	SetDlgItemText(IDC_BT_HACK,btHackInfo);
}


