// HotButton.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "HotButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotButton

CHotButton::CHotButton()
{
}

CHotButton::~CHotButton()
{
}


BEGIN_MESSAGE_MAP(CHotButton, CButton)
	//{{AFX_MSG_MAP(CHotButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotButton message handlers

LRESULT CHotButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)   
  {   
  case   WM_MOUSEMOVE:   
  {   
  TRACKMOUSEEVENT   tme;   
  ZeroMemory(&tme,   sizeof(tme));   
  tme.cbSize   =   sizeof(TRACKMOUSEEVENT);   
  tme.dwFlags   =   TME_LEAVE   |   TME_HOVER;   
  tme.hwndTrack   =   m_hWnd;   
  tme.dwHoverTime   =   1;//HOVER_DEFAULT   
  _TrackMouseEvent(&tme);   
  }   
  break   ;   
    
  case   WM_MOUSEHOVER:   
  TRACE(_T("Mouse   hover   message   ....\n"));   
  break   ;   
    
  case   WM_MOUSELEAVE:   
  TRACE(_T("Mouse   leave   message   ....\n"));   
  break   ;   
    
  }   
  //return   CButton::WindowProc(message,   wParam,   lParam);   

	return CButton::WindowProc(message, wParam, lParam);
}
