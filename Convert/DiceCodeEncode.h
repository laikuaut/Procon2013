#pragma once

#include"Procon2013\Core\Core.h"
#include"StringMatching.h"
#include"CharPositions.h"
#include"Quinary.h"
#include"StringPositions.h"

namespace pro{

class DiceCodeEncode
{
private:

	static const int STRMAX = 4000;
	static const int ENDBINARY = -1;

	//char str[STRMAX];
	vector<int> codes;
	char binary[STRMAX*8];
	int dice[STRMAX*8+1];

	void fileRead(string name);
	
	void loadDice();

	vector<int> runlength();

public:
	DiceCodeEncode(void);
	~DiceCodeEncode(void);

	void init(string name);

	void output();
	void outputRunlength();

};

}