#pragma once

#include"Procon2013\Core\Core.h"



namespace pro{

class CodeDecode
{
public:

	vector<char> str;
	vector<int> codes;

	void fileRead(string name);
	void setStr();
	char strTable(int code);

public:
	CodeDecode(void);
	~CodeDecode(void);

	void init(string name);
	void output();

};

}