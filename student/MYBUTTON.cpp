// MYBUTTON.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "MYBUTTON.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMYBUTTON

CMYBUTTON::CMYBUTTON()
{
	bHighlight = bLBtnDown = false;
	hHand = AfxGetApp()->LoadCursor(IDC_CURSOR2);
}

CMYBUTTON::~CMYBUTTON()
{
		if (fUnderline.GetSafeHandle()) fUnderline.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMYBUTTON, CButton)
	//{{AFX_MSG_MAP(CMYBUTTON)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMYBUTTON message handlers

void CMYBUTTON::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bLBtnDown = true;
	hHand = AfxGetApp()->LoadCursor(IDC_CURSOR3);
	::SetCursor(hHand);
	CButton::OnLButtonDown(nFlags, point);
}

void CMYBUTTON::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bLBtnDown = false;
	if (bHighlight)	
	{
		bHighlight = false;
		InvalidateRect(NULL);
	}
	hHand = AfxGetApp()->LoadCursor(IDC_CURSOR2);
	::SetCursor(hHand);
	CButton::OnLButtonUp(nFlags, point);
}

void CMYBUTTON::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetTimer(1,10,NULL);
	
	CButton::OnMouseMove(nFlags, point);
}

BOOL CMYBUTTON::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest ==HTCLIENT)
    {
        ::SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR2)));
        return TRUE;
    }

	/*if (bHighlight) 
	{
		::SetCursor(hHand);
		return true;
	}*/
	
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CMYBUTTON::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static bool pPainted = false;
	POINT pt;
	GetCursorPos(&pt);
	CRect rect;
	GetWindowRect (rect);
	if (bLBtnDown)	
	{		
		KillTimer (1);
		if (pPainted) InvalidateRect (NULL);		
		pPainted = FALSE;		
		return;	
	}

	if (!rect.PtInRect (pt))	
	{		
		bHighlight = false;
		KillTimer (1);

		if (pPainted)			
			InvalidateRect(NULL);

		pPainted = false;
		return;	
	}
	else
	{
		bHighlight = true;
		if (!pPainted)
		{
			pPainted = true;
			InvalidateRect(NULL);
		}
	}
	CButton::OnTimer(nIDEvent);
}

/*BOOL CMYBUTTON::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}*/

BOOL CMYBUTTON::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	COLORREF cr = GetSysColor(COLOR_ACTIVECAPTION);
	int r = GetRValue(cr);
	int g = GetGValue(cr);
	int b = GetBValue(cr);
	if (r > 1) r -= 2;
	if (g > 1) g -= 2;
	if (r < 3 && g < 3 && b < 253) b += 2;
	COLORREF cr1 = RGB(255,255,0);
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, cr1);
	return CButton::OnEraseBkgnd(pDC);
}

void CMYBUTTON::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);
	COLORREF oc=RGB(30,123,255);
		//oc = pDC->GetTextColor();
	int iObk = pDC->SetBkMode(TRANSPARENT);
		UINT state = lpDrawItemStruct->itemState;

	CFont * pOldFont = NULL;

	int iYOffset = 0, iXOffset = 0;

	CString strText;
	GetWindowText(strText);

	rect.top  += iYOffset;
	rect.left += iXOffset;


	if (state & ODS_DISABLED)
	{		
		//按钮置灰（DISABLED）
		CBrush grayBrush;
		grayBrush.CreateSolidBrush (GetSysColor (COLOR_GRAYTEXT));
		CSize sz = pDC->GetTextExtent(strText);
		int x = rect.left + (rect.Width() - sz.cx)/2;
		int y = rect.top + (rect.Height() - sz.cy)/2;
		rect.top  += 2;
		rect.left += 2;
		pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rect.top  -= 2;
		rect.left -= 2;
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		if (bHighlight)//光标在按钮上
		{
			if (state & ODS_SELECTED)
			{
				//按下按钮
				pDC->Draw3dRect(rect,RGB(0,0,255), RGB(0,0,255));
			}
			else
			{
				//未按下按钮
				pDC->Draw3dRect(rect,RGB(255,0,0),RGB(255,0,0));			}
			//字体颜色
			pDC->SetTextColor(RGB(0,0,255));

			//加下画线（也可以用其他字体）
			if (fUnderline.GetSafeHandle() == NULL)
			{
				CFont * pFont = GetFont();
				ASSERT(pFont);
				LOGFONT lf;
				pFont->GetLogFont(&lf);
				lf.lfUnderline = TRUE;
				fUnderline.CreateFontIndirect(&lf);		
			}

			pOldFont = pDC->SelectObject(&fUnderline);
		}
		else 
		{
			pDC->SetTextColor(RGB(255,123,30));
			pDC->Draw3dRect(rect,RGB(255,0,0),RGB(255,0,0));	}

		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		if (pOldFont) pDC->SelectObject(pOldFont);
	}
}

int CMYBUTTON::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	CFont * pFont = GetFont();
	ASSERT(pFont);

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfUnderline = TRUE;

	fUnderline.CreateFontIndirect(&lf);
	

	return 0;
}

//DEL int CMYBUTTON::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	bHighlight = bLBtnDown = false;
//DEL 	hHand = AfxGetApp()->LoadCursor(IDC_CURSOR2);
//DEL 	return CButton::OnMouseActivate(pDesktopWnd, nHitTest, message);
//DEL }
