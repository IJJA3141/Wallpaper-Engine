#include "Creamy.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QDebug>

#include <systemmediatransportcontrolsinterop.h>
#include <Unknwn.h>
#include <objbase.h>
#include <combaseapi.h>

int appInit(QApplication* app, Creamy* mainWindow)
{
    mainWindow->show();
    mainWindow->showFullScreen();
    return app->exec();
}

int com()
{
    ISystemMediaTransportControlsInterop* p = nullptr;

    HRESULT hres;
    hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    //hres = CoCreateInstance(CLSID_PSGenObject, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p));
    if (FAILED(hres))
    {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Creamy mainWindow;

    qDebug("1");
    appInit(&app, &mainWindow);
    qDebug("2");

    HRESULT hr;
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        qDebug("pas marche");
    }
    else
    {
        qDebug("marche");
    }
    CoUninitialize();
    return 0;
}