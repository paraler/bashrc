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





#define BKCOLOR         RGB(128,128,128)	//������ɫ
#define FRONTWIDTH	    (39+2)			    //ǰ�淽��Ŀ��
#define FRONTHEIGHT	    (39+12)			    //ǰ�淽��ĸ߶�
#define BKWIDTH	        46					//��������Ŀ��
#define BKHEIGHT        56					//��������ĸ߶�
#define ROWCOUNT        7					//����
#define COLCOUNT        12					//����

#define BLANK_STATE     -1                  //�շ���(û���κζ���)
#define INVALID_POS     -1                  //��Ч����λ��

#define BLOCK_WIDTH_SIZE	        (39+2)					//��������Ŀ��
#define BLOCK_HEIGHT_SIZE        (39+12)					//��������ĸ߶�

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

	//��¼������Ϊ��Ч״̬
	m_nY1= INVALID_POS;
	m_nX1= INVALID_POS;

	//��ʼ��������
	m_nRow=ROWCOUNT;
	m_nCol=COLCOUNT;

	m_hHackDC = NULL; 
	m_hwndHack = NULL;

	//�����Զ�����(����Ŀ�����������
	m_bAutoKick = FALSE;

	//������������̬�����ں���������ռ�
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

	//��ȡ�����ܵ��豸����
	CDC *pWinDC = GetDC();		
	//������Ϸ�����ڴ�λͼ	
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

		dc.BitBlt(30,70,               //�ڶԻ����ƫ��λ��
			m_DestClientRect.Width(),  //ͼ����
			m_DestClientRect.Height(), //ͼ��߶�
			&m_MemDC                   //��Դ�����ڴ��豸�����������ڴ�λͼ
			,0,0,SRCCOPY               //0ƫ�ƿ���
			);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkyblue_LLK_CheatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//
//Xֱ����ͨ
//
BOOL CSkyblue_LLK_CheatDlg::X1_Link_X2(int x, int y1,int y2)
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
BOOL CSkyblue_LLK_CheatDlg::Y1_Link_Y2(int x1,int x2,int y)
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
// �Ƿ�ͬһֱ��ͨ
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
//  1ֱ�ǽӿ���ͨ
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
//  2ֱ�ǽӿ���ͨ
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
		if(m_map[y1*m_nCol+x]!=BLANK_STATE)
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
//  �ж�ѡ�е����������Ƿ��������
//
BOOL CSkyblue_LLK_CheatDlg::IsLink(int x1, int y1, int x2, int y2)
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
// �Զ��ҳ�����������ͨ�ķ���
//
BOOL CSkyblue_LLK_CheatDlg::Find2Rect(int &x1,int &y1, int &x2, int &y2)
{
	BOOL bFound=FALSE;
	int* pMap=m_map;
	
	//��һ������ӵ�ͼ��0λ�ÿ�ʼ
	for(int i=0;i<m_nRow*m_nCol;i++)
	{
		//�ҵ�������ѭ��
		if(bFound)
			break;
		//�޶���Ŀո�����
		if(pMap[i]==BLANK_STATE)
			continue;
		
		//�ڶ��������ǰһ������ĺ��濪ʼ
		for(int j=i+1;j<m_nRow*m_nCol;j++)
		{
			
			//�ڶ������鲻Ϊ�� �����һ������Ķ�����ͬ
			if(pMap[j]!=BLANK_STATE&&pMap[i]==pMap[j])
			{
				//�����Ӧ����������λ��
				x1=i%m_nCol;
				y1=i/m_nCol;/*+(x1?1:0)*/
				x2=j%m_nCol;
				y2=j/m_nCol;/*+(x2?1:0)*/
				
				//�ж��Ƿ������ͨ
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
//  ��������Ŀ�����
//
BOOL CSkyblue_LLK_CheatDlg::HackIn(CString strWinName)
{
	//����Ŀ�괰�ڣ���ȡ�����Ȩ
	CWnd * m_pWndHack = FindWindow(NULL,strWinName);
	m_hwndHack = m_pWndHack->GetSafeHwnd();
	
	if(m_hwndHack != NULL)
	{
		m_hHackDC = ::GetDC(m_hwndHack);
		
		::GetClientRect(m_hwndHack,&m_DestClientRect);
		//	TextOut(m_hHackDC,100,100,"hi, my name is 007, you have been hacke!!",20);
		
		//����Ŀ�����Ļ��浽�����ڴ�λͼ
		::BitBlt(m_MemDC,0,0,
			m_DestClientRect.Width(),
			m_DestClientRect.Height(),
			m_hHackDC,0,0,SRCCOPY);
		
		//����ͼ�����ɱ��˵�ͼ����
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
// ����ͼ�����������Ϸ��ͼ
//
void CSkyblue_LLK_CheatDlg::GenMap()
{
	int colorDate;
	int i = 0;

	for(i=0;i<m_nRow*m_nCol;i++)
	{
		//�����Ӧ����������λ��
		int x=i%m_nCol;
		int y=i/m_nCol;

		colorDate = GetRectData(x,y);
		m_map[i] = colorDate;
	}
}

//
// ������λ��(x,y)�����ͼ�����
//
int CSkyblue_LLK_CheatDlg::GetRectData( int x, int y)
{
	COLORREF colorArray[5];
	int colorDate;


	int basicX,basicY; //�÷�������Ͻǻ���λ��;
	basicX = x * BLOCK_WIDTH_SIZE;
	basicY =  y* BLOCK_HEIGHT_SIZE;	
	
	//ȡ�÷����5�����ж�
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
	
	
	int xPos, yPos;//����λ��	
	for( int i=0; i< 5; i++)
	{
		xPos = aPos[i].x;
		yPos= aPos[i].y;
		//��¼5������ֵ
		colorArray[i]= GetPixel(m_MemDC,xPos,yPos);
	}
	

	int nSameCount = 0;
	for(i=0; i<4; i++)
	{	
		//�������в�����5���������ֵ�ۼ�
		colorDate += colorArray[i];	

		if(colorArray[i] == colorArray[i+1] &&
			colorArray[i] == RGB(128,128,128))
		{
			nSameCount++;
		}	
	}

	//�ж��ǲ��ǿհ׷���	
	//�������3����ͬ�����Ǳ���
	if(nSameCount>=3)
	{
		return BLANK_STATE;
	}	
	
	return colorDate;
}


//
//  ���װ�ť��Ϣ����
//
void CSkyblue_LLK_CheatDlg::OnButtonHack() 
{
	Hack();	
}

//
//  һ�����������ֹ�������
//
void CSkyblue_LLK_CheatDlg::Hack(void)
{
	//�����ɹ��жϼ�¼ֵ
	BOOL bOk; 

	//���ֻ�ȡĿ��������Ȩ
	//Ŀ���������
	CString strWinName = "skyblue ������";
	bOk = HackIn(strWinName);	
	if(!bOk)
	{
		MessageBox("��ȡʧ��,Ŀ����Ϸ����û������");
		return;
	}
	
	//����Ѱ��һ������ķ���
	int x1,y1,x2,y2;
	bOk = Find2Rect(x1, y1, x2, y2);	
	if(!bOk)
	{
		MessageBox("�Ҳ���һ��������飬������Ϸ�Ѿ�ʤ��");	
		return;
	}

	//���ݱ��ѡ�����׵Ĺ���	
	if(m_bAutoKick)
	{
		//Զ�������ҵ�����������ͨ����			
		RemoteButtonKick(x1,y1,x2,y2);
	}
	else
	{
		//�ڱ����Լ�Ŀ�����˻�����ʾͼ��		
		Local_RemoteHintDraw(x1,y1,x2,y2);
	}
}

//
// �ڱ����Լ�Ŀ�����˻�����ʾͼ��
//
void CSkyblue_LLK_CheatDlg::Local_RemoteHintDraw( int x1, int y1, int x2, int y2)
{
		//������ʾ�ҵ�����������ͨ����		
		CBrush brush(RGB(255,0,0));
		m_MemDC.SelectObject(&brush);
		//��Ƿ���1
		m_MemDC.Ellipse(x1*FRONTWIDTH,y1*FRONTHEIGHT,
			x1*FRONTWIDTH+20,y1*FRONTHEIGHT+20);
		//��Ƿ���2			
		m_MemDC.Ellipse(x2*FRONTWIDTH,y2*FRONTHEIGHT,
			x2*FRONTWIDTH+20,y2*FRONTHEIGHT+20);	
		Invalidate(FALSE);

		//Ŀ�����Ļ�ͼʵ��
		m_hHackDC = ::GetDC(m_hwndHack);
		SelectObject(m_hHackDC,brush.m_hObject);
		Ellipse(m_hHackDC,x1*FRONTWIDTH,y1*FRONTHEIGHT,
			x1*FRONTWIDTH+20,y1*FRONTHEIGHT+20);
		Ellipse(m_hHackDC,x2*FRONTWIDTH,y2*FRONTHEIGHT,
			x2*FRONTWIDTH+20,y2*FRONTHEIGHT+20);
}

//
//  ģ��Զ�˳���������
//
void CSkyblue_LLK_CheatDlg::RemoteButtonKick( int x1, int y1, int x2, int y2)
{
		int DestX,DestY;				
		//�������DOWN����Ϣ
		DestX =  x1*FRONTWIDTH +FRONTWIDTH/2;
		DestY = y1*FRONTHEIGHT + FRONTHEIGHT/2;
		//�����������
		LPARAM lParam = MAKELPARAM(DestX,DestY);
		::SendMessage(m_hwndHack,WM_LBUTTONDOWN,MK_LBUTTON,lParam);
		::SendMessage(m_hwndHack,WM_LBUTTONUP,MK_LBUTTON,lParam);
		
		DestX =  x2*FRONTWIDTH +FRONTWIDTH/2;
		DestY = y2*FRONTHEIGHT + FRONTHEIGHT/2;
		//�����������
		lParam = MAKELPARAM(DestX,DestY);
		::SendMessage(m_hwndHack,WM_LBUTTONDOWN,MK_LBUTTON,lParam);
		::SendMessage(m_hwndHack,WM_LBUTTONUP,MK_LBUTTON,lParam);
		
		Invalidate(FALSE);
}

//
//  �����޸İ�ť "Զ���Զ�����"or"������ʾ"
//
void CSkyblue_LLK_CheatDlg::OnButtonAutoKick() 
{
	//ȡ�����޸�ԭ������
	m_bAutoKick = !m_bAutoKick;	

	CString btHackSelectInfo;
	CString btHackInfo;
	if(m_bAutoKick)
	{
		btHackSelectInfo = "(&S)�����Զ����鹦��";
		btHackInfo = "(&H)����һ���������";
	}
	else
	{
		btHackSelectInfo = "(&S)�����Զ����鹦��";
		btHackInfo = "(&H)��ȡһ���������";
	}

	//�����޸ĺ��ֵ���ð�ť����ʾ
	SetDlgItemText(IDC_BT_AUTO_KICK,btHackSelectInfo);
	SetDlgItemText(IDC_BT_HACK,btHackInfo);
}


