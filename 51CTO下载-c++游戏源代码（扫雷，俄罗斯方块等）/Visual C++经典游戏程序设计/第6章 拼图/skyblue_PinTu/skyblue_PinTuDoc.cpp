/*++

Copyright (c) AFE(Active-Free-Elegance)

Module Name:

    skyblue_PinTuDoc.cpp

Abstract:

	Document , manage game's data-calculation and seralization

Author:

    Weijian Luo (Arthur Luo)   15-Jun-2005

	E-mail: skybluehacker@yahoo.com.cn

Revision History:      1.0

--*/
#include "stdafx.h"
#include "skyblue_PinTu.h"

#include "skyblue_PinTuDoc.h"
#include "skyblue_PinTuView.h"
#include "MainFrm.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuDoc

IMPLEMENT_DYNCREATE(CSkyblue_PinTuDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkyblue_PinTuDoc, CDocument)
	//{{AFX_MSG_MAP(CSkyblue_PinTuDoc)
	ON_COMMAND(IDM_NEWGAME, OnNewgame)
	ON_COMMAND(IDM_SET, OnConfig)
	ON_COMMAND(IDM_USERPIC, OnUserpic)
	ON_COMMAND(IDM_PIC1, OnPic1)
	ON_COMMAND(IDM_PIC2, OnPic2)
	ON_COMMAND(IDM_PIC3, OnPic3)
	ON_COMMAND(IDM_PIC4, OnPic4)
	ON_COMMAND(ID_MENU_ORG_PIC_SHOW, OnMenuOrgPicShow)
	ON_UPDATE_COMMAND_UI(ID_MENU_ORG_PIC_SHOW, OnUpdateMenuOrgPicShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuDoc construction/destruction

CSkyblue_PinTuDoc::CSkyblue_PinTuDoc()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��ȡע�����Ϸ������Ϣ
	m_BMP_WIDTH=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("m_BMP_WIDTH"),300);
	m_BMP_HEIGHT=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("m_BMP_HEIGHT"),250);
	hnums=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("hnums"),4);
	vnums=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("vnums"),3);
	m_gamePicID=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("m_gamePicID"),IDB_BITMAP3);
	m_bMusic=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("m_bMusic"),FALSE);
	m_bShowOrgPic=AfxGetApp()->GetProfileInt(_T("��Ϸ����"),_T("m_bShowOrgPic"),TRUE);
	m_szMusicFileName=AfxGetApp()->GetProfileString(_T("��Ϸ����"),_T("m_szMusicFileName"),"");

	m_blankPos.row =hnums;
	m_blankPos.col =vnums;
}

CSkyblue_PinTuDoc::~CSkyblue_PinTuDoc()
{
	//�ͷ�λͼ��Դ
	DeleteObject(m_bitmap);
	//д��ע�����Ϸ������Ϣ
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_BMP_WIDTH"),m_BMP_WIDTH);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_BMP_HEIGHT"),m_BMP_HEIGHT);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("hnums"),hnums);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("vnums"),vnums);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_gamePicID"),m_gamePicID);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_bMusic"),m_bMusic);
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_bShowOrgPic"),m_bShowOrgPic);
	AfxGetApp()->WriteProfileString(_T("��Ϸ����"),_T("m_szMusicFileName"),m_szMusicFileName);

}




/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuDoc serialization

void CSkyblue_PinTuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuDoc diagnostics

#ifdef _DEBUG
void CSkyblue_PinTuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkyblue_PinTuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkyblue_PinTuDoc commands

//
// ���ĵ�ͼ���ݵĳ�ʼ��
//
void CSkyblue_PinTuDoc::MapInitial()
{
	int i,j;

	//��ԭ������λ�õ�������������ڵ���ID����ID
	for(i=1;i<=hnums;i++)
	{
		for(j=1;j<=vnums;j++)
		{
			m_map[i][j].row =i;
			m_map[i][j].col =j;
		}
	}
}

//
//  ��������¼�
//
void CSkyblue_PinTuDoc::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//���ݰ������ƶ�����
	GameMove(nChar);

	//������ͼ
	CObArray HintArray; //���������������µ���ʾ"hint"
	UpdateAllViews(NULL,0,&HintArray);

	//���ö�����Ϊ��Ϸ��ʼ���Զ��ƶ����ټ���Ƿ�ʤ��
	if(/*(!m_bAutoMove) && */IsWin())
	{
		//ʤ����ʾ��ʾ
		MessageBox(NULL,"�ɹ�����","ƴͼ",MB_OK|MB_ICONINFORMATION);
	}
}

//
//   ���ݰ�������ָʾ�������ƶ�����
//
void CSkyblue_PinTuDoc::GameMove(UINT nChar)
{
	pos tempPos;

	//�����û��İ����û��ƶ�����ͼƬ
	switch(nChar)
	{
	case VK_LEFT:
		if(m_blankPos.row>1)
		{//�ƶ�����֤�������߽���ƶ��û�

			//����һ����ʱ�����ķ���������ͼƬλ�����ݽ���
			tempPos.row =m_blankPos.row-1;
			tempPos.col =m_blankPos.col ;

			m_map[m_blankPos.row][m_blankPos.col].row = m_map[tempPos.row][tempPos.col].row;
            m_map[m_blankPos.row][m_blankPos.col].col = m_map[tempPos.row][tempPos.col].col;
            
			tempPos.row = m_map[m_blankPos.row][m_blankPos.col].row;
            tempPos.col = m_map[m_blankPos.row][m_blankPos.col].col;
            
			//�޸��ƶ���Ŀհ׷���λ��
			m_blankPos.row = m_blankPos.row - 1;
	}
		break;
	case VK_RIGHT:
		if(m_blankPos.row<hnums)
		{
			tempPos.row =m_blankPos.row+1;
			tempPos.col =m_blankPos.col ;
			m_map[m_blankPos.row][m_blankPos.col].row = m_map[tempPos.row][tempPos.col].row;
            m_map[m_blankPos.row][m_blankPos.col].col = m_map[tempPos.row][tempPos.col].col;
            tempPos.row = m_map[m_blankPos.row][m_blankPos.col].row;
            tempPos.col = m_map[m_blankPos.row][m_blankPos.col].col;
  
            m_blankPos.row = m_blankPos.row + 1;
		}
		break;
	case VK_UP:
		if(m_blankPos.col>1)
		{
			tempPos.row =m_blankPos.row;
			tempPos.col =m_blankPos.col-1 ;
			m_map[m_blankPos.row][m_blankPos.col].row = m_map[tempPos.row][tempPos.col].row;
            m_map[m_blankPos.row][m_blankPos.col].col = m_map[tempPos.row][tempPos.col].col;
            tempPos.row = m_map[m_blankPos.row][m_blankPos.col].row;
            tempPos.col = m_map[m_blankPos.row][m_blankPos.col].col;
 
            m_blankPos.col = m_blankPos.col - 1;
		}
		break;
	case VK_DOWN:
		if(m_blankPos.col<vnums)
		{
			tempPos.row =m_blankPos.row;
			tempPos.col =m_blankPos.col+1 ;
			m_map[m_blankPos.row][m_blankPos.col].row = m_map[tempPos.row][tempPos.col].row;
            m_map[m_blankPos.row][m_blankPos.col].col = m_map[tempPos.row][tempPos.col].col;
            tempPos.row = m_map[m_blankPos.row][m_blankPos.col].row;
            tempPos.col = m_map[m_blankPos.row][m_blankPos.col].col;

            m_blankPos.col = m_blankPos.col + 1;
		}
		break;
	}
}

//
//  ��ʼһ������Ϸ
//
void CSkyblue_PinTuDoc::OnNewgame() 
{
	//���ݵ�ǰͼƬ�ĳߴ����ô��ڴ�С
	SetWindow_N_ViewSize();

	//��ͼ�ĳ�ʼ��
	MapInitial();

	//����ǰ���հ׿����������½�
	m_blankPos.row =hnums;
	m_blankPos.col =vnums;	

	//���ҵ�ͼ(����ƶ�n��)
//	m_bAutoMove = TRUE;
	GameMixMove();
//	m_bAutoMove = FALSE;

	//������ͼ
	UpdateAllViews(NULL);
}

//
// ��Ϸ��ʼ�����������ͼ��
//
void CSkyblue_PinTuDoc::GameMixMove()
{
	int i,temp;
	//�Ե�ǰϵͳʱ��Ϊ�������
	srand(time(NULL));

	//�����300��
	for(i=1;i<300;i++)
	{
		temp=rand()%4+1;
		switch(temp)
		{
		case 1:
			GameMove(VK_RIGHT);
			break;
		case 2:
			GameMove(VK_LEFT);
			break;
		case 3:
			GameMove(VK_UP);
			break;
		case 4:
			GameMove(VK_DOWN);
			break;
		}
	}
}

//
//  ��������
//
void CSkyblue_PinTuDoc::OnConfig() 
{
	//�������öԻ���
	CSettingDlg set;
	if(set.DoModal()==IDOK)
	{//ȷ�����޸Ĳ���

		hnums=set.m_iCols;
		vnums=set.m_iRows;
		m_bMusic=set.m_bMusic;
		m_szMusicFileName=set.m_strMusicFileName;
		//���ֲ���
		//�������ö�MCI�豸���Ͳ��Ż�ֹͣ���ŵ�ָ��
		if(m_bMusic==TRUE)
		{
			PlayMusic();
		}
		else
		{
			MCI_GENERIC_PARMS mciGP;
			mciSendCommand(m_wID,MCI_STOP,MCI_NOTIFY,(DWORD)(LPVOID)&mciGP);
		}
			OnNewgame();
	}
}

//
//   ����Ƿ�ʤ��
//
BOOL CSkyblue_PinTuDoc::IsWin(void)
{
	int i,j;
//ʤ���ļ�ⷽ�����жϵ�ͼ�����з�����ڲ�
//�����Ƿ�ȫΪ���������������ʾ���кã�ʤ��
	for(i = 1;i<=hnums;i++)
	{
		for(j = 1;j<=vnums;j++)
		{
			if(i !=m_blankPos.row || j != m_blankPos.col)
				if(m_map[i][j].row !=i || m_map[i][j].col !=j)
					return FALSE;
		}
	}
	return TRUE;
}

//
//  ���ű�������
//
//˵���� ����MCI���ƿ���ý���豸����
void CSkyblue_PinTuDoc::PlayMusic()
{
	//ǰֹͣ���ر���ǰ�򿪵��豸(�������ʹ��)
	MCI_GENERIC_PARMS mciGP;
	mciSendCommand(m_wID,MCI_CLOSE,MCI_NOTIFY,(DWORD)(LPVOID)&mciGP);
	

	//���󷵻��붨��
	DWORD dwReturn;
	//���岢��д���豸���������
	MCI_OPEN_PARMS mciOP;
	mciOP.lpstrDeviceType=NULL;
	mciOP.lpstrElementName=m_szMusicFileName;

	//���豸
	dwReturn=mciSendCommand(NULL,MCI_OPEN,
							MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOP);
	if(dwReturn==0)
	{
		m_wID=mciOP.wDeviceID;
	}

	//����
	MCI_PLAY_PARMS mciPP;
	mciSendCommand(m_wID,MCI_PLAY,
				   MCI_NOTIFY,(DWORD)(LPVOID)&mciPP);
}


//
//   �û�ѡ��·���Զ���ͼƬ
//
void CSkyblue_PinTuDoc::OnUserpic() 
{
	//���ļ��Ի���ķ�ʽѡ�񲥷ŵ�����
	CString filter="BMP�ļ�(*.bmp)|*.bmp";
	CFileDialog picfile(TRUE,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter);
	if(picfile.DoModal()==IDOK)
	{//ȷ�������λͼ����ʼ��Ϸ


		HBITMAP hbitmap;
		//���ճߴ�m_BMP_WIDTH,m_BMP_HEIGHT��
		//��λͼ�ļ�(����Դͼ�����Ŵ�����С)
		hbitmap=(HBITMAP)::LoadImage(NULL,
			picfile.GetPathName(),IMAGE_BITMAP,
			m_BMP_WIDTH,m_BMP_HEIGHT,LR_LOADFROMFILE);

		//����ѡ��
		m_bitmap.Detach();
		m_bitmap.Attach(hbitmap);

		//��ʼ��Ϸ
		CSkyblue_PinTuDoc::OnNewgame();
	}
}

//
//   ����IDѡȡ��Ϸ��ͼƬ
//
void CSkyblue_PinTuDoc::PicSelect(UINT BMP_ID)
{
	//��¼��ǰ�����λͼID����д��ע���
	//(�Ա��´����п���ֱ���ø�ͼƬ)
	m_gamePicID = BMP_ID;
	AfxGetApp()->WriteProfileInt(_T("��Ϸ����"),_T("m_gamePicID"), BMP_ID);

	//ж�ؾɵģ����������µ�ѡȡλͼ
	m_bitmap.Detach();
	m_bitmap.LoadBitmap(BMP_ID);
	
	//��ʼ��Ϸ
	CSkyblue_PinTuDoc::OnNewgame();	
}

//
// ͼ��ѡȡ 1
//
void CSkyblue_PinTuDoc::OnPic1() 
{
	PicSelect(IDB_BITMAP1);
}

void CSkyblue_PinTuDoc::OnPic2() 
{
	PicSelect(IDB_BITMAP2);
}

void CSkyblue_PinTuDoc::OnPic3() 
{
	PicSelect(IDB_BITMAP3);
}

void CSkyblue_PinTuDoc::OnPic4() 
{
	PicSelect(IDB_BITMAP4);
}

//
// ���ô���������ͼ�Ĵ�С
//
void CSkyblue_PinTuDoc::SetWindow_N_ViewSize()
{
	
	BITMAP bmp;
	//��ȡ��ǰѡ����λͼ��Ϣ(Ŀ�ģ��ߴ��С����)
	GetObject(m_bitmap.m_hObject,sizeof(BITMAP), (LPSTR)&bmp);	
	m_bmpWidth = bmp.bmWidth;
	m_bmpHeight = bmp.bmHeight;
	
	//���յ�ǰ���������и����ÿ�鷽�鵥Ԫcell�Ŀ�Ⱥ͸߶�
	m_cellWidth=m_bmpWidth/hnums;
	m_cellHeight=m_bmpHeight/vnums;

	int winWidth;
	int winHeight;
	if(m_bShowOrgPic)
	{
		//�����Ӵ��ڵĴ�С(2��λͼ�Ŀռ䣫�߿�ռ�)
		winWidth = m_bmpWidth*2+20;
		winHeight = m_bmpHeight+55;
	}
	else
	{
		//�����Ӵ��ڵĴ�С(1��λͼ�Ŀռ䣫�߿�ռ�)
		winWidth = m_bmpWidth+20;
		winHeight = m_bmpHeight+55;		
	}
	//����������Ϸ���ڵĴ�С������ѷ�ʽ��ʾ
	::AfxGetMainWnd()->SetWindowPos(NULL,0,0,winWidth,winHeight,SWP_NOMOVE );
	
	//�޸�Ŀ������ͼ������Ϸ����ͼ���2������ͼ�ռ��С
	CMainFrame *pMainFrame = (CMainFrame *)::AfxGetMainWnd();
	
	//����Ϣ
	pMainFrame->m_wndSplitter.SetRowInfo(0,m_bmpHeight+20,m_bmpHeight);
	//����Ϣ
	pMainFrame->m_wndSplitter.SetColumnInfo(0,m_bmpWidth,m_bmpWidth);
	pMainFrame->m_wndSplitter.SetColumnInfo(1,m_bmpWidth,m_bmpWidth);
	
	//�����޸���Ч
	pMainFrame->m_wndSplitter.RecalcLayout();
}

//
//  �޸Ĵ����Ƿ���ʾԴͼ�Ĳ˵���Ϣ����
//
void CSkyblue_PinTuDoc::OnMenuOrgPicShow() 
{
	//�޸�ԭ������ʾ
	m_bShowOrgPic = !m_bShowOrgPic;
	//���贰�ڴ�С����ͼ�ֲ�
	SetWindow_N_ViewSize();	
}

void CSkyblue_PinTuDoc::OnUpdateMenuOrgPicShow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowOrgPic);	
}
