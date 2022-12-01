#include <iostream>

#include "crow.h"
#include <comdef.h>
#include <WbemIdl.h>

#pragma comment(lib, "wbemuuid.lib")

crow::SimpleApp app;

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
		return "not implemented yet !";
		});

	CROW_ROUTE(app, "/refresh")([]() {
		return "not implemented yet !";
		});
}

IEnumWbemClassObject* pEnumerator = NULL;
int cpuLOAD = NULL;
BOOL cpuRES = NULL;

bool initWMI() {
	HRESULT hres;

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		std::cout << "Failed to initialize COM library. Error code = 0x" << std::hex << hres << std::endl;
		return false;
	}

	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hres)) {
		std::cout << "Failed to initialize security. Error code = 0x" << std::hex << hres << std::endl;
		CoUninitialize();
		return false;
	}

	IWbemLocator* pLoc = NULL;

	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		std::cout << "Failed to create IWbemLocator object." << " Err code = 0x" << std::hex << hres << std::endl;
		CoUninitialize();
		return false;
	}

	IWbemServices* pSvc = NULL;

	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) {
		std::cout << "Could not connect. Error code = 0x" << std::hex << hres << std::endl;
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hres)) {
		std::cout << "Could not set proxy blanket. Error code = 0x" << std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor where Name='_Total' "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hres)) {
		std::cout << "Query for operating system name failed." << std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	std::cout << "Query initialized" << std::endl;
	return true;
}

bool getCPUload(int& load) {
	pEnumerator = NULL;
	IWbemClassObject* pclsObj = NULL;
	ULONG uReturn = 0;

	std::cout << "before the start of pEnumarator process" << std::endl;
	if (initWMI()) {
		std::cout << "start pEnumarator process" << std::endl;
		while (pEnumerator) {
			std::cout << "after the start of pEnumarator process" << std::endl;
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (uReturn == 0) {
				break;
			}

			VARIANT vtProp;

			hr = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
			if (hr != WBEM_S_NO_ERROR) {
				if (pclsObj) {
					VariantClear(&vtProp);
					pclsObj->Release();
					pclsObj = NULL;
				}
				break;
			}
			std::wcout << "BSTR:" << vtProp.bstrVal << "\nUINT:" << vtProp.uintVal << std::endl;
			(vtProp.bstrVal);
			VariantClear(&vtProp);
			pclsObj->Release();
			pclsObj = NULL;
		}
	}

	return true;
}

int main() {
	cpuRES = getCPUload(cpuLOAD);

	std::wcout << "cpu load:" << cpuRES << std::endl;

	serverSetUp();
	app.port(18080).run();
	return 0;
}

/*

NOTE A MOI MEME:
PercentProcessorTime NE DONE PAS LE % DU CPU -->
SUIVRE LA FORMULE DE STACKOVERFLOWw

*/