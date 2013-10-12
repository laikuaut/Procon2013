#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class CodeEncode
{
private:

	vector<char> str;
	vector<int> codes;

	void fileRead(string name);
	void setCode();
	int codeTable(char c);

public:
	CodeEncode(void);
	~CodeEncode(void);

	void init(string name);
	void output();

};

}
