#pragma once

class notesPopup
{
public:
    notesPopup(HINSTANCE hInstance);
    ~notesPopup();

    void NewWindow();
    void CloseWindow();
private:
    const wchar_t* m_className = L"notesPopup";
    
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

    HWND m_hWnd;
    HMENU m_hMenu;

    //std::array<HWND> text;

    bool m_close = false;
};

class page
{
public:
    page(HWND parent);
private:
    HWND m_input;
    HWND m_style;
};