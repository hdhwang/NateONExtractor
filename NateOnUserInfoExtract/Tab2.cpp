// Tab2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NateOnUserInfoExtract.h"
#include "Tab2.h"
#include "afxdialogex.h"


// CTab2 대화 상자입니다.

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


// CTab2 메시지 처리기입니다.


BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	c_List.InsertColumn(0,_T("No"),LVCFMT_LEFT,30);
	c_List.InsertColumn(1,_T("Offset"),LVCFMT_CENTER,55);
	c_List.InsertColumn(2,_T("계정 명"),LVCFMT_CENTER,150);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
