#pragma once


// CSettingDialog dialog

class CSettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDialog)

public:
	CSettingDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSettingDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	HICON m_sIcon;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSure();
	afx_msg void OnBnClickedButtonCancel();
public:
	void IsPlayBackgroundMusic();
public:
	bool m_bPlayMusic;
};
