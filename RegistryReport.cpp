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

	//Product name
	fwprintf(fOut, L"Product name: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, PRODUCTNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Current build
	fwprintf(fOut, L"Current build: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, CURBUILD_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Product id
	fwprintf(fOut, L"Product id: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, PRODUCTID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Product name
	fwprintf(fOut, L"Product name: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, PRODUCTNAME_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Build branch
	fwprintf(fOut, L"Build branch: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, BUILDBRANCH_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Build guid
	fwprintf(fOut, L"Build guid: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, BUILDGUID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Organization
	fwprintf(fOut, L"Organization: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, ORGANIZATION_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Owner
	fwprintf(fOut, L"Owner: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, OWNER_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//System root
	fwprintf(fOut, L"System root: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, SYSROOT_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Release id
	fwprintf(fOut, L"Release id: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, RELEASEID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Edition id
	fwprintf(fOut, L"Edition id: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, EDITIONID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Install type
	fwprintf(fOut, L"Install type: ");
	hr = GetStringRegKey(hKey, CURVERSION_KEY, INSTALLTYPE_STR, wszStrValue);
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

	//Office 32bit 2003 serial key
	fwprintf(fOut, L"Office 32bit 2003 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE32_2003_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2007 serial key
	fwprintf(fOut, L"Office 32bit 2007 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE32_2007_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2010 serial key
	fwprintf(fOut, L"Office 32bit 2010 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE32_2010_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2013 serial key
	fwprintf(fOut, L"Office 32bit 2013 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE32_2013_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 32bit 2016 serial key
	fwprintf(fOut, L"Office 32bit 2016 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE32_2016_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2003 serial key
	fwprintf(fOut, L"Office 64bit 2003 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE64_2003_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2007 serial key
	fwprintf(fOut, L"Office 64bit 2007 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE64_2007_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2010 serial key
	fwprintf(fOut, L"Office 64bit 2010 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE64_2010_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2013 serial key
	fwprintf(fOut, L"Office 64bit 2013 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE64_2013_KEY, DIGITALPRODID_STR, wszStrValue);
	ChkHr(SafePrintString(fOut, wszStrValue, hr));

	//Office 64bit 2016 serial key
	fwprintf(fOut, L"Office 64bit 2016 serial key: ");
	hr = GetStringRegKey(hKey, OFFICE64_2016_KEY, DIGITALPRODID_STR, wszStrValue);
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

	fOut = fopen("REPORT.txt", "w");
	ChkBool(fOut != NULL, CO_E_FAILEDTOCREATEFILE);

	fwprintf(fOut, L"LOCAL MACHINE VALUES\n\n");
	ChkHr(PrintSystemInfo(HKEY_LOCAL_MACHINE, fOut));
	ChkHr(PrintOfficeInfo(HKEY_LOCAL_MACHINE, fOut));

	fwprintf(fOut, L"CURRENT USER VALUES\n\n");
	ChkHr(PrintSystemInfo(HKEY_CURRENT_USER, fOut));
	ChkHr(PrintOfficeInfo(HKEY_CURRENT_USER, fOut));
    
	ChkCleanup();

	if (fOut != NULL) {
		fclose(fOut);
	}

	ChkEpilog();
}

