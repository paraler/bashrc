#if !defined(AFX_OPTIONDLG_H__18508C0C_F5FB_4D43_92F1_84BE15AFD62B__INCLUDED_)
#define AFX_OPTIONDLG_H__18508C0C_F5FB_4D43_92F1_84BE15AFD62B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog

class COptionDlg : public CDialog
{
// Construction
	//参数顺序： 区域大小代码：0-3，分别为：12X10，18X15，24X20，30X25
	//级别：0-5，分别为：1500，1200，1000，800，600，400
	//背景音乐：TRUE 或者 FALSE
	//是否画网格线
public:
	COptionDlg(int m_iArea, int m_iLevel,int m_iBlockStyle, BOOL m_bMusic,BOOL m_bDrawGrid, CWnd* pParent = NULL);   // standard constructor
	int m_iArea,m_iLevel, m_iBlockStyle;  //用户选择的区域大小代码，及级别代码,方块样式。

// Dialog Data
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_DLG_OPTION };
	BOOL	m_bDrawGrid;
	BOOL	m_bMusic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_oldArea;
	int m_oldLevel;
	int m_oldBlockSytle;

	BOOL m_oldMusic;
	BOOL m_oldDrawGrid;


	// Generated message map functions
	//{{AFX_MSG(COptionDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONDLG_H__18508C0C_F5FB_4D43_92F1_84BE15AFD62B__INCLUDED_)
