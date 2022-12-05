#pragma once
class PEN
{
public:
	bool set(std::string s);
	crow::json::wvalue::list get();
private:
	void read(std::vector<std::string>* v);
};

extern PEN pen;