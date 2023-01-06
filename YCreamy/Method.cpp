#include "Method.h"
#include <qdebug.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Mferror.h>
#include <comdef.h>

#pragma comment(lib, "mf.lib")

Method::Method(QObject* parent) : QObject(parent)
{
    qDebug() << "Hi!";
}

void Method::Test()
{
	qDebug() << "Test Started!";
    
    HRESULT hr = S_OK;   
    /*
    IMFGetService* pGetService = NULL;
    IMFRateControl* pRateControl = NULL;

    hr = pMediaSession->QueryInterface(
        IID_IMFGetService,
        (void**)&pGetService);

    if (SUCCEEDED(hr))
    {
        hr = pGetService->GetService(
            MF_RATE_CONTROL_SERVICE,
            IID_IMFRateControl,
            (void**)&pRateControl);
    }
    if (SUCCEEDED(hr))
    {
        // Use IMFRateControl. (Not shown.)
    }

    // Clean up.
    SAFE_REELEASE(pGetService);
    SAFE_RELEASE(pRateControl);

    */
    if (FAILED(hr))
    {
        _com_error err(hr);
        LPCTSTR errMsg = err.ErrorMessage();
        qDebug() << "MFCreateMediaSession failed";
        qDebug() << errMsg;
    }
    else
    {
        qDebug() << "fine";
    }

	return;
}