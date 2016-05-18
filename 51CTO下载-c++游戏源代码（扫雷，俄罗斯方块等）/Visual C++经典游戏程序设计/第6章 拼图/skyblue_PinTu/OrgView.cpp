/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    OrgView.cpp

Abstract:

	the originally photo's View 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#include "stdafx.h"
#include "skyblue_PinTu.h"
#include "skyblue_PinTuDoc.h"
#include "OrgView.h"
#include "skyblue_PinTuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrgView

IMPLEMENT_DYNCREATE(COrgView, CView)

COrgView::COrgView()
{
}

COrgView::~COrgView()
{
}


BEGIN_MESSAGE_MAP(COrgView, CView)
	//{{AFX_MSG_MAP(COrgView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrgView drawing

//
// Դͼ�����
//
void COrgView::OnDraw(CDC* pDC)
{
	//��ȡ�ĵ����ݿ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//ʹ���ڴ�DC
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(pDoc->m_bitmap);

	//����ͼ����
	pDC->BitBlt(0,0,pDoc->m_bmpWidth,pDoc->m_bmpHeight,
				&memdc,0,0,SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// COrgView diagnostics

#ifdef _DEBUG
void COrgView::AssertValid() const
{
	CView::AssertValid();
}

void COrgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COrgView message handlers


void COrgView::DrawAll(CDC *pDC)
{

	//��ȡ�ĵ����ݿ���Ȩ
	CSkyblue_PinTuDoc* pDoc = (CSkyblue_PinTuDoc*)GetDocument();

	//ʹ���ڴ�DC
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(pDoc->m_bitmap);

	//����ͼ����
	pDC->BitBlt(0,0,pDoc->m_bmpWidth,pDoc->m_bmpHeight,
				&memdc,0,0,SRCCOPY);
}

void COrgView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(pHint != NULL)
	{
		if(pHint->IsKindOf( RUNTIME_CLASS(CObArray) ))
		{ //��Ϊ��Ϸ���������ƶ���������µ�ͼ�����
		  //������Բ����
			return;
		}
	}
	Invalidate(TRUE);	
}
