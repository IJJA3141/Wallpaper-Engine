#include <WbemIdl.h>
#include <iostream>
#include <comdef.h>
#include "WMI.h"
#include "cpu.h"

CPU::CPU()
{
	cpuLOAD = 0;
}

CPU::~CPU()
{
}

bool CPU::getCPUdata(int* ptrL, int* ptrT) {
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
		std::wcout << "BSTR:" << tempBSTR << " |INT:" << _wtoi64(tempBSTR) << std::endl;
		*ptrL = _wtoi64(tempBSTR);

		tempBSTR = NULL;
		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		tempBSTR = (vtProp.bstrVal);
		std::wcout << "BSTR:" << tempBSTR << " |INT:" << _wtoi64(tempBSTR) << std::endl;
		*ptrT = _wtoi64(tempBSTR);

		tempBSTR = NULL;
		VariantClear(&vtProp);
		q.pclsObj->Release();
		q.pclsObj = NULL;
	}

	return true;
}

bool CPU::getCPUload(int* ptrO) {
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

int CPU::int_getCPUload() {
	if (getCPUload(&cpuLOAD)) {
		return cpuLOAD;
	}
	else
	{
		return 101;
	}
}

CPU cpu = CPU();