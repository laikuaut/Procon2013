#pragma once

#include"Procon2013\Core\Core.h"
#include"Quinary.h"
#include"StringMatching.h"

namespace pro{

class QuinaryEncode
{
private:

	StringMatching stringMatching;

	int max_num;
	vector<int> codes;
	vector<int> dices;

	void fileRead(string name);
	void setDice();

public:
	QuinaryEncode(void);
	~QuinaryEncode(void);

	void init(string name);
	void output();

};

}