#if !defined(AFX_DLGREALBJ_H__A56870C1_B77D_4510_9C52_6B0ABAE48E89__INCLUDED_)
#define AFX_DLGREALBJ_H__A56870C1_B77D_4510_9C52_6B0ABAE48E89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRealBJ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRealBJ dialog
#include "CScore.h"
#include "MYBUTTON.h"
#include "HotButton.h"
class CDlgRealBJ : public CDialog
{
// Construction
public:
	static int CALLBACK CompareFun(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	BOOL m_bPanduan;
	void ChangeStr(CScore m_scr);
	CDlgRealBJ(CWnd* pParent = NULL);   // standard constructor
	void ShowClassData();
	
// Dialog Data
	//{{AFX_DATA(CDlgRealBJ)
	enum { IDD = IDD_DIALOG_BANJI };
	CMYBUTTON	m_BtnXiugai;
	CMYBUTTON	m_BtnTianjia;
	CMYBUTTON	m_BtnManage;
	CMYBUTTON	m_BtnOut;
	CMYBUTTON	m_BtnDelete;
	CListCtrl	m_ListClass;
	CComboBox	m_ComBoClass;
	CString	m_strCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRealBJ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRealBJ)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboClass();
	afx_msg void OnButtonTianjia();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonXiugai();
	afx_msg void OnColumnclickListClass(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListClass(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CreatDlgList();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREALBJ_H__A56870C1_B77D_4510_9C52_6B0ABAE48E89__INCLUDED_)
