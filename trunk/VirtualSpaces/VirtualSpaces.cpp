
#include "global.h"
#include "resource.h"

HINSTANCE TheInstance = 0;

bool CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static Controller* control = 0;
    switch (message)
    {
    case WM_INITDIALOG:
        //try
        //{
        //    control = new Controller (hwnd);
        //}
        //catch (WinException e)
        //{
        //    MessageBox (0, e.GetMessage (), "Exception",
        //                MB_ICONEXCLAMATION | MB_OK);
        //    PostQuitMessage(1);
        //}
        //catch (...)
        //{
        //    MessageBox (0, "Unknown", "Exception",
        //                MB_ICONEXCLAMATION | MB_OK);
        //    PostQuitMessage(2);
        //}
        return TRUE;
    case WM_COMMAND:
        //control->Command(hwnd, LOWORD (wParam), HIWORD (wParam));
        return TRUE;
    case WM_HSCROLL:
        //control->Scroll (hwnd, LOWORD (wParam), HIWORD (wParam));
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    case WM_CLOSE:
        //delete control;
        DestroyWindow(hwnd);
        return TRUE;
    }
    return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpCmdLine*/, int nCmdShow)
{
    TheInstance = hInst;
    //_set_new_handler (& NewHandler);

    HWND hDialog = 0;

	hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAINDLG), 0, (DLGPROC)DialogProc);

    if (!hDialog)
    {
        TCHAR buf[100];
        wsprintf(buf, _T("Error x%x"), GetLastError());
        MessageBox(0, buf, _T("CreateDialog"), MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    MSG  msg;
    int status;
    while ((status = GetMessage(&msg, 0, 0, 0)) != 0)
    {
        if (status == -1)
            return -1;
        if (!IsDialogMessage(hDialog, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}
