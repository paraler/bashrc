/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    BoxMan_Edit.cpp

Abstract:

	the BoxMan-Edit operation-contain Class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "BoxMan_Editer.h"
#include "BoxMan_Edit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int MAP_WIDTH =                16;
int MAP_HEIGHT   =             14;
int MAP_SMALL_SQUARE_SIZE  =   20;

//地图状态
#define MAP_BACKGROUP  48  //'0'  对应字符'0'
#define MAP_WHITEWALL  49  //'1'
#define MAP_BLUEWALL   50  //'2'
#define MAP_BALL       51  //'3'
#define MAP_YELLOWBOX  52  //'4'
#define MAP_REDBOX     53  //'5'
#define MAP_MANWALL    54  //'6'
#define MAP_MANBALL    55  //'7'




//假宏定义
int MAX_MISSION_NUM  = 1;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoxMan_Edit::CBoxMan_Edit()
{
	ClearMap();
	MAX_MISSION_NUM = LoadMaxMissionNum();
}

CBoxMan_Edit::~CBoxMan_Edit()
{

}


void CBoxMan_Edit::LoadMap(int iMissionNum)
{
    CString str;
    str.Format("[%d]", iMissionNum);

	FILE *pFile = fopen("map.info", "rb");
	if (pFile == NULL)
	{
        AfxMessageBox("载入地图文件失败");
        return;
	}

    char cTmp[20];
    fgets(cTmp, 20, pFile);
    while (strncmp(cTmp, str, 3) != 0)
    {
        fgets(cTmp, 20, pFile);
    }

    for (int i = 0; i < MAP_HEIGHT; i++)
        fgets(m_cMap[i], 20, pFile);

    fclose(pFile);
}

void CBoxMan_Edit::SaveMap(void)
{
    CString str;
    str.Format("[%d]", MAX_MISSION_NUM+1);
	
    //最大地图数已经在初始化时候获取

	//打开地图文件
	FILE *pFile = fopen("map.info", "a+t");
	if (pFile == NULL)
	{
        AfxMessageBox("打开地图文件失败");
        return;
	}
	//文件指针移到文件末
	fseek( pFile, 0L, SEEK_END);

	//写入体图头部
	fputs(str,pFile);
	fputs("\n",pFile);

	//写入地图数据体
	char strBuf[200];
    for (int i = 0; i < MAP_HEIGHT; i++)
	{
		memset(strBuf,0,sizeof(strBuf));
		memcpy(strBuf,m_cMap[i],MAP_WIDTH);
        fputs(strBuf, pFile);
		fputs("\n",pFile);

	}

	//关闭地图
    fclose(pFile);
	
	//最大地图数自增
	MAX_MISSION_NUM += 1;
}

int CBoxMan_Edit::LoadMaxMissionNum(void)
{
	int iMissionNum = 1;
    CString str;
    str.Format("[%d]", iMissionNum);
	
	FILE *pFile = fopen("map.info", "rb");
	if (pFile == NULL)
	{
        AfxMessageBox("载入地图文件失败");
        return -1;
	}
	
    char cTmp[20];
	while( !feof(pFile) )//not end of file
	{
		fgets(cTmp, 20, pFile);
		if(strncmp(cTmp, str, 3) == 0)
		{
		    str.Format("[%d]", ++iMissionNum);
		}
	}
    fclose(pFile);

	return iMissionNum-1;
}

CPoint CBoxMan_Edit::GetManPosition()
{
    CPoint manPosition(0, 0);
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
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

void CBoxMan_Edit::DrawMap(CDC* pDC)
{
    int i, j, x, y;
    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < MAP_WIDTH; j++)
        {// pDC->TextOut(j * 10, i * 15, m_cMap[i][j]);
            x = j * 20;
            y = i * 20;
            switch (m_cMap[i][j])
            {
            case MAP_BACKGROUP://0
                DrawBackGroup(x, y, pDC);
                break;
            case MAP_WHITEWALL://1
                DrawWhiteWall(x, y, pDC);
                break;
            case MAP_BLUEWALL://2
                DrawBlueWall(x, y, pDC);
                break;
            case MAP_BALL://3
                DrawBall(x, y, pDC);
                break;
            case MAP_YELLOWBOX://4
                DrawYellowBox(x, y, pDC);
                break;
            case MAP_REDBOX://5
                DrawRedBox(x, y, pDC);
                break;
            case MAP_MANWALL://6
                DrawManWall(x, y, pDC);
                break;
            case MAP_MANBALL://7
                DrawManBall(x, y, pDC);
                break;
            }
        }
    }
}

void CBoxMan_Edit::DrawBackGroup(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
}

void CBoxMan_Edit::DrawWhiteWall(int x, int y, CDC* pDC)
{
    COLORREF clr1 = RGB(255, 255, 255);
    COLORREF clr2 = RGB(48, 48, 48);
    COLORREF clr3 = RGB(192, 192, 192);
    pDC->FillSolidRect(x, y, 19, 19, clr1);
    pDC->FillSolidRect(x + 1, y + 1, 19, 19, clr2);
    pDC->FillSolidRect(x + 1, y + 1, 18, 18, clr3);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

void CBoxMan_Edit::DrawBlueWall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

void CBoxMan_Edit::DrawBall(int x, int y, CDC* pDC)
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

void CBoxMan_Edit::DrawYellowBox(int x, int y, CDC* pDC)
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

void CBoxMan_Edit::DrawRedBox(int x, int y, CDC* pDC)
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

void CBoxMan_Edit::DrawManWall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //蓝色墙
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);

    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //人头

    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);

    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 12);

    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}

void CBoxMan_Edit::DrawManBall(int x, int y, CDC* pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //球
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
    pDC->Ellipse(x, y, x + 20, y + 20);
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);

    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //人头

    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);

    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 12);

    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}



void CBoxMan_Edit::UpdateMap(UINT nChar)
{
    int x1, y1, x2, y2, x3, y3;

    x1 = m_ptManPosition.x;
    y1 = m_ptManPosition.y;

    switch (nChar)
    {
    case VK_UP:
        x2 = x1;
        y2 = y1 - 1;
        x3 = x1;
        y3 = y1 - 2;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_DOWN:
        x2 = x1;
        y2 = y1 + 1;
        x3 = x1;
        y3 = y1 + 2;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_LEFT:
        x2 = x1 - 1;
        y2 = y1;
        x3 = x1 - 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_RIGHT:
        x2 = x1 + 1;
        y2 = y1;
        x3 = x1 + 2;
        y3 = y1;
        UpdateMap(x1, y1, x2, y2, x3, y3);
        break;
    case 82:  //R  replay this mission
    case 114: //r  replay this mission
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 113:  //F2  play next mission
        m_iMissionNum = m_iMissionNum + 1;
        if (m_iMissionNum > MAX_MISSION_NUM)
            m_iMissionNum = 1;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
        break;
    case 112:  //F1  play forward mission

        m_iMissionNum = m_iMissionNum - 1;
        if (m_iMissionNum < 1)
            m_iMissionNum = MAX_MISSION_NUM;
        LoadMap(m_iMissionNum);
        m_ptManPosition = GetManPosition();
    }
}

void CBoxMan_Edit::UpdateMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
    switch (m_cMap[y2][x2])
    {
    case MAP_BACKGROUP:           //wrong map
        AfxMessageBox("wrong map");
        break;
    case MAP_WHITEWALL:          //do nothing
        
        break;
    case MAP_BLUEWALL:           //can go
        m_cMap[y2][x2] = MAP_MANWALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;

        break;

    case MAP_BALL:               //can go
        m_cMap[y2][x2] = MAP_MANBALL;
        if (m_cMap[y1][x1] == MAP_MANWALL)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;        
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;

        break;

    case MAP_YELLOWBOX:          //under judge
        if (m_cMap[y3][x3] == MAP_BALL)   // can go
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) //can go
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANWALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        break;

    case MAP_REDBOX:             //under judge
        if (m_cMap[y3][x3] == MAP_BALL)   // can go
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) //can go
        {
            m_cMap[y3][x3] = MAP_YELLOWBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MANWALL)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;

        }        
        break;

    case MAP_MANWALL:            //wrong map
        AfxMessageBox("wrong map");
        break;

    case MAP_MANBALL:            //wrong map
        AfxMessageBox("wrong map");
        break;
    }
}

bool CBoxMan_Edit::IsFinish()
{
    bool bFinish = true;
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (m_cMap[i][j] == MAP_BALL || m_cMap[i][j] == MAP_MANBALL)
                bFinish = false;
        }
    }
    return bFinish;
}

BOOL CBoxMan_Edit::ChangeMissionNum(int iNum)
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

int  CBoxMan_Edit::GetNowMissionNum(void)
{
	return m_iMissionNum;
}

void CBoxMan_Edit::ChangeMap(int x, int y, int iState)
{
            m_cMap[y][x] = iState;	
}

void CBoxMan_Edit::ClearMap(void)
{
	for(int x=0; x< MAP_WIDTH; x++)
		for(int y=0; y<MAP_HEIGHT; y++)
		{
            m_cMap[y][x] = MAP_BACKGROUP;	
		}
}


void CBoxMan_Edit::DrawMouseCursor(int x, int y, int iState, CDC *pDC)
{
	switch (iState)
	{
	case MAP_BACKGROUP://背景
		DrawBackGroup(x, y, pDC);
		break;
	case MAP_WHITEWALL://墙
		DrawWhiteWall(x, y, pDC);
		break;
	case MAP_BLUEWALL://通道
		DrawBlueWall(x, y, pDC);
		break;
	case MAP_BALL://目的地
		DrawBall(x, y, pDC);
		break;
	case MAP_YELLOWBOX://箱子
		DrawYellowBox(x, y, pDC);
		break;
	case MAP_REDBOX://箱子
		DrawRedBox(x, y, pDC);
		break;
	case MAP_MANWALL://人在目的地
		DrawManWall(x, y, pDC);
		break;
	case MAP_MANBALL://人在通道
		DrawManBall(x, y, pDC);
		break;
	}
}