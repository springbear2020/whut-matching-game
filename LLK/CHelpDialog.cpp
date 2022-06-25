// CHelpDialog.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog dialog

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR_HELP, m_ScrollBar);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDialog message handlers

//初始化对话框
BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置对话框图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);    //设置大图标
	SetIcon(m_hIcon, FALSE);   //设置小图标

	GetClientRect(&m_rtHelp);   //获取对话框大小
	InitHelpPicture();//加载帮助图片
	InitSrcollBar();//加载滚动条

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//绘制界面
void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	//绘制图片
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
}

//响应滚动条的操作
void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_ScrollBar.GetScrollPos();

	switch (nSBCode)
	{
	case SB_LINEUP:
		pos--;
		break;
	case SB_LINEDOWN:
		pos++;
		break;
	case SB_PAGEUP:
		pos -= m_rtHelp.bottom - m_rtHelp.top;
		break;
	case SB_PAGEDOWN:
		pos += m_rtHelp.bottom - m_rtHelp.top;
		break;
	case SB_TOP:
		pos = 0;
		break;
	case SB_BOTTOM:
		pos = bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top;
		break;
	case SB_THUMBTRACK:
		pos = nPos;
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		break;
	}

	//设置滑块位置
	m_ScrollBar.SetScrollPos(pos);
	//重绘图片
	UpdateHelp();

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

//更具滚动条的位置更新帮助图片显示
void CHelpDialog::UpdateHelp()
{
	//当前滚动条位置
	int nScrollPos = m_ScrollBar.GetScrollPos();
	
	//将重绘区绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//截取图片进行绘制
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nScrollPos, SRCCOPY);
	//更新界面
	InvalidateRect(m_rtHelp, FALSE);
}

//初始化帮助图片
void CHelpDialog::InitHelpPicture()
{
	HANDLE helpBmp;

	//加载图片资源
	helpBmp = ::LoadImage(NULL, _T("res\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获取当前设备环境
	CClientDC dc(this);
	//创建兼容DC
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcMem.CreateCompatibleDC(&dc);
	//将位图资源选入设备环境
	m_dcHelp.SelectObject(helpBmp);
	//获取位图信息
	GetObject(helpBmp, sizeof(BITMAP), &bmpMes);

	//初始化缓冲内存
	CBitmap bmpMem;
	bmpMem.CreateDiscardableBitmap(&dc, m_rtHelp.Width(), m_rtHelp.Height());
	m_dcMem.SelectObject(&bmpMem);

	//绘制白色背景
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制帮助图片到缓冲区
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);
}

//初始化滚动条
void CHelpDialog::InitSrcollBar()
{
	m_ScrollBar.SetScrollRange(0, bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top);
	m_ScrollBar.SetScrollPos(0);
}

//解决版权信息左右两边有灰色的背景，消息响应函数
HBRUSH CHelpDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}