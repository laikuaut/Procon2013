#pragma once

#include"Procon2013\Core\Core.h"
#include"Quinary.h"

namespace pro{

class DiceCodeDecode
{
private:

	static const int STRMAX = 4000;
	static const int ENDBINARY = -1;

	char str[STRMAX];
	vector<int> codes;
	char binary[STRMAX*8];
	int dice[STRMAX*8+1];

	void fileRead(string name);
	void slvDice();
	void slvDice(vector<int> dices);

	vector<int> runlength();

public:
	DiceCodeDecode(void);
	~DiceCodeDecode(void);

	void init(string name);
	void initRunlength(string name);

	void output();
	void outputRunlength();

};

}