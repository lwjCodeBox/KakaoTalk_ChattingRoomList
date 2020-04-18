
// KakaoTalk_ChattingRoomListDlg.h : header file
//

#pragma once
struct ChatRoomData
{
	HWND h_room_wnd;  // 채팅 방의 윈도우 핸들
	HWND h_edit_wnd;  // 채팅 방에 포함된 리치 에디트 컨트롤의 핸들
};

// CKakaoTalkChattingRoomListDlg dialog
class CKakaoTalkChattingRoomListDlg : public CDialogEx
{
// Construction
public:
	CKakaoTalkChattingRoomListDlg(CWnd* pParent = nullptr);	// standard constructor

// lwj
private: 
	// 카카오톡 핸들값(PID)
	HWND m_hWnd_Kakao;
	
	// 카카오톡 채팅방 리스트 핸들값(PID)
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
	// 리스트 박스에 등록된 채팅방 목록을 모두 지우는 함수
	void ResetChatRoomData();

public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnBnClickedSnedBtn();
	CListBox m_KakaoChatList;
	afx_msg void OnBnClickedSearchChatlistBtn();
	afx_msg void OnDestroy();
};
