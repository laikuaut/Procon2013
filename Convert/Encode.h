#pragma once

#include"Procon2013/Core/Core.h"
#include"CodeEncode.h"
#include"DiceCodeEncode.h"
#include"DiceEncode.h"
#include"SenaryEncode.h"

namespace pro{
	
// ï∂éöóÒ->ÉTÉCÉRÉç

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