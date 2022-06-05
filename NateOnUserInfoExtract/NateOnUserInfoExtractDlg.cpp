
// NateOnUserInfoExtractDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "NateOnUserInfoExtractDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

														// 구현입니다.
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

// CNateOnUserInfoExtractDlg 대화 상자

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

// CNateOnUserInfoExtractDlg 메시지 처리기
BOOL CNateOnUserInfoExtractDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
									// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CString strTab = _T("");

	m_mainTab.InsertItem(0, _T("친구 정보"), 0);
	m_mainTab.InsertItem(1, _T("메시지 정보"), 0);
	m_mainTab.InsertItem(2, _T("파일 전송 정보"), 0);

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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CNateOnUserInfoExtractDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CNateOnUserInfoExtractDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNateOnUserInfoExtractDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNateOnUserInfoExtractDlg::OnBnClickedButtonFileSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//탭의 모든 아이템 삭제
	m_TabDialog2.c_List.DeleteAllItems();
	m_TabDialog4.c_List.DeleteAllItems();
	m_TabDialog5.c_List.DeleteAllItems();

	start_time = GetTickCount() / 100;
	pScanner.Set_ProgressInfo(this->m_hWnd, MESSAGE_PROGRESS_STATE);

	//항목 초기화
	GetDlgItem(IDC_BUTTON_AnalysisStart)->EnableWindow(FALSE);
	c_Progress.SetPos(0);
	SetDlgItemText(IDC_STATIC_TIME_TITLE, _T(""));
	SetDlgItemText(IDC_STATIC_TIME, _T(""));
	SetDlgItemText(IDC_STATIC_PROGRESS_STATE, _T("분석중..."));

	//분석 시작
	pScanner.AnalysisStart(m_csFileLoc);
}


void CNateOnUserInfoExtractDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		//분석이 완료된경우
		end_time = GetTickCount() / 100;
		DWORD time = (DWORD)(end_time - start_time);
		tmp.Format(_T("%dms"), time);
		SetData();
		SetDlgItemText(IDC_STATIC_PROGRESS_STATE, _T("분석 완료"));
		SetDlgItemText(IDC_STATIC_TIME_TITLE, _T("분석 소요 시간 : "));
		SetDlgItemText(IDC_STATIC_TIME, tmp);
	}

	return LRESULT();
}


void CNateOnUserInfoExtractDlg::SetData(void)
{
	CString tmp;
	int tmpIndex = 0;
	DWORD dwListCount = 0;

	//친구 정보
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

	//메시지 정보

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

	//파일전송 정보

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
