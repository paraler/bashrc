/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_PinTuView.h

Abstract:

	View , manage drawing 

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_SKYBLUE_PINTUVIEW_H__684CED21_22C8_4B2F_9153_2EE0877713C7__INCLUDED_)
#define AFX_SKYBLUE_PINTUVIEW_H__684CED21_22C8_4B2F_9153_2EE0877713C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

	//方块位置结构
	struct pos
	{
		int row; //方块所在的行
		int col; //方块所在的列
	};

class CSkyblue_PinTuView : public CView
{
protected: // create from serialization only
	CSkyblue_PinTuView();
	DECLARE_DYNCREATE(CSkyblue_PinTuView)

// Attributes
public:

//图像绘制操作组
void DrawCellBlock(CDC *pDC, pos destsite, pos srcsite);
void DrawBlankBlock(CDC *pDC);
void DrawLines(CDC *pDC);
void DrawGameBlocks(CDC *pDC);

//是否程序才开始运行
BOOL m_bFirstRun;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_PinTuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_PinTuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkyblue_PinTuView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in skyblue_PinTuView.cpp
//inline CSkyblue_PinTuDoc* CSkyblue_PinTuView::GetDocument()
 //  { return (CSkyblue_PinTuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_PINTUVIEW_H__684CED21_22C8_4B2F_9153_2EE0877713C7__INCLUDED_)
