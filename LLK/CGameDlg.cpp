// CGameDlg.cpp : implementation file

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"CGameControl.h"
#include"CGameLogic.h"
#include"CHelpDialog.h"
#include"CVersionDlg.h"
#include"CSettingDialog.h"

// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/): CDialogEx(IDD__GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	//初始化图片元素大小
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//初始化图标选中状态
	m_bFirstPoint = true;
	m_bPlaying = false;

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
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_NOTICE, &CGameDlg::OnBnClickedBtnNotice)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CGameDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_GAMEOVER, &CGameDlg::OnBnClickedBtnGameover)
END_MESSAGE_MAP()

//初始化窗口背景和大小
void CGameDlg::InitBackground()
{	
	//加载BMP文件资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("res\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);

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
	//获取当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("res\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcElement.SelectObject(hBmpBG);

	//加载BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("res\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载游戏暂停BMP图片资源
	HANDLE hCache = ::LoadImage(NULL, _T("res\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcCache.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcCache.SelectObject(hCache);
}

//开始游戏按钮
void CGameDlg::OnClickedBtnStart()
{
	//暂停时不响应
	if (m_bPause == true)
	{
		return;
	}

	//初始化游戏地图
	m_GameC.StartGame();

	//初始时间是300
	timeCount = 300;

	//是否游戏标识设为true
	m_bPlaying = true;
	//禁止按键点击
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	//初始化进度条
	m_GameProgress.SetRange(0, 300);   //初始范围
	m_GameProgress.SetStep(-1);           //初始步数值
	m_GameProgress.SetPos(300);        //设置初始值

	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	
	//更新界面
	UpdateMap();
	//更新窗口
	InvalidateRect(m_rtGameRect, false);

	//设置进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
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
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1)
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

		//判断胜负
		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;

	CDialogEx::OnLButtonUp(nFlags, point);
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

//提示按钮时间响应
void CGameDlg::OnBnClickedBtnNotice()
{
	//如果没有进行游戏，则放回
	if (m_bPlaying == false)
	{
		return;
	}

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM];   //获得路径
	int nVexnum = 0;   //顶点个数

	if (m_GameC.Help(avPath, nVexnum))
	{
		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col); 

		//画提示线
		DrawTipLine(avPath, nVexnum);

		//为了使第二个提示框可以看到，暂停200ms后，再刷新页面
		Sleep(1000);   

		UpdateMap();  //更新地图

		//局部矩形更新
		InvalidateRect(m_rtGameRect, FALSE);
	}

}

//重排按钮
void CGameDlg::OnBnClickedBtnReset()
{
	//调用ResertGraph()
	m_GameC.Resert();

	//更新地图，调用UpdateMap(),更新界面显示
	UpdateMap();

	//通知界面重绘
	InvalidateRect(m_rtGameRect, FALSE);   //局部矩形更新

}

//计时器
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	//设置进度条位置之前，需要判断计时器编号是否为当前计时器
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{
		//游戏时间减一秒
		if (timeCount > 0)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			timeCount--;
			SetDlgItemText(IDC_EDIT_TIME, str);

			UpdateData(false);

			//刷新进度条位置
			m_GameProgress.StepIt();
		}
	 }

	//判断胜负
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}

//判断胜负
void CGameDlg::JudgeWin()
{
	//游戏胜负判断
	BOOL bGameStatus = m_GameC.IsWin(m_GameProgress.GetPos());

	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏表示改为false
		m_bPlaying = false;

		//关闭定时器
		KillTimer(PLAY_TIMER_ID);

		//提示获胜
		CString  strTitle;
		
		this->GetWindowTextW(strTitle);

		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("Congratulation!"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("Time Out!\nGame Over!"), strTitle);
		}

		//还原游戏按钮可点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
}

//游戏暂停按钮时间响应
void CGameDlg::OnBnClickedBtnPause()
{
	//获得当前对话框的视频内容
	CClientDC dc(this);

	//游戏未正在进行，直接返回
	if (m_bPlaying == false)
	{
		return;
	}

	//如果游戏不是暂停状态
	if (m_bPause == false)
	{
		//绘制背景到内存DC中
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);

		GetDlgItem(IDC_BTN_NOTICE)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false);   //更新界面
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BTN_NOTICE)->EnableWindow(1);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新

		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}
	m_bPause = !m_bPause;
}

void CGameDlg::OnChangeEditTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//帮助按钮
void CGameDlg::OnBnClickedBtnHelp()
{
	// TODO: Add your control notification handler code here
	CHelpDialog chd;
	chd.DoModal();
}


void CGameDlg::OnBnClickedBtnAbout()
{
	// TODO: Add your control notification handler code here
	CVersionDlg cvd;
	cvd.DoModal();
}


void CGameDlg::OnBnClickedBtnSetting()
{
	// TODO: Add your control notification handler code here
	CSettingDialog csd;
	csd.DoModal();
}


void CGameDlg::OnBnClickedBtnGameover()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnCancel();
}
