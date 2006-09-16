#pragma once

#define _WIN32_IE 0x0600

#include <windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <shlwapi.h>

ULONGLONG GetDllVersion(TCHAR* lpszDllName);

ULONGLONG Shell32Version = GetDllVersion(_T("shell32.dll"));
ULONGLONG Comctl32Version = GetDllVersion(_T("comctl32.dll"));