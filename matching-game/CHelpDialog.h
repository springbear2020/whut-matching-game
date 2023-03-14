#pragma once

// CHelpDialog dialog

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd *pParent = nullptr); // standard constructor
	virtual ~CHelpDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_DIALOG_HELP
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;	// 对话框图标
	CDC m_dcHelp;	// 帮助图片DC
	CDC m_dcMem;	// 内存DC
	CRect m_rtHelp; // 帮助图片显示区域
	BITMAP bmpMes;	// 图片信息

public:
	virtual BOOL OnInitDialog();											 // 初始化对话框
	afx_msg void OnPaint();													 // 绘制界面
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar); // 响应滚动条的操作
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);		 // 消息响应函数
	CScrollBar m_ScrollBar;
	void UpdateHelp();		// 根据滚动条的位置，设置帮助图片显示的内容
	void InitHelpPicture(); // 加载帮助图片
	void InitSrcollBar();	// 初始化滚动条
};
