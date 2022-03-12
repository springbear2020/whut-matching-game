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

	CPoint m_ptGameTop;   //游戏起始坐标
	CSize m_sizeElem;     //图片元素大小
	CRect m_rtGameRect;

	CGameControl m_GameC;

	bool m_bFirstPoint;   //选中的图片是不是第一次选中，默认为是

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();          //初始化背景
	void InitElement();             //初始化元素
	void DrawTipFrame(int nRow, int nCol);   //绘制提示框
	void UpdateWindow();            //调整窗口大小
	void UpdateMap();               //更新游戏地图
	void DrawTipLine(Vertex asvPath[4], int nVexnum);             //画提示线

	virtual BOOL OnInitDialog();    //初始化对话框

	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();      //开始游戏按钮
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);    //游戏地图内鼠标点击事件
};
