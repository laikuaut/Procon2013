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
	void setStr(vector<int> codes);
	char strTable(int code);

	vector<int> runlength();

public:
	CodeDecode(void);
	~CodeDecode(void);

	void init(string name);
	void output();

	void initRunlength(string name);
	void outputRunlength();

};

}