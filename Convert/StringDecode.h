#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class StringDecode
{
private:

	static const int STRMAX = 4000;
	static const int ENDBINARY = -1;

	char str[STRMAX];
	char binary[STRMAX*8];
	char dice[STRMAX*8+1];

	

public:
	StringDecode(void);
	~StringDecode(void);

	void init();

	void slvDice(string name);


};

}