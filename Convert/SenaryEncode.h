#pragma once

#include"Procon2013\Core\Core.h"
#include"Senary.h"

namespace pro{

class SenaryEncode
{
private:

	vector<int> codes;
	vector<int> dices;

	void fileRead(string name);
	void setDice();

	//vector<int> runlength();

public:
	SenaryEncode(void);
	~SenaryEncode(void);

	void init(string name);
	void output();

};

}