
// KakaoTalk_ChattingRoomListDlg.h : header file
//

#pragma once
struct ChatRoomData
{
	HWND h_room_wnd;  // ä�� ���� ������ �ڵ�
	HWND h_edit_wnd;  // ä�� �濡 ���Ե� ��ġ ����Ʈ ��Ʈ���� �ڵ�
};

// CKakaoTalkChattingRoomListDlg dialog
class CKakaoTalkChattingRoomListDlg : public CDialogEx
{
// Construction
public:
	CKakaoTalkChattingRoomListDlg(CWnd* pParent = nullptr);	// standard constructor

// lwj
private: 
	// īī���� �ڵ鰪(PID)
	HWND m_hWnd_Kakao;
	
	// īī���� ä�ù� ����Ʈ �ڵ鰪(PID)
	HWND m_hWnd_ChatList;

	// // ChatRoomListCtrl
	HWND hChatRoomListCtrl;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KAKAOTALK_CHATTINGROOMLIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// ����Ʈ �ڽ��� ��ϵ� ä�ù� ����� ��� ����� �Լ�
	void ResetChatRoomData();

public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnBnClickedSnedBtn();
	CListBox m_KakaoChatList;
	afx_msg void OnBnClickedSearchChatlistBtn();
	afx_msg void OnDestroy();
};
