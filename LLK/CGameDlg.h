#pragma once


// CGameDlg dialog

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__GAME_DIALOG };
#endif

protected:
	HICON m_icon;
	CDC m_dcMem;   //ÄÚ´æDC
	CDC m_dcElemet;   
	CDC m_dcMask;

	int m_anMap[4][4];   //ÓÎÏ·µØÍ¼

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitElement();
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();
	void UpdateMap();
};
