/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_PinTuView.cpp

Abstract:

	View , manage drawing 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "skyblue_PinTu.h"

#include "skyblue_PinTuDoc.h"
#include "skyblue_PinTuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuView

IMPLEMENT_DYNCREATE(CSkyblue_PinTuView, CView)

BEGIN_MESSAGE_MAP(CSkyblue_PinTuView, CView)
	//{{AFX_MSG_MAP(CSkyblue_PinTuView)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuView construction/destruction

CSkyblue_PinTuView::CSkyblue_PinTuView()
{
	// TODO: add construction code here
m_bFirstRun = TRUE;
}

CSkyblue_PinTuView::~CSkyblue_PinTuView()
{
}

BOOL CSkyblue_PinTuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuView drawing

void CSkyblue_PinTuView::OnDraw(CDC* pDC)
{
	//a.获取文档数据控制权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//b.使用内存设备环境memDC
	//  与内存环境关联的内存位图memBmp
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(pDC,
		pDoc->m_bmpWidth,pDoc->m_bmpHeight);
	memDC.SelectObject(&memBmp);

	//c. 将图像绘制到内存位图memBmp中

	//1.绘制游戏所有当前散乱的方块
	DrawGameBlocks(&memDC);
	//2.绘制空白方块
	DrawBlankBlock(&memDC);
	//3.绘制边界间隔线条
	DrawLines(&memDC);

	//d.整幅图从内存memBmp拷贝到屏幕
	pDC->BitBlt(0,0,pDoc->m_bmpWidth,pDoc->m_bmpHeight,
				&memDC,0,0,SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuView diagnostics

#ifdef _DEBUG
void CSkyblue_PinTuView::AssertValid() const
{
	CView::AssertValid();
}

void CSkyblue_PinTuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuView message handlers

//
//  绘制方块间的边界线
//
void CSkyblue_PinTuView::DrawLines(CDC *pDC)
{
	//创建并设定铅笔的样式
	CPen linePen;
	linePen.CreatePen(PS_SOLID, 3, RGB(255,0,0));	
	CPen *pOldPen = pDC->SelectObject(&linePen);

	//获取文档核心数据访问权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();
	
	int i;
	//竖向线绘制
	for(i=1;i<pDoc->hnums;i++)
	{
		pDC->MoveTo(i*pDoc->m_cellWidth-1,0);
		pDC->LineTo(i*pDoc->m_cellWidth-1,pDoc->m_bmpHeight);
	}
	
	//横向线绘制
	for(i=1;i<pDoc->vnums;i++)
	{
		pDC->MoveTo(0,i*pDoc->m_cellHeight-1);
		pDC->LineTo(pDoc->m_bmpWidth,i*pDoc->m_cellHeight-1);
	}
	
	//设备恢复
	pDC->SelectObject(pOldPen);
}

//
//  绘制空白方块
//
void CSkyblue_PinTuView::DrawBlankBlock(CDC *pDC)
{
	//获取文档核心数据访问权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//计算出矩形区域位置
	RECT rc;
	rc.left =(pDoc->m_blankPos.row-1)*pDoc->m_cellWidth;
	rc.top =(pDoc->m_blankPos.col -1)*pDoc->m_cellHeight;
	rc.right=rc.left +pDoc->m_cellWidth;
	rc.bottom =rc.top +pDoc->m_cellHeight;

	//矩形区域填充
	pDC->FillSolidRect(&rc,RGB(153,153,153));
}

//
//  绘制某cell单元方块
//
void CSkyblue_PinTuView::DrawCellBlock(CDC *pDC, pos destPos, pos srcPos)
{
	//获取文档核心数据访问权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//使用内存DC,宣布与当前位图关联
	//以便为下面提供拷贝的数据源(位图)
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(pDoc->m_bitmap);
	
	//根据源方块的位置和目标放开位置(当前方块实际位置)
	//进行拷贝
	pDC->BitBlt((destPos.row-1)*pDoc->m_cellWidth,
		(destPos.col-1)*pDoc->m_cellHeight,
		pDoc->m_cellWidth,pDoc->m_cellHeight,&memdc,
		(srcPos.row-1)*pDoc->m_cellWidth,
		(srcPos.col-1)*pDoc->m_cellHeight,SRCCOPY);
}

//
//  绘制游戏所有当前散乱的方块
//
void CSkyblue_PinTuView::DrawGameBlocks(CDC *pDC)
{
	//获取文档核心数据访问权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	int i;
	int j;
	pos destPos; //目标位置
	pos srcPos;	 //图像在源位图的位置

	//将所有方块逐个拷贝
	for(i = 1;i<=pDoc->hnums;i++)
	{
		for(j = 1;j<=pDoc->vnums;j++)
		{
			srcPos.row = pDoc->m_map[i][j].row;
			srcPos.col = pDoc->m_map[i][j].col;
			destPos.row = i;
			destPos.col = j;
			DrawCellBlock(pDC,destPos, srcPos);
		}
	}
}

//
//  处理键盘消息
//
void CSkyblue_PinTuView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//响应视图区域的键盘事件，然后交给文档作数据运算处理
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();
	pDoc->OnKeyDown(nChar,nRepCnt,nFlags);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
//  处理鼠标左键消息
//
void CSkyblue_PinTuView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//计算出鼠标点击所在的cell方块位置
	pos DownPos;
	DownPos.row =point.x/pDoc->m_cellWidth+1;
	DownPos.col =point.y/pDoc->m_cellHeight+1;

	//根据当前空白方块位置将鼠标点击其相邻方块的情况
	//转换成键盘输入提交给文档document作数据运算处理
	if(abs(DownPos.row-pDoc->m_blankPos.row)+abs(DownPos.col-pDoc->m_blankPos.col)==1)
	{
		if(DownPos.row - pDoc->m_blankPos.row == 1)
		{
			pDoc->OnKeyDown(VK_RIGHT,0,0);
		}
        if(DownPos.row - pDoc->m_blankPos.row == -1)
		{
			pDoc->OnKeyDown(VK_LEFT,0,0);
		}
		if(DownPos.col - pDoc->m_blankPos.col == 1)
		{
			pDoc->OnKeyDown(VK_DOWN,0,0);
		}
		if(DownPos.col - pDoc->m_blankPos.col == -1)
		{
			pDoc->OnKeyDown(VK_UP,0,0);
		}
	}
}

//响应Document的UpdateAllViews()
void CSkyblue_PinTuView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	Invalidate(FALSE);	
}

void CSkyblue_PinTuView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	/*
	if(m_bFirstRun)
	{
		m_bFirstRun = FALSE;
	//获取文档核心数据访问权
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();
	pDoc->OnNewgame();
	}
	*/
}

void CSkyblue_PinTuView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}
