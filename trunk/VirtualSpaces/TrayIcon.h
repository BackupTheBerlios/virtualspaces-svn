// TrayIcon class

#pragma once

#include "global.h"

const UINT WM_TRAYICON = WM_USER + 0x400;

class TrayIcon
{
public:
	TrayIcon(HWND hwnd, UINT id, HICON icon, bool isBalooned, TCHAR *toolTip, TCHAR *toolTipTitle);
	~TrayIcon(void);

	//DECLARE_PROPERTY(TCHAR*, getToolTip, setTooltip, TrayIcon, ToolTip);

	TCHAR* GetToolTip(void);
	TCHAR* SetTooltip(const TCHAR *toolTip);

	void Show();
	void Hide();
	void Update();

private:
	NOTIFYICONDATA nid;
	HWND hwnd;
	bool isBalooned;
	TCHAR *toolTip;
	TCHAR *toolTipTitle;
	bool visible;

	DWORD iconDataSize;
	bool oldIconData;
};
