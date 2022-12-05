#include <WbemIdl.h>
#include <comdef.h>
#include "WMI.h"
#include "cpu.h"

CPU::CPU()
{
	ml = 0;
}

CPU::~CPU()
{
	delete& ml;
	delete this;
}

bool CPU::fetch_CPU_data(long long* ptrL, long long* ptrT) {
	HRESULT hres;
	ULONG uReturn = 0;
	VARIANT vtProp;
	q.pEnumerator = NULL;
	BSTR tempBSTR = NULL;

	hres = q.pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PerfRawData_PerfOS_Processor where Name='_Total' "), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &q.pEnumerator);
	if (FAILED(hres)) {
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

		tempBSTR = NULL;
		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"TimeStamp_Sys100NS", 0, &vtProp, 0, 0);
		tempBSTR = (vtProp.bstrVal);
		*ptrT = _wtoi64(tempBSTR);

		tempBSTR = NULL;
		VariantClear(&vtProp);
		q.pclsObj->Release();
		q.pclsObj = NULL;
	}
	q.pEnumerator = NULL;

	return true;
}

bool CPU::calculate_CPU_load(int* ptrO) {
	long long l1 = 0;
	long long l2 = 0;
	long long t1 = 0;
	long long t2 = 0;
	float res = 0.0;

	if (fetch_CPU_data(&l1, &t1)) {
		Sleep(1000);

		if (fetch_CPU_data(&l2, &t2)) {
			if (l2 == l1 || t2 == t1) {
				return false;
			}
			res = (1 - (static_cast<float>(l2) - l1) / (t2 - t1)) * 100;
			*ptrO = res;

			return true;
		}
	}

	return false;
}

int CPU::get() {
	if (calculate_CPU_load(&ml)) {
		return ml;
	}
	else
	{
		return 101;
	}
}

CPU cpu = CPU();