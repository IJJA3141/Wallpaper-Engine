#include <WbemIdl.h>
#include <vector>
#include <string>
#pragma once

class WMIQuery
{
public:
	WMIQuery();
	~WMIQuery();

	IWbemServices* pSvc;

	bool cpu(__int64* pIl, __int64* pIt);
	bool disk(std::vector<__int64>* pIVfs, std::vector<__int64>* pIVs, std::vector<std::string>* pSVn);

private:
	BSTR mStrQuery;
	BSTR mCpuStrQueryLanguage;
	BSTR mDiskStrQueryLanguage;

	std::string _str_t(BSTR source);
};

extern WMIQuery q;