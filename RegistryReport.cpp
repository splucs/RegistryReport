// RegistryReport.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

HRESULT
GetRegKey(
	HKEY	hKey,
	LPCWSTR wszKeyName,
	LPCWSTR wszValueName,
	LPBYTE	wszValue,
	DWORD	dwType,
	DWORD	dwBufferSize
	)
{
	HKEY	hValues;

	ChkProlog();

	ChkWin32(RegOpenKeyExW(
		hKey,
		wszKeyName,
		0,
		KEY_QUERY_VALUE,
		&hValues)
	);
	ChkWin32(RegQueryValueExW(
		hValues,
		wszValueName,
		0,
		&dwType,
		wszValue,
		&dwBufferSize)
	);

	ChkNoCleanup();
}


HRESULT
GetDWORDRegKey(
	HKEY	hKey,
	LPCWSTR	wszKeyName,
	LPCWSTR	wszValueName,
	DWORD	*dwValue
	)
{
	ChkProlog();

	ChkHr(GetRegKey(
		hKey,
		wszKeyName,
		wszValueName,
		(LPBYTE)dwValue,
		REG_DWORD,
		sizeof(DWORD))
	);

	ChkNoCleanup();
}

HRESULT
GetQWORDRegKey(
	HKEY		hKey,
	LPCWSTR		wszKeyName,
	LPCWSTR		wszValueName,
	ULONGLONG	*qwValue
	)
{
	ChkProlog();

	ChkHr(GetRegKey(
		hKey,
		wszKeyName, 
		wszValueName,
		(LPBYTE)qwValue,
		REG_QWORD,
		sizeof(ULONGLONG))
	);

	ChkNoCleanup();
}

HRESULT
GetStringRegKey(
	HKEY		hKey,
	LPCWSTR		wszKeyName,
	LPCWSTR		wszValueName,
	LPWSTR		wszValue
	)
{
	ChkProlog();

	ChkHr(GetRegKey(
		hKey, 
		wszKeyName,
		wszValueName,
		(LPBYTE)wszValue,
		REG_SZ,
		MAX_STR_SIZE)
	);

	ChkNoCleanup();
}

HRESULT
SafePrintDWORD(
	FILE	*fOut,
	DWORD	dwValue,
	HRESULT hr
	)
{
	ChkProlog();

	ChkArg(fOut);
	if (hr == NOERROR) fwprintf(fOut, L"%x\n", dwValue);
	else if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) fwprintf(fOut, L"Key/Value not found\n");
	else if (hr == E_ACCESSDENIED) fwprintf(fOut, L"Access denied, please execute as admin\n");
	else ChkHr(hr);

	ChkNoCleanup();
}

HRESULT
SafePrintQWORD(
	FILE		*fOut,
	ULONGLONG	qwValue,
	HRESULT		hr
)
{
	ChkProlog();

	ChkArg(fOut);
	if (hr == NOERROR) fwprintf(fOut, L"%llx\n", qwValue);
	else if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) fwprintf(fOut, L"Key/Value not found\n");
	else if (hr == E_ACCESSDENIED) fwprintf(fOut, L"Access denied, please execute as admin\n");
	else ChkHr(hr);

	ChkNoCleanup();
}

HRESULT
SafePrintString(
	FILE		*fOut,
	LPCWSTR		wszValue,
	HRESULT		hr
)
{
	ChkProlog();

	ChkArg(fOut);
	ChkArg(wszValue);
	if (hr == NOERROR) fwprintf(fOut, L"%s\n", wszValue);
	else if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) fwprintf(fOut, L"Key/Value not found\n");
	else if (hr == E_ACCESSDENIED) fwprintf(fOut, L"Access denied, please execute as admin\n");
	else ChkHr(hr);

	ChkNoCleanup();
}

HRESULT
PrintSystemInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------SYSTEM INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Current build
	fwprintf(fOut, L"Current build: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, CURBUILD_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Product name
	fwprintf(fOut, L"Product name: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, PRODUCTNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Product id
	fwprintf(fOut, L"Product id: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, PRODUCTID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Product name
	fwprintf(fOut, L"Product name: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, PRODUCTNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Build branch
	fwprintf(fOut, L"Build branch: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, BUILDBRANCH_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Build guid
	fwprintf(fOut, L"Build guid: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, BUILDGUID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Organization
	fwprintf(fOut, L"Organization: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, ORGANIZATION_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Owner
	fwprintf(fOut, L"Owner: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, OWNER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//System root
	fwprintf(fOut, L"System root: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, SYSROOT_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Release id
	fwprintf(fOut, L"Release id: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, RELEASEID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Edition id
	fwprintf(fOut, L"Edition id: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, EDITIONID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Install type
	fwprintf(fOut, L"Installation type: ");
	hr = GetStringRegKey(hKey, WINNT_CURVERSION_KEY, INSTALLTYPE_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Common files dir
	fwprintf(fOut, L"Common files directory: ");
	hr = GetStringRegKey(hKey, WIN_CURVERSION_KEY, COMMONFILESDIR_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Common files 86 dir
	fwprintf(fOut, L"Common files 86 directory: ");
	hr = GetStringRegKey(hKey, WIN_CURVERSION_KEY, COMMONFILES86DIR_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Program files dir
	fwprintf(fOut, L"Program files directory: ");
	hr = GetStringRegKey(hKey, WIN_CURVERSION_KEY, PROGRAMFILESDIR_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Program files 86 dir
	fwprintf(fOut, L"Program files 86 directory: ");
	hr = GetStringRegKey(hKey, WIN_CURVERSION_KEY, PROGRAMFILES86DIR_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Device path
	fwprintf(fOut, L"Device path: ");
	hr = GetStringRegKey(hKey, WIN_CURVERSION_KEY, PROGRAMFILES86DIR_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Machine / criptography guid
	fwprintf(fOut, L"Machine / criptography guid: ");
	hr = GetStringRegKey(hKey, CRIPTOGRAPHY_KEY, MACHINEGUID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintOfficeInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------OFFICE INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Office 32bit 2003 product id
	fwprintf(fOut, L"Office 32bit 2003 product id: ");
	hr = GetStringRegKey(hKey, OFFICE32_2003_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2007 product id
	fwprintf(fOut, L"Office 32bit 2007 product id: ");
	hr = GetStringRegKey(hKey, OFFICE32_2007_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2010 product id
	fwprintf(fOut, L"Office 32bit 2010 product id: ");
	hr = GetStringRegKey(hKey, OFFICE32_2010_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2013 product id
	fwprintf(fOut, L"Office 32bit 2013 product id: ");
	hr = GetStringRegKey(hKey, OFFICE32_2013_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2016 product id
	fwprintf(fOut, L"Office 32bit 2016 product id: ");
	hr = GetStringRegKey(hKey, OFFICE32_2016_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2003 product id
	fwprintf(fOut, L"Office 64bit 2003 product id: ");
	hr = GetStringRegKey(hKey, OFFICE64_2003_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2007 product id
	fwprintf(fOut, L"Office 64bit 2007 product id: ");
	hr = GetStringRegKey(hKey, OFFICE64_2007_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2010 product id
	fwprintf(fOut, L"Office 64bit 2010 product id: ");
	hr = GetStringRegKey(hKey, OFFICE64_2010_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2013 product id
	fwprintf(fOut, L"Office 64bit 2013 product id: ");
	hr = GetStringRegKey(hKey, OFFICE64_2013_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2016 product id
	fwprintf(fOut, L"Office 64bit 2016 product id: ");
	hr = GetStringRegKey(hKey, OFFICE64_2016_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintLogonInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	DWORD dwValue;
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------LOGON INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Auto admin logon enabled
	fwprintf(fOut, L"Auto admin logon enabled: ");
	hr = GetStringRegKey(hKey, WINLOGON_KEY, AUTOADMIN_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Default domain name
	fwprintf(fOut, L"Default domain name: ");
	hr = GetStringRegKey(hKey, WINLOGON_KEY, DEFAULT_DOMAIN_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Default user name
	fwprintf(fOut, L"Default user name: ");
	hr = GetStringRegKey(hKey, WINLOGON_KEY, DEFAULT_USER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Screen saver time
	fwprintf(fOut, L"Screen saver time: ");
	hr = GetStringRegKey(hKey, WINLOGON_KEY, SCREENSAVER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Shell exe
	fwprintf(fOut, L"Shell exe: ");
	hr = GetStringRegKey(hKey, WINLOGON_KEY, SHELL_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Shutdown flags
	fwprintf(fOut, L"Shutdown flags: ");
	hr = GetDWORDRegKey(hKey, WINLOGON_KEY, SHUTDOWNFLAGS_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Last logged on user
	fwprintf(fOut, L"Last logged on user: ");
	hr = GetStringRegKey(hKey, LOGON_KEY, LASTUSER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Last logged on user SID
	fwprintf(fOut, L"Last logged on user SID: ");
	hr = GetStringRegKey(hKey, LOGON_KEY, LASTUSERSID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Logon startup sound
	fwprintf(fOut, L"Startup sound disabled: ");
	hr = GetDWORDRegKey(hKey, LOGONANIMATION_KEY, DISABLESTARTUPSOUND_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintExplorerInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	DWORD dwValue;
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------WINDOWS EXPLORER INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Lock screen slideshow
	fwprintf(fOut, L"Lock screen slideshow: ");
	hr = GetDWORDRegKey(hKey, LOCKSCREEN_KEY, SLIDESHOWENABLED_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Show hidden files
	fwprintf(fOut, L"Show hidden files: ");
	hr = GetDWORDRegKey(hKey, EXPLORERADV_KEY, HIDDEN_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Show super hidden files
	fwprintf(fOut, L"Show super hidden files: ");
	hr = GetDWORDRegKey(hKey, EXPLORERADV_KEY, SUPERHIDDEN_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Enable startup menu
	fwprintf(fOut, L"Enable startup menu: ");
	hr = GetDWORDRegKey(hKey, EXPLORERADV_KEY, ENABLESTARTMENU_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Filter
	fwprintf(fOut, L"Filter: ");
	hr = GetDWORDRegKey(hKey, EXPLORERADV_KEY, FILTER_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Hide file extension
	fwprintf(fOut, L"Hide file extension: ");
	hr = GetDWORDRegKey(hKey, EXPLORERADV_KEY, HIDEFILEEXT_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));

	//Last edited registry key
	fwprintf(fOut, L"Last edited registry key: ");
	hr = GetStringRegKey(hKey, APPLETS_KEY, LASTEDITEDREG_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintVolativeInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------VOLATILE INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Volatile app data
	fwprintf(fOut, L"Volatile app data: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, APPDATA_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile homedrive
	fwprintf(fOut, L"Volatile homedrive: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, HOMEDRIVE_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile homepath
	fwprintf(fOut, L"Volatile homepath: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, HOMEPATH_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile local app data
	fwprintf(fOut, L"Volatile local app data: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, LOCALAPPDATA_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile logon server
	fwprintf(fOut, L"Volatile logon server: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, LOGONSERVER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile user domain
	fwprintf(fOut, L"Volatile user domain: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, USERDOMAIN_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile user name
	fwprintf(fOut, L"Volatile user name: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, USERNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Volatile user profile
	fwprintf(fOut, L"Volatile user profile: ");
	hr = GetStringRegKey(hKey, VOLATILE_KEY, USERPROFILE_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintTcpipInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------TCPIP INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//TCPIP host name
	fwprintf(fOut, L"TCPIP host name: ");
	hr = GetStringRegKey(hKey, TCPIP_KEY, HOSTNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//TCPIP domain
	fwprintf(fOut, L"TCPIP domain: ");
	hr = GetStringRegKey(hKey, TCPIP_KEY, DOMAIN_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintPaintInfo(
	HKEY	hKey,
	FILE	*fOut
	)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	DWORD dwValue;
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------PAINT INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Last opened file 1
	fwprintf(fOut, L"Last opened file 1: ");
	hr = GetStringRegKey(hKey, PAINT_KEY, PAINTLASTUSED1_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Last opened file 2
	fwprintf(fOut, L"Last opened file 2: ");
	hr = GetStringRegKey(hKey, PAINT_KEY, PAINTLASTUSED2_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Last opened file 3
	fwprintf(fOut, L"Last opened file 3: ");
	hr = GetStringRegKey(hKey, PAINT_KEY, PAINTLASTUSED3_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Last opened file 4
	fwprintf(fOut, L"Last opened file 4: ");
	hr = GetStringRegKey(hKey, PAINT_KEY, PAINTLASTUSED4_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Last opened file 5
	fwprintf(fOut, L"Last opened file 5: ");
	hr = GetStringRegKey(hKey, PAINT_KEY, PAINTLASTUSED5_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
PrintTimeInfo(
	HKEY	hKey,
	FILE	*fOut
)
{
	WCHAR wszStrValue[MAX_STR_SIZE];
	DWORD dwValue;
	HRESULT hr;

	ChkProlog();

	fwprintf(fOut, L"----------TIMEZONE INFORMATION (%s)----------\n", hKey == HKEY_LOCAL_MACHINE ? L"HKLM" : L"HKCU");

	//Dynamic daylight disabled
	fwprintf(fOut, L"Dynamic daylight disabled: ");
	hr = GetDWORDRegKey(hKey, TIMEZONE_KEY, DYNDAYLIGHTDISABLED_DW, &dwValue);
	ChkHr(SafePrintDWORD(fOut, dwValue, hr));
	
	//Time zone name
	fwprintf(fOut, L"Time zone name: ");
	hr = GetStringRegKey(hKey, TIMEZONE_KEY, TIMEZONENAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	fwprintf(fOut, L"\n");

	ChkNoCleanup();
}

HRESULT
main(
	VOID
	)
{
	FILE * fOut = NULL;

	ChkProlog();

	fOut = fopen("SYSTEM_REPORT.txt", "w");
	ChkBool(fOut != NULL, CO_E_FAILEDTOCREATEFILE);

	ChkHr(PrintSystemInfo(HKEY_LOCAL_MACHINE, fOut));
	ChkHr(PrintOfficeInfo(HKEY_CURRENT_USER, fOut));
	ChkHr(PrintLogonInfo(HKEY_LOCAL_MACHINE, fOut));
	ChkHr(PrintExplorerInfo(HKEY_CURRENT_USER, fOut));
	ChkHr(PrintVolativeInfo(HKEY_CURRENT_USER, fOut));
	ChkHr(PrintTcpipInfo(HKEY_LOCAL_MACHINE, fOut));
	ChkHr(PrintPaintInfo(HKEY_CURRENT_USER, fOut));
	ChkHr(PrintTimeInfo(HKEY_LOCAL_MACHINE, fOut));
    
	ChkCleanup();

	if (fOut != NULL) {
		fclose(fOut);
	}

	ChkEpilog();
}

