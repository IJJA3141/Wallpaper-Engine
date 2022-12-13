#pragma once
class RAM
{
public:
	RAM();
	~RAM();

	std::vector<crow::json::wvalue> getConst();
	std::vector<crow::json::wvalue> get();

private:
	ULONGLONG mMi;
};

extern RAM ram;