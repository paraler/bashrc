#if !defined(AFX_DLGBJ_H__AB49032D_8913_4FBF_9DDA_D92B30922E03__INCLUDED_)
#define AFX_DLGBJ_H__AB49032D_8913_4FBF_9DDA_D92B30922E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBJ.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDlgBJ dialog

#include "DlgRealBJ.h"
class CDlgBJ : public CDialog
{
// Construction
public:
	CDlgBJ(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDlgBJ)
	enum { IDD = IDD_DIALOG_NIANJI };
	CComboBox	m_Combo;
	CListCtrl	m_ListSum;
	CListCtrl	m_ListAll;
	CString	m_strCombo;
	float	m_fMax;
	float	m_fMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBJ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBJ)
	virtual void OnOK();
	afx_msg void OnNianjiUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickListAll(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonChaxun();
	afx_msg void OnButtonGetfing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	static BOOL m_bAsc;
	//static int m_nCol;
	void Count();
	void Show(CScore score);
	static int CALLBACK CompareFunc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBJ_H__AB49032D_8913_4FBF_9DDA_D92B30922E03__INCLUDED_)
