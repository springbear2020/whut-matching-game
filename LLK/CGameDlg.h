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
	CDC m_dcMem;   //内存DC
	CDC m_dcElement;   
	CDC m_dcMask;
	CDC m_dcBG;

	int m_anMap[4][4];   //游戏地图
	CPoint m_ptGameTop;   //游戏起始坐标
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CPoint m_ptSelFirst;
	CPoint m_ptSelSec;
	CRect m_rtGameRect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InitElement();
	void DrawTipFrame(int nRow, int nCol);
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	virtual BOOL OnInitDialog();
	void UpdateMap();
	bool IsLink(void);

	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipLine();
};
