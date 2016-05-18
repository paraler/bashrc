// studentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "student.h"
#include "studentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDlg dialog

CStudentDlg::CStudentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStudentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStudentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_bJudge=TRUE;
	m_nWidth=250;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentDlg)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStudentDlg, CDialog)
	//{{AFX_MSG_MAP(CStudentDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDlg message handlers

BOOL CStudentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	InToProgram();			//登陆
	InitBeginWindows();    //初始化界面
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStudentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStudentDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//DEL HCURSOR CStudentDlg::OnQueryDragIcon()
//DEL {
//DEL 	return (HCURSOR) m_hIcon;
//DEL }

void CStudentDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_bj.ShowWindow(SW_SHOW);
		m_nj.ShowWindow(SW_HIDE);
		break;
	case 1:	
		m_nj.ShowWindow(SW_SHOW);
		m_bj.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}


//初始化界面
BOOL CStudentDlg::InitBeginWindows()
{
	m_Tab.InsertItem(0,"班级成绩");
	m_Tab.InsertItem(1,"年级成绩");
	m_bj.Create(IDD_DIALOG_BANJI,&m_Tab);
	m_nj.Create(IDD_DIALOG_NIANJI,&m_Tab);
	if(!m_bJudge)
	{
		m_bj.GetDlgItem(IDC_BUTTON_TIANJIA)->EnableWindow(FALSE);
		m_bj.GetDlgItem(IDC_BUTTON_XIUGAI)->EnableWindow(FALSE);
		m_bj.GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
		m_bj.GetDlgItem(IDC_BUTTON_MANAGE)->EnableWindow(FALSE);
	}
	CRect rs;
	m_Tab.GetClientRect(&rs);
	rs.top+=20; 
	m_bj.MoveWindow(rs);
	m_nj.MoveWindow(rs);
	m_bj.ShowWindow(SW_SHOW);
	m_nj.ShowWindow(SW_HIDE);
	return TRUE;
}


BOOL CStudentDlg::InToProgram()
{
	CDlgDR dlg;
	if(IDOK!=dlg.DoModal()) 
	{
		SendMessage(WM_CLOSE,0,0); 
	}
/*	if(!dlg.m_bSelet)
	{
		m_bj.GetDlgItem(IDC_BUTTON_TIANJIA)->EnableWindow(FALSE);
	}*/
	m_bJudge=dlg.m_bSelet;
	return TRUE;
}

//DEL void CStudentDlg::OnOk()
//DEL {
//DEL 	
//DEL }

void CStudentDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CStudentDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static int nIndex=0;
	CClientDC dc(this);
	m_nWidth+=5;	
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CRect rect;
	rect.left=250;
	rect.top=0;
	rect.right=m_nWidth;
	rect.bottom=rect.top+tm.tmHeight;
	CString str("欢迎使用本系统");
/*	if(m_nWidth>450||nIndex==1)
	{
		m_nWidth=250;
		dc.SetTextColor(RGB(255,255,0));
		dc.TextOut(250,0,str);
		nIndex=1;
		CDialog::OnTimer(nIDEvent);
		return ;
	}*/
	dc.SetTextColor(RGB(255,0,0));
//	CString str("欢迎使用本系统");
	dc.DrawText(str,rect,DT_LEFT);
//	rect.top=150;
//	rect.bottom=rect.top+tm.tmHeight;
//	dc.DrawText(str,rect,DT_RIGHT);
//	CSize sz=dc.GetTextExtent(str);
	if(m_nWidth>450)
	{
		m_nWidth=250;
		dc.SetTextColor(RGB(0,255,0));
		dc.TextOut(250,0,str);
		nIndex=0;
	}
	CDialog::OnTimer(nIDEvent);
}

int CStudentDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetTimer(1,50,NULL);
	return 0;
}
