; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBoxManWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "skyblue_BoxMan.h"
LastPage=0

ClassCount=8
Class1=CSkyblue_BoxManApp
Class2=CSkyblue_BoxManDoc
Class3=CSkyblue_BoxManView
Class4=CMainFrame

ResourceCount=3
Class5=CAboutDlg
Class6=CBoxManWnd
Resource1=IDD_DIALOG_HELP
Class7=CHelpDlg
Resource2=IDR_MAINFRAME
Class8=CMissionLevelDlg
Resource3=IDD_DIALOG_LEVEL_SELECT

[CLS:CSkyblue_BoxManApp]
Type=0
HeaderFile=skyblue_BoxMan.h
ImplementationFile=skyblue_BoxMan.cpp
Filter=N
LastObject=CSkyblue_BoxManApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSkyblue_BoxManDoc]
Type=0
HeaderFile=skyblue_BoxManDoc.h
ImplementationFile=skyblue_BoxManDoc.cpp
Filter=N

[CLS:CSkyblue_BoxManView]
Type=0
HeaderFile=skyblue_BoxManView.h
ImplementationFile=skyblue_BoxManView.cpp
Filter=C


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
HeaderFile=skyblue_BoxMan.cpp
ImplementationFile=skyblue_BoxMan.cpp
Filter=W
LastObject=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MENU_GAME_LEVEL
Command2=ID_MENU_GAME_HELP
Command3=ID_MENU_GAME_MUSIC
Command4=ID_MENU_GAME_EXIT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CBoxManWnd]
Type=0
HeaderFile=BoxManWnd.h
ImplementationFile=BoxManWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CBoxManWnd

[DLG:IDD_DIALOG_HELP]
Type=1
Class=CHelpDlg
ControlCount=2
Control1=IDC_STATIC,static,1342177294
Control2=IDOK,button,1342242817

[CLS:CHelpDlg]
Type=0
HeaderFile=HelpDlg.h
ImplementationFile=HelpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelpDlg

[DLG:IDD_DIALOG_LEVEL_SELECT]
Type=1
Class=CMissionLevelDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_MISSION_LEVEL,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CMissionLevelDlg]
Type=0
HeaderFile=MissionLevelDlg.h
ImplementationFile=MissionLevelDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_MISSION_LEVEL

