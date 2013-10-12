#pragma once

#include"Procon2013/Core/Core.h"
#include"DiceDecode.h"
#include"DiceCodeDecode.h"
#include"CodeDecode.h"

namespace pro{

// ƒTƒCƒRƒ->•¶Žš—ñ

class Decode
{
private:

	DiceDecode diceDecode;
	//DiceCodeDecode diceCodeDecode;
	//CodeDecode codeDecode;

public:
	Decode(void);
	~Decode(void);

	void init();
	void run();

};

}