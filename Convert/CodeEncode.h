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

	static int const _runlength = 0;
	vector<int> runlength();

public:
	CodeEncode(void);
	~CodeEncode(void);

	void init(string name);
	void output();

	void outputRunlength();



};

}
