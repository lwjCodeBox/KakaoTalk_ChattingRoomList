
// KakaoTalk_ChattingRoomListDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "KakaoTalk_ChattingRoomList.h"
#include "KakaoTalk_ChattingRoomListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKakaoTalkChattingRoomListDlg dialog



CKakaoTalkChattingRoomListDlg::CKakaoTalkChattingRoomListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KAKAOTALK_CHATTINGROOMLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKakaoTalkChattingRoomListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKakaoTalkChattingRoomListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CKakaoTalkChattingRoomListDlg message handlers

BOOL CKakaoTalkChattingRoomListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// 카톡 핸들값 얻어옴.
	m_hWnd_Kakao = ::FindWindow(NULL, L"카카오톡");
	if (!m_hWnd_Kakao) {
		AfxMessageBox(L"카카오톡을 먼저 실행하세요.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	
/*
	▶hwndParnet: 부모 윈도우의 핸들.이 윈도우의 차일드 들이 검색된다.
				  NULL일 경우 데스크 탑 윈도우으의 차일드들이 검색된다.HWND_MESSAGE인 경우 메시지 전용 윈도우가 검색된다.

	▶hwndChildAfter : 부모 윈도우의 차일드 핸들이며 이 차일드 이후의 Z순수를 가지는 차일드만 검색된다.
					   부모 윈도우 바로 아래의 차일드 핸들만 지정할 수 있으며 차일드의 차일드는 지정할 수 없다.
					   이 인수가 NULL이면 첫번째 차일드부터 검색에 포함된다.

	▶lpClassName : 검색에 사용할 차일드 윈도우 클래스 이름, 또는 아톰값.NULL이면 모든 윈도우 클래스를 검색한다.

	▶lpWindowName : 검색에 사용할 윈도우의 캡션 문자열.NULL이면 모든 캡션의 윈도우를 검색한다.
*/
	
	// 카톡 채팅방 리스트 얻어옴.
	m_hWnd_ChatList = ::FindWindowEx(m_hWnd_Kakao, NULL, L"EVA_Window", NULL);

	if (!m_hWnd_ChatList) {
		AfxMessageBox(L"프로그램 오류!! 원종이한테 문의 하세요. login??");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
		
	//m_hWnd_ChatList

	HWND mainWindow = ::FindWindow(NULL, L"kakaoTXT.txt - Notepad");
	HWND editWindow = ::FindWindowEx(mainWindow, NULL, L"edit", NULL);
	char m_strText[10] = "test";
	::SendMessageW(editWindow, WM_SETTEXT, 0, (LPARAM)TEXT("abc"));
	//::PostMessage(editWindow, WM_PASTE, 0, 0);
	//::PostMessage(editWindow, WM_KEYDOWN, VK_RETURN, NULL);
	//::PostMessage(editWindow, WM_KEYUP, VK_RETURN, NULL);




	//AfxGetMainWnd()->PostMessage(WM_CLOSE);

	//m_hwndKakaoTalk1Child = ::FindWindowEx(m_hwndKakaoTalk1, NULL, L"RichEdit20W", NULL);
	////메모장에 문자열 입력! 
	//::SendMessage(m_hwndKakaoTalk1Child, WM_SETTEXT, 0, (LPARAM)m_strText);
	//::PostMessage(m_hwndKakaoTalk1Child, WM_KEYDOWN, 0x0000000D, 0x001C0001);
	//::PostMessage(m_hwndKakaoTalk1Child, WM_KEYDOWN, 0x0000000D, 0x001C0001);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKakaoTalkChattingRoomListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKakaoTalkChattingRoomListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CKakaoTalkChattingRoomListDlg::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN)
		{
			return true; // true면 동작을 안먹게 함. false면 동작을 먹게 함.
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
