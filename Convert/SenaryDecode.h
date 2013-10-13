#pragma once

#include"Procon2013\Core\Core.h"
#include"Senary.h"

namespace pro{

class SenaryDecode
{
private:

	vector<int> dices;

	void fileRead(string name);

public:
	SenaryDecode(void);
	~SenaryDecode(void);

	void init(string name);
	void output();

};

}