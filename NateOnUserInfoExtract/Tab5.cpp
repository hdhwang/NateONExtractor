// Tab5.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "Tab5.h"
#include "afxdialogex.h"


// CTab5 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab5, CDialogEx)

CTab5::CTab5(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab5::IDD, pParent)
{

}

CTab5::~CTab5()
{
}

void CTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, c_List);
}


BEGIN_MESSAGE_MAP(CTab5, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTab5::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CTab5 �޽��� ó�����Դϴ�.

BOOL CTab5::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	c_List.InsertColumn(0,_T("No"),LVCFMT_LEFT,30);
	c_List.InsertColumn(1,_T("Offset"),LVCFMT_CENTER,55);
	c_List.InsertColumn(2,_T("�̸�"),LVCFMT_CENTER,80);
	c_List.InsertColumn(3,_T("ũ��"),LVCFMT_CENTER,80);
	c_List.InsertColumn(4,_T("URL"),LVCFMT_CENTER,80);
	c_List.InsertColumn(5,_T("MIME"),LVCFMT_CENTER,80);
	c_List.InsertColumn(6,_T("KEY"),LVCFMT_CENTER,80);
	c_List.InsertColumn(7, _T("EXPIRE"), LVCFMT_CENTER, 80);
	c_List.InsertColumn(8,_T("HASH"),LVCFMT_CENTER,210);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTab5::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
