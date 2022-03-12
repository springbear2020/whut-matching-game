// CGameDlg.cpp : implementation file

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"CGameControl.h"
#include"CGameLogic.h"


// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/): CDialogEx(IDD__GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化图标选中状态
	m_bFirstPoint = true;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameDlg message handlers

//初始化窗口背景和大小
void CGameDlg::InitBackground()
{	
	//加载BMP文件资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(hBmpBG);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//调整窗口大小
	UpdateWindow();
}

//初始化对话框
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置对话框图标
	m_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_icon, TRUE);    //设置大图标
	SetIcon(m_icon, FALSE);   //设置小图标

	//初始化背景
	InitBackground();

	//初始化元素
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
					   // 
	//将位图内存拷入视频内存
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//初始化元素
void CGameDlg::InitElement()
{
	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获取当前对话框的视频内存
	CClientDC dc(this);

	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcElement.SelectObject(hBmpBG);

	//加载BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);
}

//调整窗口大小
void CGameDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);   //获得窗口大小
	this->GetWindowRect(rtClient);   //获得客户区大小

	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}

//更新地图
void CGameDlg::UpdateMap()
{
	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK) continue;
			
			//将背景与掩码相与，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			
			//与元素图片相或，边保留，图片区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
	Invalidate(false);
}

//绘制提示框
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;

	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;

	dc.FrameRect(rtTipFrame, &brush);
}

//绘制提示线
void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}


/*
//绘制提示线
void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum)
{
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + asvPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}
*/
//开始游戏按钮
void CGameDlg::OnClickedBtnStart()
{
	//初始化游戏地图
	m_GameC.StartGame();
	//更新界面
	UpdateMap();
	//更新窗口
	InvalidateRect(m_rtGameRect, false);
}

//游戏地图事件响应
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//去掉小于0的状态
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//换算点击的坐标点
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	//判断坐标的有效性
	if (nRow > 3 || nCol > 3)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	
	if (m_bFirstPoint)   //第一个点
	{
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
	}
	else {
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecPoint(nRow, nCol);

		Vertex avPath[MAX_VERTEX_NUM];     //获得路径   16为路径最长（不会到16条路径的）
		int nVexnum = 0;      //顶点个数

		//连子判断
		if (m_GameC.Link(avPath, nVexnum))
		{
			//画提示线
			DrawTipLine(avPath, nVexnum);
			//更新地图
			UpdateMap();
		}

		Sleep(200);
		InvalidateRect(m_rtGameRect, false);
	}
	m_bFirstPoint = !m_bFirstPoint;
}
