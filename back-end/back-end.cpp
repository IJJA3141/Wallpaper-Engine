#include "framework.h"
#include "notesPopup.h"
#include "back-end.h"
#include <future>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    notesPopup npp = notesPopup(hInstance);
    std::thread worker(&notesPopup::NewWindow, &npp);
    worker.join();
    return 0;
}