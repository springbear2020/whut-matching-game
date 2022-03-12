#pragma once
#include"global.h"
#include"CGameControl.h"

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
	CDC m_dcMem;        //内存DC
	CDC m_dcElement;    //元素内存DC
	CDC m_dcMask;      //掩码内存DC
	CDC m_dcBG;        //背景DC
	CDC m_dcCache;     //缓存的内存DC

	CPoint m_ptGameTop;   //游戏起始坐标
	CSize m_sizeElem;     //图片元素大小
	CRect m_rtGameRect;   //游戏区域大小

	bool m_bFirstPoint;   //选中的图片是不是第一次选中，默认为是
	bool m_bPlaying;   //表示游戏是否正在进行
	bool m_bPause;   //游戏暂停与否
	int timeCount;    //计时

	CGameControl m_GameC;    //游戏控制类


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	void InitBackground();          //初始化背景
	void InitElement();             //初始化元素
	void UpdateWindow();            //调整窗口大小
	void UpdateMap();               //更新游戏地图
	void DrawTipFrame(int nRow, int nCol);   //绘制提示框
	void DrawTipLine(Vertex asvPath[MAX_VERTEX_NUM], int nVexnum);             //画提示线
	void JudgeWin(void);   //判断胜负
	
	CProgressCtrl m_GameProgress;
	virtual BOOL OnInitDialog();    //初始化对话框
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();      //开始游戏按钮
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);    //游戏地图内鼠标点击事件
	afx_msg void OnBnClickedBtnNotice();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnChangeEditTime();
	afx_msg void OnBnClickedBtnHelp();
};
