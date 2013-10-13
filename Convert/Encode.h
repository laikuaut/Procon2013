#pragma once

#include"Procon2013/Core/Core.h"
#include"CodeEncode.h"
#include"DiceCodeEncode.h"
#include"DiceEncode.h"
#include"SenaryEncode.h"

namespace pro{
	
// 文字列->サイコロ

class Encode
{
public:

	CodeEncode codeEncode;
	DiceCodeEncode diceCodeEncode;
	SenaryEncode senaryEncode;
	DiceEncode diceEncode;

public:
	Encode(void);
	~Encode(void);

	void init(string name);

	void run();

};

}