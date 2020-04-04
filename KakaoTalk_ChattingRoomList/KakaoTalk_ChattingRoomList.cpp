
// KakaoTalk_ChattingRoomList.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "KakaoTalk_ChattingRoomList.h"
#include "KakaoTalk_ChattingRoomListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKakaoTalkChattingRoomListApp

BEGIN_MESSAGE_MAP(CKakaoTalkChattingRoomListApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKakaoTalkChattingRoomListApp construction

CKakaoTalkChattingRoomListApp::CKakaoTalkChattingRoomListApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CKakaoTalkChattingRoomListApp object

CKakaoTalkChattingRoomListApp theApp;


// CKakaoTalkChattingRoomListApp initialization

BOOL CKakaoTalkChattingRoomListApp::InitInstance()
{
	CWinApp::InitInstance();

	CKakaoTalkChattingRoomListDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

