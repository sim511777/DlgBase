#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "resource.h"

HINSTANCE g_hInst;
HWND hDlg;
HWND hLbx;

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
void Log(const LPCWSTR format, ...);
void ClearLog();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
    g_hInst = hInstance;
    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);
    return 0;
}

int i = 0;
INT_PTR CALLBACK MainDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage) {
    case WM_INITDIALOG:
        hDlg = hWnd;
        hLbx = GetDlgItem(hDlg, IDC_LISTLOG);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDCANCEL:
            EndDialog(hDlg, 0);
            return TRUE;
        case IDC_BTN_CPPADD:
            Log(TEXT("CppAdd : %d"), i++);
            return TRUE;
        case IDC_BTN_CSADD:
            Log(TEXT("CsAdd : %d"), i++);
            return TRUE;
        case IDC_BTN_CLEARLOG:
            ClearLog();
            return TRUE;
        }
        return FALSE;
    }

    return FALSE;
}

void Log(const LPCWSTR format, ...) {
    va_list args;
    va_start(args, format);
    TCHAR buf[1024];
    vswprintf_s(buf, 1024, format, args);
    va_end(args);

    SendMessage(hLbx, LB_ADDSTRING, 0, (LPARAM)buf);
    LRESULT cnt = SendMessage(hLbx, LB_GETCOUNT, 0, 0);
    SendMessage(hLbx, LB_SETTOPINDEX, cnt - 1, 0);
}

void ClearLog() {
    SendMessage(hLbx, LB_RESETCONTENT, 0, 0);
}

