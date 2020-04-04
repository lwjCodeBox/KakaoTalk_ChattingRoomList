
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

	// ī�� �ڵ鰪 ����.
	m_hWnd_Kakao = ::FindWindow(NULL, L"īī����");
	if (!m_hWnd_Kakao) {
		AfxMessageBox(L"īī������ ���� �����ϼ���.");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	
/*
	��hwndParnet: �θ� �������� �ڵ�.�� �������� ���ϵ� ���� �˻��ȴ�.
				  NULL�� ��� ����ũ ž ���������� ���ϵ���� �˻��ȴ�.HWND_MESSAGE�� ��� �޽��� ���� �����찡 �˻��ȴ�.

	��hwndChildAfter : �θ� �������� ���ϵ� �ڵ��̸� �� ���ϵ� ������ Z������ ������ ���ϵ常 �˻��ȴ�.
					   �θ� ������ �ٷ� �Ʒ��� ���ϵ� �ڵ鸸 ������ �� ������ ���ϵ��� ���ϵ�� ������ �� ����.
					   �� �μ��� NULL�̸� ù��° ���ϵ���� �˻��� ���Եȴ�.

	��lpClassName : �˻��� ����� ���ϵ� ������ Ŭ���� �̸�, �Ǵ� ���谪.NULL�̸� ��� ������ Ŭ������ �˻��Ѵ�.

	��lpWindowName : �˻��� ����� �������� ĸ�� ���ڿ�.NULL�̸� ��� ĸ���� �����츦 �˻��Ѵ�.
*/
	
	// ī�� ä�ù� ����Ʈ ����.
	m_hWnd_ChatList = ::FindWindowEx(m_hWnd_Kakao, NULL, L"EVA_Window", NULL);

	if (!m_hWnd_ChatList) {
		AfxMessageBox(L"���α׷� ����!! ���������� ���� �ϼ���. login??");
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
	////�޸��忡 ���ڿ� �Է�! 
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
			return true; // true�� ������ �ȸ԰� ��. false�� ������ �԰� ��.
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
