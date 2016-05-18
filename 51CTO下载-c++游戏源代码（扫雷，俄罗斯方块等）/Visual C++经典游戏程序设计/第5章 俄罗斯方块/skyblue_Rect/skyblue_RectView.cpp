// skyblue_RectView.cpp : implementation of the CSkyblue_RectView class
//

#include "stdafx.h"
#include "skyblue_Rect.h"

#include "skyblue_RectDoc.h"
#include "skyblue_RectView.h"
#include "OptionDlg.h"

//���ֲ���
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
	//��һ�ο�ʼ��Ϸ
	m_bFistPlay = TRUE;

	//ȱʡΪ������Ϸ��ͣ״̬
	m_bGamePaush = FALSE;

	//ȱʡΪ����ű�������
	m_bMusic = FALSE;
	
	//ȱʡΪ��������
	m_bDrawGrid = TRUE;

	//�ܷ�ֵ����
	m_iPerformance = 0;

	//����ֵ��Ϊ12�У�10��
	m_iRow = 12;
	m_iCol = 10;

	//���Ͻ�X��Y����
	m_iStartX = 10;
	m_iStartY = 10;

	//ȱʡ����Ϊ3��
	m_iLevel = 2;
	//��һ����ʽ
	m_iBlockSytle = 0;

	//ȱʡ�����СΪm_iLarge������
	m_iLarge = 30;

	//ȱʡ��Ϸ�ǽ�����
	m_bGameEnd = TRUE;

	int i,j;

	//����ֵ
	for (i=0;i<100;i++)
		for (j=0;j<100;j++)
			GameStatus[i][j]=0;

	//������״����ĽӴ������ݣ��μ������ĽӴ�����, 
	//���ĳ����״�ķ���û��4���Ӵ��棬������������-1
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






//����һЩ�豸
int CSkyblue_RectView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	


	//������һ�ε������ķ������ʽ
	m_inextStatus = Random(7);
	
	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
*
*  ���ƣ�OnDraw
*
*  ���ܣ��е����л�����Ļ����
*
*  ����޸�ʱ�䣺2005.8.6
*
* * * * * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnDraw(CDC* pDC)
{
	DcEnvInitial();
	DrawGame(&m_memDC);  //���ڴ�λͼ����Ϸ�������

	pDC->BitBlt(0,0,m_nWidth,m_nHeight,&m_memDC,0,0,SRCCOPY);
}
//
//��ͼ�豸�����ĳ�ʼ��
//
void CSkyblue_RectView::DcEnvInitial(void)
{
	if(m_bFistPlay)
	{
		m_bFistPlay = FALSE;
		//��Ĭ�ϵĲ�������ȡ��ǰ��Ļ�豸����
		CDC *pWindowDC = GetDC();

		//1.����ӳ����Ļ���ڴ��豸����
		//��ȡ��Ϸ���ڵĴ�С�������������ڴ�λͼ�ĳߴ�
		CRect windowRect;
		GetClientRect(&windowRect);
		m_nWidth = windowRect.Width();
		m_nHeight = windowRect.Height();

		//�ڴ��豸��������Ļ�豸�������������ݣ�
		m_memDC.CreateCompatibleDC(pWindowDC);
		//�ڴ�λͼ������Ļ����(����),��СΪ��Ϸ���ڵĳߴ�
		m_memBmp.CreateCompatibleBitmap(pWindowDC,m_nWidth,m_nHeight);
		//�ڴ��豸�������ڴ�λͼ�������Ա�ͨ��m_memDC���ڴ�λͼ������
		m_memDC.SelectObject(&m_memBmp);

		//2.�洢����λͼ���ڴ���Դ
		//�ڴ��豸��������Ļ�豸�������������ݣ�
		m_memRectDC.CreateCompatibleDC(pWindowDC);
		//�൱�ڽ��ⲿλͼrect.bmp��̬����m_hMemRectBmp��
		m_hMemRectBmp=(HBITMAP)LoadImage(NULL,"rect.bmp",IMAGE_BITMAP,150,30,LR_LOADFROMFILE);
		//�ڴ��豸�������ڴ�λͼ�������Ա�ͨ��m_memDC���ڴ�λͼ������
		SelectObject(m_memRectDC.m_hDC, m_hMemRectBmp);	


	
	//��ɫ�ĺڱ�
	m_pBlackPen  = new CPen(PS_SOLID,1,BLACK);

	//��ˢ
	m_pGrayBrush  = new CBrush(RGB(66,66,66));
	m_pBlackBrush  = new CBrush(BLACK);
	}
}

void CSkyblue_RectView::DCEnvClear(void)
{
	//�豸����
	m_memDC.DeleteDC();
	m_memRectDC.DeleteDC();
	//λͼ��Դ
	DeleteObject(m_memBmp);
	DeleteObject(m_hMemRectBmp);


	delete(m_pBlackPen);
	delete(m_pGrayBrush);
	delete(m_pBlackBrush);

}


void CSkyblue_RectView::DrawGame(CDC *pDC)
{
		int i,j;
	//ѡ�ú�ɫ��ˢ������������Ϸ���ڴ��ڵı���
	pDC -> SelectObject(m_pBlackBrush);
	CRect rect;
	GetClientRect(&rect);
	pDC -> Rectangle(rect);

	//ѡ�û�ɫ��ˢ��������Ϸ����ı���
	pDC -> SelectObject(m_pGrayBrush);
	pDC -> Rectangle(m_iStartY ,m_iStartX, m_iStartY + 301, m_iStartX + 360);	

	pDC->SelectObject(m_pBlackPen);	
	//��������
	if (m_bDrawGrid)
	{
		//������
		for (i=0;i<m_iRow;i++)
		{
			pDC->MoveTo(m_iStartY, m_iStartX + i*m_iLarge);
			pDC->LineTo(m_iStartY+300, m_iStartX +i*m_iLarge);
		}	
		
		//������
		for (i=0;i<m_iCol;i++)
		{
			pDC->MoveTo(m_iStartY+i*m_iLarge, m_iStartX);
			pDC->LineTo(m_iStartY+i*m_iLarge, m_iStartX+360);
		}
	}

	int x,y,nW,nH;

	//С����Ļ���
	for (i=0;i<m_iRow;i++)
		for (j=0;j<m_iCol;j++)
		{
			if (GameStatus[i][j]==MAP_STATE_NOT_EMPTY)
			{
				//����Ϸ������״̬Ϊ��ռ��״̬���������С����
				x = m_iStartY+j*m_iLarge +2;
				y = m_iStartX+i*m_iLarge +2;
				nW = m_iLarge-4;
				nH = m_iLarge-4;
			pDC->BitBlt(x,y,nW,nH,&m_memRectDC,m_iBlockSytle*30,0,SRCCOPY);
			}
		}

	//��ʾ��Ϸ������Ϸ����ĺ�������
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX+220, "��Ϸ�����С��");
		pDC -> TextOut(m_iStartY+320, m_iStartX+240,m_strArea);

		pDC -> TextOut(m_iStartY+320, m_iStartX+280, "��Ϸ����");
		pDC -> TextOut(m_iStartY+320, m_iStartX+300,m_strLevel);
	}
				
	//��ʾ�ܷ�
	if (!m_bGameEnd)
	{
		CString lsStr;	
		lsStr.Format("�ܷ�Ϊ��%d ��",m_iPerformance);
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX+180,lsStr);
	}

	//����һ�ν�Ҫ���ֵķ��飬������ʾ�û�
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(WHITE);
		pDC -> TextOut(m_iStartY+320, m_iStartX,"��һ�����飺");

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
*  ���ƣ�OnTimer
*
*  ���ܣ��е�������������
*
*  ����޸�ʱ�䣺2005.8.6
*
* * * * * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnTimer(UINT nIDEvent) 
{
	//���ԭ���ķ����ѵ��׻���Ϸ�տ�ʼ�������һ���µķ���
	int i,j,k;
	if (m_isBottom)
	{
		//1.������һ�������׹��
		m_icurrentStatus = m_inextStatus;
		m_inextStatus = Random(7);  //�õ���һ�εķ�����ʽ
	//	if (m_inextStatus==0) m_inextStatus++;

		//2.�޸��µġ���һ��׹�
		RectStatusToNextStatus( m_inextStatus );
	//	CRect rect(m_iStartY+320, m_iStartX, m_iStartY+440, m_iStartX+160);
	//	InvalidateRect(&rect);
	//	Invalidate(FALSE);
		
		//3.���ɵġ���һ��׹�������ǰʹ��
		m_currentRect = m_icurrentStatus;   
		//���ݵ�ǰ��׹�����״ȥ��ʼ������״̬�µ���׹������
		RectStatusToActiveStatus( m_icurrentStatus );
		//����ǰ��̬�����е����ݷ�ӳ����������
		ActiveStatusToGameStatus();
		m_isBottom = FALSE;

		//4.�жϵ�ǰ�����Ƿ��ѵ���
		IsBottom();

    	//5.�ж���Ϸ�Ƿ��ѽ���: ���˵ף��ҵ�1����С����
		if (m_isBottom)
			for (i=0;i<m_iCol;i++)
				if (GameStatus[0][i])
				{
					KillTimer(1);
					AfxMessageBox("��Ϸ�ѽ�����");
					for (j=0;j<m_iRow;j++)
						for (k=0;k<m_iCol;k++)
							GameStatus[j][k]=0;
					Invalidate(FALSE);
					m_bGameEnd = TRUE;
					break;
				}

	}
	else  //��ǰ�����½�
	{
		RectDown();
	}
	
	CView::OnTimer(nIDEvent);
}


/* * * * * * * * * * * * * * * * * * * * * *
* ����������һ�����ֵ������ָ��ֵ�����������(Random)
*
* ������MaxNumber : �����������
* 
* ����ֵ: �����������
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
int CSkyblue_RectView::Random(int MaxNumber)
{
	//�����������
	srand( (unsigned)time( NULL ) );
	//���������
	int random = rand() % MaxNumber;
	//��֤��0
	if(random == 0 ) random++;

	return random;
}


/* * * * * * * * * * * * * * * * * * * * * *
* �ڲ�����������ǰ��׹���λ��ӳ�䵽��Ϸ�����ͼ������ȥ
*
* ����޸����ڣ�2005.8.6
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
* �ڲ���������ʼ����ʱ�������ݷ������ʽ������ǰ��̬�����ֵ
*
* ����޸����ڣ�2005.8.6
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
* �ڲ���������ʼ����ʱ�������ݷ������ʽ������һ�ν�Ҫ�������Ķ�̬�����ֵ
*
* ����޸����ڣ�2005.8.6
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
* �ڲ���������ǰ�����½�
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectDown()
{
	IsBottom();
	if (!m_isBottom)
	{
		//�����ǰ�ķ���
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

		//��������
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
* �ڲ���������ǰ�����½����٣����ƣ�����
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectArrow(int m_Type)
{
	//��ȡ��ǰ��׹��4��С�����λ������
	int x1,x2,x3,x4,y1,y2,y3,y4;
	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];
	y1 = ActiveStatus[0][1];
	y2 = ActiveStatus[1][1];
	y3 = ActiveStatus[2][1];
	y4 = ActiveStatus[3][1];

	//�Բ�ͬ���ƶ�����ָʾ���з���ʵ��
	switch(m_Type)
	{
	case LEFT:
		//��ÿ�ֲ�ͬ���ƶ�����ָʾ��������Ӧ�Ŀ��ƶ�����
		if ( (ActiveStatus[0][1]>0) && IsLeftLimit() && !m_isBottom)
		{
			//��ԭ���ķ���
			GameStatus[x1][y1]=MAP_STATE_EMPTY;
			GameStatus[x2][y2]=MAP_STATE_EMPTY;
			GameStatus[x3][y3]=MAP_STATE_EMPTY;
			GameStatus[x4][y4]=MAP_STATE_EMPTY;

		//	InvalidateCurrent();
			//����µ��ƶ�������״̬
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
			//��ԭ���ķ���
			GameStatus[x1][y1]=MAP_STATE_EMPTY;
			GameStatus[x2][y2]=MAP_STATE_EMPTY;
			GameStatus[x3][y3]=MAP_STATE_EMPTY;
			GameStatus[x4][y4]=MAP_STATE_EMPTY;

		//	InvalidateCurrent();
			//����µ��ƶ�������״̬
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
* �ڲ��������жϵ�ǰ�����Ƿ��ѵ��ף��������е���صĹ���
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::IsBottom()
{
	//���������ָ��1���ѵ��ײ���2����������������ķ���
	int x1,x2,x3,x4;
	int x,xx,yy,i;

	x1 = ActiveStatus[0][0];
	x2 = ActiveStatus[1][0];
	x3 = ActiveStatus[2][0];
	x4 = ActiveStatus[3][0];


	//�Ƿ�Ϊ�ײ����ж�
	//1��������Ϸ����ĵײ�
	//2����Ӵ������·���С��������Ϊ��ռ��״̬
	if (x1>=m_iRow-1 || x2>=m_iRow-1 || x3>=m_iRow-1 || x4>=m_iRow-1)
		m_isBottom = TRUE;
	else
	{
		for (i=0;i<4;i++)
		{
			if (InterFace[m_currentRect][i] > -1)
			{//ȡ��ǰ��׹���нӴ���ķ���

				//��ȡ�нӴ����С����ı��
				x=InterFace[m_currentRect][i];
				//���ݱ�Ż�ȡActiveStatus�и�С��������·�������
				xx=ActiveStatus[x][0]+1;
				yy=ActiveStatus[x][1];
				//�жϸýӴ������·���С���������Ƿ�Ϊ��ռ��״̬
				if (GameStatus[xx][yy]==MAP_STATE_NOT_EMPTY)
					m_isBottom = TRUE;
			}
		}
	}

	BOOL m_bIsSucced;
	int k,j;
	int m_iMuch=0; //��������������

	//�Ʒֹ���һ������һ�У���100�֣�һ���������У���400�֣����У�900��
	//��������x�У������Ϊ��x*(x*100)

	if (m_isBottom)
	{
		//�ж��Ƿ��ѵ÷�
		for (i=0;i<m_iRow;i++)
		{
			m_bIsSucced = TRUE;
			for (j=0;j<m_iCol;j++)
				if (GameStatus[i][j]==MAP_STATE_EMPTY)
					m_bIsSucced = FALSE;
			
			//����÷֣�����������
			if (m_bIsSucced)
			{
				for (k=i;k>0;k--)
					for (j=0;j<m_iCol;j++)
						GameStatus[k][j] = GameStatus[k-1][j];
				//��1������
				for (j=0;j<m_iCol;j++)
					GameStatus[0][j]=MAP_STATE_EMPTY;

				m_iMuch += 1;
			}
		}
		
		if (m_iMuch>0)
		{
			m_iPerformance += m_iMuch * m_iMuch * 100;
			//ˢ����Ϸ����
			CRect rect1(m_iStartY, m_iStartX, m_iStartY+300, m_iStartX+360);
			//InvalidateRect(&rect1);
			
			//ˢ�·�������
			CRect rect2(m_iStartY+320, m_iStartX+180, m_iStartY+440, m_iStartX+200);
			//InvalidateRect(&rect2);
			Invalidate(FALSE);
		}

	}

}

/* * * * * * * * * * * * * * * * * * * * * * * * *
*
*  ���ƣ�OnKeyDown
*
*  ���ܣ������û������룬����������ƣ����ټ�����
*
*  ����޸�ʱ�䣺2005.8.6
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
* �ڲ������������Ƿ񻹿�������
*
* ����޸����ڣ�2005.8.6
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

	//���ݵ�ǰ��׹��ľ�����̬�������ж����Ƿ��������ƶ��Ŀռ�
	switch(m_currentRect)
	{
		/*
		|
		   |
	       |   "1"������̬���ͣ��ж����ĸ����������߶�û���κ�������ռ�û�б�ռ��)
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
* �ڲ������������Ƿ񻹿�������
*
* ����޸����ڣ�2005.8.6
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
* �ڲ�����������ı���
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::RectChange()
{
	//��Ԥ�ȱ��Σ�Ȼ���жϱ��κ�ķ����Ƿ��пռ䣬�����㹻�ռ䣬�����ʵ�ʱ��Σ����򲻱�
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

	//���κ�λ���������еĴ��˳��������ѭ������ң���ͬһ�������Ϻ���
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

	//������κ����ڵ����������������飬���ʾ���㹻�ռ䣬���Ա���
	//�Ҳ��ܳ�Խ�߽�
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

		//�ı���״����
		m_currentRect = m_lscurrentRect;
	}
	else
	{//�ָ�ԭ��״̬
		GameStatus[x1][y1] = MAP_STATE_NOT_EMPTY;
		GameStatus[x2][y2] = MAP_STATE_NOT_EMPTY;
		GameStatus[x3][y3] = MAP_STATE_NOT_EMPTY;
		GameStatus[x4][y4] = MAP_STATE_NOT_EMPTY;
	}

	//�ж��Ƿ��ѵ���
	IsBottom();
}


/* * * * * * * * * * * * * * * * * * * * * *
* �ڲ���������Ϸ��ʼ
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnGameStart() 
{
	if (!m_bGamePaush)  //���������Ϸ��ͣ״̬���������Щ��ʼ����
	{
		m_bGameEnd = FALSE;
		//�ܷ�ֵ����, ����ʾ�ּܷǷ���
		m_iPerformance = 0;
	
		//��ʾ��ǰ��������Ϸ����ĺ�������
		CurrentAreaAndLevel();
		
		CRect rect(m_iStartY, m_iStartX, m_iStartY+440, m_iStartX+370);
		InvalidateRect(&rect);
	}

	m_bGamePaush = FALSE;
	SetTimer(1,1500-250*m_iLevel,NULL);
}


//��Ϸ��ͣ
void CSkyblue_RectView::OnGamePaush() 
{
	m_bGamePaush = TRUE;

	KillTimer(1);
}

/* * * * * * * * * * * * * * * * * * * * * *
* �ڲ���������Ϸ����
*
* ����޸����ڣ�2005.8.6
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

	m_bGamePaush = FALSE;  //�����Ϸ��ͣ״̬

	KillTimer(1);	

}

/* * * * * * * * * * * * * * * * * * * * * *
* �ڲ�������ˢ�µ�ǰ������
*
* ֻˢ����Ҫˢ�µ��ĸ�С�������򣬷�ֹ��Ļ�����������
*
* ����޸����ڣ�2005.8.6
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
* �ڲ���������Ϸ����
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
void CSkyblue_RectView::OnGameOption() 
{
	//����˳�� �����С���룺0-3���ֱ�Ϊ��12X10��18X15��24X20��m_iLargeX25
	//����0-5���ֱ�Ϊ��1500��1200��1000��800��600��400
	//�������֣�TRUE ���� FALSE
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
		//ȷ������Ĵ�С
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

		//ȷ������
		m_iLevel = dlg.m_iLevel;
		//ѡ�����ʽ
		m_iBlockSytle = dlg.m_iBlockStyle;

		//ȷ���Ƿ�����񱳾�
		m_bDrawGrid = dlg.m_bDrawGrid;

        //����Ƿ�������								  
		m_bMusic = dlg.m_bMusic;
		if (m_bMusic)
			PlayMid();
		else
			StopMid();

		Invalidate();
	}	
}


//�������ɵ�ǰ�����С�뼶������Ӧ�ĺ�������
void CSkyblue_RectView::CurrentAreaAndLevel()
{
	switch(m_iRow)
	{
	case 12:
		m_strArea = "12��10��"; break;
	case 18:
		m_strArea = "18��15��"; break;
	case 24:
		m_strArea = "24��20��"; break;
	case 30:
		m_strArea = "30��25��"; break;
	}

	switch(m_iLevel)
	{
	case 0:
		m_strLevel = "��һ��: ���ż�"; break;
	case 1:
		m_strLevel = "�ڶ���: ������"; break;
	case 2:
		m_strLevel = "������: �м�"; break;
	case 3:
		m_strLevel = "���ļ�: �и߼�"; break;
	case 4:
		m_strLevel = "���弶: �߼�"; break;
	case 5:
		m_strLevel = "������: ����"; break;
	}
}


/* * * * * * * * * * * * * * * * * * * * * *
* �ڲ�����������Ϊ�˵������뿪������
*
* ����޸����ڣ�2005.8.6
* * * * * * * * * * * * * * * * * * * * * */
//�����Ϸ��ʼ�����[��ʼ��Ϸ]��ť������
void CSkyblue_RectView::OnUpdateGameStart(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd || m_bGamePaush)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//�����Ϸ��ʼ�����[��Ϸ����]��ť������
void CSkyblue_RectView::OnUpdateGameOption(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//����Ϸ��ʼ����[��Ϸ��ͣ]��ť����
void CSkyblue_RectView::OnUpdateGamePaush(CCmdUI* pCmdUI) 
{
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//�����Ϸ��ʼ�����[��Ϸ����]��ť������
void CSkyblue_RectView::OnUpdateGameEnd(CCmdUI* pCmdUI) 
{
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
	
}

//�����Ϸ��ʼ�����[�˳�ϵͳ]��ť������
void CSkyblue_RectView::OnUpdateGameExit(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//�����Ϸ��ʼ�����[����]��ť������
void CSkyblue_RectView::OnUpdateHelpAbout(CCmdUI* pCmdUI) 
{
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//�����Ϸ��ʼ�����[����]��ť������
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


//�ò˵����������С
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


//�ò˵����������С
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

// �ò˵�������Ϸ���� 
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


//�ò˵�������Ϸ����
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


//�ò˵������Ƿ�������
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
//��ű�������, ���д������
//
void CSkyblue_RectView::PlayMid()
{
	HWND hWnd;
	hWnd = GetSafeHwnd();
	//���������ַ������壬������Ϣ���滺�壬���ŵ��ļ���
	char szCmdBuf[300],errBuf[60],szfileName[255];
	//������
	MCIERROR mciError;

	//��ʼ���豸Ԫ��
	strcpy(szfileName,"skyblue_rect.mid"); 
	//��ʼ�������ַ���
	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
	//���豸
	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
	if (mciError == 0)
	{//����򿪳ɹ��򲥷�
		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
		//���ݲ��Ų����Ƿ�ɹ������Ƿ�ر��豸
		if (mciError != 0)
			mciSendString("close bkMusic",NULL,0,NULL);
	}
}

//
//��ֹ��ű�������
//
void CSkyblue_RectView::StopMid()
{
	//�ر��豸
	mciSendString("close bkMusic",NULL,0,NULL);
}

//�ò˵������Ƿ�������
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
	//�����ڴ��豸�������ͷ���Դ
	DCEnvClear();	
}

void CSkyblue_RectView::OnHelpAbout() 
{
	HWND hwnd = ::AfxGetMainWnd()->GetSafeHwnd();

	ShellAbout(hwnd,"����˹����  ����:skyblue ���н���","E-mail:skyblue@yahoo.com.cn",NULL);	
}

