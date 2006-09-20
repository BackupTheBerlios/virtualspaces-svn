#include "Control.h"

Control::Control(HWND hwndParent, int id, bool initialState = true) : _hWnd(GetDlgItem(hwndParent, id))
{
	if (initialState == false)
		Disable();
}

Control::~Control(void)
{
}

void Control::Hide()
{
	::ShowWindow(_hWnd, SW_HIDE);
}

void Control::Show()
{
	::ShowWindow(_hWnd, SW_SHOW);
}

bool Control::IsVisible()
{
	return ::IsWindowVisible(_hWnd) != 0;
}

void Control::SetFocus()
{
	::SetFocus(_hWnd);
}

void Control::Enable()
{
	::EnableWindow(_hWnd, TRUE);
}

void Control::Disable()
{
	::EnableWindow(_hWnd, FALSE);
}

HWND Control::Hwnd() const
{
	return _hWnd;
}
