
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
	// ī�� �ڵ鰪 ����.
	m_hWnd_Kakao = ::FindWindow(NULL, L"īī����");
	if (!m_hWnd_Kakao) {
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		AfxMessageBox(L"īī������ ���� �����ϼ���.");
	}

	/*
		��hwndParnet: �θ� �������� �ڵ�.�� �������� ���ϵ� ���� �˻��ȴ�.
					  NULL�� ��� ����ũ ž ���������� ���ϵ���� �˻��ȴ�.HWND_MESSAGE�� ��� �޽��� ���� �����찡 �˻��ȴ�.

		��hwndChildAfter : �θ� �������� ���ϵ� �ڵ��̸� �� ���ϵ� ������ Z������ ������ ���ϵ常 �˻��ȴ�.
						   �θ� ������ �ٷ� �Ʒ��� ���ϵ� �ڵ鸸 ������ �� ������ ���ϵ��� ���ϵ�� ������ �� ����.
						   �� �μ��� NULL�̸� ù��° ���ϵ���� �˻��� ���Եȴ�.

		��lpClassName : �˻��� ����� ���ϵ� ������ Ŭ���� �̸�, �Ǵ� ���谪.NULL�̸� ��� ������ Ŭ������ �˻��Ѵ�.

		��lpWindowName : �˻��� ����� �������� ĸ�� ���ڿ�.NULL�̸� ��� ĸ���� �����츦 �˻��Ѵ�.

		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	*/

	HWND hOnlineMainView = ::FindWindowEx(m_hWnd_Kakao, NULL, L"EVA_ChildWindow", NULL); //::GetWindow(m_hWnd_Kakao, GW_CHILD);
	// ����
	HWND hOnlineMainView_Child = ::FindWindowEx(hOnlineMainView, NULL, L"EVA_Window", NULL); // ContactListView
	HWND hNextChild = ::GetWindow(hOnlineMainView_Child, GW_HWNDNEXT); //ChatRoomListView

	hChatRoomListCtrl = ::FindWindowEx(hNextChild, NULL, L"EVA_VH_ListControl_Dblclk", NULL); // ChatRoomListCtrl

	if (!hChatRoomListCtrl) {
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		AfxMessageBox(L"ī�� �α��� �ϼ���.");
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
			return true; // true�� ������ �ȸ԰� ��. false�� ������ �԰� ��.
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


// ����Ʈ �ڽ��� ��ϵ� ä�ù� ����� ��� ����� �Լ�
// �� ����Ʈ �ڽ��� ���ڿ� �ܿ� ä�� ��� ���õ� ������ �߰��� �����ϰ� �ֱ� ������
// �ܼ��� ResetContent�θ� �������� �ȵȴ�.
void CKakaoTalkChattingRoomListDlg::ResetChatRoomData()
{
	WritePrivateProfileString(L"List", NULL, NULL, L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");

	//HWND h_room_wnd = NULL, h_edit_wnd;
	//while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
	//	// �˻��� ��ȭ ���ڰ� 'RichEdit20W' �����츦 ������ �ִ��� üũ�Ѵ�.
	//	h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

	//	// ESC Key
	//	Sleep(150);
	//	::PostMessage(h_room_wnd, WM_KEYDOWN, VK_ESCAPE, VK_ESCAPE);
	//	::PostMessage(h_room_wnd, WM_KEYUP, VK_ESCAPE, VK_ESCAPE);

	//}

	ChatRoomData *p_data;
	int count = m_KakaoChatList.GetCount();
	// ����Ʈ �ڽ��� �� �׸� �߰��� ����� �޸𸮸� ��� ã�Ƽ� �����Ѵ�.
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
		GetDlgItemText(IDC_CHAT_EDIT, str);  // ����ڰ� �Է��� ä�� ������ ��´�.
		// ä�� ������ īī���� ä��â�� ��ġ ����Ʈ ��Ʈ�ѿ� �߰��Ѵ�.
		::SendMessage(p_data->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)(const wchar_t *)str);
		Sleep(200);  // 0.2�ʰ� ����Ѵ�.
		// EnterŰ�� �����Ͱ� ���� �޽��� ���۸� ��ġ ����Ʈ ��Ʈ�ѿ� �����Ѵ�.
		::PostMessage(p_data->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);
		::PostMessage(p_data->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
	}

	delete[] lpiSelItems; // don't forget to clean up!
	lpiSelItems = NULL;

	HWND h_room_wnd = NULL, h_edit_wnd;
	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
		// �˻��� ��ȭ ���ڰ� 'RichEdit20W' �����츦 ������ �ִ��� üũ�Ѵ�.
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

		// ESC Key
		Sleep(150);
		::PostMessage(h_room_wnd, WM_KEYDOWN, VK_ESCAPE, VK_ESCAPE);
		::PostMessage(h_room_wnd, WM_KEYUP, VK_ESCAPE, VK_ESCAPE);

	}

	/* Original
		int index = m_room_list.GetCurSel();  // ����Ʈ �ڽ��� ���õ� �׸��� ��ġ ���� ��´�.
		if (index != LB_ERR) {
			// ���õ� �׸� �߰��� �ڵ鰪 ������ ��´�.
			ChatRoomData *p_data = (ChatRoomData *)m_room_list.GetItemDataPtr(index);
			CString str;
			GetDlgItemText(IDC_CHAT_EDIT, str);  // ����ڰ� �Է��� ä�� ������ ��´�.
			// ä�� ������ īī���� ä��â�� ��ġ ����Ʈ ��Ʈ�ѿ� �߰��Ѵ�.
			::SendMessage(p_data->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)(const wchar_t *)str);
			Sleep(200);  // 0.2�ʰ� ����Ѵ�.
			// EnterŰ�� �����Ͱ� ���� �޽��� ���۸� ��ġ ����Ʈ ��Ʈ�ѿ� �����Ѵ�.
			//::PostMessage(p_data->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);
			//::PostMessage(p_data->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
		}
	*/
}


void CKakaoTalkChattingRoomListDlg::OnBnClickedSearchChatlistBtn()
{
	ResetChatRoomData();  // ���� �׸���� �����Ѵ�.
	
	// ���⼭ ���� ����...
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
		
		// ī�� ä�ù� ��ġ�� ���� �� ���� �ø�
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

		/* ���� 
		if (index != LB_ERR) {
			//LB_ERR =-1 �� ������ �Ȱ�. �� � ���ڿ��� ���� �Ǿ������� ����
			// ī�� ä�ù� ��ġ�� ���� �� ���� �ø�
		}
		*/
		::PostMessage(hChatRoomListCtrl, WM_KEYDOWN, VK_HOME, VK_HOME);
		::PostMessage(hChatRoomListCtrl, WM_KEYUP, VK_HOME, VK_HOME);

		
		HWND h_room_wnd = NULL, h_edit_wnd;
		int index = 0;
		CString strIndexNo;

		Sleep(200);

		// �ڽ��� ��ǻ�Ϳ� ����Ǿ� ��ȭ ���ڵ��� ��� �˻��Ѵ�.
		while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
			// �˻��� ��ȭ ���ڰ� 'RichEdit20W' �����츦 ������ �ִ��� üũ�Ѵ�.
			h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);

			Sleep(200);

			if (NULL != h_edit_wnd) {
				// ã�� ä�� â�� ������ �����ϱ� ���� ������ ���̸� ��´�.
				int len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
				if (len > 0) {
					// â ������ ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
					wchar_t *p_name = new wchar_t[len + 1];
					// â ������ ��´�.
					::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
					// â������ ����Ʈ �ڽ��� �߰��Ѵ�.
					m_KakaoChatList.InsertString(index, p_name);

					// ini ���Ͽ� ����.
					strIndexNo.Format(L"%d", index);
					WritePrivateProfileString(L"List", strIndexNo, p_name, L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");

					// �̸��� ��� ���� ����ߴ� �޸𸮸� �����Ѵ�.
					delete[] p_name;
				}
				else {
					strIndexNo.Format(L"%d", index);
					m_KakaoChatList.InsertString(index, L"");  // â ������ ���� ���
					WritePrivateProfileString(L"List", strIndexNo, L"untiile", L"C:\\Users\\leewonjong\\Desktop\\kakaoList\\list.ini");
				}

				// ã�� �ڵ��� �߰��� �׸� �����ϱ� ���� �޸𸮸� �Ҵ��Ѵ�.
				ChatRoomData *p_data = new ChatRoomData;
				// �˻��� �ڵ� ���� ����
				p_data->h_room_wnd = h_room_wnd;
				p_data->h_edit_wnd = h_edit_wnd;
				// ���� �߰��� �׸� �ڵ��� ����� �޸��� �ּҸ� ����
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
	ResetChatRoomData();  // ���� �׸���� �����Ѵ�.

	int index = 0;
	HWND h_room_wnd = NULL, h_edit_wnd;

	// �ڽ��� ��ǻ�Ϳ� ����Ǿ� ��ȭ ���ڵ��� ��� �˻��Ѵ�.
	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, L"#32770", NULL)) {
		// �˻��� ��ȭ ���ڰ� 'RichEdit20W' �����츦 ������ �ִ��� üũ�Ѵ�.
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, L"RichEdit20W", NULL);
		if (NULL != h_edit_wnd) {
			// ã�� ä�� â�� ������ �����ϱ� ���� ������ ���̸� ��´�.
			int len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
			if (len > 0) {
				// â ������ ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
				wchar_t *p_name = new wchar_t[len + 1];
				// â ������ ��´�.
				::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
				// â������ ����Ʈ �ڽ��� �߰��Ѵ�.
				m_room_list.InsertString(index, p_name);
				// �̸��� ��� ���� ����ߴ� �޸𸮸� �����Ѵ�.
				delete[] p_name;
			}
			else {
				m_room_list.InsertString(index, L"");  // â ������ ���� ���
			}

			// ã�� �ڵ��� �߰��� �׸� �����ϱ� ���� �޸𸮸� �Ҵ��Ѵ�.
			ChatRoomData *p_data = new ChatRoomData;
			// �˻��� �ڵ� ���� ����
			p_data->h_room_wnd = h_room_wnd;
			p_data->h_edit_wnd = h_edit_wnd;
			// ���� �߰��� �׸� �ڵ��� ����� �޸��� �ּҸ� ����
			m_room_list.SetItemDataPtr(index++, p_data);
		}
	}
*/
}


void CKakaoTalkChattingRoomListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// ����Ʈ �ڽ��� �߰��� �޸𸮸� ��� �����Ѵ�.
	ResetChatRoomData();
}
