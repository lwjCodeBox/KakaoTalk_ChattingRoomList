
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
	DDX_Control(pDX, IDC_LIST1, m_KakaoChatList);
}

BEGIN_MESSAGE_MAP(CKakaoTalkChattingRoomListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SNED_BTN, &CKakaoTalkChattingRoomListDlg::OnBnClickedSnedBtn)
	ON_BN_CLICKED(IDC_SNED_BTN2, &CKakaoTalkChattingRoomListDlg::OnBnClickedSnedBtn2)
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
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		AfxMessageBox(L"카카오톡을 먼저 실행하세요.");
	}
	
/*
	▶hwndParnet: 부모 윈도우의 핸들.이 윈도우의 차일드 들이 검색된다.
				  NULL일 경우 데스크 탑 윈도우으의 차일드들이 검색된다.HWND_MESSAGE인 경우 메시지 전용 윈도우가 검색된다.

	▶hwndChildAfter : 부모 윈도우의 차일드 핸들이며 이 차일드 이후의 Z순수를 가지는 차일드만 검색된다.
					   부모 윈도우 바로 아래의 차일드 핸들만 지정할 수 있으며 차일드의 차일드는 지정할 수 없다.
					   이 인수가 NULL이면 첫번째 차일드부터 검색에 포함된다.

	▶lpClassName : 검색에 사용할 차일드 윈도우 클래스 이름, 또는 아톰값.NULL이면 모든 윈도우 클래스를 검색한다.

	▶lpWindowName : 검색에 사용할 윈도우의 캡션 문자열.NULL이면 모든 캡션의 윈도우를 검색한다.

	AfxGetMainWnd()->PostMessage(WM_CLOSE);
*/

	HWND hOnlineMainView = ::FindWindowEx(m_hWnd_Kakao, NULL, L"EVA_ChildWindow", NULL); //::GetWindow(m_hWnd_Kakao, GW_CHILD);
	// 원본
	HWND hOnlineMainView_Child = ::FindWindowEx(hOnlineMainView, NULL, L"EVA_Window", NULL); // ContactListView
	HWND hNextChild = ::GetWindow(hOnlineMainView_Child, GW_HWNDNEXT); //ChatRoomListView

	HWND hChatRoomListCtrl = ::FindWindowEx(hNextChild, NULL, L"EVA_VH_ListControl_Dblclk", NULL); // ChatRoomListCtrl
	
	//HWND hOnlineMainView_Child = ::FindWindowEx(hOnlineMainView, NULL, L"EVA_Window", NULL); // ContactListView
	//HWND hNextChild = ::GetWindow(hOnlineMainView_Child, GW_HWNDNEXT); //ChatRoomListView

	//HWND hChatRoomListCtrl = ::FindWindowEx(hNextChild, NULL, L"Edit", NULL); // ChatRoomListCtrl

	if (!hChatRoomListCtrl) {
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		AfxMessageBox(L"카톡 로그인 하세요.");
	}
	
	/*CString str_txt;
	::SendMessage(hChatRoomListCtrl, WM_GETTEXT, 0, (LPARAM)(LPCTSTR)str_txt);*/
	
	/*wchar_t temp_text[256];
	::SendMessage(hChatRoomListCtrl, WM_GETTEXT, 256, (LPARAM)temp_text);*/
	
	//AfxMessageBox(temp_text);

	

	wchar_t temp_text[256];
	::GetWindowText(hChatRoomListCtrl, temp_text, 256);
	//MessageBox(temp_text);

	// m_hwndKakaoTalk1 = ::FindWindow(NULL, str_ChatRoom);	
	// m_hwndKakaoTalk1Child = ::FindWindowEx(m_hwndKakaoTalk1, NULL, L"RichEdit20W", NULL);
	////메모장에 문자열 입력! 
	LPCTSTR  m_strText = L"test";
	::SendMessage(hChatRoomListCtrl, WM_SETTEXT, 0, (LPARAM)m_strText);
	::PostMessage(hOnlineMainView_Child, WM_KEYDOWN, 0x0000000D, 0x001C0001);
	//::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, 0x0000000D, 0x001C0001);
	
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


void CKakaoTalkChattingRoomListDlg::OnBnClickedSnedBtn()
{
/*
	CString str_Input;
	GetDlgItemText(IDC_EDIT1, str_Input); // 입력한 내용.

	// 메모장에 입력
	HWND mainWindow = ::FindWindow(NULL, L"kakaoTXT.txt - Notepad");
	HWND editWindow = ::FindWindowEx(mainWindow, NULL, L"edit", NULL);
	
	::SendMessageW(editWindow, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)str_Input);
*/
	 
	wchar_t temp_text[256];

	HWND mainWindow = ::FindWindow(NULL, L"aaaTEXT.txt - Notepad");
	HWND editWindow = ::FindWindowEx(mainWindow, NULL, L"edit", NULL);

	::SendMessage(editWindow, WM_GETTEXT, (WPARAM)256, (LPARAM)temp_text);
	//AfxMessageBox(temp_text);
	

	m_KakaoChatList.AddString(temp_text);
	m_KakaoChatList.SetCurSel(1);
	

	



	////::PostMessage(editWindow, WM_PASTE, 0, 0);
	////::PostMessage(editWindow, WM_KEYDOWN, VK_RETURN, NULL);
	////::PostMessage(editWindow, WM_KEYUP, VK_RETURN, NULL);
}


void CKakaoTalkChattingRoomListDlg::OnBnClickedSnedBtn2()
{
	// 몇개의 아이템이 선택되어졌는지 카운트
	int nCount = m_KakaoChatList.GetSelCount();

	// 선택되어진 아이템이 하나도 없으면 리턴.
	if (nCount <= 0)
		return;

	// 배열을 하나 만들고, 크기를 설정한다.
	CArray<int, int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);

	// 아이템중에서 선택되어진 인덱스를 배열에 읽어온다.
	m_KakaoChatList.GetSelItems(nCount, aryListBoxSel.GetData());
	
	int sel;
	CString str_Sel;
	for (int i = 0; i < nCount; i++)
	{
		// 선택된걸 하나씩 뽑아서 먼가 처리를 하겠지...
		 sel = aryListBoxSel[i];
		 m_KakaoChatList.GetText(sel, str_Sel);
		 MessageBox(str_Sel);
		// do something... 
	}
// 출처 >> https://mins79.tistory.com/entry/%EC%B6%94%EA%B0%80%EC%82%BD%EC%9E%85%EC%82%AD%EC%A0%9C%EC%84%A0%ED%83%9D-MFC-ListBox-%EC%98%88%EC%A0%9C	


}
