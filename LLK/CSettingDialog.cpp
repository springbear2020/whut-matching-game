// CSettingDialog.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CSettingDialog.h"
#include "afxdialogex.h"
#include"BackgroundMusic.h"


// CSettingDialog dialog

IMPLEMENT_DYNAMIC(CSettingDialog, CDialogEx)

CSettingDialog::CSettingDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSettingDialog::~CSettingDialog()
{
}

void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SURE, &CSettingDialog::OnBnClickedButtonSure)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CSettingDialog::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CSettingDialog message handlers


BOOL CSettingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//设置对话框图标
	m_sIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_sIcon, TRUE);    //设置大图标
	SetIcon(m_sIcon, FALSE);   //设置小图标

	//设置radioButton默认选中音乐开
	((CButton*)GetDlgItem(IDC_RADIO_ON))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_OFF))->SetCheck(FALSE);

	//初始化edit control
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_MUSIC);
	pBoxOne->SetWindowTextW(_T("音量"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CSettingDialog::OnBnClickedButtonSure()
{
	// TODO: Add your control notification handler code here
	IsPlayBackgroundMusic();

	BackgroundMusic bgm ;

	if (m_bPlayMusic)
	{
		bgm.playBackgroundMusic();  //播放背景音乐
	}
	else
	{
		bgm.pauseBackgroundMusic();  //关闭背景音乐
	}

	UpdateData(false);

	CDialogEx::OnOK();

}
void CSettingDialog::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	IsPlayBackgroundMusic();
	CDialogEx::OnCancel();
}

//判断是否播放背景音乐，是修改播放标识为true
void CSettingDialog::IsPlayBackgroundMusic()
{
	int m_playMusic = GetCheckedRadioButton(IDC_RADIO_ON, IDC_RADIO_OFF);
	
	if (m_playMusic == 1029)
	{
		m_bPlayMusic = true;
	}
	else if (m_playMusic == 1030)
	{
		m_bPlayMusic = false;;
	}
}
