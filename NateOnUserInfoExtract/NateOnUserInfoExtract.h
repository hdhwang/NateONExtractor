
// NateOnUserInfoExtract.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CNateOnUserInfoExtractApp:
// �� Ŭ������ ������ ���ؼ��� NateOnUserInfoExtract.cpp�� �����Ͻʽÿ�.
//

class CNateOnUserInfoExtractApp : public CWinApp
{
public:
	CNateOnUserInfoExtractApp();
	
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CNateOnUserInfoExtractApp theApp;