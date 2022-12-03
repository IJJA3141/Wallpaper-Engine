#include <WbemIdl.h>
#include <iostream>
#include <comdef.h>
#include <vector>

#include "WMI.h"

#include "disk.h"
#include "crow/json.h"

std::string bstr_to_str(BSTR source) {
	_bstr_t wrapped_bstr = _bstr_t(source);
	int length = wrapped_bstr.length();
	char* char_array = new char[length];
	strcpy_s(char_array, length + 1, wrapped_bstr);
	return char_array;
}

DISK::DISK() {
	_diskSIZE.clear();
	_diskFREEsize.clear();
	_diskNAME.clear();
	diskARRAY.clear();
}

DISK::~DISK() {
	delete this;
}

bool DISK::getDISKdata(std::vector<int>* size, std::vector<int>* sizeFREE, std::vector<std::string>* name) {
	std::vector<int> ts;
	std::vector<int> tsf;
	std::vector<std::string> tn;

	HRESULT hres;
	ULONG uReturn = 0;
	VARIANT vtProp;
	q.pEnumerator = NULL;
	BSTR tempBSTR = NULL;
	long long tempLL = 0;
	int tempINT = 0;

	hres = q.pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_LogicalDisk"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &q.pEnumerator);
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

		hres = q.pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		tn.push_back(bstr_to_str(vtProp.bstrVal));

		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
		tempBSTR = vtProp.bstrVal;
		tempLL = _wtoi64(tempBSTR);
		int tempINT = (tempLL / 1024 / 1024 / 1024);
		ts.push_back(tempINT);

		VariantClear(&vtProp);
		tempBSTR = NULL;
		tempLL = 0;
		tempINT = 0;

		hres = q.pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
		tempBSTR = vtProp.bstrVal;
		tempLL = _wtoi64(tempBSTR);
		tempINT = tempLL / 1024 / 1024 / 1024;
		tsf.push_back(tempINT);

		VariantClear(&vtProp);
		tempBSTR = NULL;

		q.pclsObj->Release();
		q.pclsObj = NULL;
	}

	*size = ts;
	*sizeFREE = tsf;
	*name = tn;

	return true;
}

bool DISK::generateCROWres() {
	diskARRAY.clear();
	if (getDISKdata(&_diskSIZE, &_diskFREEsize, &_diskNAME)) {
		for (int i = 0; i < _diskSIZE.size(); i++) {
			crow::json::wvalue diskRES = { {"name", _diskNAME[i]}, {"size", _diskSIZE[i]}, {"sizeFree", _diskFREEsize[i]} };
			diskARRAY.push_back(diskRES);
		}
		return true;
	}
	return false;
}

DISK disk = DISK();