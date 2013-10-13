#pragma once

#include"Procon2013\Core\Core.h"
#include"Senary.h"

namespace pro{

class SenaryEncode
{
private:

	vector<int> codes;

	void fileRead(string name);


public:
	SenaryEncode(void);
	~SenaryEncode(void);

	void init(string name);
	void output();

};

}