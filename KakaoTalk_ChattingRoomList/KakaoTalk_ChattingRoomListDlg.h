
// KakaoTalk_ChattingRoomListDlg.h : header file
//

#pragma once


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
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnBnClickedSnedBtn();
	CListBox m_KakaoChatList;
	afx_msg void OnBnClickedSnedBtn2();
};
