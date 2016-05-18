/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLKDlg.h

Abstract:

	LLK-Game's kernal-solving Dialog

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_)
#define AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// C_LLK_Dlg dialog

class C_LLK_Dlg : public CDialog
{
// Construction
public:
	//��Ϸ�������
	void GameDraw(CDC * pDC);
	//��ʼһ������Ϸ
	void StartNewGame();


	//������2�����Ƿ����ͨ����
	BOOL IsLink(int x1,int y1,int x2,int y2);
	//�Ƿ��Ѿ����ʤ��
	BOOL IsWin(void);

	//ֱ����ͨ
	//X���
	BOOL X1_Link_X2(int x,int y1,int y2);
	//Y���
	BOOL Y1_Link_Y2(int x1,int x2,int y);
	//1ֱ�ǽӿ���ͨ
	BOOL OneCornerLink(int x1,int y1,int x2,int y2);
	//2ֱ�ǽӿ���ͨ
	BOOL TwoCornerLink(int x1,int y1,int x2,int y2);

	BOOL YThrough(int x,int y,BOOL bAdd);
	BOOL XThrough(int x,int y,BOOL bAdd);

	BOOL LineX(int x,int y1,int y2);
	BOOL LineY(int x1,int x2,int y);

	C_LLK_Dlg(CWnd* pParent = NULL);	// standard constructor
	~C_LLK_Dlg();
// Dialog Data
	//{{AFX_DATA(CTemp2Dlg)
	enum { IDD = IDD_LLK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemp2Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

//�ڴ�λͼ������
	CDC		m_mem3DBkDC;      //3D��ܵ��ڴ��豸����
	CBitmap m_mem3DBkBmp;     //3D��ܵ��ڴ�λͼ

	CDC		m_memAnimalDC;      //����ͼ����ڴ��豸����
	CBitmap m_memAnimalBmp;     //����ͼ����ڴ�λͼ

	CDC		m_MemDC;      //��Ϸ�����ڴ��豸����
	CBitmap m_memBitmap;  //��Ϸ�����ڴ�λͼ

//��ͼλ�����������
	int*	m_map;        //��̬��ͼ����ͷָ��(һά����)
	int		m_nRow;		  //��ͼ������(����)
	int		m_nCol;		  //��ͼ������(����)

	int		m_nX1;        //���ѡ�еļ�¼��������
	int		m_nY1;	      //���ѡ�еļ�¼��������


	// Generated message map functions
	//{{AFX_MSG(CTemp2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_LLKDLG_H__F043F328_5562_4EEC_921D_508E1DBDC900__INCLUDED_)
