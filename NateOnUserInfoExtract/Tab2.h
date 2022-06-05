#pragma once
#include "afxcmn.h"


// CTab2 대화 상자입니다.

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
