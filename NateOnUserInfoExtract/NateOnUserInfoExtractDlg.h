
// NateOnUserInfoExtractDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "Tab2.h"
#include "Tab4.h"
#include "Tab5.h"


#include "Scanner.h"

//#define  MESSAGE_PROGRESS_STATE		WM_USER+0x100


// CNateOnUserInfoExtractDlg 대화 상자
class CNateOnUserInfoExtractDlg : public CDialogEx
{
// 생성입니다.
public:
	CNateOnUserInfoExtractDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NATEONUSERINFOEXTRACT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CTabCtrl m_mainTab;

public:
	CTab2 m_TabDialog2;
	CTab4 m_TabDialog4;
	CTab5 m_TabDialog5;
	CWnd*        m_pwndShow;
	int start_time;
	int end_time;
public:

	CScanner pScanner;


public:
	

	LRESULT Set_ProgressView(WPARAM wParam, LPARAM lParam);


	afx_msg void OnBnClickedButtonFileSelect();
	afx_msg void OnBnClickedButtonAnalysisstart();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_csFileLoc;
	CProgressCtrl c_Progress;
	void SetData(void);
	afx_msg void OnStnClickedStaticTimeTitle();
};
