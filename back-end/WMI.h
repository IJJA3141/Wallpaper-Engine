#include <WbemIdl.h>
#pragma once

class WMIQuery
{
public:
	WMIQuery();
	~WMIQuery();

	IWbemLocator* pLoc;
	IWbemServices* pSvc;
	IEnumWbemClassObject* pEnumerator;
	IWbemClassObject* pclsObj;
};

extern WMIQuery q;