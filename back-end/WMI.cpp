#include <comdef.h>
#include <WbemIdl.h>
#include <string>
#include <vector>

#pragma comment(lib, "wbemuuid.lib")

#include "WMI.h"

#include <codecvt>

WMIQuery::WMIQuery()
{
	mStrQuery = _bstr_t("WQL");
	mDiskStrQueryLanguage = _bstr_t("SELECT * FROM Win32_LogicalDisk");
	mCpuStrQueryLanguage = _bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor where Name='_Total' ");

	IWbemLocator* pLoc = nullptr;
	HRESULT hres;

	//Query init:
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	pLoc->Release();
}

WMIQuery::~WMIQuery()
{
	pSvc->Release();
}

bool WMIQuery::cpu(__int64* ptrL, __int64* ptrT)
{
	HRESULT hres;
	IEnumWbemClassObject* pEnumerator = nullptr;

	hres = pSvc->ExecQuery(mStrQuery, mCpuStrQueryLanguage, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	if (FAILED(hres))
	{
		pEnumerator->Reset();
		pEnumerator->Release();
		return false;
	}

	ULONG uReturn;
	VARIANT vtProp = VARIANT();
	IWbemClassObject* pclsObj = nullptr;

	while (pEnumerator) {
		hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		hres = NULL;
		if (uReturn == 0) break;

		hres = pclsObj->Get(L"PercentProcessorTime", 0, &vtProp, 0, 0);
		*ptrL = _wtoi64(vtProp.bstrVal);

		VariantClear(&vtProp);

		hres = pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		*ptrT = _wtoi64(vtProp.bstrVal);

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	pEnumerator->Reset();
	pEnumerator->Release();

	return true;
}

bool WMIQuery::disk(std::vector<__int64>* pIVfs, std::vector<__int64>* pIVs, std::vector<std::string>* pSVn)
{
	HRESULT hres;
	IEnumWbemClassObject* pEnumerator = nullptr;

	hres = pSvc->ExecQuery(mStrQuery, mCpuStrQueryLanguage, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	pIVfs->clear();
	pIVs->clear();
	pSVn->clear();

	if (FAILED(hres))
	{
		pEnumerator->Reset();
		pEnumerator->Release();
		return false;
	}

	ULONG uReturn;
	VARIANT vtProp = VARIANT();
	IWbemClassObject* pclsObj = nullptr;

	while (pEnumerator) {
		hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		hres = NULL;
		if (uReturn == 0) break;

		hres = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		pSVn->push_back(_str_t(vtProp.bstrVal));

		VariantClear(&vtProp);

		hres = pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
		pIVs->push_back((_wtoi64(vtProp.bstrVal) / 1024 / 1024 / 1024));

		VariantClear(&vtProp);

		hres = pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
		pIVfs->push_back((_wtoi64(vtProp.bstrVal) / 1024 / 1024 / 1024));

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	pEnumerator->Reset();
	pEnumerator->Release();
	
	return true;
}

std::string WMIQuery::_str_t(BSTR source) {
	std::wstring res;
	res = _bstr_t(source);

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(res);
}