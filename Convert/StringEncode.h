#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class StringEncode
{
private:

	static const int STRMAX = 4000;
	static const int ENDBINARY = -1;

	char str[STRMAX];
	char binary[STRMAX*8];
	char dice[STRMAX*8+1];

public:
	StringEncode(void);
	~StringEncode(void);


	void init();

	void loadDice(string name);

};

}