#include "TrayIcon.h"

TrayIcon::TrayIcon(HWND hwnd, UINT id, HICON icon, bool isBalooned, TCHAR *toolTip, TCHAR *toolTipTitle)
{
	this->hwnd = hwnd;
	oldIconData = Shell32Version < MAKEDLLVERULL(5, 0, 0, 0);

	if (Shell32Version >= MAKEDLLVERULL(6, 0, 0, 0))
	{
		iconDataSize = sizeof(NOTIFYICONDATA);
		this->isBalooned = isBalooned;
	}
	else if (Shell32Version >= MAKEDLLVERULL(5, 0, 0, 0))
	{
		iconDataSize = NOTIFYICONDATA_V2_SIZE;
		this->isBalooned = isBalooned;
	}
	else
	{
		iconDataSize = NOTIFYICONDATA_V1_SIZE;
		this->isBalooned = false;
	}
	
	ZeroMemory(&nid, iconDataSize);	
	nid.cbSize = iconDataSize;
	nid.uID = id;
	nid.hWnd = hwnd;
	nid.hIcon = icon;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	if (this->isBalooned)
	{
		nid.uFlags |= NIF_INFO;
		_tcsncpy(nid.szInfoTitle, toolTipTitle, 63);
		nid.szInfoTitle[64] = NULL;
	}
	nid.uCallbackMessage = WM_TRAYICON;
	visible = false;
	SetTooltip(toolTip);
}

TrayIcon::~TrayIcon(void)
{
}

TCHAR* TrayIcon::GetToolTip(void)
{
	return toolTip;
}

TCHAR *TrayIcon::SetTooltip(const TCHAR *toolTip)
{
	TCHAR *tip = GetToolTip();
	size_t tipLen = _tcslen(toolTip);
	if (oldIconData)
	{
		_tcsncpy(nid.szTip, toolTip, 63);
		nid.szTip[64] = NULL;
	}
	else if (isBalooned)
	{
		_tcsncpy(nid.szInfo, toolTip, 255);
		nid.szTip[256] = NULL;
	}
	else
	{
		_tcsncpy(nid.szTip, toolTip, 127);
		nid.szTip[128] = NULL;
	}
	_tcscpy(this->toolTip, nid.szTip);

	if(visible)
		Update();

	return tip;
}

void TrayIcon::Show()
{
	if (!visible)
	{
		Shell_NotifyIcon(NIM_ADD, &nid);
		visible = true;
	}
	else
		Update(); // ?????
}

void TrayIcon::Hide()
{
	if (visible)
	{
		Shell_NotifyIcon(NIM_DELETE, &nid);
		visible = false;
	}
}

void TrayIcon::Update()
{
	Shell_NotifyIcon(NIM_MODIFY, &nid);
}