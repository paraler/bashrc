/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

     BoxMan.cpp

Abstract:

	BoxMan Game Class ,solve all the important movment of the man and box,
	and some thing refer to them

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "skyblue_BoxMan.h"
#include "BoxMan.h"
#include <Mmsystem.h>   //��Ч  Winmm.lib


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//��ͼ״̬
#define MAP_BACKGROUP  48  //'0'  ��Ӧ�ַ�'0'����
#define MAP_WHITEWALL  49  //'1'  ǽ
#define MAP_BLUEWALL   50  //'2'  ͨ��
#define MAP_BALL       51  //'3'  Ŀ�ĵ�
#define MAP_YELLOWBOX  52  //'4'  ����
#define MAP_REDBOX     53  //'5'  ���źõ�����
#define MAP_MANWALL    54  //'6'  ����ͨ������
#define MAP_MANBALL    55  //'7'  ����Ŀ�ĵ�����


//����״̬
#define SOUND_STATE_START   0  //��Ϸ��ʼ
#define SOUND_STATE_MOVE    1  //���������ƶ�
#define SOUND_STATE_PUSH    2  //���߲��ƶ�����
#define SOUND_STATE_VICTORY 3  //ʤ��

//��Ϸ����С�����С 
#define BLOCK_WIDTH    20   //  ���
#define BLOCK_HEIGHT    20  //  ���



//�ٺ궨��
int MAX_MISSION_NUM  = 1;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoxMan::CBoxMan()
{
    m_iMissionNum = 1;
	::MAX_MISSION_NUM = LoadMaxMissionNum();
    LoadMap(m_iMissionNum);
    m_ptManPosition = GetManPosition();
}

CBoxMan::~CBoxMan()
{

}


void CBoxMan::LoadMap(int iMissionNum)
{
    CString str;
    str.Format("[%d]", iMissionNum);

	FILE *pFile = fopen("map.info", "rb");
	if (pFile == NULL)
	{
        AfxMessageBox("�����ͼ�ļ�ʧ��");
        return;
	}

    char cTmp[M_TAB_WIDTH*2];
    fgets(cTmp, M_TAB_WIDTH*2, pFile);
    while (strncmp(cTmp, str, 3) != 0)
    {
        fgets(cTmp, M_TAB_WIDTH*2, pFile);
    }

    for (int i = 0; i < M_TAB_HEIGHT; i++)
        fgets(m_cMap[i],M_TAB_WIDTH*2, pFile);

    fclose(pFile);
}







int CBoxMan::LoadMaxMissionNum(void)
{
	int iMissionNum = 1;
    CString str;
    str.Format("[%d]", iMissionNum);
	
	FILE *pFile = fopen("map.info", "rb");
	if (pFile == NULL)
	{
        AfxMessageBox("�����ͼ�ļ�ʧ��");
        return -1;
	}
	
    char cTmp[M_TAB_WIDTH*2];
	while( !feof(pFile) )//not end of file
	{
		fgets(cTmp, M_TAB_WIDTH*2, pFile);
		if(strncmp(cTmp, str, 3) == 0)
		{
		    str.Format("[%d]", ++iMissionNum);
		}
	}
    fclose(pFile);

	return iMissionNum-1;
}

CPoint CBoxMan::GetManPosition()
{
    CPoint manPosition(0, 0);
    for (int i = 0; i < M_TAB_HEIGHT; i++)
    {
        for (int j = 0; j < M_TAB_WIDTH; j++)
        {
            if (m_cMap[i][j]==MAP_MANWALL || m_cMap[i][j]==MAP_MANBALL)
            {
                manPosition.x = j;
                manPosition.y = i;
            }
        }
    }
    return manPosition;
}

void CBoxMan::DrawGameArea(CDC* pDC)
{
    int i, j, x, y;

	//����������ͼ��Ϸ����
    for (i = 0; i < M_TAB_HEIGHT; i++)
    {
        for (j = 0; j < M_TAB_WIDTH; j++)
        {
            x = j * BLOCK_WIDTH;
            y = i * BLOCK_HEIGHT;

            switch (m_cMap[i][j])
            {
            case MAP_BACKGROUP://����
                DrawBackGroup(x, y, pDC);
                break;
            case MAP_WHITEWALL://ǽ
                DrawWhiteWall(x, y, pDC);
                break;
            case MAP_BLUEWALL://ͨ��
                DrawBlueWall(x, y, pDC);
                break;
            case MAP_BALL://Ŀ�ĵ�
                DrawBall(x, y, pDC);
                break;
            case MAP_YELLOWBOX://δ���źõ�����
                DrawYellowBox(x, y, pDC);
                break;
            case MAP_REDBOX://���źõ�����
                DrawRedBox(x, y, pDC);
                break;
            case MAP_MANWALL://����ͨ������
                DrawManWall(x, y, pDC);
                break;
            case MAP_MANBALL://����Ŀ�ĵ�����
                DrawManBall(x, y, pDC);
                break;
            }
        }
    }

	//��ȡ�ɵ��ı�����
    COLORREF crOldText = pDC->GetTextColor();
    COLORREF crOldBack = pDC->GetBkColor();
	//���ĵ�ǰ���ı�����
    pDC->SetTextColor(RGB(0, 0, 102));
	pDC->SetBkColor(RGB(0, 0, 0));
	//����ı�
    CString sTmp;
    sTmp.Format("��ǰ���� : %d ", m_iMissionNum);
    pDC->TextOut(50, 270, sTmp);
	//�ָ�ԭ���ı�����
    pDC->SetTextColor(crOldText);
    pDC->SetBkColor(crOldBack);
}

//
//  ���Ʊ���
//
void CBoxMan::DrawBackGroup(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 0);
    pDC->FillSolidRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, clr);
}

//
//  ����ǽ
//
void CBoxMan::DrawWhiteWall(int x, int y, CDC* pDC)
{
    COLORREF clr1 = RGB(255, 255, 255);
    COLORREF clr2 = RGB(48, 48, 48);
    COLORREF clr3 = RGB(192, 192, 192);

	//�ص�������3DЧ��,����3�㽥��
    pDC->FillSolidRect(x, y, 19, 19, clr1);
    pDC->FillSolidRect(x + 1, y + 1, 19, 19, clr2);
    pDC->FillSolidRect(x + 1, y + 1, 18, 18, clr3);

	//����ǽ�ķ�϶
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

//
//  ����ͨ��
//
void CBoxMan::DrawBlueWall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

//
//  ����Ŀ�ĵ�
//
void CBoxMan::DrawBall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
    pDC->Ellipse(x, y, x + 20, y + 20);
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);
}

//
//  ����δ�źõ�����
//
void CBoxMan::DrawYellowBox(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(255, 255, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 192, 0);
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);
    pDC->SetPixel(x + 3, y + 3, clr3);
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);
}

//
//  ���ư��źõ�����
//
void CBoxMan::DrawRedBox(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(255, 255, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 0, 0);
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);
    pDC->SetPixel(x + 3, y + 3, clr3);
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);
}

//
//  ��������ͨ��
//
void CBoxMan::DrawManWall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //��ɫǽ
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);

	//�˵Ļ���
    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //��ͷ

    pDC->MoveTo(x + 2, y + 11);                      //����
    pDC->LineTo(x + 18, y + 11);

    pDC->MoveTo(x + 10, y + 10);                     //������
    pDC->LineTo(x + 10, y + 12);

    pDC->MoveTo(x + 2, y + 20);                      //�˽�
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}

//
//  ��������Ŀ�ĵ�
//
void CBoxMan::DrawManBall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //��
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
    pDC->Ellipse(x, y, x + 20, y + 20);
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);

	//�˵Ļ���
    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //��ͷ

    pDC->MoveTo(x + 2, y + 11);                      //����
    pDC->LineTo(x + 18, y + 11);

    pDC->MoveTo(x + 10, y + 10);                     //������
    pDC->LineTo(x + 10, y + 12);

    pDC->MoveTo(x + 2, y + 20);                      //�˽�
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}

void CBoxMan::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    DispatchMsg(nChar);

    if (IsFinish())
    {
		m_soundState = SOUND_STATE_VICTORY;
        m_iMissionNum = m_iMissionNum +1;
        if (m_iMissionNum > MAX_MISSION_NUM)
            m_iMissionNum = 1;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
    }

	BoxManPlaySound();
}

void CBoxMan::DispatchMsg(UINT nChar)
{
    int x1, y1, x2, y2, x3, y3;

	//��ȡ���˵�ǰλ��
    x1 = m_ptManPosition.x;
    y1 = m_ptManPosition.y;

	//����������Ϣ
    switch (nChar)
    {
	//����
    case VK_UP:
        x2 = x1;
        y2 = y1 - 1;
        x3 = x1;
        y3 = y1 - 2;
		//������λ���������жϲ�����ͼ����
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
	//����
    case VK_DOWN:
        x2 = x1;
        y2 = y1 + 1;
        x3 = x1;
        y3 = y1 + 2;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
	//����
    case VK_LEFT:
        x2 = x1 - 1;
        y2 = y1;
        x3 = x1 - 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
	//����
    case VK_RIGHT:
        x2 = x1 + 1;
        y2 = y1;
        x3 = x1 + 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;

  //ѡ�ع��ܼ�
    case 82:  //R  �����浱ǰ��
    case 114: //r  
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 113:  //F2  ������һ��
        m_iMissionNum = m_iMissionNum + 1;
        if (m_iMissionNum > MAX_MISSION_NUM)
            m_iMissionNum = 1;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 112:  //F1  ����ǰһ��
        m_iMissionNum = m_iMissionNum - 1;
        if (m_iMissionNum < 1)
            m_iMissionNum = MAX_MISSION_NUM;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
    }
}

void CBoxMan::UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
    switch (m_cMap[y2][x2])
    {
    case MAP_BACKGROUP:           //��ͼ��ƴ���,��Ӧ�ó���
        AfxMessageBox("wrong map");
        break;
    case MAP_WHITEWALL:          //����ǽ�������κ�����
        
        break;
    case MAP_BLUEWALL:           //ͨ������������
        m_cMap[y2][x2] = MAP_MANWALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_MOVE;
        break;

    case MAP_BALL:               //Ŀ�ĵأ���������
        m_cMap[y2][x2] = MAP_MANBALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;        
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_MOVE;
        break;

    case MAP_YELLOWBOX:          //����
        if (m_cMap[y3][x3] == MAP_BALL)   //Ŀ�ĵؿ�������
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_PUSH;
        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) //ͨ������������
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
		m_soundState = SOUND_STATE_PUSH;
        }
        break;

    case MAP_REDBOX:             //���źõ�����
        if (m_cMap[y3][x3] == MAP_BALL)   //Ŀ�ĵؿ�������
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL)  //ͨ������������
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			m_soundState = SOUND_STATE_PUSH;
        }        
        break;

    case MAP_MANWALL:            //��ͼ��ƴ���,��Ӧ�ó���
        AfxMessageBox("wrong map");
        break;

    case MAP_MANBALL:            //��ͼ��ƴ���,��Ӧ�ó���
        AfxMessageBox("wrong map");
        break;
    }
}

bool CBoxMan::IsFinish()
{
    bool bFinish = true;
    for (int i = 0; i < M_TAB_HEIGHT; i++)
    {
        for (int j = 0; j < M_TAB_WIDTH; j++)
        {
            if (m_cMap[i][j] == MAP_BALL || m_cMap[i][j] == MAP_MANBALL)
                bFinish = false;
        }
    }
    return bFinish;
}

BOOL CBoxMan::ChangeMissionNum(int iNum)
{
	if((iNum>MAX_MISSION_NUM)||(iNum<1))
	{
		return FALSE;
	}
	else
	{
        m_iMissionNum = iNum;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
		return TRUE;
	}
}

int  CBoxMan::GetNowMissionNum(void)
{
	return m_iMissionNum;
}

void CBoxMan::BoxManPlaySound(void)
{
	if(m_bSound)
	{
		char strFileName[30];
		
		switch (m_soundState)
		{
		case SOUND_STATE_START :
			strcpy(strFileName,"start.wav");
			break;
			
		case SOUND_STATE_MOVE :
			strcpy(strFileName,"move.wav");
			break;
			
		case SOUND_STATE_PUSH :
			strcpy(strFileName,"push.wav");
			break;
			
		case SOUND_STATE_VICTORY :
			strcpy(strFileName,"victory.wav");
			break;
			
		default:
			return;
		}

		PlaySound(strFileName, NULL, SND_ASYNC | SND_FILENAME);	
	}
}

void CBoxMan::IsSound(BOOL bUse)
{
	m_bSound = bUse;
}