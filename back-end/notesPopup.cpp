#include <Windows.h>
#include "notesPopup.h"
#include <future>

#define WIDTH 700
#define HEIGHT 1100

COLORREF color = RGB(0x17, 0x17, 0x17);
HBRUSH bhr = ::CreateSolidBrush(color);

//notesPopup
notesPopup::notesPopup(HINSTANCE hInstance)
{
    WNDCLASSW wc = { 0 };
    m_hWnd = { 0 };
    m_hMenu = { 0 };

    wc.hbrBackground = bhr;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = m_className;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_DROPSHADOW;

    RegisterClassW(&wc);

    return;
}

notesPopup::~notesPopup()
{
    DestroyWindow(m_hWnd);
    return;
}

void notesPopup::NewWindow()
{
    m_hWnd = CreateWindowW(m_className, L"My Window", WS_VISIBLE | WS_POPUPWINDOW, (GetSystemMetrics(SM_CXSCREEN) - WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) / 2, WIDTH, HEIGHT, NULL, NULL, NULL, NULL);
    m_hMenu = CreateMenu();
    page p = page(m_hWnd);

    AppendMenu(m_hMenu, MF_STRING, 1, L"File");
    //SetMenu(m_hWnd, m_hMenu);

    MSG message = { 0 };
    while (GetMessage(&message, NULL, NULL, NULL) && !m_close)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void notesPopup::CloseWindow()
{
    m_close = true;
    return;
}

LRESULT CALLBACK notesPopup::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_CTLCOLORSTATIC:
    {
        LRESULT lRet = 0;
        HDC hdc = (HDC)wparam;
        HWND hwnd = (HWND)lparam;

        // if multiple edits and only one should be colored, use
        // the control id to tell them apart.
        //
        if (true)//GetDlgCtrlID(hwnd) == IDC_EDIT_RECOLOR)
        {
            SetBkColor(hdc, color); // Set to red
            SetDCBrushColor(hdc, color);
            lRet = (LRESULT)GetStockObject(DC_BRUSH); // return a DC brush.
        }
        else
        {
            lRet = DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    break;
    case WM_COMMAND:
        switch (wparam)
        {
        case 1:
            MessageBeep(MB_OK);
            break;
        }
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, message, wparam, lparam);
    }
}

//page
page::page(HWND parent)
{
    m_style = CreateWindowW(L"Static", L"~", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 16, 50, 16, parent, NULL, NULL, NULL);
    m_input = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 50, 16, WIDTH - 100, 16, parent, NULL, NULL, NULL);
    return;
}
