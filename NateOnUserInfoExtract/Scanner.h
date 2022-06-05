#pragma once


#include "NateInfoExtract.h"

//#define   MEM_FILE_READ_BUFFER_SIZE 0x4000
#define   MEM_FILE_READ_BUFFER_SIZE 0x8000

class CScanner
{
public:
	CScanner(void);
	~CScanner(void);

protected:
	CString csMemFileLoc;
	HWND  hProgressDialog;
	SHORT dwProgressID;

public:
	CNateInfoExtract pNateInfoMoudle;	//분석 모듈

	void AnalysisStart(CString FileLoc);
	void Set_ProgressInfo(HWND hHWND, short dwID);

	static VOID WINAPI DataFindThread(LPVOID p);
	void DoFind(void);
};

