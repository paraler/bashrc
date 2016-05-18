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
	//a.��ȡ�ĵ����ݿ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//b.ʹ���ڴ��豸����memDC
	//  ���ڴ滷���������ڴ�λͼmemBmp
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(pDC,
		pDoc->m_bmpWidth,pDoc->m_bmpHeight);
	memDC.SelectObject(&memBmp);

	//c. ��ͼ����Ƶ��ڴ�λͼmemBmp��

	//1.������Ϸ���е�ǰɢ�ҵķ���
	DrawGameBlocks(&memDC);
	//2.���ƿհ׷���
	DrawBlankBlock(&memDC);
	//3.���Ʊ߽�������
	DrawLines(&memDC);

	//d.����ͼ���ڴ�memBmp��������Ļ
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
//  ���Ʒ����ı߽���
//
void CSkyblue_PinTuView::DrawLines(CDC *pDC)
{
	//�������趨Ǧ�ʵ���ʽ
	CPen linePen;
	linePen.CreatePen(PS_SOLID, 3, RGB(255,0,0));	
	CPen *pOldPen = pDC->SelectObject(&linePen);

	//��ȡ�ĵ��������ݷ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();
	
	int i;
	//�����߻���
	for(i=1;i<pDoc->hnums;i++)
	{
		pDC->MoveTo(i*pDoc->m_cellWidth-1,0);
		pDC->LineTo(i*pDoc->m_cellWidth-1,pDoc->m_bmpHeight);
	}
	
	//�����߻���
	for(i=1;i<pDoc->vnums;i++)
	{
		pDC->MoveTo(0,i*pDoc->m_cellHeight-1);
		pDC->LineTo(pDoc->m_bmpWidth,i*pDoc->m_cellHeight-1);
	}
	
	//�豸�ָ�
	pDC->SelectObject(pOldPen);
}

//
//  ���ƿհ׷���
//
void CSkyblue_PinTuView::DrawBlankBlock(CDC *pDC)
{
	//��ȡ�ĵ��������ݷ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//�������������λ��
	RECT rc;
	rc.left =(pDoc->m_blankPos.row-1)*pDoc->m_cellWidth;
	rc.top =(pDoc->m_blankPos.col -1)*pDoc->m_cellHeight;
	rc.right=rc.left +pDoc->m_cellWidth;
	rc.bottom =rc.top +pDoc->m_cellHeight;

	//�����������
	pDC->FillSolidRect(&rc,RGB(153,153,153));
}

//
//  ����ĳcell��Ԫ����
//
void CSkyblue_PinTuView::DrawCellBlock(CDC *pDC, pos destPos, pos srcPos)
{
	//��ȡ�ĵ��������ݷ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//ʹ���ڴ�DC,�����뵱ǰλͼ����
	//�Ա�Ϊ�����ṩ����������Դ(λͼ)
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(pDoc->m_bitmap);
	
	//����Դ�����λ�ú�Ŀ��ſ�λ��(��ǰ����ʵ��λ��)
	//���п���
	pDC->BitBlt((destPos.row-1)*pDoc->m_cellWidth,
		(destPos.col-1)*pDoc->m_cellHeight,
		pDoc->m_cellWidth,pDoc->m_cellHeight,&memdc,
		(srcPos.row-1)*pDoc->m_cellWidth,
		(srcPos.col-1)*pDoc->m_cellHeight,SRCCOPY);
}

//
//  ������Ϸ���е�ǰɢ�ҵķ���
//
void CSkyblue_PinTuView::DrawGameBlocks(CDC *pDC)
{
	//��ȡ�ĵ��������ݷ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	int i;
	int j;
	pos destPos; //Ŀ��λ��
	pos srcPos;	 //ͼ����Դλͼ��λ��

	//�����з����������
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
//  ���������Ϣ
//
void CSkyblue_PinTuView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//��Ӧ��ͼ����ļ����¼���Ȼ�󽻸��ĵ����������㴦��
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();
	pDoc->OnKeyDown(nChar,nRepCnt,nFlags);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
//  ������������Ϣ
//
void CSkyblue_PinTuView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//�������������ڵ�cell����λ��
	pos DownPos;
	DownPos.row =point.x/pDoc->m_cellWidth+1;
	DownPos.col =point.y/pDoc->m_cellHeight+1;

	//���ݵ�ǰ�հ׷���λ�ý�����������ڷ�������
	//ת���ɼ��������ύ���ĵ�document���������㴦��
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

//��ӦDocument��UpdateAllViews()
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
	//��ȡ�ĵ��������ݷ���Ȩ
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
