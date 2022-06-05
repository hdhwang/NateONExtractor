#pragma once
#include "afxcmn.h"


// CTab4 대화 상자입니다.

class CTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab4)

public:
	CTab4(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab4();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
