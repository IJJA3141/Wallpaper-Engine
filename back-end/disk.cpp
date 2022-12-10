#include <WbemIdl.h>
#include <comdef.h>
#include <vector>


#include "WMI.h"

#include "disk.h"
#include "crow/json.h"



DISK::DISK() {
}

DISK::~DISK() {
	delete& mSd;
	delete& mFsd;
	delete& mNd;
	delete this;
}

std::vector<crow::json::wvalue> DISK::get() {
	std::vector<crow::json::wvalue> diskArray_wvalue;

	if (q.disk(&mSd, &mFsd, &mNd)) {
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