#include <WbemIdl.h>
#include <comdef.h>
#include <vector>

#include "WMI.h"

#include "disk.h"
#include "crow/json.h"

std::string bstr_to_str(BSTR source) {
	_bstr_t wrapped_bstr = _bstr_t(source);
	int length = wrapped_bstr.length();
	char* char_array = new char[length];
	strcpy_s(char_array, static_cast<rsize_t>(length) + 1, wrapped_bstr);
	return char_array;
}

DISK::DISK() {
}

DISK::~DISK() {
	delete& mSd;
	delete& mFsd;
	delete& mNd;
	delete this;
}

bool DISK::get_disk_data(std::vector<int>* pSo, std::vector<int>* pFso, std::vector<std::string>* pNo) {
	HRESULT hres;
	ULONG uReturn = 0;
	VARIANT vtProp;
	q.pEnumerator = NULL;
	BSTR tempBSTR = NULL;
	long long tempLL = 0;
	int tempINT = 0;

	hres = q.pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_LogicalDisk"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &q.pEnumerator);
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

		hres = q.pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		pNo->push_back(bstr_to_str(vtProp.bstrVal));

		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"Size", 0, &vtProp, 0, 0);
		tempBSTR = vtProp.bstrVal;
		tempLL = _wtoi64(tempBSTR);
		int tempINT = (tempLL / 1024 / 1024 / 1024);
		pSo->push_back(tempINT);

		VariantClear(&vtProp);
		tempBSTR = NULL;
		tempLL = 0;
		tempINT = 0;

		hres = q.pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
		tempBSTR = vtProp.bstrVal;
		tempLL = _wtoi64(tempBSTR);
		tempINT = tempLL / 1024 / 1024 / 1024;
		pFso->push_back(tempINT);

		VariantClear(&vtProp);
		tempBSTR = NULL;

		q.pclsObj->Release();
		q.pclsObj = NULL;
	}
	q.pEnumerator = NULL;
	return true;
}

std::vector<crow::json::wvalue> DISK::get() {
	std::vector<crow::json::wvalue> diskArray_wvalue;
	if (get_disk_data(&mSd, &mFsd, &mNd)) {
		for (int i = 0; i < mSd.size(); i++) {
			diskArray_wvalue.push_back({ {"name", mNd[i]}, {"size", mSd[i]}, {"sizeFree", mFsd[i]} });
		}
	}
	else {
		diskArray_wvalue.push_back({ { "name", "-" }, { "size", "-"}, {"sizeFree", "-"} });
	}
	mNd.clear();
	mSd.clear();
	mFsd.clear();
	return diskArray_wvalue;
}

DISK disk = DISK();