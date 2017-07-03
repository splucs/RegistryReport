// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include "windows.h"

#define ChkProlog()		HRESULT _hr = NOERROR
#define ChkHr(hr)		_hr = (hr); if (_hr != NOERROR) goto _cleanup
#define ChkCleanup()	_cleanup:
#define ChkEpilog()		return _hr
#define ChkNoCleanup()	ChkCleanup(); ChkEpilog()
#define ChkWin32(e)		ChkHr(HRESULT_FROM_WIN32(e))
#define ChkSetHr(hr)	_hr = (hr);
#define ChkBool(b, hr)	if (!(b)) ChkHr(hr)
#define ChkArg(p)		if (!(p)) ChkHr(E_INVALIDARG)

#define MAX_STR_SIZE 1024

#include "RegAddresses.h"



// TODO: reference additional headers your program requires here
