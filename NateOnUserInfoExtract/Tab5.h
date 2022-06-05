#pragma once


// CTab5 대화 상자입니다.

class CTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab5)

public:
	CTab5(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTab5();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
