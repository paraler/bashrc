#include<windows.h>
#include <time.h>

#include"snaker.h"
#include"table.h"

//��Ϸ״̬����
#define GAME_STATE_WAIT     0  //��Ϸ�ȴ�״̬
#define GAME_STATE_RUN      1  //��Ϸ����״̬
#define GAME_STATE_END      2  //��Ϸ����״̬

//�����������ߴ綨��
#define WALL_WIDTH             80  //��ǽ���󲿵���Ϸ���Ŀ��
#define WALL_HEIGHT            80  //��ǽ�Ӷ�������Ϸ���ĸ߶�

#define BMP_SCORE_BOARD_WIDTH  256 //����λͼ��Ŀ��
#define BMP_SCORE_BOARD_HEIGHT 55  //����λͼ��ĸ߶�

#define BMP_WALL_WIDTH         16  //ǽλͼ�Ŀ��
#define BMP_WALL_HEIGHT        16  //ǽλͼ�ĸ߶�

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,
						 WPARAM wParam,LPARAM lParam);
void DrawGame(void);
void ShellDraw( HDC  hdc );
void GameAreaDraw(HDC hdc);

void OnTimer(UINT uTIMER_ID);
void StartGame( void );
void EndGame( void );

//����һ������
CTable table;

int tableBlockWidth = 0;  //���ӵĸ��ӵĿ��
int tableBlockHeight = 0; //���ӵĸ��ӵĸ߶�
int iScores = 0;          //��Ϸ�ĵ÷�

UINT uGameState = GAME_STATE_WAIT; //��ǰ��Ϸ״̬

HDC windowDC = NULL;      //windows��Ļ�豸
HDC bufferDC = NULL;      //�����豸����
HDC picDC = NULL;         //snakeͼ���ڴ��豸
HDC endDC = NULL;		 //��Ϸ�ս�ͼ���ڴ��豸
HDC scoreDC = NULL;      //�������ڴ��豸

HWND hAppWnd = NULL;     //��application���ھ��


HBITMAP picBMP = NULL;      //snakeͼ��λͼ���
HBITMAP bufferBMP = NULL;   //����λͼ���
HBITMAP endBMP = NULL;      //��Ϸ�ս�ͼ���ڴ���
HBITMAP hbmpWall = NULL;    //ǽλͼ���
HBITMAP hbmpScore = NULL;   //������λͼ���

HBRUSH hbrushWall = NULL;      //ǽ��ˢ

//��ʱ����ʶ
UINT uSnakeMoveTimer;  //�ߵ��ƶ�
UINT uFoodAddTimer;    //ˮ���Ĳ���

//��ܵ�λ�����ݶ���
//GDI RECT ������ MFC CRect
RECT g_ClientRect;
RECT g_GameValueRect;
int g_iClientWidth;
int g_iClientHeight;

int WINAPI WinMain(HINSTANCE hCurrentInst,HINSTANCE hPrevInstance,
				   PSTR lpszCmdLine,int nCmdShow)
{	
	WNDCLASS wndClass;
	HWND hWnd;
	MSG msg;
	UINT width,height;
	
	
	//���崰��
	wndClass.style=CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc=WndProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=hCurrentInst;
	wndClass.hIcon=LoadIcon(NULL,MAKEINTRESOURCE(IDI_MAIN));
	wndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName="Snake_CLASS";
	//ע�ᴰ��
	RegisterClass(&wndClass);
	
	
	//ȡ������Ļ�ĳߴ�	
	width=GetSystemMetrics(SM_CXSCREEN);
	height=	GetSystemMetrics(SM_CYSCREEN);
	//��������
	hWnd=CreateWindow(
		"Snake_CLASS",
		"skyblue snake",
		WS_POPUP,
		0,0,
		width,height,
		NULL,NULL,
		hCurrentInst,
		NULL);

	hAppWnd = hWnd;

	//��ʾ����
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
    //��ȡ�����С
	GetClientRect(hAppWnd, &g_ClientRect);
	g_iClientWidth = g_ClientRect.right-g_ClientRect.left;
	g_iClientHeight = g_ClientRect.bottom-g_ClientRect.top;

	//����Ϸ����ֳ��ݣ����Ϊ20���С����
	//������ÿ������Ĵ�С
	tableBlockWidth = (g_iClientWidth-2*WALL_WIDTH)/20;
	tableBlockHeight = (g_iClientHeight-2*WALL_HEIGHT)/20;
	
	//��ȡ��ǰ�������豸��windowDC����
	windowDC=GetDC(NULL);
	//������windowDC���ݵ��ڴ��豸����
	bufferDC=CreateCompatibleDC(windowDC);
	picDC=CreateCompatibleDC(windowDC);
	endDC=CreateCompatibleDC(windowDC);	
	scoreDC=CreateCompatibleDC(windowDC);	

	//λͼ�ĳ�ʼ��������λͼ	
	bufferBMP=CreateCompatibleBitmap(windowDC,g_iClientWidth,g_iClientHeight);
	picBMP=(HBITMAP)LoadImage(NULL,"snake.bmp",IMAGE_BITMAP,160,80,LR_LOADFROMFILE);
	hbmpWall=(HBITMAP)LoadImage(NULL,"brick.bmp",IMAGE_BITMAP,16,16,LR_LOADFROMFILE);
	endBMP = (HBITMAP)LoadImage(NULL,"end.bmp",IMAGE_BITMAP,369,300,LR_LOADFROMFILE);
	hbmpScore=(HBITMAP)LoadImage(NULL,"scoreboard.bmp",IMAGE_BITMAP,265,55,LR_LOADFROMFILE);
	
	//����λͼ���豸�����Ĺ���
	SelectObject(bufferDC,bufferBMP);
	SelectObject(picDC,picBMP);
	SelectObject(endDC,endBMP);
	SelectObject(scoreDC,hbmpScore);

	//������ˢ���������Ӧ��ͼ��Ĺ�����
	//�Ա���ˢ�ӽ�ǽˢ��������PatBlt()ʵ��
	hbrushWall = CreatePatternBrush(hbmpWall);
	
	StartGame();
	
	
	while(GetMessage(&msg,NULL,0,0))
	{		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,
						 WPARAM wParam,LPARAM lParam)
{
	
	switch(message)
	{
	case WM_TIMER :
		OnTimer((UINT)wParam);		
		break;		

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			exit(0);
			break;
		case VK_UP:
			table.ChangeSnakeDirect(S_UP);
			break;
		case VK_DOWN:
			table.ChangeSnakeDirect(S_DOWN);
			break;
		case VK_LEFT:
			table.ChangeSnakeDirect(S_LEFT);
			break;
		case VK_RIGHT:
			table.ChangeSnakeDirect(S_RIGHT);
			break;
		case VK_SPACE:
			if(	uGameState == GAME_STATE_END )
		{
			StartGame();
			break;
		}

		}
		return 0;
		case WM_SETCURSOR:
			SetCursor(NULL);
			return 0;
		case WM_DESTROY:
			ReleaseDC(hWnd,picDC);
			ReleaseDC(hWnd,bufferDC);
			ReleaseDC(hWnd,windowDC);
			PostQuitMessage(0);
			return 0;			
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}

void DrawGame(void)
{
	//����������򵽻���
	ShellDraw(bufferDC);

	//������Ϸ���򵽻���
	GameAreaDraw(bufferDC);

	//����������ӻ���DC��������Ļ
	BitBlt(windowDC,0,0,g_iClientWidth,g_iClientHeight,bufferDC,0,0,SRCCOPY);
}



void OnTimer(UINT uTIMER_ID)
{
	if ( uTIMER_ID == uSnakeMoveTimer )
	{
		//�ƶ���
		table.SnakeMove();
		
		//����Ƿ���������(����)��������Ϸ
		if(table.GetSnake()->IsHeadTouchBody(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y))
		{
			EndGame();
		}
		
		//������ͷ���ڵ�����������Ӧ�Ĵ���
		switch(table.GetData(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y))
		{
		case TB_STATE_FOOD:
			table.ClearFood(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y);
			table.AddBlock((rand())%tableBlockWidth,(rand())%tableBlockHeight);
			table.GetSnake()->AddBody();
			++iScores;
			break;
		case TB_STATE_BLOCK:
		case TB_STATE_SBLOCK:
			//����Ƿ������ϰ��������Ϸ
			EndGame();
			break;
		}
		
		//��ʾ
		DrawGame();
	}
	else if ( uTIMER_ID == uFoodAddTimer )
	{//��ʱ��ʳ��
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
}

void StartGame()
{
	iScores=0;

	//����ĳ�ʼ��
	table.InitialTable(tableBlockWidth,tableBlockHeight);
	table.GetSnake()->ChangeDirect(S_RIGHT);
	table.GetSnake()->SetHeadPos(tableBlockWidth/2,tableBlockHeight/2);

	//Ԥ�������������ʳ��
	srand( (unsigned)time(NULL) );
	for(int iFoodNum=0;  iFoodNum<4; iFoodNum++)
	{
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
	//����������Ҳ����ֱ����rand(),
	//����ÿ����Ϸ��ʼ���ǲ�����ȫһ����α�漴����

	//�򿪶�ʱ��
	uSnakeMoveTimer = SetTimer(hAppWnd,500,100,NULL);
	uFoodAddTimer = SetTimer(hAppWnd,600,7000,NULL);

		uGameState = GAME_STATE_RUN;
}

void EndGame( void )
{
	//�رն�ʱ��
	KillTimer(hAppWnd,uSnakeMoveTimer);
	KillTimer(hAppWnd,uFoodAddTimer);
	uGameState = GAME_STATE_END;
}

void ShellDraw( HDC  hdc )
{	
//	HDC hMemDc;
//	BOOL ret = TRUE;
//	HDC hMemoryDC;
//	HBITMAP hbmp;
	//������ʾ��ʾ����
	char szText[30] = "Score: ";
	char szNum[20];

	int iNowScore = iScores*100;
	itoa(iNowScore,szNum,10);
	strcat(szText, szNum);
	
	RECT rt, rect;
	GetClientRect(hAppWnd, &rt);
	//ǽ�Ļ���
	SelectObject(hdc,hbrushWall);
	PatBlt(hdc,rt.left,rt.top,rt.right,rt.bottom,PATCOPY);
	//�ڲ���Ϸ���İ�ɫ��ƽ��
	rect.left = rt.left+WALL_WIDTH;
	rect.top = rt.top + WALL_HEIGHT;
	rect.right = rt.right - WALL_WIDTH;
	rect.bottom = rt.bottom - WALL_HEIGHT;		
	FillRect(hdc, &rect, (HBRUSH) (COLOR_WINDOW+1));
	
	//������ʾ��Ļ���		
/*	hMemoryDC =	CreateCompatibleDC(NULL);	
	hbmp = CreateCompatibleBitmap(hdc,265,55);		
	SelectObject(hMemoryDC,hbrushScore);	
	SelectObject(hMemoryDC,hbmp);	
	PatBlt(hMemoryDC,0,0,256,55,PATCOPY);	
	BitBlt(hdc,GetSystemMetrics(SM_CXSCREEN)/3,
		   10,256,55,hMemoryDC,0,0,SRCCOPY);
*/
	BitBlt(hdc,GetSystemMetrics(SM_CXSCREEN)/3,
		   10,256,55,scoreDC,0,0,SRCCOPY);
	
//�����Ĵ�ӡ����
	SetBkMode(hdc, TRANSPARENT); 	
	TextOut(hdc, GetSystemMetrics(SM_CXSCREEN)/3+50, 30,szText,strlen(szText) );
}

void GameAreaDraw(HDC hdc)
{
	int i,j;
	int x,y, x_pos,y_pos;
	BitmapState  state;
	char strMark[20];

	//����ˮ���� ����
	for(i=0;i<tableBlockHeight;i++)
		for(j=0;j<tableBlockWidth;j++)
		{	
			x_pos = j*20+WALL_WIDTH;
			y_pos = i*20+WALL_HEIGHT;

			switch(table.GetData(j,i))
			{
			case TB_STATE_FOOD:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,0,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,0,SRCAND);
				break;
			case TB_STATE_BLOCK:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,0,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,0,SRCAND);
				break;
			}
		}

		//���ݵ�ǰ��״̬������ͷ		
		x=table.GetSnake()->GetPos()[0].x;
		y=table.GetSnake()->GetPos()[0].y;
		x_pos = x*20+WALL_WIDTH;
		y_pos = y*20+WALL_HEIGHT;		
		state=table.GetSnake()->GetStateArray()[0];

		switch(state)
		{
		case M_UP_UP:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,20,SRCAND);
			break;
		case M_DOWN_DOWN:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,20,SRCAND);
			break;
		case M_LEFT_LEFT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,20,SRCAND);
			break;
		case M_RIGHT_RIGHT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,20,SRCAND);
			break;
		}

		//���ݸ�������ڵ��״̬�����������״
		for(i=1;i<table.GetSnake()->GetLength()-1;i++)
		{
			x=table.GetSnake()->GetPos()[i].x;
			y=table.GetSnake()->GetPos()[i].y;
			x_pos = x*20+WALL_WIDTH;
			y_pos = y*20+WALL_HEIGHT;	
			state=table.GetSnake()->GetStateArray()[i];
			switch(state)
			{
			case M_UP_UP:
			case M_DOWN_DOWN:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,40,SRCAND);
				break;
			case M_LEFT_LEFT:
			case M_RIGHT_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,40,SRCAND);
				break;
			case M_RIGHT_DOWN:
			case M_UP_LEFT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,60,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,60,SRCAND);
				break;
			case M_LEFT_DOWN:
			case M_UP_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,60,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,60,SRCAND);
				break;
			case M_RIGHT_UP:
			case M_DOWN_LEFT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,40,SRCAND);
				break;
			case M_LEFT_UP:
			case M_DOWN_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,40,SRCAND);
				break;
				
			}
		}

		//������β��
		x=table.GetSnake()->GetPos()[table.GetSnake()->GetLength()-1].x;
		y=table.GetSnake()->GetPos()[table.GetSnake()->GetLength()-1].y;
		x_pos = x*20+WALL_WIDTH;
		y_pos = y*20+WALL_HEIGHT;	
		state=table.GetSnake()->GetStateArray()[table.GetSnake()->GetLength()-1];		
		switch(state)
		{
		case M_UP_UP:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,60,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,60,SRCAND);
			break;
		case M_DOWN_DOWN:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,0,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,0,SRCAND);
			break;
		case M_LEFT_LEFT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,60,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,60,SRCAND);
			break;
		case M_RIGHT_RIGHT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,0,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,0,SRCAND);
			break;
		}
		
		if(uGameState == GAME_STATE_END)
		{//������Ϸ����ͼ��
			int x_pos = g_iClientWidth/3;
			int y_pos = g_iClientHeight/4;

			BitBlt(hdc, x_pos, y_pos, 369, 300, endDC, 0, 0, SRCCOPY);			
		}
}