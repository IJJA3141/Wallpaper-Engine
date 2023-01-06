#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext.h>
#include <QWindow>

#include <mfapi.h>
#include <mfidl.h>
#include <Mferror.h>
#include <comdef.h>

#include "Method.h"

#pragma comment(lib, "mf.lib")

static void test_MFCreateMediaType(void)
{
    HRESULT hr;
    IMFMediaType* mediatype;

    hr = MFStartup(MF_VERSION);

    if (0)
    {
        /* Crash on Windows Vista/7 */
        hr = MFCreateMediaType(NULL);
    }

    hr = MFCreateMediaType(&mediatype);

    MFShutdown();
}

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<Method>("Method", 1, 0, "Method");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject* m_rootObject = engine.rootObjects().first();
    if (m_rootObject)
    {
        QWindow* window = qobject_cast<QWindow*>(m_rootObject);
        if (window)
        {
            HWND wid = (HWND)window->winId();
        }
    }

    return app.exec();
}
