// CGameDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD__GAME_DIALOG, pParent)
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
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 4;
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
	// TODO: Add your implementation code here.
	
	//获得当前对话框的视频内容
	CClientDC dc(this);
	
	//加载BMP文件资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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

	//设置窗口大小
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

	// TODO:  Add extra initialization here

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
	//将位图内存拷入视频内存
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//初始化元素
void CGameDlg::InitElement()
{
	// TODO: Add your implementation code here.
	//获取当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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
	// TODO: Add your implementation code here.

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, 
		           m_rtGameRect.Width(), m_rtGameRect.Height(),
		  &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			//将背景与掩码相与，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);
			//与元素图片相或，边保留，图片区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);
		}
	}
	Invalidate(false);
}

//判断是否第一次选中图片
bool CGameDlg::IsLink(void)
{
	if (m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] == m_anMap[m_ptSelSec.y][m_ptSelSec.x]) {
		return true;
	}
	return false;
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
void CGameDlg::DrawTipLine()
{
	// TODO: Add your implementation code here.

	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + m_ptSelFirst.x * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + m_ptSelFirst.y * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.LineTo(m_ptGameTop.x + m_ptSelSec.x * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + m_ptSelSec.y * m_sizeElem.cy + m_sizeElem.cy / 2);

	dc.SelectObject(pOldPen);
}

//开始游戏按钮事件监听
void CGameDlg::OnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	int anMap[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_anMap[i][j] = anMap[i][j];
		}
	}
	UpdateMap();
}

//游戏地图事件响应
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	if (nRow > 3 || nCol > 3) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//如果是第一次选中图片，则绘制矩形框
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_ptSelFirst.x = nCol;
		m_ptSelFirst.y = nRow;
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_ptSelSec.x = nCol;
		m_ptSelSec.y = nRow;

		//判断是否是相同图片
		if (IsLink()) {
			DrawTipLine();
			m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] = -1;
			m_anMap[m_ptSelSec.y][m_ptSelSec.x] = -1;
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, false);
	}
	m_bFirstPoint = !m_bFirstPoint;
}
