#pragma once

#include "global.h"

class Control
{
public:
	Control(HWND hwndParent, int id, bool initialState);
	~Control();

	void Hide();
	void Show();

	bool IsVisible();
	void SetFocus();

	void Enable();
	void Disable();

	HWND Hwnd() const;

protected:
	HWND _hWnd;
};
