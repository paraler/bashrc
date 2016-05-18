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

#define BKCOLOR         RGB(128,128,128)	//������ɫ
#define FRONTWIDTH	    (39+2)			    //ǰ�淽��Ŀ��
#define FRONTHEIGHT	    (39+12)			    //ǰ�淽��ĸ߶�
#define BKWIDTH	        46					//��������Ŀ��
#define BKHEIGHT        56					//��������ĸ߶�
#define ROWCOUNT        7					//����
#define COLCOUNT        12					//����

#define BLANK_STATE     -1                  //�շ���(û���κζ���)

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

	//��¼������Ϊ��Ч״̬
	m_nY1= BLANK_STATE;
	m_nX1= BLANK_STATE;

	//��ʼ��������
	m_nRow=ROWCOUNT;
	m_nCol=COLCOUNT;

	//������������̬�����ں���������ռ�
	m_map=new int[m_nRow*m_nCol];
}

C_LLK_Dlg::~C_LLK_Dlg()
{
	//�ͷŶ�̬����ռ�
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

	//��ȡ�����ܵ��豸����
	CDC *pWinDC = GetDC();	

	//�ڴ��豸�����Լ��ڴ�λͼ�Ĵ�������ʼ��,����

	//3D����߿�ͼ���ڴ�λͼ
	m_mem3DBkDC.CreateCompatibleDC(pWinDC);
	m_mem3DBkBmp.LoadBitmap(IDB_BITMAP_3D_FRAMES);
	m_mem3DBkDC.SelectObject(&m_mem3DBkBmp);
	//����ͼ���ڴ�λͼ
	m_memAnimalDC.CreateCompatibleDC(pWinDC);
	m_memAnimalBmp.LoadBitmap(IDB_BMP_ANIMAL);
	m_memAnimalDC.SelectObject(&m_memAnimalBmp);
	//������Ϸ�����ڴ�λͼ	
	m_MemDC.CreateCompatibleDC(pWinDC);
	m_memBitmap.CreateCompatibleBitmap(pWinDC,
		m_nCol*FRONTWIDTH+5,
		m_nRow*FRONTHEIGHT+5);
	m_MemDC.SelectObject(&m_memBitmap);
	
	//��ʼһ���µ���Ϸ
	StartNewGame();

	//�����������ǰ����ʾ
	HWND hWnd = ::AfxGetMainWnd()->m_hWnd;
	::SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C_LLK_Dlg::StartNewGame()
{
	//��ʼ����ͼ,����ͼ�����з�������λ����Ϊ�շ���״̬
	for(int iNum=0;iNum<(m_nCol*m_nRow);iNum++)
	{
		m_map[iNum] = BLANK_STATE;
	}

	//�����������
	srand(time(NULL));

	//���������ͼ
	//������ƥ��ɶԵĶ������ַŽ�һ����ʱ�ĵ�ͼ��
	CDWordArray tmpMap;	
	for(int i=0;i<(m_nCol*m_nRow)/4;i++)
		for(int j=0;j<4;j++)
			tmpMap.Add(i);

	//ÿ�δ��������ʱ��ͼ��ȡ��(��ȡ������ʱ��ͼɾ��)
	//һ������ŵ���ͼ�Ŀշ�����
	for(i=0;i<m_nRow*m_nCol;i++)
	{	
		//�����ѡһ��λ��
		int nIndex=(int(rand()*0.1+rand()*0.01+rand()))%tmpMap.GetSize();
		//��ȡ��ѡ������ŵ���ͼ�Ŀշ���
		m_map[i]=tmpMap.GetAt(nIndex);

		//����ʱ��ͼ��ȥ�ö���
		tmpMap.RemoveAt(nIndex);		
	}
	

	//������ʾ
	Invalidate(TRUE);
}

//
//  ��Ϸ����Ļ���
//
void C_LLK_Dlg::GameDraw(CDC * pDC)
{
	//���Ʊ�����ɫ
	pDC->FillSolidRect(0,0,m_nCol*FRONTWIDTH+5,m_nRow*FRONTHEIGHT+5,BKCOLOR);

	for(int i=0;i<m_nRow;i++)
	{
		for(int j=0;j<m_nCol;j++)
		{			
			if(m_map[i*m_nCol+j]==BLANK_STATE)
			{
			continue;
			}
			//���Ʒ���߿�
			pDC->BitBlt(j*FRONTWIDTH,i*FRONTHEIGHT,
				BKWIDTH,BKHEIGHT,
				&m_mem3DBkDC,
				0,BKHEIGHT,
				SRCCOPY);
			//���Ʒ���
			//��ΪҪʹ��Ч��͸����������ͼ���ĵ�ɫ�Լ����������ֹ���
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
		
		//�Ƚ�������Ϸ�����ͼ����Ƶ��ڴ�λͼ
		GameDraw(&m_MemDC);
		//���ڴ�λͼ�л��ƺõ�ͼ��һ���Կ�������Ļ
		dc.BitBlt(0,0,m_nCol*FRONTWIDTH,m_nCol*FRONTHEIGHT,&m_MemDC,0,0,SRCCOPY);
}

//
// ��������Ϣ����
//
void C_LLK_Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//1.�������������ĵ�λ��
	int x=point.x/FRONTWIDTH+(point.x%FRONTWIDTH?1:0)-1;
	int y=point.y/FRONTHEIGHT+(point.y%FRONTHEIGHT?1:0)-1;
	
	//2.����Ϸ�����ڲ��Ҹ������и������ǿյ�����
	if(x<m_nCol&&y<m_nRow&&m_map[y*m_nCol+x]!= BLANK_STATE)
	{
		
		
		//3.������δ��¼��һ������
		if(m_nX1==BLANK_STATE)
		{
			//4.��¼��һ�������λ��
			m_nX1=x;
			m_nY1=y;
			
			//��ȡ�����ܵ��豸����
			CDC *pWinDC = GetDC();
			
			//��ʱ���Ƶ��еķ������
			//ֻ����Ļ�������ڴ�λͼ
			CPen myPen;
			CPen *pOldPen;
			myPen.CreatePen(PS_SOLID, 4, RGB(255,0,0));
			pOldPen = 	pWinDC->SelectObject(&myPen);
			//���������ƣ��������ƻ��ƿ��
			pWinDC->MoveTo(x*FRONTWIDTH,y*FRONTHEIGHT);
			pWinDC->LineTo(x*FRONTWIDTH,(y+1)*FRONTHEIGHT);
			pWinDC->LineTo((x+1)*FRONTWIDTH,(y+1)*FRONTHEIGHT);
			pWinDC->LineTo((x+1)*FRONTWIDTH,y*FRONTHEIGHT);
			pWinDC->LineTo(x*FRONTWIDTH,y*FRONTHEIGHT);
			//�ֳ��ָ�
			pWinDC->SelectObject(pOldPen);
		}
		else
		{ 
			//5.�ж��Ƿ����ķ���Ǳ���, �Ƿ���ͬһ�ֶ���
			if((m_nX1!=x||m_nY1!=y)&& 
			  m_map[m_nY1*m_nCol+m_nX1]==m_map[y*m_nCol+x]
				)
			{
				//6.����Ƿ��������
				if(IsLink(m_nX1,m_nY1,x,y))
				{
					//7.��������
					m_map[m_nY1*m_nCol+m_nX1]=BLANK_STATE;
					m_map[y*m_nCol+x]=BLANK_STATE;
				}				
			}
			//8.��ռ�¼�����ֵ
			m_nX1=BLANK_STATE;  
			m_nY1=BLANK_STATE;	
						
			//֪ͨ�ػ�
			Invalidate(FALSE);
		}
	}
	
	//�쿴�Ƿ��Ѿ�ʤ��
	if(IsWin())
	{
		MessageBox("��ϲ��ʤ������,������ʼ�¾�");
		StartNewGame();
	}
}


//
//Xֱ����ͨ
//
BOOL C_LLK_Dlg::X1_Link_X2(int x, int y1,int y2)
{
	//��֤y1��ֵС��y2
	if(y1>y2)
	{
		//���ݽ���
		int n=y1;
		y1=y2;
		y2=n;
	}

	//ֱͨ 	
	for(int i=y1+1;i<=y2;i++)
	{
		if(i==y2)
			return TRUE;
		if(m_map[i*m_nCol+x]!=BLANK_STATE)
			break;
	}
	//��ͨ
	if(XThrough(x-1,y1,FALSE)&&XThrough(x-1,y2,FALSE))
		return TRUE;
	//��ͨ
	if(XThrough(x+1,y1,TRUE)&&XThrough(x+1,y2,TRUE))
		return TRUE;
	return FALSE;
}

//
//Yֱ����ͨ
//
BOOL C_LLK_Dlg::Y1_Link_Y2(int x1,int x2,int y)
{
	if(x1>x2)
	{
		int x=x1;
		x1=x2;
		x2=x;
	}
	//ֱͨ
	for(int i=x1+1;i<=x2;i++)
	{
		if(i==x2)
			return TRUE;
		if(m_map[y*m_nCol+i]!=BLANK_STATE)
			break;
	}
	//��ͨ
	if(YThrough(x1,y-1,FALSE)&&YThrough(x2,y-1,FALSE))
		return TRUE;
	//��ͨ
	if(YThrough(x1,y+1,TRUE)&&YThrough(x2,y+1,TRUE))
		return TRUE;
	return FALSE;
}

//
// �Ƿ�ͬһֱ��ͨ
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
// �Ƿ�ͬһֱ��ͨ
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
//  1ֱ�ǽӿ���ͨ
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
//  2ֱ�ǽӿ���ͨ
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
	//��ͨ
	if(XThrough(x1+1,y1,TRUE)&&XThrough(x2+1,y2,TRUE))
		return TRUE;
	//��ͨ
	if(XThrough(x1-1,y1,FALSE)&&XThrough(x2-1,y2,FALSE))
		return TRUE;
	//��ͨ
	if(YThrough(x1,y1-1,FALSE)&&YThrough(x2,y2-1,FALSE))
		return TRUE;
	//��ͨ
	if(YThrough(x1,y1+1,TRUE)&&YThrough(x2,y2+1,TRUE))
		return TRUE;
	//��
	for(int x=x1+1;x<m_nCol;x++)
	{
		if(m_map[y1*m_nCol+x]>-1)
			break;
		if(OneCornerLink(x,y1,x2,y2))
			return TRUE;
	}
	//��
	for(x=x1-1;x>-1;x--)
	{
		if(m_map[y1*m_nCol+x]!=BLANK_STATE)
			break;
		if(OneCornerLink(x,y1,x2,y2))
			return TRUE;
	}
	//��
	for(int y=y1-1;y>-1;y--)
	{
		if(m_map[y*m_nCol+x1]!=BLANK_STATE)
			break;
		if(OneCornerLink(x1,y,x2,y2))
			return TRUE;
	}
	//��
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
//  �ж�ѡ�е����������Ƿ��������
//
BOOL C_LLK_Dlg::IsLink(int x1, int y1, int x2, int y2)
{
	//Xֱ����ʽ
	if(x1==x2)
	{
		if(X1_Link_X2(x1,y1,y2))
			return TRUE;
	}
	//Yֱ����ʽ
	else if(y1==y2)
	{
		if(Y1_Link_Y2(x1,x2,y1))
			return TRUE;
	}

	//һ��ת��ֱ�ǵ���ͨ��ʽ
	if(OneCornerLink(x1,y1,x2,y2))
	{
		return TRUE;
	}
	//����ת��ֱ�ǵ���ͨ��ʽ
	else if(TwoCornerLink(x1,y1,x2,y2))
	{
		return TRUE;
	}
	return FALSE;
}

//
//  �ػ������Ϣ F2 (��������Ϸ��ʼ)
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
//   ����Ƿ��Ѿ�Ӯ������Ϸ
//
BOOL C_LLK_Dlg::IsWin(void)
{
	//��������Ƿ����з�δ�������ķ���
	// (��BLANK_STATE״̬)
	for(int i=0;i<m_nRow*m_nCol;i++)
	{
		if(m_map[i] != BLANK_STATE)
		{
			return FALSE;
		}
	}

	return TRUE;
}



