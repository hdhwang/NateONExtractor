// Tab4.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "Tab4.h"
#include "afxdialogex.h"


// CTab4 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

CTab4::CTab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTab4::IDD, pParent)
{

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, c_List);
}


BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTab4::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CTab4 �޽��� ó�����Դϴ�.


BOOL CTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	c_List.InsertColumn(0,_T("No"),LVCFMT_LEFT,30);
	c_List.InsertColumn(1,_T("Offset"),LVCFMT_CENTER,55);
	c_List.InsertColumn(2,_T("�߽��� ���� ��"),LVCFMT_CENTER,150);
	c_List.InsertColumn(3,_T("������ ���� ��"),LVCFMT_CENTER,150);
	c_List.InsertColumn(4,_T("�޽��� ����"),LVCFMT_CENTER,360);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTab4::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
