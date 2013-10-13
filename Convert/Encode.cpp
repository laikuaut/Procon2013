#include "Encode.h"

#include<iostream>

using namespace std;

namespace pro{

Encode::Encode(void)
{
}


Encode::~Encode(void)
{
}

void Encode::init(string name){
	codeEncode.init(name);
}

void Encode::run(){
	// CodeEncode
	//codeEncode.output();
	codeEncode.outputRunlength();

	// SenaryEncode
	senaryEncode.init("CodeEncode.txt");
	senaryEncode.output();

	// DiceCodeEncode
	//diceCodeEncode.init("CodeEncode.txt");
	//diceCodeEncode.outputRunlength();

	diceEncode.init("DiceEncode.txt");
	diceEncode.drawing();
}

}