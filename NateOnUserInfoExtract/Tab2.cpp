// Tab2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "Tab2.h"
#include "afxdialogex.h"


// CTab2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab2::IDD, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, c_List);
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTab2::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CTab2 �޽��� ó�����Դϴ�.


BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	c_List.InsertColumn(0,_T("No"),LVCFMT_LEFT,30);
	c_List.InsertColumn(1,_T("Offset"),LVCFMT_CENTER,55);
	c_List.InsertColumn(2,_T("���� ��"),LVCFMT_CENTER,150);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTab2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
