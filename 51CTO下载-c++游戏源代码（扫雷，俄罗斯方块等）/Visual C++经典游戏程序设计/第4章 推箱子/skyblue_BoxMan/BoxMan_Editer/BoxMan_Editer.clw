; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBoxman_EditerWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BoxMan_Editer.h"
LastPage=0

ClassCount=7
Class1=CBoxMan_EditerApp
Class2=CBoxMan_EditerDoc
Class3=CBoxMan_EditerView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CBoxman_EditerWnd
Class7=CLoadMapDlg
Resource2=IDD_DIALOAG_LOAD_NMU

[CLS:CBoxMan_EditerApp]
Type=0
HeaderFile=BoxMan_Editer.h
ImplementationFile=BoxMan_Editer.cpp
Filter=N
LastObject=CBoxMan_EditerApp

[CLS:CBoxMan_EditerDoc]
Type=0
HeaderFile=BoxMan_EditerDoc.h
ImplementationFile=BoxMan_EditerDoc.cpp
Filter=N

[CLS:CBoxMan_EditerView]
Type=0
HeaderFile=BoxMan_EditerView.h
ImplementationFile=BoxMan_EditerView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=BoxMan_Editer.cpp
ImplementationFile=BoxMan_Editer.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MENU_NEW_MAP
Command2=ID_MENU_LOAD_MAP
Command3=ID_MENU_SAVE_MAP
Command4=ID_MENU_MAP_WHITEWALL
Command5=ID_MENU_MAP_BLUEWALL
Command6=ID_MENU_MAP_BALL
Command7=ID_MENU_MAP_YELLOWBOX
Command8=ID_MENU_MAP_MAN_WALL_BALL
Command9=ID_MENU_MAP_BKGROUND
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

[CLS:CBoxman_EditerWnd]
Type=0
HeaderFile=Boxman_EditerWnd.h
ImplementationFile=Boxman_EditerWnd.cpp
BaseClass=CFrameWnd
Filter=C
VirtualFilter=WC
LastObject=CBoxman_EditerWnd

[DLG:IDD_DIALOAG_LOAD_NMU]
Type=1
Class=CLoadMapDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_LOAD_NUM,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_MAX_NUM,static,1342308352

[CLS:CLoadMapDlg]
Type=0
HeaderFile=LoadMapDlg.h
ImplementationFile=LoadMapDlg.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=CLoadMapDlg

