
// NateOnUserInfoExtractDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "NateOnUserInfoExtractDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

														// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CNateOnUserInfoExtractDlg ��ȭ ����

CNateOnUserInfoExtractDlg::CNateOnUserInfoExtractDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNateOnUserInfoExtractDlg::IDD, pParent)
	, m_csFileLoc(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNateOnUserInfoExtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mainTab);
	DDX_Text(pDX, IDC_EDIT1, m_csFileLoc);
	DDX_Control(pDX, IDC_PROGRESS1, c_Progress);
}

BEGIN_MESSAGE_MAP(CNateOnUserInfoExtractDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(MESSAGE_PROGRESS_STATE, Set_ProgressView)


	//ON_BN_CLICKED(IDC_BUTTON2, &CNateOnUserInfoExtractDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SELECT, &CNateOnUserInfoExtractDlg::OnBnClickedButtonFileSelect)
	ON_BN_CLICKED(IDC_BUTTON_AnalysisStart, &CNateOnUserInfoExtractDlg::OnBnClickedButtonAnalysisstart)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CNateOnUserInfoExtractDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CNateOnUserInfoExtractDlg::OnTcnSelchangingTab1)
	ON_STN_CLICKED(IDC_STATIC_TIME_TITLE, &CNateOnUserInfoExtractDlg::OnStnClickedStaticTimeTitle)
END_MESSAGE_MAP()

// CNateOnUserInfoExtractDlg �޽��� ó����
BOOL CNateOnUserInfoExtractDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
									// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CString strTab = _T("");

	m_mainTab.InsertItem(0, _T("ģ�� ����"), 0);
	m_mainTab.InsertItem(1, _T("�޽��� ����"), 0);
	m_mainTab.InsertItem(2, _T("���� ���� ����"), 0);

	CRect rect;

	m_mainTab.GetClientRect(&rect);

	m_TabDialog5.Create(IDD_DIALOG5, &m_mainTab);
	m_TabDialog5.SetWindowPos(NULL, 0, 21, rect.Width(), rect.Height(), SWP_HIDEWINDOW | SWP_NOZORDER);

	m_TabDialog4.Create(IDD_DIALOG4, &m_mainTab);
	m_TabDialog4.SetWindowPos(NULL, 0, 21, rect.Width(), rect.Height(), SWP_HIDEWINDOW | SWP_NOZORDER);

	m_TabDialog2.Create(IDD_DIALOG2, &m_mainTab);
	m_TabDialog2.SetWindowPos(NULL, 0, 21, rect.Width(), rect.Height(), SWP_SHOWWINDOW | SWP_NOZORDER);

	m_pwndShow = &m_TabDialog2;
	m_mainTab.SetCurSel(0);

	GetDlgItem(IDC_BUTTON_AnalysisStart)->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CNateOnUserInfoExtractDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CNateOnUserInfoExtractDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CNateOnUserInfoExtractDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNateOnUserInfoExtractDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CNateOnUserInfoExtractDlg::OnBnClickedButtonFileSelect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog dlg(TRUE, _T(""), _T("*.*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);


	if (dlg.DoModal() == IDOK)
	{

		m_csFileLoc = dlg.GetPathName();

		UpdateData(FALSE);
	}

	else
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_AnalysisStart)->EnableWindow(TRUE);
	UpdateData(FALSE);
}


void CNateOnUserInfoExtractDlg::OnBnClickedButtonAnalysisstart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//���� ��� ������ ����
	m_TabDialog2.c_List.DeleteAllItems();
	m_TabDialog4.c_List.DeleteAllItems();
	m_TabDialog5.c_List.DeleteAllItems();

	start_time = GetTickCount() / 100;
	pScanner.Set_ProgressInfo(this->m_hWnd, MESSAGE_PROGRESS_STATE);

	//�׸� �ʱ�ȭ
	GetDlgItem(IDC_BUTTON_AnalysisStart)->EnableWindow(FALSE);
	c_Progress.SetPos(0);
	SetDlgItemText(IDC_STATIC_TIME_TITLE, _T(""));
	SetDlgItemText(IDC_STATIC_TIME, _T(""));
	SetDlgItemText(IDC_STATIC_PROGRESS_STATE, _T("�м���..."));

	//�м� ����
	pScanner.AnalysisStart(m_csFileLoc);
}


void CNateOnUserInfoExtractDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tmp;

	//if(m_pwndShow != NULL) 
	//{ 
	//	m_pwndShow->ShowWindow(SW_HIDE); 
	//	//m_pwndShow = NULL; 
	//} 

	//m_pwndShow->ShowWindow(SW_HIDE); 
	int nIndex = m_mainTab.GetCurSel();

	//tmp.Format(_T("%d"),nIndex);

	//AfxMessageBox(tmp);

	switch (nIndex)
	{
	case 0:
		m_TabDialog2.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabDialog2;
		m_TabDialog4.ShowWindow(SW_HIDE);
		m_TabDialog5.ShowWindow(SW_HIDE);

		break;

	case 1:
		m_TabDialog4.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabDialog4;
		m_TabDialog2.ShowWindow(SW_HIDE);
		m_TabDialog5.ShowWindow(SW_HIDE);
		break;

	case 2:
		m_TabDialog5.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabDialog5;
		m_TabDialog2.ShowWindow(SW_HIDE);
		m_TabDialog4.ShowWindow(SW_HIDE);
		break;
	}

	UpdateData(FALSE);
	*pResult = 0;
}


void CNateOnUserInfoExtractDlg::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

LRESULT CNateOnUserInfoExtractDlg::Set_ProgressView(WPARAM wParam, LPARAM lParam)
{
	CString tmp;

	DWORD dwPos = (DWORD)wParam;
	//tmp.Format(_T("%d %%"), dwPos);
	c_Progress.SetPos(dwPos);
	UpdateData(FALSE);

	if (dwPos == 100)
	{
		//�м��� �Ϸ�Ȱ��
		end_time = GetTickCount() / 100;
		DWORD time = (DWORD)(end_time - start_time);
		tmp.Format(_T("%dms"), time);
		SetData();
		SetDlgItemText(IDC_STATIC_PROGRESS_STATE, _T("�м� �Ϸ�"));
		SetDlgItemText(IDC_STATIC_TIME_TITLE, _T("�м� �ҿ� �ð� : "));
		SetDlgItemText(IDC_STATIC_TIME, tmp);
	}

	return LRESULT();
}


void CNateOnUserInfoExtractDlg::SetData(void)
{
	CString tmp;
	int tmpIndex = 0;
	DWORD dwListCount = 0;

	//ģ�� ����
	m_TabDialog2.c_List.ModifyStyle(LVS_EX_GRIDLINES, LVS_REPORT);
	m_TabDialog2.c_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	for (unsigned int i = 0; i < pScanner.pNateInfoMoudle.Friendsinfo.size(); i++)
	{
		tmp.Format(_T("%d"), i);
		m_TabDialog2.c_List.InsertItem(i, tmp, 0);
		tmp.Format(_T("%I64x"), pScanner.pNateInfoMoudle.Friendsinfo[i].dwScanOffset);

		m_TabDialog2.c_List.SetItemText(i, 1, tmp);
		m_TabDialog2.c_List.SetItemText(i, 2, pScanner.pNateInfoMoudle.Friendsinfo[i]._id);
	}

	//�޽��� ����

	m_TabDialog4.c_List.ModifyStyle(LVS_EX_GRIDLINES, LVS_REPORT);
	m_TabDialog4.c_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	for (unsigned int i = 0; i < pScanner.pNateInfoMoudle.MessageInfo.size(); i++)
	{
		tmp.Format(_T("%d"), i);
		m_TabDialog4.c_List.InsertItem(i, tmp, 0);
		tmp.Format(_T("%I64x"), pScanner.pNateInfoMoudle.MessageInfo[i].dwScanOffset);

		m_TabDialog4.c_List.SetItemText(i, 1, tmp);
		m_TabDialog4.c_List.SetItemText(i, 2, pScanner.pNateInfoMoudle.MessageInfo[i]._sender_id);
		m_TabDialog4.c_List.SetItemText(i, 3, pScanner.pNateInfoMoudle.MessageInfo[i]._receiver_id);
		m_TabDialog4.c_List.SetItemText(i, 4, pScanner.pNateInfoMoudle.MessageInfo[i]._message_content);
		tmpIndex = i;
	}

	//�������� ����

	m_TabDialog5.c_List.ModifyStyle(LVS_EX_GRIDLINES, LVS_REPORT);
	m_TabDialog5.c_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	tmp.Format(_T("%d"), pScanner.pNateInfoMoudle.FiletransInfo.size());

	//AfxMessageBox(tmp);

	for (unsigned int i = 0; i<pScanner.pNateInfoMoudle.FiletransInfo.size(); i++)
	{
		tmp.Format(_T("%d"), i);
		m_TabDialog5.c_List.InsertItem(i, tmp, 0);
		tmp.Format(_T("%I64x"), pScanner.pNateInfoMoudle.FiletransInfo[i].dwScanOffset);

		m_TabDialog5.c_List.SetItemText(i, 1, tmp);
		m_TabDialog5.c_List.SetItemText(i, 2, pScanner.pNateInfoMoudle.FiletransInfo[i]._file_name);
		m_TabDialog5.c_List.SetItemText(i, 3, pScanner.pNateInfoMoudle.FiletransInfo[i]._size);
		m_TabDialog5.c_List.SetItemText(i, 4, pScanner.pNateInfoMoudle.FiletransInfo[i]._url_href);
		m_TabDialog5.c_List.SetItemText(i, 5, pScanner.pNateInfoMoudle.FiletransInfo[i]._MIME);
		m_TabDialog5.c_List.SetItemText(i, 6, pScanner.pNateInfoMoudle.FiletransInfo[i]._key);
		m_TabDialog5.c_List.SetItemText(i, 7, pScanner.pNateInfoMoudle.FiletransInfo[i]._expire);
		m_TabDialog5.c_List.SetItemText(i, 8, pScanner.pNateInfoMoudle.FiletransInfo[i]._hash);
	}

	pScanner.pNateInfoMoudle.Friendsinfo.clear();
	pScanner.pNateInfoMoudle.MessageInfo.clear();
	pScanner.pNateInfoMoudle.FiletransInfo.clear();
}


void CNateOnUserInfoExtractDlg::OnStnClickedStaticTimeTitle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
