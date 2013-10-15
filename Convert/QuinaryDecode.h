#pragma once

#include"Procon2013\Core\Core.h"
#include"Quinary.h"

namespace pro{

class QuinaryDecode
{
private:

	int max;
	vector<int> dices;

	void fileRead(string name);

public:
	QuinaryDecode(void);
	~QuinaryDecode(void);

	void init(string name);
	void output();

};

}