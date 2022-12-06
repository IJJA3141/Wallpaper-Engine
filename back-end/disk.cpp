#include <WbemIdl.h>
#include <comdef.h>
#include <vector>
#include <codecvt>

#include "WMI.h"

#include "disk.h"
#include "crow/json.h"

std::string bstr_to_str(BSTR source) {
	std::wstring res;
	res = _bstr_t(source);

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(res);
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
	VARIANT vtProp = VARIANT();
	q.pEnumerator = NULL;

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
		pSo->push_back((_wtoi64(vtProp.bstrVal) / 1024 / 1024 / 1024));

		VariantClear(&vtProp);

		hres = q.pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
		pFso->push_back((_wtoi64(vtProp.bstrVal) / 1024 / 1024 / 1024));

		VariantClear(&vtProp);

		q.pclsObj->Release();
		q.pclsObj = NULL;
	}

	CoUninitialize();
	q.pLoc->Release();
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