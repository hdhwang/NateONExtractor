
// NateOnUserInfoExtractDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "Tab2.h"
#include "Tab4.h"
#include "Tab5.h"


#include "Scanner.h"

//#define  MESSAGE_PROGRESS_STATE		WM_USER+0x100


// CNateOnUserInfoExtractDlg ��ȭ ����
class CNateOnUserInfoExtractDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CNateOnUserInfoExtractDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NATEONUSERINFOEXTRACT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
