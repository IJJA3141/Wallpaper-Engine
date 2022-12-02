#include <iostream>

#include "crow.h"
#include <comdef.h>
#include <WbemIdl.h>
#include "back-end.h"

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

IWbemLocator* pLoc = NULL;
IWbemServices* pSvc = NULL;
IEnumWbemClassObject* pEnumerator = NULL;
IWbemClassObject* pclsObj = NULL;

int cpuLOAD = 0;
bool cpuRES = false;
bool initRES = false;

bool initWMI() {
	HRESULT hres;
	pLoc = NULL;
	pSvc = NULL;
	pEnumerator = NULL;

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

	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		std::cout << "Failed to create IWbemLocator object." << " Err code = 0x" << std::hex << hres << std::endl;
		CoUninitialize();
		return false;
	}

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

	std::cout << "Query initialized" << std::endl;
	return true;
}

bool getCPUdata(int* ptrL, int* ptrT) {
	HRESULT hres;
	ULONG uReturn = 0;
	VARIANT vtProp;
	pEnumerator = NULL;
	BSTR tempBSTR = NULL;

	hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor where Name='_Total' "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hres)) {
		std::cout << "Query for operating system name failed." << std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return false;
	}
	
	pclsObj = NULL;

	while (pEnumerator) {
		hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (uReturn == 0) break;

		hres = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
		std::wcout << "BSTR:" << vtProp.bstrVal << std::endl;
		tempBSTR = (vtProp.bstrVal);
		*ptrL = _wtoi64(tempBSTR);

		VariantClear(&vtProp);

		hres = pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		std::wcout << "BSTR:" << vtProp.bstrVal << std::endl;
		tempBSTR = (vtProp.bstrVal);
		*ptrT = _wtoi64(tempBSTR);

		VariantClear(&vtProp);
		pclsObj->Release();
		pclsObj = NULL;
	}

	return true;
}

bool getCPUload(int* ptrO){
	int l1 = 0;
	int l2 = 0;
	int t1 = 0;
	int t2 = 0;
	float res = 0.0;

	if (getCPUdata(&l1, &t1)) {
		Sleep(1000);
		if (getCPUdata(&l2, &t2)) {
			if (l2 == l1 || t2 == t1) {
				std::cout << "l1:" << l1 << " |t1:" << t1 << " |l2:" << l2 << " |t2:" << t2 << std::endl;
				return false;
			}

			res = (1 - (static_cast<float>(l2) - l1) / (t2 - t1)) * 100;
			*ptrO = res;
			return true;
		}
	}
	
	std::cout << "l1:" << l1 << " |t1:" << t1 << " |l2:" << l2 << " |t2:" << t2 << std::endl;
	return false;
}

int main() {
	initRES = initWMI();
	cpuRES = getCPUload(&cpuLOAD);
	std::wcout << "init:" << initRES << " |cpu:" << cpuRES << " |cpu load:" << cpuLOAD << "%" << std::endl;

	serverSetUp();
	app.port(18080).run();
	return 0;
}

/*

NOTE A MOI MEME:
PercentProcessorTime NE DONE PAS LE % DU CPU -->
SUIVRE LA FORMULE DE STACKOVERFLOWw

*/