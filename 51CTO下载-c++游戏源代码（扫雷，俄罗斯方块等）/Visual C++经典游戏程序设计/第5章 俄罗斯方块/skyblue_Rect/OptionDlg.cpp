// OptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "skyblue_Rect.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog


COptionDlg::COptionDlg(int m_iArea, int m_iLevel, int m_iBlockStyle,BOOL m_bMusic, BOOL m_bDrawGrid, CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	
	m_oldArea = m_iArea;
	m_oldLevel = m_iLevel;
	m_oldBlockSytle = m_iBlockStyle;

	m_oldMusic = m_bMusic;
	m_oldDrawGrid = m_bDrawGrid;

	//{{AFX_DATA_INIT(COptionDlg)
	m_bMusic = FALSE;
	m_bDrawGrid = FALSE;
	//}}AFX_DATA_INIT
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
	DDX_Check(pDX, IDC_CHECK_GRID, m_bDrawGrid);
	DDX_Check(pDX, IDC_CHECK_MUSIC, m_bMusic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	//{{AFX_MSG_MAP(COptionDlg)
		ON_WM_CREATE()
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg message handlers
int COptionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}

BOOL COptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//参传来的参数赋初值 
	CComboBox *m_comboArea;
	CComboBox *m_comboLevel;
	CComboBox *m_comboBlockStyle;
	CButton   *m_btnDrawGrid;
	CButton   *m_btnMusic;

	m_comboArea = (CComboBox *)GetDlgItem(IDC_COMBO_AREA);
	m_comboArea -> SetCurSel( m_oldArea );

	m_comboLevel = (CComboBox *)GetDlgItem(IDC_COMBO_LEVEL);
	m_comboLevel -> SetCurSel( m_oldLevel );

	m_comboBlockStyle = (CComboBox *)GetDlgItem(IDC_COMBO_BLOCK_SYTLE);
	m_comboBlockStyle -> SetCurSel( m_oldBlockSytle );

	m_btnDrawGrid = (CButton *)GetDlgItem(IDC_CHECK_GRID);
	m_btnDrawGrid -> SetCheck(m_oldDrawGrid);

	m_btnMusic = (CButton *)GetDlgItem(IDC_CHECK_MUSIC);
	m_btnMusic -> SetCheck(m_oldMusic);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionDlg::OnOK() 
{
	CComboBox *m_comboArea;
	CComboBox *m_comboLevel;
	CComboBox *m_comboBlockStyle;

	m_comboArea = (CComboBox *)GetDlgItem(IDC_COMBO_AREA);
	m_comboLevel = (CComboBox *)GetDlgItem(IDC_COMBO_LEVEL);
	m_comboBlockStyle = (CComboBox *)GetDlgItem(IDC_COMBO_BLOCK_SYTLE);

	m_iArea = m_comboArea -> GetCurSel();
	if (m_iArea<0 || m_iArea>3)
		m_iArea = 0;
	
	m_iLevel = m_comboLevel -> GetCurSel();
	if (m_iLevel<0 || m_iLevel>5)
		m_iLevel = 2;
	
	m_iBlockStyle = m_comboBlockStyle -> GetCurSel();
	if (m_iBlockStyle<0 || m_iBlockStyle>5)
		m_iBlockStyle = 0;

	CDialog::OnOK();
}
