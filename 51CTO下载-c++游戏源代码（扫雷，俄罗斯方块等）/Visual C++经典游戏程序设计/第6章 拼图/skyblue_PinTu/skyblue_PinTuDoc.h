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

#include <mmsystem.h>     //MCI设备使用到API接口

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

	//方块位置结构
	struct pos
	{
		int row; //方块所在的行
		int col; //方块所在的列
	};

// 操作方法：
public:
	BOOL IsWin(void);
	void PlayMusic(void);
	void MapInitial(void);
	void GameMixMove(void);
	void GameMove(UINT nChar);
	void PicSelect(UINT BMP_ID);
	void SetWindow_N_ViewSize(void);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

//属性：
public:
	UINT m_gamePicID;
	CBitmap m_bitmap;

	//系统自动移动标记
	//用作开始游戏前方块的打乱
//	BOOL m_bAutoMove;	
	BOOL m_bShowOrgPic;       //是否显示源图

	//音乐相关
	BOOL m_bMusic;             //关闭音乐
	CString m_szMusicFileName; //音乐文件名称
	MCIDEVICEID m_wID;         //MCI媒体设备ID

	//横向，纵向方块数
	int hnums;
	int vnums;

	//空白方块(黑色区域)的位置
	pos m_blankPos;

	//核心地图
	pos m_map[100][100];

	//每个方块得宽度和高度
	int m_cellWidth;
	int m_cellHeight;

	//当前图片得尺寸
	int m_bmpWidth;
	int m_bmpHeight; 
	//图片的导入时的预定尺寸
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
