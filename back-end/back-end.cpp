#include <iostream>

#include "crow.h"
#include <comdef.h>
#include <WbemIdl.h>
#include "back-end.h"

#pragma comment(lib, "wbemuuid.lib")

class WMIQuery
{
public:
	WMIQuery();
	~WMIQuery();

	IWbemLocator* pLoc;
	IWbemServices* pSvc;
	IEnumWbemClassObject* pEnumerator;
	IWbemClassObject* pclsObj;
private:

};

WMIQuery::WMIQuery()
{
	pLoc = NULL;
	pSvc = NULL;
	pEnumerator = NULL;
	pclsObj = NULL;

	HRESULT hres;
	pLoc = NULL;
	pSvc = NULL;
	pEnumerator = NULL;

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		std::cout << "Failed to initialize COM library. Error code = 0x" << std::hex << hres << std::endl;
		return;
	}

	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hres)) {
		std::cout << "Failed to initialize security. Error code = 0x" << std::hex << hres << std::endl;
		CoUninitialize();
		return;
	}

	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		std::cout << "Failed to create IWbemLocator object." << " Err code = 0x" << std::hex << hres << std::endl;
		CoUninitialize();
		return;
	}

	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) {
		std::cout << "Could not connect. Error code = 0x" << std::hex << hres << std::endl;
		pLoc->Release();
		CoUninitialize();
		return;
	}

	std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hres)) {
		std::cout << "Could not set proxy blanket. Error code = 0x" << std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	std::cout << "Query initialized" << std::endl;
}

WMIQuery::~WMIQuery()
{
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}

WMIQuery q = WMIQuery();

int cpuLOAD = 0;
bool cpuRES = false;
bool initRES = false;

crow::SimpleApp app;
crow::json::wvalue ConstRES = NULL;
crow::json::wvalue refreshRES = NULL;

bool getCPUdata(int* ptrL, int* ptrT) {
	HRESULT hres;
	ULONG uReturn = 0;
	VARIANT vtProp;
	q.pEnumerator = NULL;
	BSTR tempBSTR = NULL;

	hres = q.pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor where Name='_Total' "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &q.pEnumerator);
	if (FAILED(hres)) {
		std::cout << "Query for operating system name failed." << std::hex << hres << std::endl;
		q.pSvc->Release();
		q.pLoc->Release();
		CoUninitialize();
		return false;
	}
	
	q.pclsObj = NULL;

	while (q.pEnumerator) {
		hres = q.pEnumerator->Next(WBEM_INFINITE, 1, &q.pclsObj, &uReturn);
		if (uReturn == 0) break;

		hres = q.pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
		tempBSTR = (vtProp.bstrVal);
		*ptrL = _wtoi64(tempBSTR);

		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		tempBSTR = (vtProp.bstrVal);
		*ptrT = _wtoi64(tempBSTR);

		VariantClear(&vtProp);
		q.pclsObj->Release();
		q.pclsObj = NULL;
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
				return false;
			}
			std::wcout << L"DL:" << l2 - l1 << L"\nDT:" << t2 - t1 << std::endl;
			res = (1 - (static_cast<float>(l2) - l1) / (t2 - t1)) * 100;
			*ptrO = res;
			std::cout << *ptrO << "%" << std::endl;

			return true;
		}
	}

	return false;
}

void serverSetUp() {
	CROW_ROUTE(app, "/getConst")([]() {
		return "not implemented yet !";
	});

	CROW_ROUTE(app, "/refresh")([]() {
		if (getCPUload(&cpuLOAD)) {
			refreshRES["cpu"] = cpuLOAD;
		} else {
			refreshRES["cpu"] = "NA";
		}

		return refreshRES;
	});
}

int main() {
	getCPUload(&cpuLOAD);
	
	serverSetUp();
	app.port(18080).run();

	return 0;
}