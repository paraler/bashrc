#include<windows.h>
#include <time.h>

#include"snaker.h"
#include"table.h"

//游戏状态定义
#define GAME_STATE_WAIT     0  //游戏等待状态
#define GAME_STATE_RUN      1  //游戏运行状态
#define GAME_STATE_END      2  //游戏结束状态

//界面相关物件尺寸定义
#define WALL_WIDTH             80  //外墙从左部到游戏区的宽度
#define WALL_HEIGHT            80  //外墙从顶部到游戏区的高度

#define BMP_SCORE_BOARD_WIDTH  256 //分数位图板的宽度
#define BMP_SCORE_BOARD_HEIGHT 55  //分数位图板的高度

#define BMP_WALL_WIDTH         16  //墙位图的宽度
#define BMP_WALL_HEIGHT        16  //墙位图的高度

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,
						 WPARAM wParam,LPARAM lParam);
void DrawGame(void);
void ShellDraw( HDC  hdc );
void GameAreaDraw(HDC hdc);

void OnTimer(UINT uTIMER_ID);
void StartGame( void );
void EndGame( void );

//创建一个桌子
CTable table;

int tableBlockWidth = 0;  //桌子的格子的宽度
int tableBlockHeight = 0; //桌子的格子的高度
int iScores = 0;          //游戏的得分

UINT uGameState = GAME_STATE_WAIT; //当前游戏状态

HDC windowDC = NULL;      //windows屏幕设备
HDC bufferDC = NULL;      //缓冲设备环境
HDC picDC = NULL;         //snake图像内存设备
HDC endDC = NULL;		 //游戏终结图像内存设备
HDC scoreDC = NULL;      //分数板内存设备

HWND hAppWnd = NULL;     //本application窗口句柄


HBITMAP picBMP = NULL;      //snake图像位图句柄
HBITMAP bufferBMP = NULL;   //缓冲位图句柄
HBITMAP endBMP = NULL;      //游戏终结图像内存句柄
HBITMAP hbmpWall = NULL;    //墙位图句柄
HBITMAP hbmpScore = NULL;   //分数板位图句柄

HBRUSH hbrushWall = NULL;      //墙画刷

//定时器标识
UINT uSnakeMoveTimer;  //蛇的移动
UINT uFoodAddTimer;    //水果的产生

//框架的位置数据定义
//GDI RECT 而不是 MFC CRect
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
	
	
	//定义窗口
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
	//注册窗口
	RegisterClass(&wndClass);
	
	
	//取整个屏幕的尺寸	
	width=GetSystemMetrics(SM_CXSCREEN);
	height=	GetSystemMetrics(SM_CYSCREEN);
	//创建窗口
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

	//显示窗口
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
    //获取窗体大小
	GetClientRect(hAppWnd, &g_ClientRect);
	g_iClientWidth = g_ClientRect.right-g_ClientRect.left;
	g_iClientHeight = g_ClientRect.bottom-g_ClientRect.top;

	//将游戏区域分成纵，横均为20块的小方块
	//并计算每块区域的大小
	tableBlockWidth = (g_iClientWidth-2*WALL_WIDTH)/20;
	tableBlockHeight = (g_iClientHeight-2*WALL_HEIGHT)/20;
	
	//获取当前主窗口设备与windowDC关联
	windowDC=GetDC(NULL);
	//创建与windowDC兼容的内存设备环境
	bufferDC=CreateCompatibleDC(windowDC);
	picDC=CreateCompatibleDC(windowDC);
	endDC=CreateCompatibleDC(windowDC);	
	scoreDC=CreateCompatibleDC(windowDC);	

	//位图的初始化或载入位图	
	bufferBMP=CreateCompatibleBitmap(windowDC,g_iClientWidth,g_iClientHeight);
	picBMP=(HBITMAP)LoadImage(NULL,"snake.bmp",IMAGE_BITMAP,160,80,LR_LOADFROMFILE);
	hbmpWall=(HBITMAP)LoadImage(NULL,"brick.bmp",IMAGE_BITMAP,16,16,LR_LOADFROMFILE);
	endBMP = (HBITMAP)LoadImage(NULL,"end.bmp",IMAGE_BITMAP,369,300,LR_LOADFROMFILE);
	hbmpScore=(HBITMAP)LoadImage(NULL,"scoreboard.bmp",IMAGE_BITMAP,265,55,LR_LOADFROMFILE);
	
	//声明位图与设备环境的关联
	SelectObject(bufferDC,bufferBMP);
	SelectObject(picDC,picBMP);
	SelectObject(endDC,endBMP);
	SelectObject(scoreDC,hbmpScore);

	//建立画刷与其名相对应的图像的关联，
	//以备用刷子将墙刷出来，用PatBlt()实现
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
	//绘制外壳区域到缓冲
	ShellDraw(bufferDC);

	//绘制游戏区域到缓冲
	GameAreaDraw(bufferDC);

	//将整个画面从缓冲DC拷贝出屏幕
	BitBlt(windowDC,0,0,g_iClientWidth,g_iClientHeight,bufferDC,0,0,SRCCOPY);
}



void OnTimer(UINT uTIMER_ID)
{
	if ( uTIMER_ID == uSnakeMoveTimer )
	{
		//移动蛇
		table.SnakeMove();
		
		//检测是否碰到身体(环绕)，结束游戏
		if(table.GetSnake()->IsHeadTouchBody(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y))
		{
			EndGame();
		}
		
		//根据蛇头所在的区域作出相应的处理
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
			//检测是否碰到障碍物，结束游戏
			EndGame();
			break;
		}
		
		//显示
		DrawGame();
	}
	else if ( uTIMER_ID == uFoodAddTimer )
	{//定时加食物
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
}

void StartGame()
{
	iScores=0;

	//桌面的初始化
	table.InitialTable(tableBlockWidth,tableBlockHeight);
	table.GetSnake()->ChangeDirect(S_RIGHT);
	table.GetSnake()->SetHeadPos(tableBlockWidth/2,tableBlockHeight/2);

	//预先随机产生几个食物
	srand( (unsigned)time(NULL) );
	for(int iFoodNum=0;  iFoodNum<4; iFoodNum++)
	{
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
	//不部下种子也可以直接用rand(),
	//但是每次游戏开始都是产生完全一样的伪随即序列

	//打开定时器
	uSnakeMoveTimer = SetTimer(hAppWnd,500,100,NULL);
	uFoodAddTimer = SetTimer(hAppWnd,600,7000,NULL);

		uGameState = GAME_STATE_RUN;
}

void EndGame( void )
{
	//关闭定时器
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
	//分数提示显示文字
	char szText[30] = "Score: ";
	char szNum[20];

	int iNowScore = iScores*100;
	itoa(iNowScore,szNum,10);
	strcat(szText, szNum);
	
	RECT rt, rect;
	GetClientRect(hAppWnd, &rt);
	//墙的绘制
	SelectObject(hdc,hbrushWall);
	PatBlt(hdc,rt.left,rt.top,rt.right,rt.bottom,PATCOPY);
	//内部游戏区的白色底平面
	rect.left = rt.left+WALL_WIDTH;
	rect.top = rt.top + WALL_HEIGHT;
	rect.right = rt.right - WALL_WIDTH;
	rect.bottom = rt.bottom - WALL_HEIGHT;		
	FillRect(hdc, &rect, (HBRUSH) (COLOR_WINDOW+1));
	
	//分数提示板的绘制		
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
	
//分数的打印绘制
	SetBkMode(hdc, TRANSPARENT); 	
	TextOut(hdc, GetSystemMetrics(SM_CXSCREEN)/3+50, 30,szText,strlen(szText) );
}

void GameAreaDraw(HDC hdc)
{
	int i,j;
	int x,y, x_pos,y_pos;
	BitmapState  state;
	char strMark[20];

	//绘制水果与 毒果
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

		//根据当前的状态绘制蛇头		
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

		//根据各个蛇身节点的状态绘制蛇身的形状
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

		//绘制蛇尾巴
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
		{//绘制游戏结束图像
			int x_pos = g_iClientWidth/3;
			int y_pos = g_iClientHeight/4;

			BitBlt(hdc, x_pos, y_pos, 369, 300, endDC, 0, 0, SRCCOPY);			
		}
}