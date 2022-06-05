#pragma once
#include <vector>
using namespace std;

//휘발성 정보 추출 관련 구조체- 네이트온 사용자 정보 추출

#define FRIENDSINFO 0x01
#define MESSAGEINFO 0x02
#define FILETRANSINFO 0x03

typedef struct _FRIENDSLIST{
	CString _id;
	__int64 dwScanOffset;

}_FRIENDSLIST;

typedef struct _MESSAGE{
	CString _sender_id;
	CString _receiver_id;
	CString _message_content;
	__int64 dwScanOffset;
}_MESSAGE;

typedef struct _FILETRANS{
	CString _key;
	CString _type;
	CString _file_name;
	CString _MIME;
	CString _size;
	CString _url_href;
	CString _url_dn;
	CString _url_th;
	CString _expire;
	CString _hash;
	__int64 dwScanOffset;
}_FILETRANS;

class CNateInfoExtract
{
public:
	CNateInfoExtract(void);
	~CNateInfoExtract(void);

protected:
	int SearchSignature(char* temp_buf,int start_loc,char flag);
	void Analysis(char *strBuffer,int dwSize, UINT64 dwReadOffs,char flag);
	void FriendsInfoExtract(char* temp_buf, int offset);
	void MessageInfoExtract(char* temp_buf, int offset);
	void FileTransInfoExtract(char* temp_buf,int offset);

public:
	vector <_FRIENDSLIST> Friendsinfo;
	vector <_MESSAGE> MessageInfo;
	vector <_FILETRANS> FiletransInfo;

public:
	int MAX_BUF_SIZE;
	UINT64 dwScanOffset;

	bool NatUserInfoExtract(char *strBuffer,int dwSize, UINT64 dwReadOffset);
};

