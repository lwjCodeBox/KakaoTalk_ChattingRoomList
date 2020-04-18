
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
	ON_BN_CLICKED(IDC_SEARCH_CHATLIST_BTN, &CKakaoTalkChattingRoomListDlg::OnBnClickedSearchChatlistBtn)
	ON_WM_DESTROY()
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

	hChatRoomListCtrl = ::FindWindowEx(hNextChild, NULL, L"EVA_VH_ListControl_Dblclk", NULL); // ChatRoomListCtrl

	if (!hChatRoomListCtrl) {
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		AfxMessageBox(L"카톡 로그인 하세요.");
	}

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
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return true; // true면 동작을 안먹게 함. false면 동작을 먹게 함.
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


// 리스트 박스에 등록된 채팅방 목록을 모두 지우는 함수
// 이 리스트 박스는 문자열 외에 채팅 방과 관련된 정보를 추가로 저장하고 있기 때문에
// 단순히 ResetContent로만 지워서는 안된다.
void CKakaoTalkChattingRoomListDlg::ResetChatRoomData()
{
	WritePrivateProfileString(L"List", NULL, NULL, L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");

	//HWND h_room_wnd = NULL, h_edit_wnd;
	//while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
	//	// 검색된 대화 상자가 'RichEdit20W' 윈도우를 가지고 있는지 체크한다.
	//	h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

	//	// ESC Key
	//	Sleep(150);
	//	::PostMessage(h_room_wnd, WM_KEYDOWN, VK_ESCAPE, VK_ESCAPE);
	//	::PostMessage(h_room_wnd, WM_KEYUP, VK_ESCAPE, VK_ESCAPE);

	//}

	ChatRoomData *p_data;
	int count = m_KakaoChatList.GetCount();
	// 리스트 박스의 각 항목에 추가로 저장된 메모리를 모두 찾아서 제거한다.
	for (int i = 0; i < count; i++) {
		p_data = (ChatRoomData *)m_KakaoChatList.GetItemDataPtr(i);
		delete p_data;
	}
	m_KakaoChatList.ResetContent();
}


void CKakaoTalkChattingRoomListDlg::OnBnClickedSnedBtn()
{
	int iNumSel = m_KakaoChatList.GetSelCount(); // get number of selected items
	LPINT lpiSelItems = new int[iNumSel]; // allocate memory for all of them
	m_KakaoChatList.GetSelItems(iNumSel, lpiSelItems);

	for (int i = 0; i < iNumSel; i++)
	{
		int index = lpiSelItems[i];

		ChatRoomData *p_data = (ChatRoomData *)m_KakaoChatList.GetItemDataPtr(index);
		CString str;
		GetDlgItemText(IDC_CHAT_EDIT, str);  // 사용자가 입력한 채팅 정보를 얻는다.
		// 채팅 정보를 카카오톡 채팅창의 리치 에디트 컨트롤에 추가한다.
		::SendMessage(p_data->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)(const wchar_t *)str);
		Sleep(200);  // 0.2초간 대기한다.
		// Enter키를 누른것과 같은 메시지 전송를 리치 에디트 컨트롤에 전송한다.
		::PostMessage(p_data->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);
		::PostMessage(p_data->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
	}

	delete[] lpiSelItems; // don't forget to clean up!
	lpiSelItems = NULL;

	HWND h_room_wnd = NULL, h_edit_wnd;
	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
		// 검색된 대화 상자가 'RichEdit20W' 윈도우를 가지고 있는지 체크한다.
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

		// ESC Key
		Sleep(150);
		::PostMessage(h_room_wnd, WM_KEYDOWN, VK_ESCAPE, VK_ESCAPE);
		::PostMessage(h_room_wnd, WM_KEYUP, VK_ESCAPE, VK_ESCAPE);

	}

	/* Original
		int index = m_room_list.GetCurSel();  // 리스트 박스에 선택된 항목의 위치 값을 얻는다.
		if (index != LB_ERR) {
			// 선택된 항목에 추가된 핸들값 정보를 얻는다.
			ChatRoomData *p_data = (ChatRoomData *)m_room_list.GetItemDataPtr(index);
			CString str;
			GetDlgItemText(IDC_CHAT_EDIT, str);  // 사용자가 입력한 채팅 정보를 얻는다.
			// 채팅 정보를 카카오톡 채팅창의 리치 에디트 컨트롤에 추가한다.
			::SendMessage(p_data->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)(const wchar_t *)str);
			Sleep(200);  // 0.2초간 대기한다.
			// Enter키를 누른것과 같은 메시지 전송를 리치 에디트 컨트롤에 전송한다.
			//::PostMessage(p_data->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);
			//::PostMessage(p_data->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
		}
	*/
}


void CKakaoTalkChattingRoomListDlg::OnBnClickedSearchChatlistBtn()
{
	ResetChatRoomData();  // 기존 항목들을 제거한다.
	
	// 여기서 부터 진행...
	if (NULL != hChatRoomListCtrl) {
		POINT mousepos;
		RECT rect;
		::GetClientRect(hChatRoomListCtrl, &rect);

		int x = (rect.right - rect.left) / 2, y = rect.top = 30;
		SetCursorPos(x, y); 
		GetCursorPos(&mousepos);

		// mouse left button click
		::PostMessage(hChatRoomListCtrl, WM_LBUTTONDOWN, (WPARAM)mousepos.x, (LPARAM)mousepos.y);
		::PostMessage(hChatRoomListCtrl, WM_LBUTTONUP, (WPARAM)mousepos.x, (LPARAM)mousepos.y);
		
		// 카톡 채팅방 위치를 가장 맨 위로 올림
		::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_HOME, VK_HOME);
		::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_HOME, VK_HOME);

		Sleep(150);
		// Enter Key
		::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_RETURN, VK_RETURN);
		::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_RETURN, VK_RETURN);

		for (int i = 0; i < 4; i++) {
			Sleep(200);
			// DOWN ARROW key
			::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_DOWN, VK_DOWN);
			::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_DOWN, VK_DOWN);

			Sleep(200);
			// Enter Key
			::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_RETURN, VK_RETURN);
			::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_RETURN, VK_RETURN);
		}

		//if (NULL != h_room_wnd) {
		//	// ESC
		//	::PostMessage(h_room_wnd, WM_KEYDOWN, VK_ESCAPE, VK_ESCAPE);
		//	::PostMessage(h_room_wnd, WM_KEYUP, VK_ESCAPE, VK_ESCAPE);
		//	Sleep(150);
		//}

		/* 참고 
		if (index != LB_ERR) {
			//LB_ERR =-1 이 디파인 된것. 즉 어떤 문자열이 선택 되었을때만 실행
			// 카톡 채팅방 위치를 가장 맨 위로 올림
		}
		*/
		::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_HOME, VK_HOME);
		::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_HOME, VK_HOME);

		
		HWND h_room_wnd = NULL, h_edit_wnd;
		int index = 0;
		CString strIndexNo;

		Sleep(200);

		// 자신의 컴퓨터에 실행되어 대화 상자들을 모두 검색한다.
		while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
			// 검색된 대화 상자가 'RichEdit20W' 윈도우를 가지고 있는지 체크한다.
			h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

			Sleep(200);

			if (NULL != h_edit_wnd) {
				// 찾은 채팅 창의 제목을 저장하기 위해 제목의 길이를 얻는다.
				int len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
				if (len > 0) {
					// 창 제목의 길이만큼 메모리를 할당한다.
					wchar_t *p_name = new wchar_t[len + 1];
					// 창 제목을 얻는다.
					::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
					// 창제목을 리스트 박스에 추가한다.
					m_KakaoChatList.InsertString(index, p_name);

					// ini 파일에 쓰기.
					strIndexNo.Format(L"%d", index);
					WritePrivateProfileString(L"List", strIndexNo, p_name, L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");

					// 이름을 얻기 위해 사용했던 메모리를 제거한다.
					delete[] p_name;
				}
				else {
					strIndexNo.Format(L"%d", index);
					m_KakaoChatList.InsertString(index, L"");  // 창 제목이 없는 경우
					WritePrivateProfileString(L"List", strIndexNo, L"untiile", L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");
				}

				// 찾은 핸들을 추가된 항목에 저장하기 위해 메모리를 할당한다.
				ChatRoomData *p_data = new ChatRoomData;
				// 검색한 핸들 값들 저장
				p_data->h_room_wnd = h_room_wnd;
				p_data->h_edit_wnd = h_edit_wnd;
				// 새로 추가된 항목에 핸들이 저장된 메모리의 주소를 저장
				m_KakaoChatList.SetItemDataPtr(index++, p_data);
			}
		}
	}
	

	/* test
		int downArrowKey_cnt = 10;
		int upArrowKey_cnt = downArrowKey_cnt;


		for (int i = 1; i < downArrowKey_cnt; i++) {
			::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_DOWN, VK_DOWN);
			::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_DOWN, VK_DOWN);
			Sleep(150);
		}

		for (int i = 1; i < upArrowKey_cnt; i++) {
			::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_UP, VK_UP);
			::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_UP, VK_UP);
			Sleep(150);
		}*/

/* Original Code made tipsware
	ResetChatRoomData();  // 기존 항목들을 제거한다.

	int index = 0;
	HWND h_room_wnd = NULL, h_edit_wnd;

	// 자신의 컴퓨터에 실행되어 대화 상자들을 모두 검색한다.
	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
		// 검색된 대화 상자가 'RichEdit20W' 윈도우를 가지고 있는지 체크한다.
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);
		if (NULL != h_edit_wnd) {
			// 찾은 채팅 창의 제목을 저장하기 위해 제목의 길이를 얻는다.
			int len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
			if (len > 0) {
				// 창 제목의 길이만큼 메모리를 할당한다.
				wchar_t *p_name = new wchar_t[len + 1];
				// 창 제목을 얻는다.
				::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
				// 창제목을 리스트 박스에 추가한다.
				m_room_list.InsertString(index, p_name);
				// 이름을 얻기 위해 사용했던 메모리를 제거한다.
				delete[] p_name;
			}
			else {
				m_room_list.InsertString(index, L"");  // 창 제목이 없는 경우
			}

			// 찾은 핸들을 추가된 항목에 저장하기 위해 메모리를 할당한다.
			ChatRoomData *p_data = new ChatRoomData;
			// 검색한 핸들 값들 저장
			p_data->h_room_wnd = h_room_wnd;
			p_data->h_edit_wnd = h_edit_wnd;
			// 새로 추가된 항목에 핸들이 저장된 메모리의 주소를 저장
			m_room_list.SetItemDataPtr(index++, p_data);
		}
	}
*/
}


void CKakaoTalkChattingRoomListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 리스트 박스에 추가된 메모리를 모두 제거한다.
	ResetChatRoomData();
}
