#if !defined(AFX_TIANJIADLG_H__183D34AB_3AD4_4FF6_B315_4FFA21706AED__INCLUDED_)
#define AFX_TIANJIADLG_H__183D34AB_3AD4_4FF6_B315_4FFA21706AED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TianJiaDlg.h : header file
//
#include "DlgRealBJ.h"
/////////////////////////////////////////////////////////////////////////////
// CTianJiaDlg dialog

class CTianJiaDlg : public CDialog
{
// Construction
public:
	BOOL AddDataToList();
	CTianJiaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTianJiaDlg)
	enum { IDD = IDD_DIALOG_TIANJIA };
	int		m_bRadioSex;
	float	m_fHuaxue;
	float	m_fShengwu;
	float	m_fShuxue;
	float	m_fTiyu;
	float	m_fWuli;
	CString	m_strName;
	CString	m_strNO;
	float	m_fYingyu;
	float	m_fYuwen;
	CString	m_strCombo;
	BOOL	m_bWrite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTianJiaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTianJiaDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void XiuGai();
	void OnitXiuGai();
	CDlgRealBJ *m_pbj;
	BOOL IsAnyEmpty();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIANJIADLG_H__183D34AB_3AD4_4FF6_B315_4FFA21706AED__INCLUDED_)
