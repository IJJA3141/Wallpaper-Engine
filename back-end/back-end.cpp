#define _WIN32_DCOM
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#include <array>

#pragma comment(lib, "wbemuuid.lib")

class Query {
private:
    HRESULT _hres;
    IWbemLocator* _pLoc = NULL;
    IWbemServices* _pSvc = NULL;
    IEnumWbemClassObject* _pEnumerator = NULL;

public:
    Query() {
        _hres = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(_hres))
        {
            std::cout << "Qurery: Failed to initialize COM library. Error code = 0x"
                << std::hex <<_hres << std::endl;
            return;
        }

        _hres = CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities 
            NULL                         // Reserved
        );


        if (FAILED(_hres))
        {
            std::cout << "Query: Failed to initialize security. Error code = 0x"
                << std::hex << _hres << std::endl;
            CoUninitialize();
            return;
        }        

        _hres = CoCreateInstance(
            CLSID_WbemLocator,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID*)&_pLoc);

        if (FAILED(_hres))
        {
            std::cout << "Query: Failed to create IWbemLocator object."
                << " Err code = 0x"
                << std::hex << _hres << std::endl;
            CoUninitialize();
            return;
        }

        _hres = _pLoc->ConnectServer(
            _bstr_t(L"ROOT\\CIMV2"),  // Object path of WMI namespace
            NULL,                     // User name. NULL = current user
            NULL,                     // User password. NULL = current
            0,                        // Locale. NULL indicates current
            NULL,                     // Security flags.
            0,                        // Authority (for example, Kerberos)
            0,                        // Context object 
            &_pSvc                    // pointer to IWbemServices proxy
        );

        if (FAILED(_hres))
        {
            std::cout << "Query: Could not connect. Error code = 0x"
                << std::hex << _hres << std::endl;
            _pLoc->Release();
            CoUninitialize();
            return;
        }

        std::cout << "Query: Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

        _hres = CoSetProxyBlanket(
            _pSvc,                       // Indicates the proxy to set
            RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
            RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
            NULL,                        // Server principal name 
            RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
            RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
            NULL,                        // client identity
            EOAC_NONE                    // proxy capabilities 
        );

        if (FAILED(_hres))
        {
            std::cout << "Query: Could not set proxy blanket. Error code = 0x"
                << std::hex << _hres << std::endl;
            _pSvc->Release();
            _pLoc->Release();
            CoUninitialize();
            return;
        }

        return;
    }

    ~Query() {
        _pSvc->Release();
        _pLoc->Release();
        _pEnumerator->Release();
        CoUninitialize();
    }

    BSTR Get(std::string target, std::array<BSTR, size_t()>& req) {
        
        std::string str = "SELECT * FROM " + std::string(target);
        BSTR QueryMessage = bstr_t(str.c_str());
        
        _pEnumerator = NULL;
        _hres = _pSvc->ExecQuery(
            bstr_t("WQL"),
            QueryMessage,
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &_pEnumerator);

        if (FAILED(_hres))
        {
            std::cout << "Query for operating system name failed."
                << " Error code = 0x"
                << std::hex << _hres << std::endl;
            _pSvc->Release();
            _pLoc->Release();
            CoUninitialize();
            return NULL;               // Program has failed.
        }


        // Step 7: -------------------------------------------------
        // Get the data from the query in step 6 -------------------

        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (_pEnumerator)
        {
            HRESULT hr = _pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn)
            {
                break;
            }

            VARIANT vtProp;

            VariantInit(&vtProp);
            // Get the value of the Name property
            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            std::wcout << " OS Name : " << vtProp.bstrVal << std::endl;

            return vtProp.bstrVal;

            VariantClear(&vtProp);

            pclsObj->Release();
        }
    }
};

int main()
{
    Query q = Query();
    std::string a = "Win32_VideoController";
    std::string b = "Win32_Processor";

    std::array<std::string, 4> l{ "Name", "Name", "Name", "Name" };
    BSTR o = q.Get(a, &l);
    BSTR p = q.Get(b, );

    std::wcout << p << std::endl;
}