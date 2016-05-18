//
/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_LLK_CheatDlg.h

Abstract:

	the game's cheating-kernal-solving Dialog class

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/

#if !defined(AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_)
#define AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_LLK_CheatDlg dialog

class CSkyblue_LLK_CheatDlg : public CDialog
{
// Construction
public:
	CSkyblue_LLK_CheatDlg(CWnd* pParent = NULL);	// standard constructor

	//������2�����Ƿ����ͨ����
	BOOL IsLink(int x1,int y1,int x2,int y2);

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

//  ����ͼ�������
	void Hack(void);
	BOOL HackIn(CString strWinName);
	void GenMap();
	int GetRectData( int x, int y);
	BOOL Find2Rect(int &x1,int &y1, int &x2, int &y2);
	void Local_RemoteHintDraw( int x1, int y1, int x2, int y2);
	void RemoteButtonKick( int x1, int y1, int x2, int y2);


// Dialog Data
	//{{AFX_DATA(CSkyblue_LLK_CheatDlg)
	enum { IDD = IDD_SKYBLUE_LLK_CHEAT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_LLK_CheatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CDC		m_MemDC;      //������Ϸ�����ڴ��豸����
	CBitmap m_memBitmap;  //������Ϸ�����ڴ�λͼ

//  ��ͼλ�����������
	int*	m_map;        //��̬��ͼ����ͷָ��(һά����)
	int		m_nRow;		  //��ͼ������(����)
	int		m_nCol;		  //��ͼ������(����)

	int		m_nX1;        //���ѡ�еļ�¼��������
	int		m_nY1;	      //���ѡ�еļ�¼��������

//	Ŀ��������������
	CRect m_DestClientRect;  //Ŀ����򴰿ڴ�С
	HDC m_hHackDC;   //Ŀ�������豸�������
	HWND m_hwndHack; //Ŀ�����Ĵ��ھ��
	BOOL m_bAutoKick; //�Ƿ��Զ�����Ŀ�����������


	// Generated message map functions
	//{{AFX_MSG(CSkyblue_LLK_CheatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonHack();
	afx_msg void OnButtonAutoKick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_LLK_CHEATDLG_H__4363FEC8_7EDB_4E3F_98C3_656A0F1D544E__INCLUDED_)
