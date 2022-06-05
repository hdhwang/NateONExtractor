#include "StdAfx.h"
#include "Scanner.h"
#include <time.h>

CScanner::CScanner(void)
{
}

CScanner::~CScanner(void)
{
}

void CScanner::Set_ProgressInfo(HWND hHWND, short dwID)
{
	hProgressDialog = hHWND;
	dwProgressID = dwID;
}

void CScanner::AnalysisStart(CString FileLoc)
{
	DWORD dwThreadId;
	HANDLE hThread;

	csMemFileLoc = FileLoc;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&DataFindThread, this, 0, &dwThreadId);
	CloseHandle(hThread);
}
VOID WINAPI CScanner::DataFindThread(LPVOID p)
{
	((CScanner*)p)->DoFind();
}

void CScanner::DoFind(void)
{
	DWORD dwFileSizeLow, dwFileSizeHigh;
	DWORD dwByteRead;
	__int64 dwMemFileSize;
	LARGE_INTEGER _ReadFileOffset;
	int dwPercent;
	CString tmp;
	HANDLE hReadFile = CreateFile(csMemFileLoc.GetBuffer(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hReadFile == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(_T("Read File Error "));
		return;
	}

	char *strReadBuffer = new char[MEM_FILE_READ_BUFFER_SIZE];
	dwFileSizeLow = ::GetFileSize(hReadFile, &dwFileSizeHigh);
	dwMemFileSize = (__int64)dwFileSizeHigh << 32 | dwFileSizeLow;
	_ReadFileOffset.QuadPart = 0;

	for (; _ReadFileOffset.QuadPart < dwMemFileSize;)
	{
		SetFilePointer(hReadFile, _ReadFileOffset.LowPart, &(_ReadFileOffset.HighPart), FILE_BEGIN);

		if (FALSE == ReadFile(hReadFile, strReadBuffer, (DWORD)MEM_FILE_READ_BUFFER_SIZE, &dwByteRead, NULL))
		{
			//printf("ReadFileError \n");
			break;
		}

		if (dwByteRead <= 0)
		{
			break;
		}

		pNateInfoMoudle.NatUserInfoExtract(strReadBuffer, dwByteRead, _ReadFileOffset.QuadPart);
		_ReadFileOffset.QuadPart += dwByteRead;
		dwPercent = (DWORD)((_ReadFileOffset.QuadPart / (DOUBLE)dwMemFileSize) * 100);
		time_t start_time, end_time = 0;

		start_time = time(NULL);
		for (int i = 0; i <= 100; i++)
		{
			if (dwPercent == i)
			{
				SendMessage(hProgressDialog, dwProgressID, (WPARAM)i, NULL);
			}
		}

		if (dwPercent == 100)
		{
			break;
		}
	}

	//메모리 반환
	delete strReadBuffer;
}