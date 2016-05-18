// skyblue_RectView.h : interface of the CSkyblue_RectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBLUE_RECTVIEW_H__D33E8EC7_BE69_4161_9B54_FB14CBA27F2E__INCLUDED_)
#define AFX_SKYBLUE_RECTVIEW_H__D33E8EC7_BE69_4161_9B54_FB14CBA27F2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ���������ɫ�ͺ�ɫ
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define BLUE RGB(0,0,255)

//�жϲ������˶�����
#define LEFT  0      //�����ƶ�
#define RIGHT 1      //�����ƶ�
#define UP    2		//����(����)      
#define DOWN  3      //�����ƶ�(����)

//��Ϸ�����ͼ�������
#define  MAX_ROW    100     //��ͼ���������
#define  MAX_COL    100      //��ͼ���������

//��ͼ״̬
#define MAP_STATE_EMPTY             0    //��(δ��ռ��)
#define MAP_STATE_NOT_EMPTY         1    //��ռ��

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
	int m_nWidth;  //�Ӵ��ڵĿ��
	int m_nHeight; //�Ӵ��ڵĸ߶�

	//�����е�����
	int m_iCol;
	int m_iRow;

	//С����Ĵ�С,�������������еĲ�ͬ����ͬ������Ϊ��
	// 12��10�У�30�����ص�������
	// 18��15�У�20
	// 24��20�У�15
	// 30��25�У�12
	int m_iLarge;

	//��ǰ�ļ��𣬻�����ٶȵ��㷨Ϊ��1500 - m_iLevel*200
	int m_iLevel;
	//��ǰѡ��ķ�����ʾ��ʽ
	int m_iBlockSytle;

	//��Ϸ�������Ͻǵ�����
	int m_iStartX;
	int m_iStartY;

	void RectChange();
	BOOL IsLeftLimit();       //��׹����Ƿ�������ƶ�
	BOOL IsRightLitmit();

	//�Ӵ����ά���飬��¼1��7����׹���1��4����̬�ĽӴ�����Ϣ
	//���ǰѸ���׹���ĳ����̬�ֵ�4�����飬�нӴ������¼��λ������Ϊ-1��ʶ��
	int InterFace[74][4];
	
	//��ǰ�ķ�����״
	int m_currentRect;

	//�жϵ�ǰ�����Ƿ񵽵�

void IsBottom();
	//��ǰ�����½�
	void RectDown();

	//��ǰ������٣�UP�����ƣ�LEFT�����ƣ�RIGHT
	void RectArrow(int m_Type);
	
//������׹�������ӳ������ľ�����̬  ������
//���ݾɵ���һ��׹��ӳ�����ǰ����״̬�µ���׹����̬
	void RectStatusToActiveStatus(int m_which); 
//������׹����̬ӳ�����һ��׹�����̬
	void RectStatusToNextStatus(int m_which); 
//����ǰ��״̬ӳ�䵽��ͼ��Ϸ����
	void ActiveStatusToGameStatus(); 


	int Random(int MaxNumber);
	//��ʶ�����ѵ��׵ı���������ΪTRUE
	BOOL m_isBottom;

	//���ڱ�־����״̬�����飬��С�ɺ�����������ݾ�����Ϊ1��ʾ�÷�����ʾ�����߲���ʾ
	//����״ֻ��Ҫ�޸���������ӦԪ�ص�״ֵ̬����
	//��ʱ�ӿ��ƣ���ʱ��OnPaint�����и������黭����
	int GameStatus[MAX_ROW][MAX_COL];

	//���ڱ��浱ǰ����Ķ�̬λ�ã�4��С����ֱ��ڴ������е�λ��
	//���λ��Ϊ������ң�ÿһ������ѭ���Ϻ��µ�ԭ��
	int ActiveStatus[4][2];

	//������һ��Ҫ�����ķ����ģ��������
	int NextStatus[4][2];

// Generated message map functions
protected:
	BOOL m_bGamePaush;
	void StopMid();
	void PlayMid();
	void CurrentAreaAndLevel();
	//���ڼ�¼��ǰ�����С�뵱ǰ������ַ�����������ʾ����Ļ����ʾ�û���ǰ״̬
	CString m_strArea;
	CString m_strLevel;

	//��ǰ����ʽ ����һ��������ֵ���ʽ
	int m_icurrentStatus;
	int m_inextStatus;

	//OnDraw����Ҫ�õ����豸����
	CPen *m_pBlackPen;
	CBrush *m_pGrayBrush;
	CBrush *m_pBlackBrush;

	//�Ƿ�������
	BOOL m_bDrawGrid;

	//�Ƿ��ű�������
	BOOL m_bMusic;

	//��Ϸ�ܳɼ�
	int m_iPerformance;

	//��Ϸ�Ƿ��ѽ�����ΪFALSE��ʾ��ʼ������Ϊ����
	BOOL m_bGameEnd;
	
	//ˢ��ָ�����������Ĵ�СΪ���ĸ�С�������ڵ������εĴ�С
	void InvalidateCurrent();

	//�ڴ��ͼ�豸�Ĵ���
	CDC m_memDC;                   //�ڴ��豸���� 
	CBitmap m_memBmp;              //�ڴ�λͼ

	CDC m_memRectDC;       //�����ڴ��豸����
	HBITMAP m_hMemRectBmp;  //�����ڴ�λͼ���

	int m_bFistPlay;               //�Ƿ��ǵ�һ�ο�ʼ��Ϸ
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
	//�ڲ���ȡ���ݽṹ
	int m_stateMap[MAX_ROW][MAX_COL];
	
	//��ʼ������
	GameInitnal();      //��Ϸ�ĳ�ʼ��
	
	//�����ж��������״̬�Ĳ���
	IsLeftLimit();       //��׹����Ƿ�������ƶ�
	IsRightLitmit();     //
	IsBottom();          //�Ƿ��Ѿ������˵ײ�
	IsGameEnd();         //�Ƿ���Ϸ�Ѿ�����
		
	//���������׹�����еĲ���
	RectChange();        //��׹�������
	RectDown();          //��׹�����������
	RectArrow();         //��׹��������ƶ�(���ң��¼��٣�

  	//״̬���Ʋ���
	GameStart();         //��Ϸ��ʼ
	GamePause();         //��Ϸ��ͣ
	GameEnd();           //��Ϸ����
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
