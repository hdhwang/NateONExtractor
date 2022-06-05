#include "StdAfx.h"
#include "NateInfoExtract.h"
#include <vector>
#include <string.h>    // strstr 함수가 선언된 헤더 파일
#include <malloc.h>

CNateInfoExtract::CNateInfoExtract(void)
{
}


CNateInfoExtract::~CNateInfoExtract(void)
{
}

bool CNateInfoExtract::NatUserInfoExtract(char *strBuffer, int dwSize, UINT64 dwReadOffs)
{
	CString tmp;

	//친구 정보 분석
	Analysis(strBuffer, dwSize, dwReadOffs, FRIENDSINFO);

	//메시지 정보 분석
	Analysis(strBuffer, dwSize, dwReadOffs, MESSAGEINFO);

	//파일 전송 정보 분석
	Analysis(strBuffer, dwSize, dwReadOffs, FILETRANSINFO);

	return false;
}

//분석 수행
void CNateInfoExtract::Analysis(char *strBuffer, int dwSize, UINT64 dwReadOffs, char flag)
{
	int offset;
	MAX_BUF_SIZE = dwSize;
	dwScanOffset = dwReadOffs;

	for (int i = 0; i < MAX_BUF_SIZE; i = offset + 1)
	{
		//시그니처 탐색
		offset = SearchSignature(strBuffer, i, flag);

		//시그니처 오프셋이 존재하지 않는 경우
		if (offset == -1)
		{
			break;
		}

		//친구 정보인 경우
		if (flag == FRIENDSINFO)
		{
			FriendsInfoExtract(strBuffer, offset);
		}

		//메시지 정보인 경우
		else if (flag == MESSAGEINFO)
		{
			MessageInfoExtract(strBuffer, offset);
		}

		//파일 전송 정보인 경우
		else if (flag == FILETRANSINFO)
		{
			FileTransInfoExtract(strBuffer, offset);
		}
	}
}

//시그니처 탐색
int CNateInfoExtract::SearchSignature(char* strBuffer, int offset, char flag)
{
	int size;
	char* signature;

	if (flag == FRIENDSINFO)
	{
		size = 4;
		signature = new char[size + 1];
		ZeroMemory(signature, size + 1);
		signature[0] = (char)0x90;
		signature[1] = (char)0x8c;
		//signature[2] = (char)0x48;
		signature[2] = (char)0x32;
		signature[3] = (char)0x01;
	}

	else if (flag == MESSAGEINFO)
	{
		size = 72;
		signature = new char[size + 1];
		ZeroMemory(signature, size + 1);

		signature[0] = (char)0x1D;
		signature[1] = (char)0x81;
		signature[2] = (char)0x09;
		signature[3] = (char)0x82;
		signature[4] = (char)0x11;
		signature[5] = (char)0x11;
		signature[6] = (char)0x11;
		signature[7] = (char)0x11;
		signature[8] = (char)0x11;
		signature[9] = (char)0x11;
		signature[10] = (char)0x11;
		signature[11] = (char)0x0D;
		signature[12] = (char)0x08;
		signature[13] = (char)0x83;
		signature[14] = (char)0x65;
		signature[15] = (char)0x08;
		signature[16] = (char)0x11;
		signature[17] = (char)0x02;
		signature[18] = (char)0x2D;
		signature[19] = (char)0x35;
		signature[20] = (char)0x0D;
		signature[21] = (char)0x19;
		signature[22] = (char)0x0D;
		signature[23] = (char)0x11;
		signature[24] = (char)0x4F;
		signature[25] = (char)0x00;
		signature[26] = (char)0x33;
		signature[27] = (char)0x00;
		signature[28] = (char)0x70;
		signature[29] = (char)0x00;
		signature[30] = (char)0x66;
		signature[31] = (char)0x00;
		signature[32] = (char)0x55;
		signature[33] = (char)0x00;
		signature[34] = (char)0x74;
		signature[35] = (char)0x00;
		signature[36] = (char)0x79;
		signature[37] = (char)0x00;
		signature[38] = (char)0x31;
		signature[39] = (char)0x00;
		signature[40] = (char)0x68;
		signature[41] = (char)0x00;
		signature[42] = (char)0x36;
		signature[43] = (char)0x00;
		signature[44] = (char)0x73;
		signature[45] = (char)0x00;
		signature[46] = (char)0x4F;
		signature[47] = (char)0x00;
		signature[48] = (char)0x45;
		signature[49] = (char)0x00;
		signature[50] = (char)0x6F;
		signature[51] = (char)0x00;
		signature[52] = (char)0x63;
		signature[53] = (char)0x00;
		signature[54] = (char)0x31;
		signature[55] = (char)0x00;
		signature[56] = (char)0x42;
		signature[57] = (char)0x00;
		signature[58] = (char)0x45;
		signature[59] = (char)0x00;
		signature[60] = (char)0x69;
		signature[61] = (char)0x00;
		signature[62] = (char)0x64;
		signature[63] = (char)0x00;
		signature[64] = (char)0x75;
		signature[65] = (char)0x00;
		signature[66] = (char)0x36;
		signature[67] = (char)0x00;
		signature[68] = (char)0x76;
		signature[69] = (char)0x00;
		signature[70] = (char)0x5F;
		signature[71] = (char)0x53;
	}

	else if (flag == FILETRANSINFO)
	{
		size = 16;
		signature = new char[size + 1];
		ZeroMemory(signature, size + 1);
		signature[0] = (char)0x95;
		signature[1] = (char)0x6F;
		signature[2] = (char)0x5C;
		signature[3] = (char)0xD9;
		signature[4] = (char)0x99;
		signature[5] = (char)0x66;
		signature[6] = (char)0x0E;
		signature[7] = (char)0x00;
		signature[8] = (char)0xC0;
		signature[9] = (char)0x27;
		signature[10] = (char)0x04;
		signature[11] = (char)0x0B;
		signature[12] = (char)0x68;
		signature[13] = (char)0xD7;
		signature[14] = (char)0xE9;
		signature[15] = (char)0x04;
	}

	char* checkData = new char[size + 1];
	ZeroMemory(checkData, size + 1);

	//버퍼를 초과하지 않도록 for문 조건문 지정
	for (int i = offset; i < MAX_BUF_SIZE - size - 1; i++)
	{
		for (int j = 0; j < size; j++)
		{
			checkData[j] = strBuffer[i + j];
		}

		//시그니처가 존재하는 경우 오프셋 반환
		if (strncmp(checkData, signature, size) == 0)
		{
			return i;
		}
	}

	delete[] signature;
	signature = NULL;

	delete[] checkData;
	checkData = NULL;

	return -1;
}

//친구 정보 추출
void CNateInfoExtract::FriendsInfoExtract(char* strBuffer, int offset)
{
	_FRIENDSLIST tmp_struct;
	tmp_struct.dwScanOffset = dwScanOffset + offset;

	// 오프셋 + 4 값과 오프셋 + 8 값이 동일하지 않은 경우 친구 정보 시그니처가 아님
	if (strBuffer[offset + 4] != strBuffer[offset + 8])
	{
		return;
	}

	// 시그니처 오프셋 + 16 부터 친구 계정 정보가 위치함
	offset += 16;

	// 값이 숫자 또는 알파벳 소문자인 경우
	if ((int)strBuffer[offset] >= 0x30 && (int)strBuffer[offset] <= 0x39 ||
		(int)strBuffer[offset] >= 0x61 && (int)strBuffer[offset] <= 0x7A)
	{
		int size = ((int)strBuffer[offset - 8]);

		//계정 명 길이가 6 미만인 경우 리턴
		if (size < 6)
		{
			return;
		}

		string id = "";

		//아이디 값이 a.r.o.o.s.s.@.n.a.t.e..c.o.m. 형태로 되어 있어서 홀수 데이터만 저장
		for (int i = 0; i < size * 2; i++)
		{
			if (i % 2 == 0)
			{
				id += strBuffer[offset + i];
			}
		}

		//배열에 계정 명 필수 문자(@) 들어있는지 확인
		if (id.find("@", 0) == string::npos)
		{
			return;
		}

		//계정 명이 아닌 내용 필터링
		for (int i = 0; i < size; i++)
		{
			int checkData = (int)id[i];

			// 특수문자 (- @ . _) 또는 숫자 또는 영소문자가 아닌 경우 리턴
			if ( !(checkData == 0x2D || checkData == 0x40 || checkData == 0x2E || checkData == 0x5F || (checkData >= 0x30 && checkData <= 0x39) || (checkData >= 0x61 && checkData <= 0x7A)) )
			{
				return;
			}
		}

		tmp_struct._id = id.c_str();

		// 계정 중복 추가 방지를 위한 체크
		for (unsigned int i = 0; i < Friendsinfo.size(); i++)
		{
			//이미 존재하는 경우 리턴
			if (Friendsinfo[i]._id.Compare(tmp_struct._id) == 0)
			{
				return;
			}
		}

		Friendsinfo.push_back(tmp_struct);
	}
}

// 메시지 정보 추출
void CNateInfoExtract::MessageInfoExtract(char* strBuffer, int offset)
{
	_MESSAGE tmp_struct;
	tmp_struct.dwScanOffset = dwScanOffset + offset;

	// 시그니처 오프셋 + 72 + 3 부터 메시지 정보가 위치함
	offset += 72 + 3;

	//메시지
	int size = 0;
	string msg = "";
	for (unsigned int i = offset; i < _msize(strBuffer) - 7; i++)
	{
		// 메시지 종료 시그니처
		if ( (int)strBuffer[i] == 0x77 && (int)strBuffer[i + 1] == 0x00 && (int)strBuffer[i + 2] == 0x62 && (int)strBuffer[i + 3] == 0x00 && 
			(int)strBuffer[i + 4] == 0x6D && (int)strBuffer[i + 5] == 0x00 && (int)strBuffer[i + 6] == 0x6C && (int)strBuffer[i + 7] == 0x00)
		{
			break;
		}
		size++;
	}

	//데이터가 h.e.l.l.o. 형태로 되어 있어서 홀수 데이터만 저장
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			//메시지에 올 수 없는 문자인 경우
			if ((int)strBuffer[offset + i] < 0x20)
			{
				return;
			}

			msg += strBuffer[offset + i];
		}
	}
	tmp_struct._message_content = msg.c_str();

	//메시지 이후 송신자 데이터 나올때까지 오프셋 이동
	for (unsigned int i = offset; i < _msize(strBuffer) - 1; i++)
	{
		if ((int)strBuffer[i] == 0x3A && (int)strBuffer[i + 1] == 0x00)
		{
			offset += 2;
			break;
		}
		offset++;
	}

	//발신자
	size = 0;
	string sender = "";
	for (unsigned int i = offset; i < _msize(strBuffer); i++)
	{
		// 발신자 종료 시그니처
		if ((int)strBuffer[i] == 0x3A)
		{
			break;
		}
		size++;
	}

	//아이디 값이 a.r.o.o.s.s.@.n.a.t.e..c.o.m. 형태로 되어 있어서 홀수 데이터만 저장
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			sender += strBuffer[offset + i];
		}
	}

	//배열에 계정 명 필수 문자(@) 들어있는지 확인
	if (sender.find("@", 0) == string::npos)
	{
		return;
	}

	//계정 명이 아닌 내용 필터링
	for (unsigned int i = 0; i < sender.length(); i++)
	{
		int checkData = (int)sender[i];

		// 특수문자 (- @ . _) 또는 숫자 또는 영소문자가 아닌 경우 리턴
		if (!(checkData == 0x2D || checkData == 0x40 || checkData == 0x2E || checkData == 0x5F || (checkData >= 0x30 && checkData <= 0x39) || (checkData >= 0x61 && checkData <= 0x7A)))
		{
			return;
		}
	}
	tmp_struct._sender_id = sender.c_str();

	//발신자 이후 수신자 데이터 나올때까지 오프셋 이동
	int signatureCount = 0;
	for (unsigned int i = offset; i < _msize(strBuffer) - 1; i++)
	{
		if ((int)strBuffer[i] == 0x3A && (int)strBuffer[i + 1] == 0x00)
		{
			signatureCount++;

			if (signatureCount == 2)
			{
				offset += 2;
				break;
			}
		}
		offset++;
	}

	//수신자
	size = 0;
	string receiver = "";
	for (unsigned int i = offset; i < _msize(strBuffer); i++)
	{
		// 수신자 종료 시그니처
		if ((int)strBuffer[i] == 0x3A)
		{
			break;
		}
		size++;
	}

	//아이디 값이 a.r.o.o.s.s.@.n.a.t.e..c.o.m. 형태로 되어 있어서 홀수 데이터만 저장
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			receiver += strBuffer[offset + i];
		}
	}

	//배열에 계정 명 필수 문자(@) 들어있는지 확인
	if (receiver.find("@", 0) == string::npos)
	{
		return;
	}

	//계정 명이 아닌 내용 필터링
	for (unsigned int i = 0; i < receiver.length(); i++)
	{
		int checkData = (int)receiver[i];

		// 특수문자 (- @ . _) 또는 숫자 또는 영소문자가 아닌 경우 리턴
		if (!(checkData == 0x2D || checkData == 0x40 || checkData == 0x2E || checkData == 0x5F || (checkData >= 0x30 && checkData <= 0x39) || (checkData >= 0x61 && checkData <= 0x7A)))
		{
			return;
		}
	}
	tmp_struct._receiver_id = receiver.c_str();

	if (tmp_struct._message_content == _T("") || tmp_struct._receiver_id == _T("") || tmp_struct._sender_id == _T(""))
	{
		return;
	}

	for (unsigned int i = 0; i < MessageInfo.size(); i++)
	{
		if (MessageInfo[i]._message_content.Compare(tmp_struct._message_content) == 0
			&& (MessageInfo[i]._sender_id.Compare(tmp_struct._sender_id) == 0)
			&& (MessageInfo[i]._receiver_id.Compare(tmp_struct._receiver_id) == 0))
		{
			return;
		}
	}

	MessageInfo.push_back(tmp_struct);
}

// 파일 전송 정보 추출
void CNateInfoExtract::FileTransInfoExtract(char* strBuffer, int offset)
{
	_FILETRANS tmp_struct;
	tmp_struct.dwScanOffset = dwScanOffset + offset;

	offset += 19;

	int size = 0;
	for (unsigned int i = offset; i < _msize(strBuffer) - 1; i++)
	{
		// 파일 전송 json 종료 시그니처 확인
		if ((int)strBuffer[i] == 0x00 && (int)strBuffer[i + 1] == 0x00)
		{
			break;
		}
		size++;
	}
	string tmpData = "";

	//데이터가 ".k.e.y.".:.". 형태로 되어 있어서 홀수 데이터만 저장
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			tmpData += strBuffer[offset + 1 + i];
		}
	}

	//key
	string signature = "\"key\":\"";
	int pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string key = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			key += tmpData[i];
		}

		tmp_struct._key = key.c_str();
	}

	//type
	signature = "\"type\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string type = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			type += tmpData[i];
		}

		tmp_struct._type = type.c_str();
	}

	//file_name
	signature = "\"name\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string name = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			name += tmpData[i];
		}

		tmp_struct._file_name = name.c_str();
	}

	//mime
	signature = "\"mime\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string mime = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			mime += tmpData[i];
		}

		tmp_struct._MIME = mime.c_str();
	}

	//size
	signature = "\"size\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string fileSize = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			fileSize += tmpData[i];
		}

		tmp_struct._size = fileSize.c_str();
	}

	//url.href
	signature = "\"url.href\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string urlHref = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			urlHref += tmpData[i];
		}

		tmp_struct._url_href = urlHref.c_str();
	}

	//url.dn
	signature = "\"url.dn\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string urlDn = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			urlDn += tmpData[i];
		}

		tmp_struct._url_dn = urlDn.c_str();
	}

	//url.th
	signature = "\"url.th\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string urlTh = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			urlTh += tmpData[i];
		}

		tmp_struct._url_th = urlTh.c_str();
	}

	//expire
	signature = "\"expire\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string expire = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			expire += tmpData[i];
		}

		tmp_struct._expire = expire.c_str();
	}

	//hash
	signature = "\"hash\":{\"value\":\"";
	pos = tmpData.find(signature, 0);
	if (pos != string::npos)
	{
		string hash = "";

		for (unsigned int i = pos + signature.length(); i < tmpData.length(); i++)
		{
			if ((int)tmpData[i] == 0x22)
			{
				break;
			}
			hash += tmpData[i];
		}

		tmp_struct._hash = hash.c_str();
	}

	for (unsigned int i = 0; i < FiletransInfo.size(); i++)
	{
		if (FiletransInfo[i]._file_name.Compare(tmp_struct._file_name) == 0
			&& (FiletransInfo[i]._hash.Compare(tmp_struct._hash) == 0)
			&& (FiletransInfo[i]._key.Compare(tmp_struct._key) == 0))
		{
			return;
		}
	}

	FiletransInfo.push_back(tmp_struct);
}