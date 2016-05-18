// skyblue_RectView.h : interface of the CSkyblue_RectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBLUE_RECTVIEW_H__D33E8EC7_BE69_4161_9B54_FB14CBA27F2E__INCLUDED_)
#define AFX_SKYBLUE_RECTVIEW_H__D33E8EC7_BE69_4161_9B54_FB14CBA27F2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 宏变量：白色和黑色
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define BLUE RGB(0,0,255)

//中断操作的运动趋势
#define LEFT  0      //向左移动
#define RIGHT 1      //向左移动
#define UP    2		//向上(变形)      
#define DOWN  3      //向下移动(加速)

//游戏区域地图最大限制
#define  MAX_ROW    100     //地图的最大行数
#define  MAX_COL    100      //地图的最大列数

//地图状态
#define MAP_STATE_EMPTY             0    //空(未被占据)
#define MAP_STATE_NOT_EMPTY         1    //被占据

class CSkyblue_RectView : public CView
{
protected: // create from serialization only
	CSkyblue_RectView();
	DECLARE_DYNCREATE(CSkyblue_RectView)

// Attributes
public:
	CSkyblue_RectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_RectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_RectView();


protected:
	int m_nWidth;  //子窗口的宽度
	int m_nHeight; //子窗口的高度

	//列与行的数量
	int m_iCol;
	int m_iRow;

	//小方块的大小,它会随着行与列的不同而不同，具体为：
	// 12行10列，30个象素的正方形
	// 18行15列，20
	// 24行20列，15
	// 30行25列，12
	int m_iLarge;

	//当前的级别，换算成速度的算法为：1500 - m_iLevel*200
	int m_iLevel;
	//当前选择的方块显示样式
	int m_iBlockSytle;

	//游戏区域左上角的坐标
	int m_iStartX;
	int m_iStartY;

	void RectChange();
	BOOL IsLeftLimit();       //下坠物件是否可向左移动
	BOOL IsRightLitmit();

	//接触面二维数组，记录1～7种下坠物的1～4种形态的接触面信息
	//我们把该下坠物的某种形态种的4个方块，有接触面则记录方位，无则为-1标识。
	int InterFace[74][4];
	
	//当前的方块形状
	int m_currentRect;

	//判断当前方块是否到底

void IsBottom();
	//当前方块下降
	void RectDown();

	//当前方块加速：UP，左移：LEFT，右移：RIGHT
	void RectArrow(int m_Type);
	
//根据下坠物的类型映射出它的具体形态  功能组
//根据旧的下一下坠物映射出当前激活状态下的下坠物形态
	void RectStatusToActiveStatus(int m_which); 
//根据下坠物形态映射出下一下坠物的形态
	void RectStatusToNextStatus(int m_which); 
//将当前的状态映射到地图游戏区域
	void ActiveStatusToGameStatus(); 


	int Random(int MaxNumber);
	//标识方块已到底的变量，到底为TRUE
	BOOL m_isBottom;

	//用于标志方块状态的数组，大小由横格与竖格数据决定，为1表示该方块显示，或者不显示
	//画形状只需要修改数组中相应元素的状态值即可
	//由时钟控制，定时在OnPaint函数中根据数组画方块
	int GameStatus[MAX_ROW][MAX_COL];

	//用于保存当前方块的动态位置，4个小方块分别在大数组中的位置
	//存放位置为先左后右，每一列又遵循先上后下的原则
	int ActiveStatus[4][2];

	//存入下一次要出来的方块的模样的数组
	int NextStatus[4][2];

// Generated message map functions
protected:
	BOOL m_bGamePaush;
	void StopMid();
	void PlayMid();
	void CurrentAreaAndLevel();
	//用于记录当前区域大小与当前级别的字符串，用于显示在屏幕上提示用户当前状态
	CString m_strArea;
	CString m_strLevel;

	//当前的样式 ，下一个将会出现的样式
	int m_icurrentStatus;
	int m_inextStatus;

	//OnDraw中需要用到的设备名称
	CPen *m_pBlackPen;
	CBrush *m_pGrayBrush;
	CBrush *m_pBlackBrush;

	//是否画网格线
	BOOL m_bDrawGrid;

	//是否插放背景音乐
	BOOL m_bMusic;

	//游戏总成绩
	int m_iPerformance;

	//游戏是否已结束，为FALSE表示开始，否则为结束
	BOOL m_bGameEnd;
	
	//刷新指定的区域，它的大小为：四个小方块所在的正方形的大小
	void InvalidateCurrent();

	//内存绘图设备的处理
	CDC m_memDC;                   //内存设备环境 
	CBitmap m_memBmp;              //内存位图

	CDC m_memRectDC;       //方块内存设备环境
	HBITMAP m_hMemRectBmp;  //方块内存位图句柄

	int m_bFistPlay;               //是否是第一次开始游戏
	void DcEnvInitial(void); 
	void DCEnvClear(void);
	void DrawGame(CDC *pDC);
	

// Generated message map functions
protected:
	//{{AFX_MSG(CSkyblue_RectView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGameStart();
	afx_msg void OnGameEnd();
	afx_msg void OnGameOption();
	afx_msg void OnUpdateGameStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameOption(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameExit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpAbout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpHelp(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHelpHelp();
	afx_msg void OnUpdateOptionArea1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionArea2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionArea3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionArea4(CCmdUI* pCmdUI);
	afx_msg void OnOptionArea1();
	afx_msg void OnOptionArea2();
	afx_msg void OnOptionArea3();
	afx_msg void OnOptionArea4();
	afx_msg void OnUpdateOptionLevel1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionLevel2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionLevel3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionLevel4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionLevel5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionLevel6(CCmdUI* pCmdUI);
	afx_msg void OnOptionLevel1();
	afx_msg void OnOptionLevel2();
	afx_msg void OnOptionLevel3();
	afx_msg void OnOptionLevel4();
	afx_msg void OnOptionLevel5();
	afx_msg void OnOptionLevel6();
	afx_msg void OnUpdateOptionGrid(CCmdUI* pCmdUI);
	afx_msg void OnOptionGrid();
	afx_msg void OnUpdateOptionMusic(CCmdUI* pCmdUI);
	afx_msg void OnOptionMusic();
	afx_msg void OnUpdateGamePaush(CCmdUI* pCmdUI);
	afx_msg void OnGamePaush();
	afx_msg void OnGameExit();
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/*
CRectGameView : public CView
{
	//内部存取数据结构
	int m_stateMap[MAX_ROW][MAX_COL];
	
	//初始化操作
	GameInitnal();      //游戏的初始化
	
	//用于判断数据相关状态的操作
	IsLeftLimit();       //下坠物件是否可向左移动
	IsRightLitmit();     //
	IsBottom();          //是否已经到达了底部
	IsGameEnd();         //是否游戏已经结束
		
	//方块物件下坠过程中的操作
	RectChange();        //下坠物件变形
	RectDown();          //下坠物件正常下落
	RectArrow();         //下坠物件方向移动(左，右，下加速）

  	//状态控制操作
	GameStart();         //游戏开始
	GamePause();         //游戏暂停
	GameEnd();           //游戏结束
}
#ifndef _DEBUG  // debug version in skyblue_RectView.cpp
inline CSkyblue_RectDoc* CSkyblue_RectView::GetDocument()
   { return (CSkyblue_RectDoc*)m_pDocument; }
#endif
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_RECTVIEW_H__D33E8EC7_BE69_4161_9B54_FB14CBA27F2E__INCLUDED_)
