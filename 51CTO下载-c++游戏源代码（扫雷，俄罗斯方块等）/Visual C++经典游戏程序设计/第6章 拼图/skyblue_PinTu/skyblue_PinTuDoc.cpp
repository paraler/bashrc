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
	//读取注册表游戏参数信息
	m_BMP_WIDTH=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("m_BMP_WIDTH"),300);
	m_BMP_HEIGHT=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("m_BMP_HEIGHT"),250);
	hnums=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("hnums"),4);
	vnums=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("vnums"),3);
	m_gamePicID=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("m_gamePicID"),IDB_BITMAP3);
	m_bMusic=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("m_bMusic"),FALSE);
	m_bShowOrgPic=AfxGetApp()->GetProfileInt(_T("游戏参数"),_T("m_bShowOrgPic"),TRUE);
	m_szMusicFileName=AfxGetApp()->GetProfileString(_T("游戏参数"),_T("m_szMusicFileName"),"");

	m_blankPos.row =hnums;
	m_blankPos.col =vnums;
}

CSkyblue_PinTuDoc::~CSkyblue_PinTuDoc()
{
	//释放位图资源
	DeleteObject(m_bitmap);
	//写入注册表游戏参数信息
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_BMP_WIDTH"),m_BMP_WIDTH);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_BMP_HEIGHT"),m_BMP_HEIGHT);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("hnums"),hnums);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("vnums"),vnums);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_gamePicID"),m_gamePicID);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_bMusic"),m_bMusic);
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_bShowOrgPic"),m_bShowOrgPic);
	AfxGetApp()->WriteProfileString(_T("游戏参数"),_T("m_szMusicFileName"),m_szMusicFileName);

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
// 核心地图数据的初始化
//
void CSkyblue_PinTuDoc::MapInitial()
{
	int i,j;

	//将原来各个位置的数据填好其所在的行ID，列ID
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
//  处理键盘事件
//
void CSkyblue_PinTuDoc::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//根据按键作移动操作
	GameMove(nChar);

	//更新视图
	CObArray HintArray; //利用这个物件作更新的提示"hint"
	UpdateAllViews(NULL,0,&HintArray);

	//当该动作不为游戏初始化自动移动才再检测是否胜利
	if(/*(!m_bAutoMove) && */IsWin())
	{
		//胜利提示显示
		MessageBox(NULL,"成功闯关","拼图",MB_OK|MB_ICONINFORMATION);
	}
}

//
//   根据按键输入指示命令作移动操作
//
void CSkyblue_PinTuDoc::GameMove(UINT nChar)
{
	pos tempPos;

	//根据用户的按键置换移动方块图片
	switch(nChar)
	{
	case VK_LEFT:
		if(m_blankPos.row>1)
		{//移动方向保证不超出边界才移动置换

			//引用一个临时变量的方法做方块图片位置数据交还
			tempPos.row =m_blankPos.row-1;
			tempPos.col =m_blankPos.col ;

			m_map[m_blankPos.row][m_blankPos.col].row = m_map[tempPos.row][tempPos.col].row;
            m_map[m_blankPos.row][m_blankPos.col].col = m_map[tempPos.row][tempPos.col].col;
            
			tempPos.row = m_map[m_blankPos.row][m_blankPos.col].row;
            tempPos.col = m_map[m_blankPos.row][m_blankPos.col].col;
            
			//修改移动后的空白方块位置
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
//  开始一个新游戏
//
void CSkyblue_PinTuDoc::OnNewgame() 
{
	//根据当前图片的尺寸设置窗口大小
	SetWindow_N_ViewSize();

	//地图的初始化
	MapInitial();

	//打乱前将空白块起点放在右下角
	m_blankPos.row =hnums;
	m_blankPos.col =vnums;	

	//打乱地图(随机移动n步)
//	m_bAutoMove = TRUE;
	GameMixMove();
//	m_bAutoMove = FALSE;

	//更新视图
	UpdateAllViews(NULL);
}

//
// 游戏初始化，随机打乱图像
//
void CSkyblue_PinTuDoc::GameMixMove()
{
	int i,temp;
	//以当前系统时间为随机种子
	srand(time(NULL));

	//随机走300步
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
//  参数配置
//
void CSkyblue_PinTuDoc::OnConfig() 
{
	//弹出设置对话框
	CSettingDlg set;
	if(set.DoModal()==IDOK)
	{//确认则修改参数

		hnums=set.m_iCols;
		vnums=set.m_iRows;
		m_bMusic=set.m_bMusic;
		m_szMusicFileName=set.m_strMusicFileName;
		//音乐操作
		//根据配置对MCI设备发送播放或停止播放的指令
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
//   检测是否胜利
//
BOOL CSkyblue_PinTuDoc::IsWin(void)
{
	int i,j;
//胜利的检测方法是判断地图的所有方块的内部
//数据是否全为其行列数，是则表示排列好，胜利
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
//  播放背景音乐
//
//说明： 利用MCI机制控制媒体设备放音
void CSkyblue_PinTuDoc::PlayMusic()
{
	//前停止并关闭以前打开的设备(如果正在使用)
	MCI_GENERIC_PARMS mciGP;
	mciSendCommand(m_wID,MCI_CLOSE,MCI_NOTIFY,(DWORD)(LPVOID)&mciGP);
	

	//错误返回码定义
	DWORD dwReturn;
	//定义并填写打开设备的命令参数
	MCI_OPEN_PARMS mciOP;
	mciOP.lpstrDeviceType=NULL;
	mciOP.lpstrElementName=m_szMusicFileName;

	//打开设备
	dwReturn=mciSendCommand(NULL,MCI_OPEN,
							MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOP);
	if(dwReturn==0)
	{
		m_wID=mciOP.wDeviceID;
	}

	//播放
	MCI_PLAY_PARMS mciPP;
	mciSendCommand(m_wID,MCI_PLAY,
				   MCI_NOTIFY,(DWORD)(LPVOID)&mciPP);
}


//
//   用户选择路径自定义图片
//
void CSkyblue_PinTuDoc::OnUserpic() 
{
	//用文件对话框的方式选择播放的音乐
	CString filter="BMP文件(*.bmp)|*.bmp";
	CFileDialog picfile(TRUE,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter);
	if(picfile.DoModal()==IDOK)
	{//确定后读入位图并开始游戏


		HBITMAP hbitmap;
		//按照尺寸m_BMP_WIDTH,m_BMP_HEIGHT读
		//入位图文件(根据源图比例放大与缩小)
		hbitmap=(HBITMAP)::LoadImage(NULL,
			picfile.GetPathName(),IMAGE_BITMAP,
			m_BMP_WIDTH,m_BMP_HEIGHT,LR_LOADFROMFILE);

		//弃旧选新
		m_bitmap.Detach();
		m_bitmap.Attach(hbitmap);

		//开始游戏
		CSkyblue_PinTuDoc::OnNewgame();
	}
}

//
//   根据ID选取游戏的图片
//
void CSkyblue_PinTuDoc::PicSelect(UINT BMP_ID)
{
	//记录当前所算的位图ID，并写入注册表
	//(以便下次运行可以直接用该图片)
	m_gamePicID = BMP_ID;
	AfxGetApp()->WriteProfileInt(_T("游戏参数"),_T("m_gamePicID"), BMP_ID);

	//卸载旧的，重新载入新的选取位图
	m_bitmap.Detach();
	m_bitmap.LoadBitmap(BMP_ID);
	
	//开始游戏
	CSkyblue_PinTuDoc::OnNewgame();	
}

//
// 图像选取 1
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
// 设置窗口与两视图的大小
//
void CSkyblue_PinTuDoc::SetWindow_N_ViewSize()
{
	
	BITMAP bmp;
	//获取当前选定的位图信息(目的：尺寸大小数据)
	GetObject(m_bitmap.m_hObject,sizeof(BITMAP), (LPSTR)&bmp);	
	m_bmpWidth = bmp.bmWidth;
	m_bmpHeight = bmp.bmHeight;
	
	//按照当前的行列数切割，计算每块方块单元cell的宽度和高度
	m_cellWidth=m_bmpWidth/hnums;
	m_cellHeight=m_bmpHeight/vnums;

	int winWidth;
	int winHeight;
	if(m_bShowOrgPic)
	{
		//计算子窗口的大小(2个位图的空间＋边框空间)
		winWidth = m_bmpWidth*2+20;
		winHeight = m_bmpHeight+55;
	}
	else
	{
		//计算子窗口的大小(1个位图的空间＋边框空间)
		winWidth = m_bmpWidth+20;
		winHeight = m_bmpHeight+55;		
	}
	//立刻设置游戏窗口的大小，以最佳方式显示
	::AfxGetMainWnd()->SetWindowPos(NULL,0,0,winWidth,winHeight,SWP_NOMOVE );
	
	//修改目标样板图像与游戏区域图像的2个子视图空间大小
	CMainFrame *pMainFrame = (CMainFrame *)::AfxGetMainWnd();
	
	//行信息
	pMainFrame->m_wndSplitter.SetRowInfo(0,m_bmpHeight+20,m_bmpHeight);
	//列信息
	pMainFrame->m_wndSplitter.SetColumnInfo(0,m_bmpWidth,m_bmpWidth);
	pMainFrame->m_wndSplitter.SetColumnInfo(1,m_bmpWidth,m_bmpWidth);
	
	//呼叫修改生效
	pMainFrame->m_wndSplitter.RecalcLayout();
}

//
//  修改窗口是否显示源图的菜单消息处理
//
void CSkyblue_PinTuDoc::OnMenuOrgPicShow() 
{
	//修改原来的显示
	m_bShowOrgPic = !m_bShowOrgPic;
	//重设窗口大小与视图分布
	SetWindow_N_ViewSize();	
}

void CSkyblue_PinTuDoc::OnUpdateMenuOrgPicShow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowOrgPic);	
}
