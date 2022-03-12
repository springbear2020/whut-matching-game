#pragma once


// CVersionDlg dialog

class CVersionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVersionDlg)

public:
	CVersionDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CVersionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
protected:
	HICON m_vIcon;   //Í¼±ê
public:
	virtual BOOL OnInitDialog();
};
