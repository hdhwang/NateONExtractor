#pragma once


// CTab5 ��ȭ �����Դϴ�.

class CTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab5)

public:
	CTab5(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTab5();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
