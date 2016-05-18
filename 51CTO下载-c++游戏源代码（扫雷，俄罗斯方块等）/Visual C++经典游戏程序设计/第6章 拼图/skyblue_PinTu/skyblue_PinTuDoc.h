/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_PinTuDoc.h

Abstract:

	Document , manage game's data-calculation and seralization

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#if !defined(AFX_SKYBLUE_PINTUDOC_H__83B7ABD5_EC45_4E30_9C9A_B2B28AFA8925__INCLUDED_)
#define AFX_SKYBLUE_PINTUDOC_H__83B7ABD5_EC45_4E30_9C9A_B2B28AFA8925__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>     //MCI�豸ʹ�õ�API�ӿ�

class CSkyblue_PinTuDoc : public CDocument
{
protected: // create from serialization only
	CSkyblue_PinTuDoc();
	DECLARE_DYNCREATE(CSkyblue_PinTuDoc)

// Attributes
public:
	HICON m_hIcon;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyblue_PinTuDoc)
	public:
	virtual void Serialize(CArchive& ar);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkyblue_PinTuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//����λ�ýṹ
	struct pos
	{
		int row; //�������ڵ���
		int col; //�������ڵ���
	};

// ����������
public:
	BOOL IsWin(void);
	void PlayMusic(void);
	void MapInitial(void);
	void GameMixMove(void);
	void GameMove(UINT nChar);
	void PicSelect(UINT BMP_ID);
	void SetWindow_N_ViewSize(void);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

//���ԣ�
public:
	UINT m_gamePicID;
	CBitmap m_bitmap;

	//ϵͳ�Զ��ƶ����
	//������ʼ��Ϸǰ����Ĵ���
//	BOOL m_bAutoMove;	
	BOOL m_bShowOrgPic;       //�Ƿ���ʾԴͼ

	//�������
	BOOL m_bMusic;             //�ر�����
	CString m_szMusicFileName; //�����ļ�����
	MCIDEVICEID m_wID;         //MCIý���豸ID

	//�������򷽿���
	int hnums;
	int vnums;

	//�հ׷���(��ɫ����)��λ��
	pos m_blankPos;

	//���ĵ�ͼ
	pos m_map[100][100];

	//ÿ������ÿ�Ⱥ͸߶�
	int m_cellWidth;
	int m_cellHeight;

	//��ǰͼƬ�óߴ�
	int m_bmpWidth;
	int m_bmpHeight; 
	//ͼƬ�ĵ���ʱ��Ԥ���ߴ�
	int m_BMP_WIDTH;
	int m_BMP_HEIGHT;

// Generated message map functions
public:
	//{{AFX_MSG(CSkyblue_PinTuDoc)
	afx_msg void OnNewgame();
	afx_msg void OnConfig();
	afx_msg void OnUserpic();
	afx_msg void OnPic1();
	afx_msg void OnPic2();
	afx_msg void OnPic3();
	afx_msg void OnPic4();
	afx_msg void OnMenuOrgPicShow();
	afx_msg void OnUpdateMenuOrgPicShow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBLUE_PINTUDOC_H__83B7ABD5_EC45_4E30_9C9A_B2B28AFA8925__INCLUDED_)
