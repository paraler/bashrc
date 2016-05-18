; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSkyblue_PinTuView
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "skyblue_PinTu.h"
LastPage=0

ClassCount=6
Class1=CSkyblue_PinTuApp
Class2=CSkyblue_PinTuDoc
Class3=CSkyblue_PinTuView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=COrgView
Resource2=IDD_ABOUTBOX
Resource3=IDD_SETTING

[CLS:CSkyblue_PinTuApp]
Type=0
HeaderFile=skyblue_PinTu.h
ImplementationFile=skyblue_PinTu.cpp
Filter=N
LastObject=CSkyblue_PinTuApp

[CLS:CSkyblue_PinTuDoc]
Type=0
HeaderFile=skyblue_PinTuDoc.h
ImplementationFile=skyblue_PinTuDoc.cpp
Filter=N
LastObject=IDM_PIC2
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSkyblue_PinTuView]
Type=0
HeaderFile=skyblue_PinTuView.h
ImplementationFile=skyblue_PinTuView.cpp
Filter=C
LastObject=CSkyblue_PinTuView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=skyblue_PinTu.cpp
ImplementationFile=skyblue_PinTu.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_SET
Command2=IDM_NEWGAME
Command3=ID_MENU_ORG_PIC_SHOW
Command4=ID_APP_EXIT
Command5=IDM_USERPIC
Command6=IDM_PIC1
Command7=IDM_PIC2
Command8=IDM_PIC3
Command9=IDM_PIC4
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:COrgView]
Type=0
HeaderFile=OrgView.h
ImplementationFile=OrgView.cpp
BaseClass=CView
Filter=C
LastObject=COrgView
VirtualFilter=VWC

[DLG:IDD_SETTING]
Type=1
Class=?
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_MusicFileName,edit,1350631552
Control6=IDC_OPEN,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_Rows,edit,1350639744
Control10=IDC_SPINROWS,msctls_updown32,1342177330
Control11=IDC_Cols,edit,1350639744
Control12=IDC_SPINCOLS,msctls_updown32,1342177330
Control13=IDC_CHKMUSIC,button,1342242819

